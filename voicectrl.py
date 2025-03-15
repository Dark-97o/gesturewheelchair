import speech_recognition as sr   
import random                   
import pyttsx3                    
import webbrowser               
import serial                
import pywhatkit                 

robot_name = 'control'

hi_words_u = ['hi', 'hello']
bye_words_u = ['bye', 'tata']
hi_words = ['hi there', 'hello there', 'whats up']
bye_words = ['bye', 'see you']

engine = pyttsx3.init()
voices = engine.getProperty('voices')
engine.setProperty('voice', voices[0].id)  
engine.setProperty('rate', 150)            
listener = sr.Recognizer()                

try:
    port = serial.Serial("COM5",9600)
    print("Status: Connected")
except:
    print("Status: Disconnected")

def listen():
	try:
		with sr.Microphone() as source:                         # Microphone Access
			print("<<=INPUT=>>")
			voice = listener.listen(source)                     # Microphone Listener
			command = listener.recognize_google(voice).lower()  # Google API
			command = command.lower()                          
			print(command)

			if (command.split(' ')[0] == robot_name):
				print("<<=PROCESSING=>>")
				process(command)                 # call process funtion to take action
	except:
		pass

def process(words):
	print(words)
	word_list = words.split(' ')[1:]
	if word_list[0] == 'uppercut':
		port.write(b'U')

	elif word_list[0] == 'smash':
		port.write(b's')

	elif word_list[0] == 'punch':
		port.write(b'p')

	for word in word_list:
		if word in hi_words_u:
			port.write(b'h')
			talk(random.choice(hi_words))

		elif word in bye_words_u:
			talk(random.choice(bye_words))
			port.write(b'h')


def talk(sentence):
	engine.say(sentence)
	engine.runAndWait()

while True:
    listen()  # Listens One Time may not func2tion properly
	
