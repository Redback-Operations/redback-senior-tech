import joblib
import numpy as np
from sleep_metrics import SleepMetrics

class SleepMetricsExtended(SleepMetrics):
    """
    A class that extends SleepMetrics to include model prediction based on sleep metrics.
    """

    def __init__(self, csv_file, model_file):
        """
        Initializes the extended class with CSV data and a pre-trained model.

        Args:
            csv_file (str): Path to the CSV file with sleep stage data.
            model_file (str): Path to the pre-trained model file (pkl).
        """
        super().__init__(csv_file)
        self.model = joblib.load(model_file)

    def prepare_input_data(self, gender, age, bmi):
        """
        Rearranges the calculated sleep metrics to match the model's input format.

        Args:
            gender (int): Gender (0 for female, 1 for male).
            age (int): Age of the individual.
            bmi (float): BMI of the individual.

        Returns:
            tuple: (sleep metrics, np.array of rearranged input data for the model)
        """
        # Run all metrics
        sleep_latency, sleep_duration, sleep_to_rem_latency, norem1, \
            norem2, norem3, rem, arousal_index = self.run_all_metrics()

        # Prepare input data in the required order
        input_data = [
            gender,  # gender (0 or 1)
            age,  # age
            sleep_to_rem_latency,  # Latency start sleep to REM [min]
            arousal_index,  # Arousal index
            norem1,  # NoREM1%
            norem2,  # NoREM2%
            norem3,  # NoREM3%
            rem,  # REM%
            sleep_duration,  # sleep time
            sleep_latency,  # sleep latency
            bmi  # bmi
        ]
        
        # Return both the sleep metrics and input data for the model
        sleep_metrics = [
            sleep_latency, sleep_duration, sleep_to_rem_latency,
            norem1, norem2, norem3, rem, arousal_index
        ]

        return sleep_metrics, np.array(input_data).reshape(1, -1)

    def predict_sleep_disorder(self, gender, age, bmi):
        """
        Makes a prediction on sleep disorder using the pre-trained model.

        Args:
            gender (int): Gender (0 for female, 1 for male).
            age (int): Age of the individual.
            bmi (float): BMI of the individual.

        Returns:
            tuple: (Prediction result (0 means healthy, 1 means disorder), sleep metrics).
        """
        # Get metrics and input data
        sleep_metrics, input_data = self.prepare_input_data(gender, age, bmi)

        # Make prediction
        prediction = self.model.predict(input_data)[0]  # Get the first value from the prediction array

        # Return both the prediction and the calculated sleep metrics
        return int(prediction), sleep_metrics 
