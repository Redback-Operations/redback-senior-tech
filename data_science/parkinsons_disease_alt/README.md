
# Parkinson's Disease (PD) Wrist-Mounted Prediction Model

## Model Objective:
The objective of this project is to build a model that specifically utilises data retrieved from a wrist-worn device to determine if the wearer of the device is experiencing hand tremors; a potential indicator of Parkinson's Disease.

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

Unlike models previously built for the Lachesis device, this model is specifically built to utilise retrievable data from a wrist-worn device. Supervised learning techniques will be used to classify measurements as Hand Tremors and a variety of methodologies will be explored.

**Focus:**
- Test and evaluate various machine learning algorithms to create a reliable model that can classify measurments as Hand Tremors.
- Ensure model remains in line with the capabilities of the Lachesis wrist-worn device.

**Limitations:**
- Only the LSM6DS3 module on Arduino Nano 33 IoT will be utilised to retrieve data (Retrievable data: 3-axis accelerometer, 3-axis gyroscope).
- Due to the limited availability of applicable datasets, only a single dataset was found and will be used to build the model.

---

## Research Summary

A variety of studies were investigated when determining the validity of detecting Parkinson's Disease via a wrist-mounted device. The major symptoms detectable were determined to be Bradykinesia, Gait changes and Hand Tremors. An brief summary of the studies that were reviewed can be found in the document labelled 'Research Summary - PD.pdf'.

Based on the information reviewed, Hand Tremors were selected as the best indicator of Parkinson's Disease for the Lachesis device, due to it being one of the earliest symptoms presents and also being detectable solely via a wirst-mounted device.

---

## Dataset Analysis

Due to the limited availability of datasets available online, only a single source could be located that utilsies a 3-axis accelerometer and 3-axis gyroscope.

The dataset utilised contains data retieved from 3 MPU9250 sensors mounted on a wearers hand. 
The readings are taken from the below sensors:
- 3-axis accelerometer (aX, aY, aZ)
- 3-axis gyroscope (gX, gY, gZ)
- 3-axis magnetometer (mX, mY, mZ)
Each reading is taken simultaniously and is associated with a label that denotes a shaking hand (1) or a stable hand (0)

As the 3-axis magnetometer is not currently incorporated into the Lachesis these readings will be excluded from the model.

The dataset can be located at: https://www.kaggle.com/datasets/aaryapandya/hand-tremor-dataset-collected-using-mpu9250-sensor?resource=download

---

## Model Comparison and Evaluation

Different models will be tested and compared. The models include:
- Logistic Regression
- Support Vector Machine (SVM)
- Random Forest
- Decision Tree
- Neural Network
- k-Nearest Neighbours (k-NN)

Each model will be ran using a 70/30 Train/Test split and evaluated by comapring precision, recall, f1-score and support. A confusion matrix will also be used for better visualisation of performance.

---

## Tech Stack

- Python: Primary programming language
- pandas: Importing datasets
- scikit-learn: Generating models and comparing performance

---

## Data Structure

The dataset in use is named HandTremorDataset.csv and contains the following features that will be used:
- aX: Accelerometer reading on X-axis (integer value)
- aY: Accelerometer reading on Y-axis (integer value)
- aZ: Accelerometer reading on Z-axis (integer value)
- gX: Gyroscope reading on X-axis (integer value)
- gY: Gyroscope reading on Y-axis (integer value)
- gZ: Gyroscope reading on Z-axis (integer value)
- Result: Value to determine presense of Hand Tremor (Binary value)

The following features are removed from the dataset:
- mX: Magnetometer reading on X-axis (integer value)
- mY: Magnetometer reading on Y-axis (integer value)
- mZ: Magnetometer reading on Z-axis (integer value)

---

## Model Implementaton

Talka bout the methodologies used in the model implementation

---

## Outcome

Summarise findings from the model

---

## Project Roadmap

Explore future cosiderations for the model