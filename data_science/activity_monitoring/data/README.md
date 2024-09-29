# README for the Data Folder

## Overview

This folder contains scripts and Jupyter notebooks for processing the WEDA Fall and Activity Monitoring dataset, as well as any other new datasets you may want to use. The pre-processed data files stored in this folder can be used directly to retrain the activity monitoring model without additional processing.

## Contents

- **Scripts and Notebooks**: 
  - `data_augmentation.py`: Script for augmenting the dataset to increase its size and variability.
  - `data_preprocessing.ipynb`: Jupyter notebook for processing the dataset. This includes steps like cleaning, normalisation, and sequential data generation.
  - `eda.ipynb`: Exploratory Data Analysis notebook for understanding the dataset and visualising various features.

- **Pre-processed Data**:
  - `augmented_info.npy`: Numpy array containing information about the augmented dataset.
  - `label_ids.npy`: Numpy array mapping activity labels to their corresponding IDs.
  - `label_to_id.npy`: Numpy array mapping activity labels to their corresponding numerical IDs.
  - `sequential_data.npy`: Numpy array containing the processed sequential data, ready for model training or retraining.
  - `sequential_label.npy`: Numpy array containing the labels for the sequential data.

## Using the Scripts

### Processing a New Dataset
If you want to process a new dataset, you can modify and use the provided scripts and notebooks (`data_augmentation.py` and `data_preprocessing.ipynb`) to follow a similar workflow. Ensure your new dataset is in a compatible format before starting.

### Re-processing the WEDA Dataset

1. **Download the WEDA 50Hz Dataset**: 
   - Download the 50Hz folder from the [WEDA Fall and Activity Monitoring Dataset](https://github.com/joaojtmarques/WEDA-FALL).

2. **Place the Dataset in the Data Folder**:
   - Place the downloaded `50Hz` folder directly into this `data/` directory.

3. **Run the Preprocessing Script**:
   - Open `data_preprocessing.ipynb` and follow the steps to process the WEDA dataset with different settings, such as custom data augmentation or different sampling rates.

## Notes

- The pre-processed `.npy` files can be used directly with the model training scripts without the need for reprocessing, saving time and computational resources.
- If you make changes to the dataset or processing settings, ensure that the corresponding `.npy` files are updated to reflect these changes.

This structure and approach will help you to easily modify, extend, and retrain models with new data or settings as needed.