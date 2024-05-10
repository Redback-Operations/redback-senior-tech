# Voice Assistant Feature for Elderly Care Wearable Device

## Feature AIM
The primary objective of integrating a voice assistant feature into the elderly care wearable device is to provide essential assistance to elderly individuals with accessibility challenges. This feature aims to offer responses to basic inquiries, provide health-related information, and assist users in managing their daily schedules and health concerns through voice commands.

## Folder Structure
The folder contains the python files required to run the feature. Further, the ```main.py``` file can be run directly to use the voice assistant. The ```train_model.py``` file can be run independently to retrain the model and save it. Finally, the ```venv``` folder contains all the required files to run the feature.

```
Voice Assistant
├─ LICENSE
├─ README.md
├─ docs
│  └─ Voice Assistant Requirement Documentation.pdf
├─ generate_response.py
├─ intents.json
├─ main.py
├─ models
│  ├─ voice_assistant_model.keras
│  ├─ voice_assistant_model_intents.pkl
│  └─ voice_assistant_model_words.pkl
├─ pygame_win.py
├─ speech_to_text.py
├─ text_to_speech.py
├─ train_model.py
└─ venv
```

## Project Status
- **Primary Features Implemented:** Providing responses to basic queries regarding time and weather, assisting in querying symptoms.
- **Secondary Features to be Implemented:** Providing guidance on mental health matters, enabling voice-initiated calls and messages, conducting periodic health assessments.

## Future Considerations
- Expanding the range of questions the voice assistant can address to encompass a wider array of topics.
- Incorporating multilingual support to facilitate communication for users of diverse linguistic backgrounds.
- Ensuring compatibility with emerging healthcare technologies to stay up-to-date with advancements in the field.
- Collaborate with the Software and App Development and Backend Development teams to incorporate the feature to the wearable device and futher implement the secondary features.

## Compliance and Safety
Adherence to regulatory standards and ensuring user safety are vital considerations for the implementation of this feature:
- Compliance with healthcare privacy regulations to safeguard sensitive user data.
- Implementation of robust security measures to securely store and transmit user information.
- Ensuring the voice assistant delivers appropriate responses and refrains from responding to inappropriate inquiries.

## How to run the project on Local Machine
To run the project on a local machine, follow these steps:

1. Clone the repository from GitHub
2. Navigate to the ```Voice Assistant``` directory
3. To retrain a model, run the ```train_model.py``` script
4. Run the ```main.py``` script to start the voice assistant feature
