# Used to hide pygame message
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"

# Used for window
import pygame
import sys


# The class button creates an object for the pygame button.
# Takes in the x and y position of the button, the text to be displayed and the screen to be displayed on
# Parts of the button class are taken from following GitHub Repo – https://github.com/russs123/pygame_button
class Button:

    # Initiating the button object
    def __init__(self, x_pos, y_pos, button_text, screen):
        self.x = x_pos
        self.y = y_pos
        self.text = button_text
        self.screen = screen
        self.width = 250
        self.height = 80
        self.button_rect = pygame.Rect(self.x, self.y, self.width, self.height)

    # Draws the button onto the screen
    def draw_button(self):
        # Draw the button rectangle and border
        pygame.draw.rect(self.screen, pygame.Color("aquamarine3"), self.button_rect)
        pygame.draw.rect(self.screen, pygame.Color("cyan4"), self.button_rect, 3)

        # Add text to button
        font = pygame.font.SysFont('Constantia', 28)
        text_img = font.render(self.text, True, pygame.Color("black"))
        text_width, text_height = text_img.get_size()

        # Calculate x and y to center the text
        text_x = self.x + int(self.width / 2) - int(text_width / 2)
        text_y = self.y + int(self.height / 2) - int(text_height / 2)

        # Display the text
        self.screen.blit(text_img, (text_x, text_y))


# Draws the whole window and the buttons inside
def draw_window(screen, recording_button, exit_button):
    # Clear screen
    screen.fill(pygame.Color('white'))

    recording_button.draw_button()
    exit_button.draw_button()

    # Update the display
    pygame.display.flip()


# Opens the window that contains the buttons
def run_window(start_queue, stop_queue, queue):
    # Initialising the pygame module
    pygame.init()

    # Create the screen using width,height and title
    screen_width, screen_height = 400, 300
    screen = pygame.display.set_mode((screen_width, screen_height))
    pygame.display.set_caption("Voice Assistant")

    # Creating the recording and exit button
    recording_button = Button((screen_width - 250) // 2, 30, "Ask Question", screen)
    exit_button = Button((screen_width - 250) // 2, 170, "Exit", screen)

    # runs the pygame window
    while True:
        # Checking if any message in queue from recorder
        if not stop_queue.empty():
            message = stop_queue.get()

            # Checking if recording is done to change text on button
            if message == "recording_done":
                recording_button.text = "Processing..."
            # Checking if recorder had trouble converting speech to text
            elif message == "error_understanding":
                recording_button.text = "Please speak again.."
            # Checking if user response was provided
            elif message == "done":
                recording_button.text = "Ask question"
            elif message == "stop_program":
                # Send a message to end program
                queue.put("stop_program")

        # Checking through all pygame events
        for event in pygame.event.get():
            # Checking if close window button is clicked
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            # Checking if mouse is clicked
            elif event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                # Checking if mouse is clicked in button 1 position
                if recording_button.button_rect.collidepoint(event.pos):
                    # Change button text to recording
                    recording_button.text = "Recording..."
                    # Send message to voice record to listen for audio
                    start_queue.put("start_recording")

                # Checking if mouse is clicked in button 2 position
                elif exit_button.button_rect.collidepoint(event.pos):
                    # Send a message to end program
                    queue.put("stop_program")

        # Draw the buttons and screen
        draw_window(screen, recording_button, exit_button)
