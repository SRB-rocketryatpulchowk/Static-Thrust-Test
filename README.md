# Static-Thrust-Test
This repo provides the code used to calibrate the load cell before performing the static test. 
Hardware used are: 
1. Arduino Nano
2. HX711 amplifier
3. loadcell

The code python_callibration.ino is used to first calibrate the loadcell and use it to measure the thrust. 
Steps to calibrate: 
1. Take a known weight(in Newton)
2. Place the thrust stand in vertical position(the measuring plate being horizontal; make sure with leveler)
3. Connect the PCBs and wiring, and upload the code 
4. Open the serial monitor
5. Place the known weight and observe the output
6. Adjust line 14 of code: #define NEWTONS_PER_COUNT (0.0728 * 0.0098) - Change the value "0.0728" until you get the correct value in the serial monitor.
7. While doing step 6. You have to remove the weight and re-upload the code every time you change the value in the code.

Once calibration is done. You can conduct the static testing, copy the data from the serial monitor, and post-process it.
Or, you can use the Python script "data_logger_modified.py", open it in any IDE or notebook, change the baud rate to the one set in the .ino code, and also change the port. 
Once you run it, a terminal will open and show the serial output. Once the terminal is closed, it will save the data in a text file named "serialoutput.txt". 

NOTE: To run another time, you have to delete the serialoutput.txt or rename it, otherwise, the script will not work 
