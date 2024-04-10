# Used to listen to speech and convert to text
import speech_recognition as sr


# Records user question and converts to text
def speech_to_text(start_queue, stop_qu):

    # The recogniser object
    recogniser = sr.Recognizer()

    # Checking if mic is currently on
    recording = False

    # Continuously checking for message to start recording
    while True:
        if not start_queue.empty():
            message = start_queue.get()

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
                        stop_qu.put("recording_done")
                        recording = False
                        print(f"Recognized: {text}")

                    # Prints an error if audio is not understood
                    except sr.UnknownValueError:
                        print("Could not understand audio, please try again.")

                    # For any other error
                    except sr.RequestError as e:
                        print(f"Error: {e}")
