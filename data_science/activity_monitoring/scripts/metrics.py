"""This module contains the class used to calculate the display different metrics for a model."""

from prettytable import PrettyTable
from sklearn.metrics import (
    accuracy_score,
    precision_score,
    recall_score,
    f1_score,
    classification_report,
)


class Metrics:
    """Class to initialise, store, and calculate performance metrics."""

    def __init__(self):
        """Initialises metrics collection structures."""
        # Initialise the table with field names
        self.metrics_table = PrettyTable()
        self.metrics_table.field_names = [
            "Model",
            "Accuracy",
            "Precision",
            "Recall",
            "F1 Score",
            "Total Training Time (s)",
            "Avg Training Time (s)",
            "Total Testing Time (s)",
        ]

        # Dictionary to store classification reports
        self.class_reports = {}

    def calculate_metrics(
        self,
        model_name,
        y_test,
        y_pred_classes,
        label_to_id,
        training_time,
        testing_time,
        epochs,
    ):
        """Calculates performance metrics and updates internal data structures."""

        # Calculate performance metrics
        acc = accuracy_score(y_test, y_pred_classes)
        precision = precision_score(
            y_test, y_pred_classes, average="weighted", zero_division=0
        )
        recall = recall_score(
            y_test, y_pred_classes, average="weighted", zero_division=0
        )
        f1 = f1_score(
            y_test,
            y_pred_classes,
            average="weighted",
            zero_division=0)

        # Generate classification report
        target_names = list(label_to_id.keys())
        class_report = classification_report(
            y_test, y_pred_classes, target_names=target_names, zero_division=0
        )
        print(f"\nClassification Report for {model_name}:\n")
        print(class_report)

        self.metrics_table.add_row(
            [
                model_name,
                f"{acc:.4f}",
                f"{precision:.4f}",
                f"{recall:.4f}",
                f"{f1:.4f}",
                f"{training_time:.2f}",
                f"{training_time/epochs:.2f}",
                f"{testing_time:.2f}",
            ]
        )

        # Update classification reports
        self.class_reports[model_name] = class_report

    def display_metrics(self):
        """Displays the overall metrics table."""
        print("\nOverall Metrics for All Models:")
        print(self.metrics_table)
