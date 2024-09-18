# Parkinson's Disease Prediction

## Project Overview

This project aims to build and refine a machine learning model to predict the presence of Parkinson's disease using features extracted from biomedical voice measurements. The focus is on selecting relevant features, retraining multiple models, and optimizing their performance through hyperparameter tuning.

## Dataset

The dataset used in this project is derived from biomedical voice measurements. It includes 195 instances with 22 numerical features, including metrics like jitter, shimmer, and harmonic-to-noise ratio, which are key indicators in diagnosing Parkinson's disease.

## Project Structure

- **Data Processing:** 
  - The dataset was loaded and cleaned, with categorical features separated from numerical features.
  - The 'name' column, which is irrelevant for modeling, was dropped.
  - Missing values were checked and handled.
  
- **Data Visualization:** 
  - KDE plots were used to explore the distribution of each feature.
  - A clustermap was generated to visualize the correlations between features.
  - Box plots were created to show the distribution of features grouped by Parkinson's status.
  - A bar plot was used to display the count of healthy vs Parkinson's individuals.

- **Model Training - Normal:**
  - Four models were trained using the entire feature set: Logistic Regression, SVM, Decision Tree, and Random Forest.
  - Each model's performance was evaluated based on accuracy, precision, recall, and F1 score.
  
- **Model Training - Newer Version:**
  - Selected a subset of features that were most relevant to the prediction task.
  - Retrained the models with the refined feature set, and compared their performance to the initial results.

- **Model Training - Hyperparameter Tuning:**
  - Applied hyperparameter tuning using GridSearchCV to further optimize each model.
  - Used Recursive Feature Elimination (RFE) for feature selection in Logistic Regression.

- **Conclusion and Results:**
  - SVM showed the most significant improvement with hyperparameter tuning and is a strong candidate for deployment.
  - Decision Tree and Random Forest performed consistently well, with Random Forest emerging as the best-performing model overall.
  - Logistic Regression, while not showing significant improvement, remains a simple and interpretable model.

## Key Findings

- **Random Forest** emerged as the best model for predicting Parkinson's disease, with the highest accuracy and performance metrics.
- **SVM** also performed well after hyperparameter tuning and could be considered depending on the specific needs of the deployment environment.

## Installation

To replicate this project, you'll need to install the following Python packages:

```bash
pip install numpy pandas seaborn scikit-learn matplotlib
