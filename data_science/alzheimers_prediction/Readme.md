
# Alzheimer's Disease Prediction Notebook

## Overview
This notebook is designed to predict Alzheimer's disease using machine learning models. It performs data preprocessing, feature engineering, model training, evaluation, and visualization. The dataset includes clinical and neuroimaging data, and the goal is to predict the onset or progression of Alzheimer's disease.

## Requirements
- Python 3.x
- Libraries:
  - NumPy
  - Pandas
  - Scikit-learn
  - Matplotlib/Seaborn
  - SMOTE from imblearn (for handling class imbalance)
  - Optionally: XGBoost or SHAP for further improvements

Install the necessary libraries using:
```bash
pip install numpy pandas scikit-learn matplotlib seaborn imbalanced-learn
```

## Structure of the Notebook

1. **Data Loading**: Reads in the dataset containing clinical and neuroimaging features.
2. **Data Preprocessing**: Handles missing values, normalizes data, and splits it into training and testing sets.
3. **Exploratory Data Analysis (EDA)**: Visualizes the distribution of important features like age, CDR, nWBV, and more.
4. **Model Building**: Trains a Random Forest classifier. Hyperparameters are tuned using GridSearchCV, and class imbalance is handled using SMOTE.
5. **Model Evaluation**: Evaluates the model using accuracy, precision, recall, F1-score, and visualizes feature importance.
6. **Feature Importance**: Analyzes the contribution of different features to the model’s predictions.

## Results

- The best Random Forest model achieved an accuracy of **99.2%** on the test set.

### Classification Report (without SMOTE):

```markdown
             precision    recall  f1-score   support

         0       0.97      1.00      0.99        72
         1       1.00      0.97      0.98        66
         2       1.00      1.00      1.00        58
         3       1.00      1.00      1.00        60

  accuracy                           0.99       256
 macro avg       0.99      0.99      0.99       256
 weighted avg    0.99      0.99      0.99       256
```

- **Test Set Accuracy** with SMOTE: **99.2%**
- **Classification Report** with SMOTE:

```markdown
           precision    recall  f1-score   support

       0       0.99      0.99      0.99        72
       1       0.98      0.98      0.98        66
       2       1.00      1.00      1.00        58
       3       1.00      1.00      1.00        60

  accuracy                           0.99       256
 macro avg       0.99      0.99      0.99       256
 weighted avg    0.99      0.99      0.99       256
```

- The most important features were:
  1. nWBV (Normalized Whole Brain Volume) – Importance: **0.2118**
  2. CDR (Clinical Dementia Rating) – Importance: **0.1808**
  3. Age – Importance: **0.1263**
  4. ASF (Atlas Scaling Factor) – Importance: **0.1084**

## Usage
1. Run the notebook cell-by-cell to load data, preprocess, and train the model.
2. Use the tuned Random Forest model for making predictions.
3. Adjust hyperparameters or the model architecture as needed to fit your project.

## Conclusion
This notebook provides a complete workflow for predicting Alzheimer's disease based on clinical and neuroimaging data. With a high accuracy of 99.2%, it offers a robust model suitable for real-world applications.
