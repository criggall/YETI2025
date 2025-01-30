# Import libraries:
import serial
import struct
from matplotlib import pyplot as plt

# Establish serial connection with receiver Arduino:
usb_port = 'COM3'
serial_connection = serial.Serial(usb_port, 9600, timeout=1)

# Initialize position and temperature vectors:
X_values = []
Y_values = []
T_values = []

# Read and plot data if receiving:
if serial_connection.in_waiting > 1:

    # Read and translate binary signal from Arduino:
    binary_data = serial_connection.read(3)
    X, Y, T = struct.unpack('BBB', binary_data)
    X_values.append(X)
    Y_values.append(Y)
    T_values.append(T)

    # Update and plot heat map:
    plt.figure(1)
    plt.plot(X_values, Y_values, T_values, cmap='viridis')
    plt.savefig('heat_map.png', dpi=300)

# Reset variables if no longer receiving:
else:
    X_values = []
    Y_values = []
    T_values = []