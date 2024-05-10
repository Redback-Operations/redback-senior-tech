# Fall Detection Feature for Elderly Care Wearable Device

## Feature AIM
The primary objective of integrating a fall detection feature into an elderly wearable device is to promptly detect falls during activities such as walking or climbing stairs and notify emergency contacts. The feature also aims to detect abnormalities like limping due to injuries during walking and provide timely alerts to ensure swift assistance.

## Folder Structure
Fall Detection
│
├── data
│  └── acc_gyr.csv
├── docs
│  ├── requirements.txt
│  └── Fall detection requirement document.pdf
├── models
│  └── fall_detection_model.keras
├── fall_detection.ipynb
├── LICENSE
└── README.md

## Project Status
- **Primary Features Implemented:** Detection of fall using an accelerometer and a gyroscope.
- **Secondary Features to be Implemented:** Activity monitoring of the elderly, notification to the elderly and emergency contacts in case of abnormal walking patterns like limping.


## Assumptions
1. The fall detection model can be generalised for the elderly.
2. The model can generalize to detect falls in elderly individuals outside specified height ranges.
3. Readings taken with the sensor positioned around the wrist are assumed to be comparable to those taken around the chest.

## Future Considerations
- Explore advanced AI algorithms to enhance fall detection accuracy.
- Implement proactive health monitoring features to detect early signs of potential health issues beyond falls.
- Incorporate intuitive user interfaces based on ongoing user feedback to optimize usability.
- Acquire a larger dataset, retrain the model, and conducting hyperparameter tuning to attain optimal performance in fall detection.
- Collaborate with the Software and App Development and Backend Development teams to incorporate the feature to the wearable device.

## Compliance and Safety
Adherence to regulatory standards and ensuring user safety are vital considerations for the implementation of this feature:
- Compliance with healthcare privacy regulations to safeguard sensitive user data.
- Implementation of robust security measures to securely store and transmit user information.

## How to run the project on Local Machine
To run the project on a local machine, follow these steps:

1. Clone the repository from GitHub
2. Navigate to the ```Fall detection``` directory
3. Install the required dependencies using ```pip install -r docs/requirements.txt```
4. To run the project, run the ```fall_detection.ipynb``` file
5. To retrain the model with a different dataset, add the dataset into the ```/data``` directory. The trained models are stored in the ```/models``` directory