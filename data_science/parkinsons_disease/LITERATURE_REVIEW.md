<a name="br1"></a> 

## DOCUMENTATION AND ANALYSIS: PARKINSON'S PREDICTION MODELS AND INTEGRATION WITH REDBACK WEARABLE DEVICE

**INTRODUCTION**

Parkinson's disease (PD) is a progressive neurodegenerative disorder that affects motor control,
speech, and cognitive function. Early prediction of Parkinson’s can greatly improve patient
outcomes by enabling earlier interventions, slowing disease progression, and improving the
quality of life. With advancements in machine learning and wearable technology, it is possible
to detect early motor symptoms such as tremors, bradykinesia, and rigidity, which are key
indicators of Parkinson's. Wearable devices, offer a promising avenue for continuous monitoring of motor functions.
These devices can gather sensor data related to movement, which is critical for Parkinson’s
prediction. The goal of this document is to explore the integration of Parkinson’s prediction
models with the Redback wearable device, focusing on sensor data collection, predictive model
integration, and IoT solutions.

**LITERATURE REVIEW: PARKINSON'S PREDICTION MODELS**

**Prediction Models**

Parkinson's prediction models are typically built using machine learning and deep learning
techniques. Common machine learning algorithms include Support Vector Machines (SVM),
Random Forest, and k-Nearest Neighbors (k-NN). These models focus on extracting key
features such as tremor frequency, bradykinesia, and irregular gait from sensor data to predict
the onset or progression of Parkinson’s disease.
Deep learning models, such as Convolutional Neural Networks (CNNs) and Recurrent Neural
Networks (RNNs), have shown improvements in handling temporal and spatial data such as
gait patterns and motor movements. CNNs can be particularly useful in analyzing movement
data from sensors to detect subtle signs of Parkinson’s that traditional models may miss.

**Datasets**

Datasets used in Parkinson's prediction typically include sensor data, clinical observations, and
patient-reported symptoms. Some popular datasets include:

- **mPower**: A dataset from the Parkinson’s mHealth study that includes sensor data from smartphones and wearables.

- **UCI Parkinson's Telemonitoring Dataset**: This dataset captures motor function measurements.

- **Daphnet Freezing of Gait Dataset**: Data captured from wearable sensors monitoring the gait of Parkinson's patients.



<a name="br2"></a> 

**Significance of Sensor Data**

Sensor data is crucial in Parkinson’s prediction because it captures motor irregularities in real-
time, which are key indicators of disease progression. Data such as acceleration, angular
velocity (from gyroscopes), and heart rate can help detect motor symptoms like tremor and
instability. By analysing this sensor data, models can predict the likelihood of Parkinson’s onset
or progression.

**Feature Extraction**

Key features extracted from sensor data include:

- **Tremor frequency**: Oscillatory movements detected by accelerometers.

- **Gait speed and variability**: Measured using wearable sensors to detect bradykinesia.

- **Postural instability**: Balance issues detected by gyroscopes in wearables.

**REDBACK WEARABLE DEVICE: POTENTIAL FOR PARKINSON’S PREDICTION**

**Redback Wearable Sensors**

The Redback wearable device is equipped with a range of sensors, including:

 **Accelerometer**: Measures linear acceleration, essential for detecting tremors and
movement irregularities.

- **Gyroscope**: Tracks angular velocity, helping to detect changes in posture and balance.

- **Heart Rate Monitor**: Monitors cardiovascular health, as Parkinson’s can also affect
the autonomic nervous system.

- **Gait Sensors**: These could be embedded or derived from accelerometer data to monitor
walking patterns.

**Potential Data for Parkinson’s Prediction**

Sensor data from the Redback wearable device, such as tremor frequency and gait variability,
can be used to predict Parkinson's. For instance:



- **Tremors**: Accelerometers can capture minute tremors in the wrists, often one of the
earliest motor symptoms of Parkinson’s.

- **Gait Analysis**: The accelerometer and gyroscope can measure step length, gait speed,
and variability in movement, which are critical for detecting bradykinesia.

