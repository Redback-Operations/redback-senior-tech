"""This module contains the classes used to Build and Train TF Models"""

import os
from tensorflow.keras import Sequential
from tensorflow.keras.layers import (
    InputLayer,
    Conv1D,
    MaxPooling1D,
    Flatten,
    Dense,
    Dropout,
    GRU,
)
from tensorflow.keras.callbacks import ReduceLROnPlateau, EarlyStopping, TensorBoard
from tensorflow import keras


class ModelBuilder:
    """Builds different neural network models."""

    def __init__(self, input_shape, n_labels):
        self.input_shape = input_shape
        self.n_labels = n_labels

    def build_cnn_model(self):
        """Builds a CNN model."""
        model = Sequential(
            [
                InputLayer(shape=self.input_shape),
                Conv1D(64, kernel_size=3, activation="relu", padding="same"),
                MaxPooling1D(pool_size=2),
                Conv1D(128, kernel_size=3, activation="relu", padding="same"),
                MaxPooling1D(pool_size=2),
                Flatten(),
                Dense(
                    256,
                    activation="relu",
                    kernel_regularizer=keras.regularizers.l2(0.001),
                ),
                Dropout(0.5),
                Dense(
                    128,
                    activation="relu",
                    kernel_regularizer=keras.regularizers.l2(0.001),
                ),
                Dense(self.n_labels, activation="softmax"),
            ]
        )
        return model

    def build_gru_model(self):
        """Builds a GRU model."""
        model = Sequential(
            [
                InputLayer(shape=self.input_shape),
                GRU(128, return_sequences=True),
                GRU(128),
                Dense(
                    128,
                    activation="relu",
                    kernel_regularizer=keras.regularizers.l2(0.001),
                ),
                Dropout(0.5),
                Dense(
                    64,
                    activation="relu",
                    kernel_regularizer=keras.regularizers.l2(0.001),
                ),
                Dense(self.n_labels, activation="softmax"),
            ]
        )
        return model

    def build_cnn_gru_model(self):
        """Builds a model combining CNN and GRU layers."""
        model = Sequential(
            [
                InputLayer(shape=self.input_shape),
                Conv1D(64, kernel_size=3, activation="relu", padding="same"),
                MaxPooling1D(pool_size=2),
                Conv1D(128, kernel_size=3, activation="relu", padding="same"),
                MaxPooling1D(pool_size=2),
                GRU(128),
                Dense(
                    128,
                    activation="relu",
                    kernel_regularizer=keras.regularizers.l2(0.001),
                ),
                Dropout(0.5),
                Dense(
                    64,
                    activation="relu",
                    kernel_regularizer=keras.regularizers.l2(0.001),
                ),
                Dense(self.n_labels, activation="softmax"),
            ]
        )
        return model

    def build_models(self):
        """Builds and returns a dictionary of models."""
        models = {
            "CNN": self.build_cnn_model(),
            "GRU": self.build_gru_model(),
            "CNN_GRU": self.build_cnn_gru_model(),
        }
        return models


class Trainer:
    """Handles model compilation, training, and evaluation."""

    def __init__(self, model, model_name, log_dir="logs"):
        self.model = model
        self.model_name = model_name
        self.log_dir = log_dir

    def compile_model(self):
        """Compiles the model with specified loss and optimizer."""
        self.model.compile(
            optimizer="adam",
            loss="sparse_categorical_crossentropy",
            metrics=["accuracy"],
        )

    def train_model(
            self,
            x_train,
            y_train,
            x_val,
            y_val,
            epochs=50,
            batch_size=32):
        """Trains the model with specified parameters."""
        # Set up callbacks
        callbacks = [
            ReduceLROnPlateau(
                monitor="val_loss",
                factor=0.1,
                patience=5,
                min_lr=1e-6,
                verbose=1),
            EarlyStopping(
                monitor="val_loss",
                patience=10,
                restore_best_weights=True,
                verbose=1),
            TensorBoard(
                log_dir=os.path.join(
                    self.log_dir,
                    self.model_name)),
        ]

        history = self.model.fit(
            x_train,
            y_train,
            validation_data=(x_val, y_val),
            epochs=epochs,
            batch_size=batch_size,
            callbacks=callbacks,
            verbose=0,
        )  # Suppress output logs

        return history

    def evaluate_model(self, x_test, y_test):
        """Evaluates the model on the test set."""
        test_loss, test_acc = self.model.evaluate(x_test, y_test, verbose=0)
        print(f"Test Loss: {test_loss:.4f}")
        print(f"Test Accuracy: {test_acc:.4f}")
        return test_loss, test_acc

    def predict(self, x_data):
        """Generates predictions for the input samples."""
        return self.model.predict(x_data, verbose=0)

    def save_model(self, folder="models"):
        """Saves the model in the given folder."""
        self.model.save(f'{folder}/{self.model_name.lower()}.keras')
