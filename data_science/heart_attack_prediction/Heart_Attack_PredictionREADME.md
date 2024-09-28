# Heart Attack Prediction Model in Elderly Wearable Tech

This project is aimed at creating a Heart Attack Risk Prediction Model based on health data such as age, cholesterol levels, and heart rate. The model is intended to enable proactive monitoring of older patients by predicting heart attack risks using machine learning techniques such as Random Forest and Logistic Regression, while resolving data imbalance with SMOTE. This model will be integrated into a broader wearable technology solution to enable real-time heath monitoring. 

## Table of Contents

* Project Structure
* Features
* Tech Stack
* Installation
* Usage
* Project Roadmap

## Project structure
The project is organised as follows:

* Data Folder: Stores patient demographic and health indicators datasets.
* Jupyter Notebooks are used to conduct exploratory data analysis, preprocessing, model training, and evaluation.
* Trained models and outputs include performance measures including confusion matrices, accuracy reports, and feature importance visualisations.
* README file contains comprehensive project information and setup instructions.

## Features
* Heart Attack Risk Prediction: Uses Random Forest, Logistic Regression, and SVM models to forecast heart attack risk based on patient data.
* Class Imbalance Handling: SMOTE is used to ensure a balanced dataset and improve model performance.
* Visualisations: To help with data interpretation, I created detailed visualisations such as correlation heatmaps, distribution plots, and confusion matrices.
* Feature Engineering: Engineered features, such as differentiating systolic and diastolic blood pressure, provide more precise forecasts.
* Power BI Dashboard: Provides a simple interface for healthcare practitioners to track critical health data and heart attack risk factors.


## Tech Stack
* Python is used for scripting, data preprocessing, and model construction.
* TensorFlow/Keras: Used to create deep learning models (MLP Neural Networks).
* Scikit-learn supports standard machine learning models, SMOTE, and evaluation measures.
* Seaborn with Matplotlib: Tools for visualising data and visualising model performance metrics.
* Power BI: Created interactive dashboards for non-technical users that provided insights into patient data.

## Installation
To establish the project locally, perform these steps:

* Clone the repository on your local workstation.
* Create a Python virtual environment with python -m venv venv.
* Activate the virtual environment.
* For Windows: venv\Scripts\Activate.
* For Mac and Linux: source venv/bin/activate.
* Install dependencies with the specified requirements.txt file:
* Copy the code: pip install -r requirements.txt.
* Prepare the dataset by organising it into the right folder structure.


## Usage

* Data Preprocessing: Clean and preprocess the health measurements data with the data preprocessing notebooks.
* Model Training: Use the included Jupyter notebooks to train models with Random Forest, Logistic Regression, and SVM.
* Model Evaluation: Run the models on test data and analyse the outcomes with metrics like accuracy, precision, recall, and confusion matrices.
* Visualisations: Use the given visualisations to investigate feature importance and better understand the model's decision-making process.
* Dashboard: Use the Power BI dashboard to monitor health parameters and estimated heart attack risks interactively.

## Project Roadmap
* The project started with data gathering and exploration, which was followed by the creation of prediction models like Logistic Regression, Random Forest, and SVM. 
* To overcome class imbalance, SMOTE was used, which considerably improved model performance. The next step was to improve data visualisation tools, such as correlation heatmaps, box plots, and confusion matrices, in order to deliver clearer insights. 
* Finally, the project included a Power BI dashboard, which allows healthcare practitioners to monitor patient risk indicators in real time. 
* Future initiatives include looking into more complex models, such as XGBoost, and incorporating additional health data to improve forecasts.



