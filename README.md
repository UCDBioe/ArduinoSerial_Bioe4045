
1-Way plotting and 2-Way Communications between Arduino and Matlab
------------------------------------------------------------------

Required Libraries
-------------------
* arduinojson


1-Way Comunication and GUI
-----------------------------------------
Arduino_UI.mlapp and Arduino_to_MATLAB.ino
=========================================
A program that plots data that is being continuously recieved from an arduino

* Associated arduino program (Arduino_to_MATLAB.ino)


2-Way Comunication
----------------------------------------------
ArduinoSerialBioe4045.ino and Arduino_Serial.m
==============================================
A program that allows for 2-way communication between an arduino and matlab.

* **void check_serial()** - Function that checks the serial port to see if data is available. If data is available, the function reads the data until a newline character is reached. The data is validated to be a correctly formatted JSON string. The JSON string is decoded and the decoded string is stored into global variables for the PID values and heater setpoint.

* **void json\_output(&double)** - Gathers data, builds JSON message and outputs message to the serial port of theArduino. JSON output string is encoded to contain information for the inside and outside tempertures, the PID output value and the time of the request. This data is then output on the serial port. Takes an address to a double as an input. This double is the input heater value for the PID control. Therefore, the PID heater input value is updated within the json\_output function.

* **void startup()** - Standard Arduino startup function. Starts serial coms, assigns sensors, set PID mode and sets heater setpoint.

* **void loop()** - Main Arduino program loop. 


