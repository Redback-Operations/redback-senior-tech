# Parkinson's Disease Prediction

## Tagline:
Detecting Parkinson's Disease (PD) through comprehensive analysis of **biomedical voice measurements** and **gait data**.

## Description:
This project focuses on the early detection of Parkinson’s Disease using two key datasets:
1. **Voice Data**: Utilizing features from biomedical voice measurements to detect irregularities in speech patterns.
2. **Gait Data**: Analyzing the Vertical Ground Reaction Forces (VGRF) from sensors placed on the feet of patients to identify gait abnormalities related to Parkinson’s Disease.

Data from **Phisonet’s Gaitpdb database** and **Parkinson's voice dataset** are leveraged, with machine learning models trained to distinguish between PD patients and healthy individuals.

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

The **Parkinson's Disease Prediction** project aims to identify Parkinson’s Disease through two approaches:
- **Voice Data Analysis**: Focusing on biomedical voice metrics such as jitter, shimmer, and fundamental frequency (Fo), to capture differences in speech between healthy individuals and PD patients.
- **Gait Data Analysis**: Using VGRF data from 8 sensors applied to the feet to identify differences in walking patterns between PD patients and control subjects.

Both analyses are aimed at aiding early detection and improving diagnostic accuracy.

---

## Voice Data Analysis

- **Dataset**: The voice data is gathered from a publicly available Parkinson’s dataset. It includes features such as vocal fundamental frequency (Fo), jitter, shimmer, and other measures related to vocal cord irregularities.
- **Objective**: Detect patterns in speech anomalies to differentiate between Parkinson's patients and healthy subjects.
- **Methodology**:
  - Feature Selection with Recursive Feature Elimination (RFE)
  - Model training using Logistic Regression, SVM, Decision Tree, and Random Forest
  - Hyperparameter tuning using GridSearchCV for optimization
  - Evaluation of models using accuracy, precision, recall, and F1 scores

---

## Gait Data Analysis

- **Dataset**: The gait data is sourced from the **Phisonet’s Gaitpdb** database, which uses sensors to capture **Vertical Ground Reaction Forces (VGRF)**.
- **Objective**: Identify differences in gait patterns between PD patients and control subjects, aiming for accurate disease detection based on movement abnormalities.
- **Methodology**:
  - Data compression using 7 statistical functions to reduce the dataset from 3 million tuples to 310 representative tuples
  - Gait data analysis using machine learning models to identify abnormalities in PD patients

---

## Features

- **Feature Selection**: Recursive Feature Elimination (RFE) is used to select the most important features from both voice and gait data.
- **Hyperparameter Tuning**: GridSearchCV is used for optimizing parameters in various models.
- **Modeling**: A range of models is applied, including:
  - Logistic Regression
  - Support Vector Machine (SVM)
  - Decision Tree
  - Random Forest
- **Evaluation**: The models are evaluated using accuracy, precision, recall, and F1 scores for comprehensive performance comparison.

---

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Redback-Operations/redback-senior-tech.git
