
# Parkinson's Disease (PD) Wrist-Mounted Prediction Model

## Executive Summary:
The goal of this project is to develop a machine learning model that leverages data from a wrist-mounted device to detect hand tremors—an early potential indicator of Parkinson's Disease (PD). Using data from a 3-axis accelerometer and gyroscope, the project evaluates various models to determine their effectiveness in classifying tremors. The Random Forest model is the most promising, balancing accuracy and computational efficiency. Future steps include validating results with additional datasets and integrating the model into the Lachesis wearable device.

---

## Table of Contents
1. [Model Focus and Limitations](#model-focus-and-limitations)
2. [Research Summary](#research-summary)
3. [Dataset Analysis](#dataset-analysis)
4. [Model Comparison and Evaluation](#model-comparison-and-evaluation)
5. [Tech Stack](#tech-stack)
6. [Data Structure](#data-structure)
7. [Model Implementation](#model-implementation)
8. [Outcome](#outcome)
9. [Project Roadmap](#project-roadmap)

---

## Model Focus and Limitations

This project focuses on creating a machine learning model that uses wrist-mounted device data to detect hand tremors. Supervised learning techniques are applied to classify the data, exploring multiple methodologies. The device, referred to as Lachesis, uses the LSM6DS3 module on an Arduino Nano 33 IoT, retrieving data from a 3-axis accelerometer and gyroscope.

**Key Considerations:**
- **Focus**: Prioritize minimizing false negatives to ensure early detection of potential PD symptoms. False positives are more acceptable as they prompt further medical investigation.
- **Limitations**: 
  - The device cannot provide medical diagnoses but alerts users to symptoms for further consultation.
  - Due to the limited dataset, only a single source is used for training the model.
  - Computational efficiency and minimal resource use are prioritized to maintain device portability and battery life.

---

## Research Summary


A review of studies identified Bradykinesia, Gait Changes, and Hand Tremors as detectable symptoms of PD. Hand Tremors were selected for this project as:
1. They are one of the earliest symptoms of PD.
2. They can be detected solely using a wrist-mounted device.

A summary of the reviewed studies is available in the document [Reseach_Summary_PD.md](#). These studies validated the approach of using wearable devices for detecting PD symptoms.

---

## Dataset Analysis

The dataset used for this project contains data collected using three MPU9250 sensors on a participant's hand. It includes readings from:
- **3-axis Accelerometer**: (aX, aY, aZ)
- **3-axis Gyroscope**: (gX, gY, gZ)
- **3-axis Magnetometer**: (mX, mY, mZ)

Each reading corresponds to a label:
- **1**: Hand Tremor detected
- **0**: No Hand Tremor detected

### Data Preprocessing:
- Magnetometer readings (mX, mY, mZ) are excluded, as the Lachesis device does not support them.
- The final dataset features include:
  - Accelerometer: aX, aY, aZ
  - Gyroscope: gX, gY, gZ
  - Result (label): Binary value indicating hand tremor presence.

### Dataset Source:
- [Hand Tremor Dataset (Kaggle)](https://www.kaggle.com/datasets/aaryapandya/hand-tremor-dataset-collected-using-mpu9250-sensor?resource=download)

---

## Model Comparison and Evaluation

Various models were tested using a 70/30 Train/Test split. Each model was evaluated using precision, recall, F1-score, and confusion matrices for performance visualization. 

**Models Tested**:
- Logistic Regression
- Random Forest
- Decision Tree
- Support Vector Machine (SVM)
- Neural Network
- k-Nearest Neighbours (k-NN)

Hyperparameter tuning was applied to optimize model performance.

---

## Tech Stack

- **Programming Language**: Python
- **Libraries**: 
  - `pandas`: Data manipulation
  - `NumPy`: Array manipulation
  - `scikit-learn`: Model development and evaluation
  - `matplotlib`: Generating graphs for comparison
  - `seaborn`: Generating heat maps for comparison

---

## Data Structure

The dataset includes the following features:
- **aX, aY, aZ**: Accelerometer readings (integer)
- **gX, gY, gZ**: Gyroscope readings (integer)
- **Result**: Hand Tremor label (binary)

Excluded Features:
- **mX, mY, mZ**: Magnetometer readings

---

## Model Implementation

Detailed implementation of each model is documented in [Wrist_Mounted_Parkinsons_Disease_model.ipynb](#).

---

## Outcome

The results demonstrate high model accuracy in predicting hand tremors using accelerometer and gyroscope data. Key findings:
- **Top Performers**: Random Forest, Decision Tree, and Neural Network models achieved near-perfect accuracy.
- **Computational Efficiency**:
  - Random Forest and Decision Tree models are computationally efficient, making them suitable for resource-limited devices.
  - Neural Networks, while accurate, required more computational resources, making them less practical.
  - SVM and k-NN models were computationally expensive and less scalable.

**Preferred Model**: Random Forest is recommended for deployment due to its accuracy, robustness against overfitting, and computational efficiency.

**Caveat**: The dataset's high correlation between features and labels may have inflated accuracy scores. Validation on additional datasets is crucial to confirm model reliability.

---

## Project Roadmap

**Immediate Goals**:
- Validate the model on additional datasets to ensure performance consistency.
- Investigate the feasibility of obtaining new data tailored to wrist-mounted devices.

**Medium-Term Goals**:
- Integrate the model into the Lachesis device:
  - Develop a data pipeline for real-time sensor readings.
  - Implement model inference within the device.

**Long-Term Goals**:
- UI/UX Design:
  - Determine whether tremor detection is passive or user-initiated.
  - Define thresholds for triggering alerts (e.g., frequency and duration of tremors).

---