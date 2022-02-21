/* Arduino_to_MATLAB 
 Created by: Steve Lammers (adapted from code originally written by Huda Farooqui)
 2/21/2022

 Write sine wave points to the serial port encoded as JSON.
 Followed by the Carriage Return and LineFeed terminator so the callback in MatLab works.
 */

// *********************** INCLUDE LIBRARIES *************************
 // JSON Library
#include <ArduinoJson.h>

// *********************** GLOBAL VARIABLES **************************
int i = 0;

// **************************** SETUP ********************************
// The setup routine runs once when you press reset:
void setup() {
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// ****************************** FUNCTIONS *****************************
// Gathers output data, format as JSON and output as serial communication
double json_output(float signalValue)
{ 
   // Create JSON object.
  StaticJsonDocument<200> doc;
  JsonObject jsonRoot = doc.to<JsonObject>();
  jsonRoot["signalValue"] = signalValue;
  jsonRoot["time"] = millis();//(millis() * 205 ) >> 11; //millis()/1000;
  serializeJson(doc, Serial);
  // Matlab needs a carrige return for the "readline" function to work
  Serial.println(" ");
}


// The loop routine runs over and over again forever:
void loop() {
  // Write the sinewave points, followed by the terminator "Carriage Return" and "Linefeed".
  json_output(sin(i*50.0/360.0));

  i += 1;
}
