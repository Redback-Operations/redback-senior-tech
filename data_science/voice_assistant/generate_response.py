# Used to create the model that generates response based on input
from neuralintents.assistants import BasicAssistant

# Used to do web scrapping to get the weather details
from bs4 import BeautifulSoup
import requests

# Used to extract city names from text
import locationtagger


# Used to perform Google search and get Soup var
def get_request(query):
    req = requests.get(f'https://www.google.com/search?q={query}')

    return BeautifulSoup(req.content, 'html.parser')


# The function used to get weather updates for the city
def get_weather(input_text):

    # Checking if user input contains any city name to get weather for
    get_location = locationtagger.find_locations(text=input_text)
    city = "Melbourne" if len(get_location.cities) == 0 else get_location.cities[0]

    # Used to scrape through the content to get temperature and details
    soup = get_request(f'{city}+weather')

    # Extracting the temperature and condition details
    temp = soup.find("div", attrs={"class": "BNeawe iBp4i AP7Wnd"}).text
    conditions = soup.find("div", attrs={"class": "BNeawe tAd8D AP7Wnd"}).text.split("\n")[1]

    # Returning the weather update
    return f"Sure, following is the weather update for {city} city. The current temperature is {temp}. And the conditions are {conditions}."


# The function used to get time for a city
def get_time(input_text):

    # Checking if user input contains any city name to get time for
    get_location = locationtagger.find_locations(text=input_text)
    city = "Melbourne" if len(get_location.cities) == 0 else get_location.cities[0]

    # Used to scrape through the content to get temperature and details
    soup = get_request(f'{city}+time')

    # Extracting the temperature and condition details
    time = soup.find("div", attrs={"class": "BNeawe iBp4i AP7Wnd"}).text
    date = soup.find("div", attrs={"class": "BNeawe tAd8D AP7Wnd"}).text.split('\n')[0]

    # Returning the weather update
    return f"The time in {city} is {time} on {date}."


# The function used to end the program
def goodbye():
    return " stop"


# Creates an object of the Assistant to be used to get the response
def get_response(user_input):

    # Getting the response using the assistant model
    return assistant.process_input(user_input)


# Creating the object
assistant = BasicAssistant('intents.json',
                           method_mappings={
                               "weather": (get_weather, "input_text"),
                               "time": (get_time, "input_text"),
                               "goodbye": goodbye },
                           model_name="models/voice_assistant_model")

# Loading the model
assistant.load_model()
