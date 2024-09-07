# Used to create the model that generates response based on input
from neuralintents.assistants import BasicAssistant

# Creating the object
assistant = BasicAssistant('intents.json', model_name="models/voice_assistant_model")

# Training the model
assistant.fit_model(epochs=50)
assistant.save_model()
