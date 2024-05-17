# Used to listen to speech and convert to text
import speech_recognition as sr

# Used to create a response and speak the response
from text_to_speech import text_to_speech


# Records user question and converts to text
def speech_to_text(start_queue, stop_queue):
    # The recogniser object
    recogniser = sr.Recognizer()

    # Checking if mic is currently on
    recording = False

    # Continuously checking for message to start recording
    while True:
        if not start_queue.empty():
            message = start_queue.get()

            if message == "stop_program":
                stop_queue.put(message)

            # Checking if message is to start recording and checking if mic is off
            if message == "start_recording" and not recording:

                # Set mic to on
                recording = True

                # Keep recording till a response is received
                while recording:

                    # Listening for audio
                    with sr.Microphone() as source:
                        # Used to adjust for any background sound
                        recogniser.adjust_for_ambient_noise(source, duration=0.2)

                        # User response stored in audio
                        audio = recogniser.listen(source)

                    try:
                        # Convert audio to text using Google Speech Recognition
                        text = recogniser.recognize_google(audio)
                        # Once audio is converted, notify pygame to change button text
                        stop_queue.put("recording_done")

                        # Sending the text to text_to_speech to give response to user
                        response = text_to_speech(text)

                        # Checking if there is any request to be put to stop_queue
                        if response is not None:
                            stop_queue.put(response)
                        else:
                            stop_queue.put("done")

                        recording = False

                    # Prints an error if audio is not understood
                    except sr.UnknownValueError:
                        stop_queue.put("error_understanding")
                        print("Could not understand audio, please try again.")

                    # For any other error
                    except sr.RequestError as e:
                        print(f"Error: {e}")
