# Gesture Wheelchair

## Description
A wheelchair controlled by gestures and voice commands, utilizing RF communication and sensor data.

## Components
- **gwbasecontrol.ino**: Controls the wheelchair's movement based on RF signals and distance measurements.
- **transmitterctrl.ino**: Reads data from the MPU6050 sensor and transmits it to the control system.
- **voicectrl.py**: Implements voice control for the wheelchair using speech recognition.

## Installation
- Required libraries:
  - `speech_recognition`
  - `pyttsx3`
  - `pywhatkit`
  - `serial`
  - `RF24`
  - `Wire`
  - `I2Cdev`
  - `MPU6050`
  
- Instructions for setting up the Arduino environment and Python environment.

## Usage
- Run the Arduino sketches to control the wheelchair.
- Execute the Python script for voice control.
- Example voice commands:
  - "control up" to move the wheelchair forward.
  - "control down" to move the wheelchair backward.
  - "control forward" to stop the wheelchair.

## License
This project is licensed under the MIT License.
