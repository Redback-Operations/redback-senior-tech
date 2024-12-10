#### **Project Overview**

This project focuses on analyzing Alzheimer's disease indicators and classifying patients as Nondemented or Dementedusing machine learning models. Two primary classifiers, Random Forest and XGBoost, are implemented to evaluate performance in terms of classification accuracy and AUC-ROC metrics. Additionally, a second dataset is harmonized and processed for mental health analysis to further demonstrate data preprocessing, feature engineering, and model training.

#### **Dataset**

1.  **Alzheimer's Dataset**
    
    *   Contains features such as Age, M/F, EDUC, SES, and MMSE.
        
    *   Target variable: Group (encoded as 0: Nondemented, 1: Demented, 2: Converted).
        
    *   The Converted class is filtered out during preprocessing.
        
2.  **Mental Health Dataset**
    
    *   Contains features like Age Group, Mental Health, Race, and Data\_Value.
        
    *   Target variable: Outcome.
        

#### **Steps in the Code**

##### **1\. Data Loading**

The Alzheimer's dataset is loaded from the specified file path:


##### **2\. Preprocessing**

*   **Handling Missing Values:**
    
    *   For features like SES and MMSE, missing values are replaced with the median.
        
*   **Feature Encoding:**
    
    *   The M/F feature and Group target variable are encoded using LabelEncoder.
        
*   **Filtering:**
    
    *   Instances where the target is Converted are excluded.
        

##### **3\. Feature and Target Selection**

Relevant features (Age, M/F, EDUC, SES, and MMSE) are selected along with the target variable (Group).

##### **4\. Splitting the Dataset**

Data is split into training and testing sets using an 80:20 ratio:

 `

##### **5\. Model Training and Evaluation**

*   **Random Forest Classifier:**
    
    *   Trains on the preprocessed dataset.
        
    *   Outputs a classification report and AUC-ROC score.
        
*   **XGBoost Classifier:**
    
    *   Trains on the preprocessed dataset.
        
    *   Outputs a classification report and AUC-ROC score.
        

##### **6\. Mental Health Dataset Harmonization**

*   Features are harmonized and renamed for consistency.
    
*   Missing values are handled, and categorical features (Race) are one-hot encoded.
    

##### **7\. Standardization**

Numerical features like MentalDistressPercentage are normalized using StandardScaler.

##### **8\. Additional Model Training**

A Random Forest Classifier is trained on the processed mental health dataset, with a classification report and an ROC curve visualization.
