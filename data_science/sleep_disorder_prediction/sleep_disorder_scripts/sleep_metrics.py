import pandas as pd

class SleepMetrics:
    """
    A class to compute sleep metrics from sleep stage data.

    Attributes:
        data (pd.DataFrame): DataFrame containing the sleep data.
    """

    def __init__(self, csv_file):
        """
        Initializes the class with the CSV file containing sleep data.

        Args:
            csv_file (str): Path to the CSV file with sleep stage data.
        """
        self.data = pd.read_csv(csv_file)

    def calculate_sleep_latency(self):
        """
        Computes the sleep latency in minutes.

        Returns:
            int: Sleep latency in minutes.
        """
        first_occurrence_index = self.data[
            self.data['Class'] == 6
        ].index.min()
        temp_index = None

        for index, value in enumerate(self.data['Class']):
            if value in [1, 2, 3, 4] and temp_index is None:
                temp_index = index
                break
            if value == 6:
                temp_index = None

        segment_difference = temp_index - first_occurrence_index
        time_difference_seconds = segment_difference * 30
        return time_difference_seconds // 60

    def calculate_sleep_duration(self):
        """
        Computes the total sleep duration in minutes.

        Returns:
            int: Total sleep duration in minutes.
        """
        total_time = 0
        index = 0

        while index < len(self.data['Class']):
            start_index = None
            end_index = None

            if self.data['Class'][index] in [1, 2, 3, 4, 5]:
                start_index = index
                while index < len(self.data['Class']) and \
                        self.data['Class'][index] in [1, 2, 3, 5]:
                    index += 1
                end_index = index - 1

                if start_index is not None and end_index >= 0:
                    segment_diff = end_index - start_index + 1
                    total_time += segment_diff * 30

            index += 1
        return total_time // 60

    def calculate_sleep_to_rem_latency(self):
        """
        Computes the time to first REM sleep in minutes.

        Returns:
            int: Time to first REM sleep in minutes.
        """
        first_nrem_index = self.data[self.data['Class'].isin(
            [1, 2, 3, 4])].index.min()
        first_rem_index = self.data[self.data['Class'] == 5].index.min()

        segment_difference = first_rem_index - first_nrem_index
        time_difference_seconds = segment_difference * 30
        return time_difference_seconds // 60

    def calculate_sleep_stage_percentages(self):
        """
        Computes the percentage of time spent in each sleep stage.

        Returns:
            tuple: NoREM1, NoREM2, NoREM3+NoREM4, REM percentages.
        """
        total_segments = len(self.data['Class'])
        stage_times = {1: 0, 2: 0, 3: 0, 4: 0, 5: 0}

        index = 0
        while index < total_segments:
            start_index = None
            if self.data['Class'][index] in stage_times:
                start_index = index
                class_type = self.data['Class'][index]
                while index < total_segments and \
                        self.data['Class'][index] == class_type:
                    index += 1
                end_index = index - 1
                segment_diff = end_index - start_index + 1
                stage_times[class_type] += segment_diff * 30
            else:
                index += 1

        total_time = sum(stage_times.values())
        if total_time == 0:
            return 0, 0, 0, 0

        norem1 = (stage_times[1] / total_time) * 100
        norem2 = (stage_times[2] / total_time) * 100
        norem3 = ((stage_times[3] + stage_times[4]) / total_time) * 100
        rem = (stage_times[5] / total_time) * 100

        return norem1, norem2, norem3, rem

    def calculate_arousal_index(self):
        """
        Computes the Arousal Index (Arousals per hour of sleep).

        Returns:
            float: Arousal Index.
        """
        arousal_count = 0
        total_sleep_time = 0

        for index in range(len(self.data['Class']) - 1):
            if self.data['Class'][index] in [2, 3, 4, 5]:
                total_sleep_time += 30
                if self.data['Class'][index + 1] in [1, 6]:
                    arousal_count += 1

        total_sleep_time_hours = total_sleep_time / 3600
        if total_sleep_time_hours == 0:
            return 0
        return arousal_count / total_sleep_time_hours

    def run_all_metrics(self):
        """
        Runs all the sleep metrics calculations and returns the results.

        Returns:
            tuple: Sleep latency, sleep duration, sleep to REM latency,
                   NoREM1 percentage, NoREM2 percentage,
                   NoREM3 (NoREM3 + NoREM4) percentage, REM percentage,
                   Arousal index.
        """
        sleep_latency = self.calculate_sleep_latency()
        sleep_duration = self.calculate_sleep_duration()
        sleep_to_rem_latency = self.calculate_sleep_to_rem_latency()
        norem1, norem2, norem3, rem = self.calculate_sleep_stage_percentages()
        arousal_index = self.calculate_arousal_index()

        return (sleep_latency, sleep_duration, sleep_to_rem_latency,
                norem1, norem2, norem3, rem, arousal_index)