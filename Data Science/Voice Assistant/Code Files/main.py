import multiprocessing as mp
from pygame_win import run_window
from speech_to_text import speech_to_text
import sys

if __name__ == "__main__":

    # Creating multiprocessing queues for communication between functions
    queue = mp.Queue()  # Communication between pygame window and main function
    start_queue = mp.Queue()  # Communication to start recording
    stop_queue = mp.Queue()  # Communication to stop recording

    # Creating the multiprocessing process for the pygame and speech to text windows
    window_process = mp.Process(target=run_window, args=(start_queue, stop_queue, queue,))
    window_process.start()

    speech_process = mp.Process(target=speech_to_text, args=(start_queue, stop_queue,))
    speech_process.start()

    # Keep looping till user quits
    while True:
        # Looping through messages to check if program needs to end
        if not queue.empty():
            message = queue.get()

            if message == "stop_program":
                # End the processes
                window_process.terminate()
                speech_process.terminate()
                sys.exit()
            else:
                queue.put(message)
