
# Heart Attack Prediction Using Deep Learning

This study seeks to create a Heart Attack Risk Prediction Model for older people by combining deep with machine learning techniques such as Neural Networks and Random Forest. The goal is to provide proactive monitoring by using health data such as age, cholesterol levels, and heart rate, while also resolving class imbalance with SMOTEENN.



## Table of Contents

* Project Structure
* Features
* Tech Stack
* Installation
* Usage
* Project Roadmap
## Project Structure

The project is organized as follows:

* Data Folder: Contains health datasets (e.g., heart_attack_prediction_dataset.csv).
* Notebooks: Jupyter Notebooks for data preprocessing, model training, and evaluation.
* Models: Python scripts for Neural Network and Random Forest implementations.
* README File: Comprehensive project information and setup instructions.

## Features

* Heart Attack Risk Prediction: Neural Networks and Random Forest models are used to anticipate the risk of heart attacks.
* Class Imbalance Handling: The dataset was balanced using SMOTEENN to improve model performance.
* Detailed visualisations include confusion matrices, feature significance graphs, and correlation heatmaps.
* Feature engineering involves changes such as dividing blood pressure into systolic and diastolic values.

## Tech Stack

* Python: Scripting, data preprocessing, and model building.
* TensorFlow/Keras: For creating deep learning models.
* Scikit-Learn: For machine learning models and evaluation metrics.
* Matplotlib/Seaborn: For visualizing data and model performance.
SMOTEENN: For handling class imbalances.
## Usage

* Data Preprocessing: Run the preprocessing steps in the Jupyter notebooks to clean and prepare the data.
* Model Training: Execute the training scripts (neural_network_model.py or random_forest_model.py) to build and evaluate the models.
* Model evaluation involves analysing performance using criteria like as accuracy, precision, recall, and confusion matrices.
* Visualization: Create plots to better understand feature importance and model predictions.

## Project Roadmap

* Phase 1: Data collection and exploratory data analysis (EDA).
* Phase 2: Model development using Neural Networks and Random Forest.
* Phase 3: Address data imbalance using SMOTEENN.
* Phase 4: Visualization of results through detailed plots and confusion matrices.
* Future Steps: Explore advanced models like XGBoost and integrate the model into a wearable device for real-time monitoring.
