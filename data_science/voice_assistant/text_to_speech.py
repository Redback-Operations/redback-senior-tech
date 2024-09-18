# Used to Speak the response
import time
import os

# Used to get response from user input
from generate_response import get_response


# Function that will speak the response to user
def speak_response(response):
    time.sleep(2)
    os.system(f'say "{response}"')


# Function that will keep the voice assistant running
def text_to_speech(message):
    # Getting the response using user input
    response = get_response(message)

    # Checking if there is any request to end program
    if response.split()[-1] == "stop":
        # Speaking response and sending request to end program
        speak_response(f"{' '.join(response.split()[:-1])}")
        return "stop_program"

    # Speak response back to user
    speak_response(f"{response}")
