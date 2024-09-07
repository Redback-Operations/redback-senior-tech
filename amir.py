import subprocess
import json
import os
import re
import sys
import argparse
import ast
import logging
from typing import List, Dict, Any
import bandit
from bandit.core import manager as bandit_manager

logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

class AdvancedVulnerabilityScanner:
    def __init__(self, file_path: str):
        self.file_path = file_path
        self.vulnerabilities: List[Dict[str, Any]] = []
        self.code_lines: List[str] = []
        self.ast_tree: ast.AST = None
        self.vulnerability_db = self.load_vulnerability_db()

    def load_vulnerability_db(self):
        # Mock vulnerability database
        return {
            'requests': {'2.25.0': ['CVE-2021-12345']},
            'django': {'2.2.0': ['CVE-2021-67890']}
        }

    def parse_file(self):
        logging.info(f"Parsing file: {self.file_path}")
        with open(self.file_path, 'r', encoding='utf-8') as file:
            self.code_lines = file.readlines()
            self.ast_tree = ast.parse(''.join(self.code_lines))
        logging.info(f"File parsed. Total lines: {len(self.code_lines)}")

    def run_bandit(self):
        b_mgr = bandit_manager.BanditManager(bandit.config.BanditConfig(), agg_type='file')
        b_mgr.discover_files([self.file_path])
        b_mgr.run_tests()
        return b_mgr.get_issue_list()

    def add_vulnerability(self, category: str, description: str, line_number: int, severity: str, confidence: str):
        self.vulnerabilities.append({
            'category': category,
            'description': description,
            'line_number': line_number,
            'severity': severity,
            'confidence': confidence
        })
        logging.info(f"Vulnerability added: {category} at line {line_number}")

    def check_hardcoded_secrets(self):
        pattern = re.compile(r'(?i)(password|secret|key|token)\s*=\s*["\'][^"\']+["\']')
        for i, line in enumerate(self.code_lines):
            if match := pattern.search(line):
                self.add_vulnerability('Hardcoded Secret', f"Potential hardcoded secret: {match.group(0)}", i+1, 'HIGH', 'MEDIUM')

    def check_sql_injection(self):
        sql_patterns = [
            r'(?i)(?:execute|cursor\.execute)\s*\(.*?%s.*?\)',
            r'(?i)(?:execute|cursor\.execute)\s*\(.*?f["\'].*?\{.*?\}.*?["\'].*?\)'
        ]
        for i, line in enumerate(self.code_lines):
            for pattern in sql_patterns:
                if re.search(pattern, line):
                    self.add_vulnerability('SQL Injection', f"Potential SQL injection: {line.strip()}", i+1, 'HIGH', 'HIGH')

    def check_xss_vulnerabilities(self):
        xss_patterns = [
            r'(?i)render_template_string\s*\(',
            r'(?i)jinja2\.Template\s*\(',
            r'(?i)flask\.render_template_string\s*\(',
            r'(?i)response\.write\(.+\)',
            r'(?i)print\(.+\)'
        ]
        for i, line in enumerate(self.code_lines):
            for pattern in xss_patterns:
                if re.search(pattern, line):
                    self.add_vulnerability('Cross-Site Scripting (XSS)', f"Potential XSS vulnerability: {line.strip()}", i+1, 'HIGH', 'MEDIUM')

    def check_vulnerable_components(self):
        import_pattern = r'(?:from|import)\s+([\w\.]*)(?:\s+import)?'
        for i, line in enumerate(self.code_lines):
            if match := re.search(import_pattern, line):
                lib = match.group(1).split('.')[0]
                if lib in self.vulnerability_db:
                    self.add_vulnerability('Vulnerable Component', f"Potentially vulnerable library: {lib}", i+1, 'HIGH', 'MEDIUM')

    def perform_taint_analysis(self):
        logging.info("Performing taint analysis")
        tainted_vars = set()
        for node in ast.walk(self.ast_tree):
            if isinstance(node, ast.Assign):
                for target in node.targets:
                    if isinstance(target, ast.Name):
                        if isinstance(node.value, ast.Call) and isinstance(node.value.func, ast.Name) and node.value.func.id in ['input', 'request.form.get']:
                            tainted_vars.add(target.id)
            elif isinstance(node, ast.Name) and node.id in tainted_vars:
                if isinstance(node.ctx, ast.Load):
                    self.add_vulnerability('Tainted Variable Usage', f"Potentially tainted variable used: {node.id}", getattr(node, 'lineno', 0), 'MEDIUM', 'MEDIUM')

    def check_ssrf_vulnerabilities(self):
        ssrf_patterns = [
            r'(?i)requests\.get\s*\(',
            r'(?i)urllib\.request\.urlopen\s*\(',
            r'(?i)http\.client\.HTTPConnection\s*\('
        ]
        for i, line in enumerate(self.code_lines):
            for pattern in ssrf_patterns:
                if re.search(pattern, line):
                    self.add_vulnerability('SSRF', f"Potential SSRF vulnerability: {line.strip()}", i+1, 'HIGH', 'MEDIUM')

    def check_logging_and_monitoring(self):
        logging_patterns = [
            r'(?i)logging\.',
            r'(?i)print\s*\(',
            r'(?i)sys\.stdout\.write\s*\('
        ]
        has_logging = any(re.search(pattern, line) for pattern in logging_patterns for line in self.code_lines)
        if not has_logging:
            self.add_vulnerability('Insufficient Logging', "No logging statements found in the file", 0, 'MEDIUM', 'HIGH')

    def check_idor(self):
        idor_patterns = [
            r'(?i)request\.args\.get\s*\([\'"].*role.*[\'"]\)',
            r'(?i)if\s+.*role\s*==\s*[\'"]admin[\'"]'
        ]
        for i, line in enumerate(self.code_lines):
            for pattern in idor_patterns:
                if re.search(pattern, line):
                    self.add_vulnerability('Insecure Direct Object Reference', f"Potential IDOR vulnerability: {line.strip()}", i+1, 'HIGH', 'MEDIUM')

    def check_sensitive_data_exposure(self):
        sensitive_patterns = [
            r'(?i)os\.environ',
            r'(?i)send_file\s*\(',
            r'(?i)open\s*\('
        ]
        for i, line in enumerate(self.code_lines):
            for pattern in sensitive_patterns:
                if re.search(pattern, line):
                    self.add_vulnerability('Sensitive Data Exposure', f"Potential sensitive data exposure: {line.strip()}", i+1, 'HIGH', 'MEDIUM')

    def check_insecure_deserialization(self):
        deser_patterns = [
            r'(?i)pickle\.loads\s*\(',
            r'(?i)yaml\.load\s*\(',
            r'(?i)json\.loads\s*\('
        ]
        for i, line in enumerate(self.code_lines):
            for pattern in deser_patterns:
                if re.search(pattern, line):
                    self.add_vulnerability('Insecure Deserialization', f"Potential insecure deserialization: {line.strip()}", i+1, 'HIGH', 'HIGH')

    def analyze(self):
        try:
            self.parse_file()
            self.check_sql_injection()
            self.check_xss_vulnerabilities()
            self.check_hardcoded_secrets()
            self.check_vulnerable_components()
            self.perform_taint_analysis()
            self.check_ssrf_vulnerabilities()
            self.check_logging_and_monitoring()
            self.check_idor()
            self.check_sensitive_data_exposure()
            self.check_insecure_deserialization()

            dependency_check_results = run_dependency_check(os.path.dirname(self.file_path))
            for vuln in dependency_check_results:
                self.add_vulnerability("Dependency Vulnerability", f"{vuln['name']}: {vuln['description']}", 0, vuln['severity'], "HIGH")

            bandit_issues = self.run_bandit()
            for issue in bandit_issues:
                self.add_vulnerability(f"Bandit: {issue.test_id}", issue.text, issue.lineno, issue.severity, issue.confidence)

            logging.info("Analysis completed successfully")
        except Exception as e:
            logging.error(f"An error occurred during analysis: {str(e)}")

    def generate_report(self):
        print(f"Advanced Vulnerability Scan Results for {self.file_path}:")
        print(f"Total lines of code: {len(self.code_lines)}")
        print("\nDetected Vulnerabilities:")
        if not self.vulnerabilities:
            print("No vulnerabilities detected.")
        else:
            for vuln in sorted(self.vulnerabilities, key=lambda x: x['severity'], reverse=True):
                print(f"- {vuln['category']}: {vuln['description']}")
                print(f"  Severity: {vuln['severity']}, Confidence: {vuln['confidence']}")
                if vuln['line_number'] > 0:
                    print(f"  Location: Line {vuln['line_number']}")
                    print(f"  Code: {self.code_lines[vuln['line_number']-1].strip()}")
                print()

