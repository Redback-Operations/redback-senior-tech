# Alzheimer's Disease Prediction

## Project Overview
This project analyzes Alzheimer's disease indicators to classify patients as **Nondemented** or **Demented** using machine learning models. Two primary classifiers, **Random Forest** and **XGBoost**, are implemented and evaluated for performance in terms of **classification accuracy** and **AUC-ROC metrics**. Additionally, a secondary dataset is harmonized and processed for **mental health analysis**, showcasing preprocessing, feature engineering, and model training.

---

## Datasets

### 1. Alzheimer's Dataset
- **Source:** [Catalog of U.S. Government Data](https://catalog.data.gov/dataset/alzheimers-disease-and-healthy-aging-data)
- **Features:**
  - `Age`: Patient's age.
  - `M/F`: Gender.
  - `EDUC`: Years of education.
  - `SES`: Socioeconomic status.
  - `MMSE`: Mini-Mental State Examination score.
- **Target Variable:**
  - `Group`: Encoded as `0` (Nondemented), `1` (Demented), `2` (Converted).
- **Preprocessing:**
  - Instances with the `Converted` class are excluded for binary classification.

### 2. Mental Health Dataset
- **Focus:**
  - Insights into frequent mental distress among older adults.
  - Stratification by demographics (e.g., age groups, race/ethnicity).
- **Features:**
  - `Age Group`
  - `Mental Health`
  - `Race`
  - `Data Value`
- **Target Variable:** `Outcome`

---

## Methodology

### Models Trained
1. **Random Forest Classifier**: Ensemble-based method for robust classification.
2. **XGBoost Classifier**: Gradient-boosting framework optimized for performance.

### Evaluation Metrics
- **Classification Report:**
  - Precision, Recall, F1-Score for each class.
- **AUC-ROC Score:**
  - Measures the classifier's ability to distinguish between classes.

---

## Results

### Random Forest
- **Accuracy:** 76%
- **AUC-ROC Score:** 0.89
- **Strengths:** High recall for `Demented` class (effective for detecting dementia).
- **Weaknesses:** Lower precision for `Nondemented` class, leading to false positives.

### XGBoost
- **Accuracy:** 76%
- **AUC-ROC Score:** 0.92
- **Strengths:** Improved overall accuracy and AUC-ROC, demonstrating better discriminatory ability.
- **Weaknesses:** Similar challenges in identifying `Nondemented` class.

---

## Workflow

### 1. Data Loading
- Alzheimer's dataset loaded from `data/alzheimers.csv`.
- Mental health dataset loaded and harmonized.

### 2. Preprocessing
- **Alzheimer's Dataset:**
  - Missing values in `SES` and `MMSE` replaced with the median.
  - Categorical variables (`M/F` and `Group`) encoded using `LabelEncoder`.
  - Instances with `Converted` class excluded.
- **Mental Health Dataset:**
  - Missing values handled.
  - Categorical variables (e.g., `Race`) one-hot encoded.

### 3. Feature and Target Selection
- Relevant features selected for training (e.g., `Age`, `M/F`, `EDUC`, `SES`, `MMSE`).

### 4. Splitting the Dataset
- Data split into training and testing sets (80:20 ratio).

### 5. Model Training and Evaluation
- **Random Forest** and **XGBoost** trained on the Alzheimer's dataset.
- Classification report and AUC-ROC scores generated.

### 6. Harmonization and Standardization
- Mental health dataset features normalized using `StandardScaler`.

### 7. Additional Model Training
- Random Forest trained on the processed mental health dataset.
- ROC curve visualized for model comparison.

---

