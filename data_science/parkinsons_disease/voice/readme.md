
# Parkinson's Disease Prediction

This project focuses on **Parkinson's Disease Prediction** using machine learning models based on **biomedical voice measurements**. The models are built and refined to detect the presence of Parkinson's disease, using features such as voice frequency, jitter, shimmer, and other related metrics. This project includes feature selection, model training, and hyperparameter tuning to optimize predictive performance.

## Table of Contents
1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Data Structure](#data-structure)
6. [Modeling Process](#modeling-process)
7. [Future Enhancements](#future-enhancements)
8. [Contributing](#contributing)
9. [License](#license)

---

## Project Overview

The **Parkinson's Disease Prediction** project uses biomedical voice measurements to predict the presence of Parkinson's disease in individuals. The dataset includes voice measurements that capture irregularities in speech, which are common in Parkinson's patients. The project explores several machine learning models, including **Logistic Regression**, **Support Vector Machine (SVM)**, **Decision Tree**, and **Random Forest**. Feature selection and hyperparameter tuning are applied to improve model accuracy and reliability.

---

## Features

- **Feature Selection with RFE**: Uses Recursive Feature Elimination (RFE) to select the most important features for prediction.
- **Hyperparameter Tuning**: GridSearchCV is used to tune model parameters for improved accuracy.
- **Model Comparison**: Multiple models are evaluated and compared using key metrics like accuracy, precision, recall, and F1 score.
- **Best Model Selection**: Random Forest emerged as the best model, with consistently high performance across all metrics.

---

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/parkinsons-disease-prediction.git
   ```

2. **Navigate to the Project Directory**:
   ```bash
   cd parkinsons-disease-prediction
   ```

3. **Install Required Dependencies**: You need Python 3.x installed along with the following libraries:
   ```bash
   pip install pandas numpy scikit-learn seaborn matplotlib
   ```

4. **Run the Notebook or Script**:
   ```bash
   jupyter notebook Parkinsons_Disease_Prediction.ipynb
   ```
   OR, if you're using a Python script:
   ```bash
   python parkinsons_prediction.py
   ```

---

## Usage

### Data Input:
The model is trained on a dataset that includes several biomedical voice measurements. The dataset should follow a structured format, as described in the **Data Structure** section. Ensure that the data is correctly formatted before training the models.

### Start Model Training:
Run the Jupyter notebook or Python script to train the models and evaluate their performance. The notebook walks through feature selection, model training, hyperparameter tuning, and evaluation.

### Model Evaluation:
The models will be evaluated based on metrics like accuracy, precision, recall, and F1 score. After evaluation, the best-performing model (Random Forest) can be used to predict Parkinson's disease in new datasets.

---

## Data Structure

The dataset should include the following columns:

- `MDVP:Fo(Hz)`: Average vocal fundamental frequency
- `MDVP:Fhi(Hz)`: Maximum vocal fundamental frequency
- `MDVP:Flo(Hz)`: Minimum vocal fundamental frequency
- `MDVP:Jitter(%)`: Measure of variation in frequency
- `MDVP:Shimmer`: Measure of variation in amplitude
- `NHR`: Noise to harmonic ratio
- `HNR`: Harmonic to noise ratio
- `RPDE`: Nonlinear dynamical complexity measure
- `DFA`: Signal fractal scaling exponent
- `PPE`: Pitch period entropy
- `status`: Target variable (1 = Parkinson's, 0 = Healthy)

---

## Modeling Process

The notebook includes the following key steps:

1. **Data Exploration and Preprocessing**: Initial data analysis, handling missing values, and feature scaling.
2. **Feature Selection with RFE**: Recursive Feature Elimination (RFE) is used to select the top 15 most relevant features.
3. **Model Training and Hyperparameter Tuning**:
   - Models trained include **Logistic Regression**, **SVM**, **Decision Tree**, and **Random Forest**.
   - GridSearchCV is used for hyperparameter tuning, optimizing the models for better accuracy.
4. **Model Evaluation**: Each model is evaluated using the following metrics:
   - **Accuracy**
   - **Precision**
   - **Recall**
   - **F1 Score**
   - **Confusion Matrix** for a detailed breakdown of model predictions.
5. **Final Model Selection**: The **Random Forest** model is selected as the best model due to its consistently strong performance across all metrics.

---

## Future Enhancements

Potential improvements and future features:

- **Integration with Real-Time Voice Analysis**: Use real-time voice data collection for more immediate predictions.
- **Additional Feature Engineering**: Investigate new voice features that may improve prediction accuracy.
- **Model Interpretability**: Implement SHAP (SHapley Additive exPlanations) or LIME for better model interpretability.
- **Deployment**: Develop a web or mobile app for real-time Parkinson's prediction based on voice inputs.

---

## Contributing

Contributions are welcome! If you have ideas for improvement or new features, feel free to open a pull request or submit an issue. Follow the standard GitHub workflow to contribute to this project.

---

## License

This project is licensed under the MIT License - see the LICENSE file for details.