def scan_file_or_directory(path):
    if os.path.isfile(path):
        scanner = AdvancedVulnerabilityScanner(path)
        scanner.analyze()
        scanner.generate_report()
    elif os.path.isdir(path):
        for root, dirs, files in os.walk(path):
            for file in files:
                if file.endswith('.py'):
                    file_path = os.path.join(root, file)
                    print(f"\nScanning: {file_path}")
                    scanner = AdvancedVulnerabilityScanner(file_path)
                    scanner.analyze()
                    scanner.generate_report()
    else:
        print(f"Error: {path} is not a valid file or directory.")

def run_dependency_check(project_path):
    cmd = f"dependency-check --scan {project_path} --format JSON --out dependency-check-report.json"
    try:
        subprocess.run(cmd, shell=True, check=True)
        
        with open('dependency-check-report.json', 'r') as f:
            report = json.load(f)
        
        vulnerabilities = []
        for dependency in report.get('dependencies', []):
            for vulnerability in dependency.get('vulnerabilities', []):
                vulnerabilities.append({
                    'description': vulnerability.get('description', ''),
                    'severity': vulnerability.get('severity', 'UNKNOWN'),
                    'name': vulnerability.get('name', '')
                })
        
        return vulnerabilities
    except subprocess.CalledProcessError:
        logging.error("Dependency-Check failed to run. Ensure it's properly installed and in your PATH.")
        return []
    except FileNotFoundError:
        logging.error("Dependency-Check report not found. Ensure Dependency-Check is running correctly.")
        return []

def main():
    parser = argparse.ArgumentParser(description="Advanced Vulnerability Scanner")
    parser.add_argument("path", help="Path to the Python file or directory to scan")
    args = parser.parse_args()

    scan_file_or_directory(args.path)

if __name__ == "__main__":
    main()