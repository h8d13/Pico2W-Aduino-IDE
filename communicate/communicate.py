import serial
import time

# Connect to Pico
pico = serial.Serial('COM7', 115200, timeout=0.1)  # Change to your port, baudrate, timeout
time.sleep(1)

print("Connected! Press ENTER to click, 'q' to quit")

while True:
    user_input = input()
    if user_input.lower() == 'q':
        break
    
    # Send click command
    pico.write(b'c')
    pico.flush()

pico.close()
