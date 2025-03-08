import speech_recognition as sr
import random
import pyttsx3
import webbrowser
import serial
import pywhatkit


robot_name = 'control'

hi_words_u = ['hi', 'hello', 'namaskar']
bye_words_u = ['bye', 'tata', 'alvida']
hi_words = ['hi there', 'hello there', ]
bye_words = ['bye bye', 'cya' , 'sayonara']
r_u_there = ['are you there', 'you there']
jokes = [' ',' ',' ']    

engine = pyttsx3.init()
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[0].id)
engine.setProperty('rate', 170)
listener = sr.Recognizer()

def listen():
    try:
        with sr.Microphone() as source:
            print("<<=TALK=>>")
            voice = listener.listen(source)
            command = listener.recognize_google(voice).lower()
            print(command)

            if (command.split(' ')[0] == robot_name):
                print("<<=REPLYING=>>") 
                process(command)  

    except Exception as e:
        print(f"Error: {e}") 


def process(words):
    print(words) 
    word_list = words.split(' ')[1:]

    if word_list[0] == 'above':
       talk("adjusting up")
		
    elif word_list[0] == 'down':
        talk("adjusting down")

    elif word_list[0] == 'forward':
        talk("moving forward")

    elif word_list[0] == 'backward':
        talk("moving backward")

    elif word_list[0] == 'left':
        talk("moving left")

    elif word_list[0] == 'right':
        talk("moving right")

    for word in word_list:
        if word in hi_words_u:
            talk(random.choice(hi_words))
        elif word in bye_words_u:
            talk(random.choice(bye_words))

def talk(sentence):
    engine.say(sentence)
    engine.runAndWait()

while True:
    listen()
