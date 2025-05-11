# This module is responsible for converting text responses into spoken output.
# A caching mechanism has been implemented to store responses for repeated queries, ensuring faster response times.
import time
import os
import subprocess
# Function to generate a response using our NLP model
from generate_response import get_response

# Global cache to store previously generated responses keyed by the input message.
response_cache = {}

# Function that will speak the response to user
def speak_response(response):
    time.sleep(2)
    subprocess.run(['say', response], check=True)


# Function that will keep the voice assistant running
def text_to_speech(message):
    # Check for cached response to avoid reprocessing
    if message in response_cache:
        response = response_cache[message]
        print("Cache hit: Returning cached response.")
    else:
        response = get_response(message)
        response_cache[message] = response
        print("Cache miss: Generated new response and added it to the cache.")

    # Checking if there is any request to end program
    if response:
    # Check if response ends with "stop" keyword
      if response.split()[-1] == "stop":
        speak_response(' '.join(response.split()[:-1]))
        return "stop_program"
      else:
        speak_response(response)
    else:  
        speak_response("Sorry, I couldn't understand or generate a response.")