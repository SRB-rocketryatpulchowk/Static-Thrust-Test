import serial
import os

# Configure the serial port (change the port and baud rate as needed)
ser = serial.Serial('COM8', 115200)

# Define the directory where you want to save the data
output_directory = "D:\SRB\Project_TRISUL\Propulsion_Test"

# Create the directory if it doesn't exist
if not os.path.exists(output_directory):
    os.makedirs(output_directory)

# Define the output file path
output_file = os.path.join(output_directory, "serial_output.txt")

# Open the file in write mode
with open(output_file, "w") as file:
    try:
        while True:
            # Read a line of data from the serial port
            data = ser.readline().decode('utf-8')

            # Print the data to the console (optional)
            print(data, end='')

            # Write the data to the file
            file.write(data)

            # Check for the 't' keypress to send the tare command to the Arduino
            if ser.in_waiting:
                command = ser.read(1)
                if command == b't':
                    print("Sending tare command to Arduino")
                    ser.write(b't')

    except KeyboardInterrupt:
        print("Data logging stopped.")

# Close the serial port
ser.close()
