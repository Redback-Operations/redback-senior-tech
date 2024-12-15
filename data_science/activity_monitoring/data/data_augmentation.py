"""This module contains the class used to perform Data Augmentation on datasets."""

import numpy as np
import matplotlib.pyplot as plt


class DataAugmentation:
    """
    A class for performing various data augmentation techniques on accelerometer
    and gyroscope data.
    """

    def __init__(self, data, thres=None):
        """Initialize the class with file path and optional configuration.

        Args:
            data (numpy.ndarray): Numpy array of accelerometer and gyroscope data.
            thres (dict): Optional configuration dictionary for augmentation parameters.
        """
        self.data = data

        if thres:
            self.thres = thres
        else:
            self.thres = {
                "noise_level": 0.09,
                "scaling_factor": 1.2,
                "shift_range": 10,
                "cropping_ratio": 0.8,
                "magnitude_warping_sigma": 0.2,
                "cutout_proportion": 0.1,
            }

        # Dictionary to map augmentation names to functions
        self.augmentation_methods = {
            "add_noise": self.add_noise,
            "scaling": self.scaling,
            "time_shift": self.time_shift,
            "flipping": self.flipping,
            "random_cropping": self.random_cropping,
            "magnitude_warping": self.magnitude_warping,
            "cutout": self.cutout,
        }

    def add_noise(self):
        """Add random noise (Jittering) to the data."""
        noise_level = self.thres["noise_level"]
        noise = noise_level * np.random.randn(*self.data.shape)
        return self.data + noise

    def scaling(self):
        """Scale the data by a random factor."""
        scaling_factor = np.random.uniform(1, self.thres["scaling_factor"])
        return self.data * scaling_factor

    def time_shift(self):
        """Shift the data along the time axis."""
        shift_range = self.thres["shift_range"]
        shift = np.random.randint(-shift_range, shift_range)
        return np.roll(self.data, shift, axis=0)

    def flipping(self):
        """Flip the data along the time axis (axis inversion)."""
        return np.flip(self.data, axis=0)

    def random_cropping(self):
        """Randomly crop the data (Window Cropping)."""
        cropping_ratio = self.thres["cropping_ratio"]
        length = self.data.shape[0]
        crop_length = int(length * cropping_ratio)
        start = np.random.randint(0, length - crop_length)
        return self.data[start: start + crop_length]

    def magnitude_warping(self):
        """Warp the magnitude of the data."""
        sigma = self.thres["magnitude_warping_sigma"]
        factor = np.random.normal(
            loc=1.0, scale=sigma, size=(
                self.data.shape[0], 1))
        return self.data * factor

    def cutout(self):
        """Apply cutout/masking to the data."""
        cutout_proportion = self.thres["cutout_proportion"]
        cutout_length = int(self.data.shape[0] * cutout_proportion)
        start = np.random.randint(0, self.data.shape[0] - cutout_length)
        masked_data = self.data.copy()
        masked_data[start: start + cutout_length] = 0
        return masked_data

    def augment_data(self, augmentations):
        """Apply a list of augmentations to the given data.

        Args:
            augmentations (list): List of augmentation techniques to be applied.

        Returns:
            list: List of augmented data.

        Raises:
            ValueError: If the augmentation is not recognized.
        """
        augmented_data_list = []

        for augment_technique in augmentations:
            func = self.augmentation_methods.get(augment_technique, None)

            if func is None:
                raise ValueError(
                    f"Augmentation '{augment_technique}' not recognized.")

            augmented_data_list.append(func())

        return augmented_data_list

    def plot_data(self, original, augmented, aug_name, figsize=(12, 6)):
        """Plot original and augmented data for comparison."""
        plt.figure(figsize=figsize)

        data_axes = [
            "Accel X",
            "Accel Y",
            "Accel Z",
            "Gyro X",
            "Gyro Y",
            "Gyro Z"]

        for i, axes_name in enumerate(data_axes):
            plt.subplot(2, 3, i + 1)
            plt.plot(original[:, i], color="#008080", label="Original")
            plt.plot(augmented[:, i], color="#FF6347", label="Augmented")
            plt.title(axes_name)
            plt.legend()

        plt.suptitle(f"Augmentation: {aug_name}")
        plt.tight_layout()
        plt.show()
