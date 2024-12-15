# Activity Monitoring

## Feature Aim

The primary objective of the **Activity Monitoring** feature is to enable elderly individuals to track their daily activities. This system can be further developed to detect changes in gait, potential falls, and other mobility-related issues. By providing real-time monitoring and analysis, it aims to enhance the safety and well-being of elderly individuals.

## Folder Structure

```
├── 📁data
│   ├── augmented_info.npy
│   ├── data_augmentation.py
│   ├── data_preprocessing.ipynb
│   ├── demo_plot_data.csv
│   ├── eda.ipynb
│   ├── label_ids.npy
│   ├── label_to_id.npy
│   ├── README.md
│   ├── sequential_data.npy
│   └── sequential_label.npy
├── 📁literature_review
│   ├── image_1.png
│   ├── image_2.png
│   ├── image_3.png
│   ├── image.png
│   └── LITERATURE_REVIEW.md
├── 📁logs
│   └── [TensorBoard logs]
├── 📁models
│   ├── cnn_gru.keras
│   ├── cnn.keras
│   └── gru.keras
├── 📁scripts
│   ├── metrics.py
│   ├── model_usage.py
│   └── utils.py
├── activity_recognition.ipynb
├── environment.yml
└── README.md
```

- **data/**: Contains the dataset files required for training and testing the models, along with scripts for data processing.
- **models/**: Stores the trained models, which can be used for predictions.
- **logs/**: Contains logs generated during training, useful for visualisation with TensorBoard (not added to GitHub to keep the repository clean).
- **scripts/**: Includes Python scripts for model building, training, evaluation, and utility functions.
  - `model_usage.py`: Defines model architectures and training procedures.
  - `utils.py`: Contains utility functions for data loading and plotting.
  - `metrics.py`: Contains the `Metrics` class for calculating and storing performance metrics.
- **activity_recognition.ipynb**: The main Jupyter Notebook for running the training and evaluation pipeline.
- **environment.yml**: The YML file containing the necessary libraries to set up the environment.
- **README.md**: Provides an overview and instructions for the project.

## Project Status

The basic activity monitoring system has been implemented, achieving **92% accuracy** on the test dataset. The model can detect **11 different activities** found in the WEDA Fall and Activity Monitoring dataset. Training on an augmented dataset has enhanced the model's generalisation capabilities, making it more robust to variations in data.

## Assumptions

- The model has been trained on data from both young adults and elderly individuals.
- The model's accuracy may vary when predicting activities for elderly individuals exclusively, due to potential differences in movement patterns.

## Dataset Used

The **[WEDA Fall and Activity Monitoring Dataset](https://github.com/joaojtmarques/WEDA-FALL)** was used for training and evaluating the models.

- **Dataset Description**: The WEDA dataset contains sensor data collected from wearable devices during various activities and simulated falls. It includes data from both young adults and elderly individuals, providing a diverse range of movement patterns.
- **Activities Covered**: The dataset includes 11 different activities, such as walking, sitting, standing, lying down, ascending stairs, descending stairs, and various types of falls.

*Note: Please refer to the [dataset's official documentation](https://github.com/joaojtmarques/WEDA-FALL) for more detailed information.*

## Future Considerations

- **Hyperparameter Tuning**: Perform more extensive hyperparameter tuning to optimise model performance.
- **Advanced Data Augmentation**: Implement a more robust data augmentation procedure to simulate real-world variations and enhance the model's ability to generalise.
- **Real-World Testing**: Validate the model's performance in real-world scenarios with live data from elderly users.
- **Integration with Devices**: Explore integration with wearable devices for real-time activity monitoring and alerts.

## Running on Local Machine

**Note**: The model was developed and trained on a Mac. Steps may vary slightly for Windows or Linux systems.

### Prerequisites

- Python 3.x
- Required Python libraries listed in `environment.yml`

### Steps

1. **Clone the Repository**

   ```bash
   git clone https://github.com/Redback-Operations/redback-senior-tech.git
   ```

2. **Navigate to the Activity Monitoring Folder**

   ```bash
   cd redback-senior-tech/data_science/activity_monitoring
   ```

3. **Set Up the Environment**

   Install the dependencies using the `environment.yml` file:

   ```bash
   conda env create -f environment.yml
   conda activate <your_environment_name>
   ```

4. **Prepare the Dataset**

   - Ensure that the dataset is placed in the `data/` folder.
   - The dataset should follow the same format as the WEDA Fall and Activity Monitoring dataset.
   - Alternatively, the processed dataset is stored in `.npy` files in the `data/` folder.

5. **Run the Main Script**

   - Open the `activity_recognition.ipynb` notebook in Jupyter Notebook or JupyterLab.
   - Run the notebook cells sequentially to execute the training and evaluation pipeline.

6. **Using Pre-trained Models**

   - Pre-trained models are stored in the `models/` folder.
   - You can load these models to make predictions without retraining.
   - Example:

     ```python
     from tensorflow.keras.models import load_model

     model = load_model('models/cnn.keras')
     predictions = model.predict(your_input_data)
     ```

7. **Retraining the Model**

   - To retrain the model, you need a dataset similar in format to the WEDA Fall dataset.
   - Place your dataset files in the `data/` folder, ensuring they are named appropriately.
   - Run the `activity_recognition.ipynb` notebook to train the model on your data.

### Notes

- **Compatibility**: Ensure that all paths and file permissions are correct, especially when running on Windows or Linux machines.
- **Environment**: It's recommended to use a virtual environment to manage dependencies.

---