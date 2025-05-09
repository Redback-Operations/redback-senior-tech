# This module creates responses based on user input using the pre-trained assistant model.
# It also handles specific tasks like retrieving weather or time information.

# Used to create the model that generates response based on input
from neuralintents.assistants import BasicAssistant

# Used to do web scrapping to get the weather details
from bs4 import BeautifulSoup
import requests

# Used to extract city names from text
import locationtagger

# Global variable to hold the most recent user input.
last_input = ""

# Used to perform Google search and get Soup var
def get_request(query):
    req = requests.get(f'https://www.google.com/search?q={query}')

    return BeautifulSoup(req.content, 'html.parser')


# The function used to get weather updates for the city
def get_weather(input_text):

    # Checking if user input contains any city name to get weather for
    get_location = locationtagger.find_locations(text=input_text)
    city = "Melbourne" if len(get_location.cities) == 0 else get_location.cities[0]
    
    soup = get_request(f'{city}+weather')
    
    # Try to extract temperature information
    temp_div = soup.find("div", attrs={"class": "BNeawe iBp4i AP7Wnd"})
    if not temp_div:
        return f"Sorry, I couldn't fetch the temperature for {city}."
    temp = temp_div.text

    # Try to extract condition details
    condition_div = soup.find("div", attrs={"class": "BNeawe tAd8D AP7Wnd"})
    if not condition_div:
        return f"Sorry, I couldn't extract weather conditions for {city}."
    condition_text = condition_div.text
    conditions = condition_text.split("\n")[1] if "\n" in condition_text else condition_text

    return f"Sure, here is the weather update for {city}. The temperature is {temp} and the conditions are {conditions}."

# The function used to get time for a city
def get_time(input_text):

    # Checking if user input contains any city name to get time for
    get_location = locationtagger.find_locations(text=input_text)
    city = "Melbourne" if len(get_location.cities) == 0 else get_location.cities[0]

    # Used to scrape through the content to get temperature and details
    soup = get_request(f'{city}+time')

    # Try to extract the time information
    time_div = soup.find("div", attrs={"class": "BNeawe iBp4i AP7Wnd"})
    if not time_div:
        return f"Sorry, I couldn't fetch the time for {city}."
    time_info = time_div.text
    
    # Try to extract the date information
    date_div = soup.find("div", attrs={"class": "BNeawe tAd8D AP7Wnd"})
    if not date_div:
        return f"Sorry, I couldn't extract the date details for {city}."
    date_text = date_div.text
    date = date_text.split('\n')[0] if "\n" in date_text else date_text

    return f"The time in {city} is {time_info} on {date}."


# The function used to end the program
def goodbye():
    return " stop"


# Creates an object of the Assistant to be used to get the response
def get_response(user_input):

    global last_input
    last_input = user_input  # store the input so that lambda wrappers can access it
    # Getting the response using the assistant model
    return assistant.process_input(user_input)


# Creating the object
# We use lambda wrappers in the method_mappings to pass the globally stored last_input.
assistant = BasicAssistant('intents.json',
                           method_mappings={
                               "weather": lambda: get_weather(last_input), 
                               "time": lambda: get_time(last_input), 
                               "goodbye": lambda: goodbye() },
                           model_name="models/voice_assistant_model")

# Loading the model
assistant.load_model()
