
# Fall Detection in Elderly Wearable Tech

This project aims to develop a fall detection model using accelerometer and gyroscope data collected from wearable devices. The model employs a Convolutional Neural Network (CNN) to distinguish falls from typical movements, correcting data imbalance with SMOTE and assuring resilience for real-time monitoring in elderly care. 

## Table of Contents
1. [Project Structure](#project-structure)
2. [Features](#features)
3. [Tech Stack](#tech-stack)
4. [Installation](#installation)
5. [Usage](#usage)
6. [Project Roadmap](#project-roadmap)

## Folder Structure
```
WEDA-FALL
├── dataset
│   ├── fall_timestamps.csv
│   └── 50hz/
│       ├── F01/ (Folders for each fall scenario)
│       │   ├── U01_R01_accel.csv (Accelerometer data)
│       │   ├── U01_R01_gyro.csv (Gyroscope data
│       │   └── ... (More files)
│       ├── F02/
│       └── ...
├── final_merged_dataset_with_users_fall.csv
└── README.md
```
## Dataset Setup Instructions

To run this project, you need to set up the dataset and output directories.

1. **Dataset Directory**:
   - Create a directory where your dataset will be stored.
   - Inside this directory, include the subdirectories for the sensor data (e.g., `50hz/`) and the `fall_timestamps.csv` file.
   - Update the script with the correct path to your dataset folder. Example:
     ```
     fall_timestamps_path = '/path/to/dataset/fall_timestamps.csv'
     base_dir = '/path/to/dataset/50hz/'
     ```

2. **Output Directory**:
   - Create a directory where the final merged dataset will be saved.
   - Update the script with the correct output path. Example:
     ```
     final_output_path = '/path/to/output/final_merged_dataset_with_users_fall.csv'
     ```

Make sure the paths in the code match your folder structure before running the project.
## Project structure

The project has numerous components:

* The data folder contains raw sensor data (accelerometer and gyroscope).
* A collection of Jupyter notebooks for data exploration,pre-processing, and model training.
* Trained models and outcomes, including performance indicators like confusion matrices and accuracy graphs.
* A README file contains extensive project information.

## Features
- Merges accelerometer and gyroscope data based on timestamps for each user session.
- CNN-based classification of falls vs non-falls using sensor data.
- SMOTE applied to handle data imbalance.
- Visualizations of sensor data and model performance (accuracy, loss curves).

## Tech Stack
- **Python** for scripting and model building.
- **TensorFlow/Keras** for building deep learning models.
- **Scikit-learn** for preprocessing, model evaluation, and SMOTE.
- **Matplotlib/Seaborn** for visualizations.

## Installation
To run this project locally, take the following steps:

* Clone the repository on your local workstation.
* Create a Python virtual environment.
* Install the dependencies specified in the given requirements file.
* Before running the code, make sure that your data is in the correct folder structure.

## Usage

* Start by cleaning, merging, and labelling the sensor data.
* Run the model training notebook to train the CNN model using the preprocessed data.
* Evaluate the model with the validation set to get performance measures like accuracy and loss.
* Visualise the results using the accompanying graphs of model accuracy, loss curves, and confusion matrices.

## Project Roadmap

* Initial Phase: Collecting, cleaning, and integrating sensor data from numerous sessions.
* Mid-Phase: Creating and training the CNN model, as well as addressing class imbalance with SMOTE.
* The final phase involves validating the model, visualising the results, and preparing for possible real-time integration with wearable devices.



