# dummy_data_science.py

import pandas as pd
import numpy as np
import sqlite3
import os

# 1. Sensitive Data Exposure (OWASP A3)
# Storing sensitive data in plain text (e.g., hard-coded credentials)
db_password = "password123"  # Sensitive information hard-coded

# 2. Injection (OWASP A1)
# Using string formatting in SQL queries (leads to SQL Injection)
user_input = "1 OR 1=1"  # Example of a malicious input
query = f"SELECT * FROM users WHERE user_id = {user_input};"

# 3. Cross-Site Scripting (XSS) (OWASP A7)
# Using untrusted input in HTML output (relevant for data science web apps)
def generate_html(user_name):
    return f"<html><body>Hello, {user_name}</body></html>"

# 4. Insecure Deserialization (OWASP A8)
# Using `eval()` to deserialize data
serialized_data = "{'key': 'value'}"
data = eval(serialized_data)  # Insecure deserialization

# 5. Security Misconfiguration (OWASP A6)
# Debug mode is enabled in production (common in Flask or Django apps)
DEBUG = True

# 6. Insecure Direct Object References (IDOR) (OWASP A4)
# Direct access to user files without validation
def read_user_file(filename):
    with open(filename, 'r') as file:
        return file.read()

# 7. Cross-Site Request Forgery (CSRF) (OWASP A5)
# Simulating a data download function without CSRF protection
def download_data():
    user_token = os.getenv("USER_TOKEN")
    if user_token:
        return pd.read_csv("data.csv")
    return None

# 8. Using Components with Known Vulnerabilities (OWASP A9)
# Using outdated libraries (e.g., an outdated version of pandas)
df = pd.DataFrame(np.random.randn(100, 4), columns=list('ABCD'))

# 9. Insufficient Logging & Monitoring (OWASP A10)
# Lack of logging for important actions
def perform_critical_action(user_id):
    # Critical action performed without logging
    print(f"Performing critical action for user {user_id}")

# 10. Broken Access Control (OWASP A2)
# Function allows unauthorized access
def get_admin_data(user_role):
    if user_role == "user":  # Insufficient access control
        return "Admin data"
    return None

# Data processing example (relevant to data science students)
def process_data(df):
    # Assume df is a DataFrame
    df['E'] = df['A'] + df['B']
    return df

# Entry point of the script
if __name__ == "__main__":
    # Process data without validation
    df = pd.read_csv("data.csv")  # Assume data.csv is present
    result = process_data(df)
    print(result)
