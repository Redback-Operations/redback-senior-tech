
# Parkinson's Disease Prediction

## Tagline:
Gait Analysis and Voice Data Analysis for Parkinson’s Disease (PD) Detection using data from Phisonet’s Gaitpdb database and a Parkinson’s voice dataset.

## Description:
This project focuses on detecting Parkinson’s Disease through two key approaches:
1. **Voice Data Analysis**: Analyzing biomedical voice measurements for early detection of Parkinson's.
2. **Gait Data Analysis**: Using gait data from Phisonet’s Gaitpdb database to detect differences in walking patterns that indicate Parkinson’s Disease.

The project involves feature selection, model training, and evaluation for both datasets using a variety of machine learning models, optimizing the predictive performance.

---

## Table of Contents
1. [Project Overview](#project-overview)
2. [Voice Data Analysis](#voice-data-analysis)
3. [Gait Data Analysis](#gait-data-analysis)
4. [Features](#features)
5. [Installation](#installation)
6. [Usage](#usage)
7. [Data Structure](#data-structure)
8. [Modeling Process](#modeling-process)
9. [Future Enhancements](#future-enhancements)
10. [Contributing](#contributing)
11. [License](#license)

---

## Project Overview

The **Parkinson's Disease Prediction** project aims to identify Parkinson’s Disease using two datasets:
- **Voice Data**: Focused on biomedical voice metrics such as jitter, shimmer, and fundamental frequency (Fo).
- **Gait Data**: Uses Vertical Ground Reaction Force (VGRF) data from 8 sensors applied to the feet to detect differences in walking patterns.

By combining insights from both datasets, this project strives to improve early detection and diagnosis of Parkinson’s Disease.

---

## Voice Data Analysis

- **Dataset**: The dataset is collected from biomedical voice measurements that reflect irregularities in speech due to Parkinson's Disease.
- **Objective**: Detect patterns in speech anomalies to differentiate between Parkinson's patients and healthy subjects.
- **Methodology**:
  - Feature selection with Recursive Feature Elimination (RFE)
  - Model training using Logistic Regression, SVM, Decision Tree, and Random Forest
  - Hyperparameter tuning using GridSearchCV
  - Evaluation based on accuracy, precision, recall, and F1 scores

---

## Gait Data Analysis

- **Dataset**: The gait data is sourced from the **Phisonet’s Gaitpdb** database, using sensors to capture **Vertical Ground Reaction Forces (VGRF)**.
- **Objective**: Identify differences in gait patterns between PD patients and healthy controls.
- **Methodology**:
  - Data compression using statistical functions to reduce the dataset from 3 million tuples to 310 representative tuples
  - Model training using machine learning algorithms to identify gait abnormalities

---

## Features

- **Feature Selection with RFE**: Uses Recursive Feature Elimination (RFE) to select the most important features for both voice and gait data.
- **Hyperparameter Tuning**: Optimizes models using GridSearchCV to improve accuracy.
- **Model Comparison**: Various models are evaluated, including:
  - Logistic Regression
  - Support Vector Machine (SVM)
  - Decision Tree
  - Random Forest
- **Evaluation**: Models are evaluated using standard metrics such as accuracy, precision, recall, and F1 score.

---

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Redback-Operations/redback-senior-tech.git
   ```

2. **Navigate to the Project Directory**:
   ```bash
   cd redback-senior-tech/data_science
   ```

3. **Install Required Dependencies**: Install the necessary libraries for both voice and gait analysis:
   ```bash
   pip install pandas numpy scikit-learn seaborn matplotlib tensorflow
   ```

4. **Run the Notebooks or Scripts**:
   To run the notebooks or scripts for both analyses

---

## Usage

### Voice Data:
The **voice analysis** focuses on processing vocal features to detect Parkinson's Disease. Run the **Parkinsons_Disease_Prediction_Voice.ipynb** to load, preprocess, and train the models using the voice dataset.

### Gait Data:
The **gait analysis** uses VGRF data to detect Parkinson's through walking patterns. Run the **Parkinsons_Disease_Prediction_Gait.ipynb** to analyze gait data and train models for detection.

### Model Evaluation:
After training, evaluate the models based on accuracy, precision, recall, and F1 score for both voice and gait data.

---

## Data Structure

### Voice Data Structure:
The voice dataset should include the following columns:
- `MDVP:Fo(Hz)`: Average vocal fundamental frequency
- `MDVP:Fhi(Hz)`: Maximum vocal fundamental frequency
- `MDVP:Flo(Hz)`: Minimum vocal fundamental frequency
- `MDVP:Jitter(%)`: Measure of variation in frequency
- `MDVP:Shimmer`: Measure of variation in amplitude
- `NHR`: Noise to harmonic ratio
- `HNR`: Harmonic to noise ratio
- `status`: Target variable (1 = Parkinson's, 0 = Healthy)

### Gait Data Structure:
The gait dataset includes VGRF data from 8 sensors per foot. After compression using statistical functions, the dataset contains 310 tuples with aggregated statistics.

---

## Modeling Process

### Voice Data:
1. **Data Preprocessing**: Handle missing values and scale the data for modeling.
2. **Feature Selection**: Use Recursive Feature Elimination (RFE) to select the top features.
3. **Model Training**: Train various models, including Logistic Regression, SVM, Decision Tree, and Random Forest.
4. **Evaluation**: Evaluate model performance using standard metrics (accuracy, precision, recall, F1 score).

### Gait Data:
1. **Data Compression**: Apply statistical functions to reduce the dataset.
2. **Modeling**: Use machine learning models to analyze gait patterns.
3. **Evaluation**: Assess the models’ ability to distinguish between PD patients and control subjects.

---

## Future Enhancements

Potential improvements and future features:
- **Real-Time Analysis**: Integrate real-time voice and gait data collection for immediate detection of Parkinson’s Disease.
- **Additional Feature Engineering**: Experiment with new features for improved model performance.
- **Anomaly Detection**: Implement advanced algorithms to flag anomalies in voice or gait patterns.
- **Deployment**: Build a user-friendly web or mobile application for real-time PD prediction.

---

## Contributing

Contributions are welcome! Feel free to open a pull request or submit an issue if you have ideas or suggestions for improvement. Follow the standard GitHub workflow for contributions.

---

## License

This project is licensed under the MIT License - see the LICENSE file for details.
