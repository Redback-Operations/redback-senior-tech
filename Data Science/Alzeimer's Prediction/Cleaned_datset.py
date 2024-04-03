import pandas as pd
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt

dataset = pd.read_csv(r"C:\Users\asus\Desktop\Elderly_Wearable_Tech\Data Science\Alzeimer's Prediction\Alzheimer's dataset.csv")

# Check for null values in each column
null_values = dataset.isnull().sum()

# Determine the data types of each column
data_types = dataset.dtypes
#print(data_types)

# Identify categorical and numerical columns
categorical_columns = dataset.select_dtypes(include=['object']).columns.tolist()
numerical_columns = dataset.select_dtypes(include=['number']).columns.tolist()

# Creating a summary table
null_summary = pd.DataFrame({
    "Column Name": dataset.columns,
    "Data Type": ["Categorical" if col in categorical_columns else "Numerical" for col in dataset.columns],
    "Null Values": null_values.values
})
print(null_summary)

# Imputing the 'SES' column with mode
# Mode can return multiple values; we take the first one
ses_mode = dataset['SES'].mode()[0]  
dataset['SES'].fillna(ses_mode, inplace=True)

# Imputing the 'MMSE' column with median
mmse_median = dataset['MMSE'].median()
dataset['MMSE'].fillna(mmse_median, inplace=True)

# Verifying the imputation
imputation_check = dataset.isnull().sum()

# Printing the results
print(imputation_check)

cleaned = dataset