- **Postural Instability**: Gyroscope data can help identify balance issues, which are
common in later stages of Parkinson's.



<a name="br3"></a> 

**PROOF OF CONCEPT (POC) FOR INTEGRATING PREDICTION MODEL**

**Integration Process**

To integrate the prediction model with the Redback wearable, the process would include:

1\. **Sensor Data Collection**: Continuous collection of sensor data from the device,
capturing movement, tremors, and gait patterns.

2\. **Preprocessing**: Raw data would be filtered to remove noise and segmented into time
windows for analysis.

3\. **Feature Extraction**: Key features such as tremor amplitude, gait speed, and step
variability would be extracted.

4\. **Prediction Model**: The extracted features would be fed into a machine learning model
(e.g., Random Forest) or a deep learning model (CNN) to predict Parkinson’s onset or
severity.

**Challenges**

- **Data Accuracy**: Sensor data may suffer from inaccuracies due to noise, requiring
robust filtering and preprocessing.

- **Real-Time Processing**: The wearable device must be capable of transmitting data in
real-time to a centralized server, which may require optimized IoT protocols.

- **Battery Life**: Continuous monitoring can drain the wearable device’s battery, requiring
careful optimization of data collection intervals.

**PLANNED WORK: DEVELOPMENT AND INTEGRATION**

**Steps for Integration**

1\. **Data Collection**: Begin by collecting real-time sensor data from wearables.

2\. **Model Training**: Train machine learning models on a dataset combining data from
Redback wearables and existing Parkinson’s datasets (such as mPower).

3\. **Testing and Validation**: Validate the model using unseen data to ensure it generalizes
well and can predict early signs of Parkinson’s accurately.

4\. **Integration with IoT**: Implement a system where data is sent from the wearable to a
cloud-based platform for real-time analysis.

**Challenges**

- **Sensor Calibration**: Ensuring accurate sensor calibration to avoid false predictions.

- **Data Transmission**: Manage large volumes of data transfer without significant delays
or data loss.



<a name="br4"></a> 

**IOT-BASED SOLUTION FOR BEST-CASE PARKINSON’S PREDICTION**

**IoT Infrastructure**

The ideal IoT solution would involve:


- **Cloud Storage and Processing**: Wearable data would be transmitted to a cloud server
for processing.

- **Real-Time Prediction**: The model would run on the cloud, processing incoming data
in real-time and providing alerts if Parkinson’s symptoms are detected.

- **Low Latency**: To ensure minimal delay, data processing pipelines would need to be
optimized for low latency, ensuring quick feedback to the user or healthcare provider.

**Enhancing Prediction**

- **Edge Computing**: Integrating edge computing into the wearable could allow some
level of preprocessing and prediction to occur on the device itself, reducing the data
transfer burden and latency.


- **Continuous Learning**: The system could employ continuous learning, updating the
model with new data to improve prediction accuracy over time.

**CONCLUSION**

The integration of Parkinson’s prediction models with the Redback wearable device holds
significant promise for early detection and continuous monitoring of the disease. By leveraging
real-time sensor data and robust machine learning models, it is possible to offer patients and
healthcare providers valuable insights into disease progression. The integration of IoT-based
solutions would further enhance the usability and effectiveness of the system, creating a real-
time feedback loop for Parkinson’s disease management.

**REFERENCES**

*1. Zhang, H, Song, C, Rathore, AS, Huang, M-C, Zhang, Y & Xu, W 2021, ‘mHealth*
*Technologies Towards Parkinson’s Disease Detection and Monitoring in Daily Life: A*
*Comprehensive Review’, IEEE Reviews in Biomedical Engineering, vol. 14, Institute of*
*Electrical and Electronics Engineers (IEEE), pp. 71–81.*

*2. Williamson, JR, Telfer, B, Mullany, R & Friedl, KE 2021, ‘Detecting Parkinson’s*
*Disease from Wrist-Worn Accelerometry in the U.K. Biobank’, Sensors, vol. 21,*
*Multidisciplinary Digital Publishing Institute, no. 6, pp. 2047–2047.*


