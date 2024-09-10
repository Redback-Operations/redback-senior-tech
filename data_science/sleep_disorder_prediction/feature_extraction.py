import numpy as np
import scipy.stats as stats
from scipy.signal import find_peaks
from statsmodels.robust import mad
import nolds
from scipy.integrate import simps


class PPGFeatureExtractor:
    def __init__(self, ppg_signal, sampling_rate=100):
        """
        Initialize the PPGFeatureExtractor.

        Parameters:
        ppg_signal (array-like): The raw PPG signal data.
        sampling_rate (int): The sampling rate of the signal (default: 100Hz).
        """
        self.ppg_signal = np.array(ppg_signal).flatten()
        self.sampling_rate = sampling_rate
        self.peaks, _ = find_peaks(self.ppg_signal)
        self.troughs, _ = find_peaks(-self.ppg_signal)
        self.pp_intervals = np.diff(self.peaks) / sampling_rate

    def rms(self, x):
        """Calculate the Root Mean Square (RMS) of an array."""
        return np.sqrt(np.mean(x**2))

    def calculate_sdsd(self, x):
        """Calculate the Standard Deviation of Successive Differences"""
        return np.std(np.diff(x))

    def calculate_rmssd(self, x):
        """Calculate Root Mean Square of Successive Differences (RMSSD)"""
        return np.sqrt(np.mean(np.diff(x)**2))

    def calculate_areas(self, signal, inflection_indices):
        """Calculate systolic and diastolic areas."""
        area_sys = simps(signal[inflection_indices
                         [:len(inflection_indices)//2]],
                         dx=1/self.sampling_rate)
        area_dias = simps(signal[inflection_indices
                          [len(inflection_indices)//2:]],
                          dx=1/self.sampling_rate)
        return area_sys, area_dias

    def calculate_pulse_width(self):
        """Calculate the pulse width between peaks and troughs."""
        widths = []
        for i in range(len(self.peaks) - 1):
            if i < len(self.troughs) and self.peaks[i] < self.troughs[i]:
                widths.append((self.troughs[i] - self.peaks[i])
                              / self.sampling_rate)
        return np.array(widths)

    def inflection_points(self):
        """Find inflection points in the PPG signal."""
        inflections = []
        signal = self.ppg_signal
        for i in range(1, len(signal) - 1):
            prev = signal[i - 1]
            curr = signal[i]
            next = signal[i + 1]
            if (prev < curr > next) or (prev > curr < next):
                inflections.append(i)
        return inflections

    def higuchi_fd(self, x, kmax=5):
        """Calculate Higuchi Fractal Dimension (HFD) of a time series."""
        N = len(x)
        Lk = np.zeros(kmax)

        for k in range(1, kmax + 1):
            Lm = np.zeros((k,))

            for m in range(0, k):
                Lmk = 0
                for i in range(1, int(np.floor((N - m) / k))):
                    Lmk += abs(x[m + i * k] - x[m + (i - 1) * k])
                Lm[m] = (Lmk * (N - 1) / (k * np.floor((N - m) / k)))

            Lk[k - 1] = np.sum(Lm) / k

        # Perform linear regression to find the slope (fractal dimension)
        Lk_log = np.log(Lk)
        k_log = np.log(range(1, kmax + 1))
        higuchi, _ = np.polyfit(k_log, Lk_log, 1)

        return higuchi

    def extract_features(self):
        """Extract all features from the PPG signal."""
        # Peak-to-Peak Features
        av_pp_amp = np.mean(self.pp_intervals)
        sd_pp_amp = np.std(self.pp_intervals)
        sdsd_pp_amp = self.calculate_sdsd(self.pp_intervals)
        rmssd_pp_amp = self.calculate_rmssd(self.pp_intervals)
        max_pp_amp = np.max(self.pp_intervals)
        min_pp_amp = np.min(self.pp_intervals)
        median_pp_amp = np.median(self.pp_intervals)
        skew_pp_amp = stats.skew(self.pp_intervals)
        kurt_pp_amp = stats.kurtosis(self.pp_intervals)

        # Pulse Width Features
        pulse_widths = self.calculate_pulse_width()
        mean_pulse_width = np.mean(pulse_widths)
        sd_pulse_width = np.std(pulse_widths)
        sdsd_pw = self.calculate_sdsd(pulse_widths)
        rmssd_pw = self.calculate_rmssd(pulse_widths)
        max_pw = np.max(pulse_widths)
        min_pw = np.min(pulse_widths)
        median_pw = np.median(pulse_widths)
        skew_pw = stats.skew(pulse_widths)
        kurt_pw = stats.kurtosis(pulse_widths)

        # Systolic and Diastolic Areas
        inflection_indices = self.inflection_points()
        if len(inflection_indices) >= 2:
            area_sys, area_dias = self.calculate_areas(self.ppg_signal,
                                                       inflection_indices)
            mean_area = (area_sys + area_dias) / 2
            std_area = np.std([area_sys, area_dias])
            meanIPAR = area_sys / area_dias
            stdIPAR = np.std(meanIPAR)
        else:
            area_sys = area_dias = mean_area = np.nan
            std_area = meanIPAR = stdIPAR = np.nan

        # Systolic and Diastolic Times
        mean_t1 = np.mean(np.diff(self.peaks[:len(self.peaks)//2])
                          / self.sampling_rate)
        std_t1 = np.std(np.diff(self.peaks[:len(self.peaks)//2])
                        / self.sampling_rate)
        mean_t2 = np.mean(np.diff(self.peaks[len(self.peaks)//2:])
                          / self.sampling_rate)
        std_t2 = np.std(np.diff(self.peaks[len(self.peaks)//2:])
                        / self.sampling_rate)

        # Inflection Point Time Ratio (IPTR)
        mean_iptr = mean_t1 / mean_t2 if mean_t2 != 0 else np.nan
        std_iptr = std_t1 / std_t2 if std_t2 != 0 else np.nan

        # Nonlinear Features
        hjorth_activity = np.var(self.ppg_signal)
        hjorth_mobility = np.sqrt(np.var(np.gradient(self.ppg_signal))
                                  / hjorth_activity)
        hjorth_complexity = np.sqrt(np.var(np.gradient
                                           (np.gradient(self.ppg_signal)))
                                    / np.var(np.gradient(self.ppg_signal))
                                    / hjorth_mobility)

        poincare_sd1 = np.std(np.diff(self.pp_intervals)) / np.sqrt(2)
        poincare_sd2 = np.sqrt(2 * np.std(self.pp_intervals)**2
                               - poincare_sd1**2)

        hurst_exp = nolds.hurst_rs(self.ppg_signal)
        dfa_alpha = nolds.dfa(self.ppg_signal)
        lyapunov_exp = nolds.lyap_r(self.ppg_signal
                                    , emb_dim=6)

        # Robust Statistical Features
        mad_pp_amp = mad(self.pp_intervals)
        mad_pw = mad(pulse_widths)
        iqr_pp_amp = np.subtract(*np.percentile(self.pp_intervals, [75, 25]))
        iqr_pw = np.subtract(*np.percentile(pulse_widths, [75, 25]))

        # Frequency Domain Features (Using FFT)
        fft_signal = np.fft.fft(self.ppg_signal)
        fft_freqs = np.fft.fftfreq(len(self.ppg_signal)
                                   , d=1/self.sampling_rate)
        fft_amplitudes = np.abs(fft_signal)

        total_power = np.sum(fft_amplitudes**2)
        lf_band = np.logical_and(fft_freqs >= 0.04, fft_freqs < 0.15)
        hf_band = np.logical_and(fft_freqs >= 0.15, fft_freqs < 0.4)
        lf_power = np.sum(fft_amplitudes[lf_band]**2)
        hf_power = np.sum(fft_amplitudes[hf_band]**2)
        lf_hf_ratio = lf_power / hf_power if hf_power != 0 else np.nan

        # Feature Dictionary
        features = {
            # Peak-to-Peak Features
            "AVppAmp": av_pp_amp, "SDppAmp": sd_pp_amp, "SDSDppAmp":
            sdsd_pp_amp, "RMSSDppAmp": rmssd_pp_amp,
            "MaxppAmp": max_pp_amp, "MinppAmp": min_pp_amp,
            "MedianppAmp": median_pp_amp, "SkewppAmp": skew_pp_amp,
            "KurtosisppAmp": kurt_pp_amp,
            "MADppAmp": mad_pp_amp, "IQRppAmp": iqr_pp_amp,

            # Pulse Width Features
            "AVpw": mean_pulse_width, "SDpw": sd_pulse_width,
            "SDSDpw": sdsd_pw, "RMSSDpw": rmssd_pw,
            "Maxpw": max_pw, "Minpw": min_pw,
            "Medianpw": median_pw, "Skewpw": skew_pw,
            "Kurtosispw": kurt_pw, "MADpw": mad_pw, "IQRpw": iqr_pw,

            # Systolic and Diastolic Area Features
            "meanA1": area_sys, "meanA2": area_dias,
            "meanArea": mean_area, "stdArea": std_area,
            "MeanIPAR": meanIPAR, "StdIPAR": stdIPAR,

            # Systolic and Diastolic Times
            "meanT1": mean_t1, "stdT1": std_t1,
            "meanT2": mean_t2, "stdT2": std_t2,

            # Inflection Point Time Ratio (IPTR)
            "meanIPTR": mean_iptr, "stdIPTR": std_iptr,

            # Nonlinear Features
            "HjorthActivity": hjorth_activity,
            "HjorthMobility": hjorth_mobility,
            "HjorthComplexity": hjorth_complexity,
            "PoincareSD1": poincare_sd1, "PoincareSD2": poincare_sd2,
            "HurstExp": hurst_exp,
            "DFAAlpha": dfa_alpha, "LyapunovExp": lyapunov_exp,
            "HFD": self.higuchi_fd(self.ppg_signal, 5),
            "HFD_cardio": self.higuchi_fd(self.pp_intervals, 5),

            # Frequency Domain Features
            "TotalPower": total_power, "LFPower": lf_power,
            "HFPower": hf_power, "LFHFRatio": lf_hf_ratio,
        }
        return features
