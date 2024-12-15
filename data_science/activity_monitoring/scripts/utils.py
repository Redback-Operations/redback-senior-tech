"""This module contains the functions used to load data,
and plot the accuracy and losses of a model training history.
"""

import os
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split


def load_and_split_data(
        data_dir="data",
        test_size=0.4,
        val_size=0.5,
        random_state=69):
    """Loads and splits data into training, validation, and test sets."""
    # Load data
    data_filename = os.path.join(data_dir, "sequential_data.npy")
    label_ids_filename = os.path.join(data_dir, "label_ids.npy")
    label_to_id_filename = os.path.join(data_dir, "label_to_id.npy")

    data = np.load(data_filename)
    label_ids = np.load(label_ids_filename)
    label_to_id = np.load(label_to_id_filename, allow_pickle=True).item()

    n_labels = len(np.unique(label_ids))

    # Split data into training, validation, and test sets
    x_train, x_temp, y_train, y_temp = train_test_split(
        data, label_ids, test_size=test_size, random_state=random_state
    )

    x_val, x_test, y_val, y_test = train_test_split(
        x_temp, y_temp, test_size=val_size, random_state=random_state
    )

    # Ensure the data is of type float32
    x_train = x_train.astype("float32")
    x_val = x_val.astype("float32")
    x_test = x_test.astype("float32")

    return x_train, x_val, x_test, y_train, y_val, y_test, label_to_id, n_labels


def plot_metric(ax, epochs, train, val, title, ylabel):
    """Helper function to simplify the code"""
    ax.plot(epochs, train, "b", label="Training")
    ax.plot(epochs, val, "r", linestyle="--", label="Validation")
    ax.set_title(title)
    ax.set_xlabel("Epochs")
    ax.set_ylabel(ylabel)
    ax.legend()
    ax.grid(True)
    ax.set_xticks(epochs[::5])


def plot_histories(histories, model_names, figsize=(12, 5)):
    """Plots the training and validation accuracy and loss for multiple models.

    Args:
        histories (list): List of Keras History objects.
        model_names (list): List of model names corresponding to the histories.
        figsize (tuple, optional): Figure size. Defaults to (15, 10).
    """

    num_models = len(histories)
    _, axes = plt.subplots(2, num_models, figsize=figsize)

    for i, (history, model_name) in enumerate(zip(histories, model_names)):
        epochs = range(1, len(history.history["accuracy"]) + 1)

        plot_metric(
            axes[0, i],
            epochs,
            history.history["accuracy"],
            history.history["val_accuracy"],
            f"{model_name} - Accuracy",
            "Accuracy",
        )

        plot_metric(
            axes[1, i],
            epochs,
            history.history["loss"],
            history.history["val_loss"],
            f"{model_name} - Loss",
            "Loss",
        )

    plt.tight_layout()
    plt.show()
