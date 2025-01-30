# Import libraries:
import serial
import struct
from matplotlib import pyplot as plt

# Establish serial connection with receiver Arduino:
usb_port = 'COM4'
serial_connection = serial.Serial(usb_port, 9600, timeout=1)

# Initialize position and temperature vectors:
X_values = []
Y_values = []
T_values = []

while True:

    # Read and translate binary signal from Arduino:
    binary_data = serial_connection.read(3)
    if len(binary_data) == 3:
        X, Y, T = struct.unpack('BBB', binary_data)
        X_values.append(X)
        Y_values.append(Y)
        T_values.append(T)

        # Plot heat map:
        if len(X_values) > 1:
            plt.figure(1)
            plt.scatter(X_values, Y_values, c=T_values, cmap='viridis')
            plt.colorbar(label=r'Temperature ($^\circ$F)')
            plt.xlabel('Position (arbitrary)')
            plt.ylabel('Position (arbitrary)')
            plt.plot(X_values, Y_values, color='gray', linestyle='-', linewidth=0.5)
            plt.savefig('heat_map.png', dpi=300)
            plt.clf()
            print('Plot updated!')

    # Print notice if no data is being received:
    else:
        print('Awaiting data...')