/* Bioe3090_Incubator.ino - Example controls for Bioe 3090 Incubator Project
	Created by: Steve Lammers, 12/11/2017
	Released to the public domain.
*/

// JSON Library
#include <ArduinoJson.h>

// Refresh rate for checking temperatures and updating PID input milliseconds, default 1000
#define TEMP_CHK_MS 1000


// Define global variables
double masterData = 0;
String inString = "";
bool serialRecievedFlag = false;
bool humanDebugFLAG = false;

// Create JSON object.
//StaticJsonBuffer<200> jsonBuffer;
//JsonObject& jsonRoot = jsonBuffer.createObject();
bool jsonFlag = true; 


void check_serial(){
  // Ask user to input the setpoint for the heater.
  //Serial.print("Enter temperature setpoint in degrees Celsius: ");
  // send data only when you receive data:
  // Clear the input string 
  while (Serial.available() > 0) {
    // read the incoming byte:
    int incomingByte = Serial.read();
    /*
    // if the data is a digit, add it to inString
    if (isDigit(incomingByte)){
      inString += (char)incomingByte;
    }
    else{
      // ignore if the incomming byte is a carrige return or newline char
      if (incomingByte == '\n' || incomingByte == '\r'){
          Serial.println("newline or CR");
        }
      else{
        Serial.println("Incompatible character, use only numbers");
      }
    }
    */

    inString += (char)incomingByte;
    // Check if the incoming byte is a newline character
    if (incomingByte == '\n'){
      
      // say what you got:
      if (humanDebugFLAG) {
        Serial.print("I received: ");
        Serial.println(inString);
      } // humanDebugFLAG
      
      // Create JSON object, must create json object as a local objet here, not
      //  as a global as typical in the example docs in the ArduinoJson library.
      //  Otherwise the object is not destroyed after the loop is complete and
      //  if the parsing does not succeed then future calls to parse incomming
      //  correctly formatted json strings will also fail. Making the object local
      //  fixes this problem.
      //    StaticJsonBuffer<200> jsonBuffer;
      //    JsonObject& jsonRoot = jsonBuffer.parseObject(inString);

      // Set serial recieved FLAG
      serialRecievedFlag = true;
      
      // Create JSON object.
      StaticJsonDocument<200> doc;
      deserializeJson(doc, inString);

      // Test if parsing succeeds.
      auto error = deserializeJson(doc, inString);
      if (error) {
        Serial.print(F("deserializeJson(() fialed with code"));
        Serial.println(error.c_str());
        return;
      }
      

      masterData = doc["myMasterData"];

     
      // Clear the input string 
      inString = "";
    }

  } 
} // << check_serial





// Gathers output data, format as JSON and output as serial communication
double json_output()
{ 
   // Create JSON object.
  StaticJsonDocument<200> doc;
  JsonObject jsonRoot = doc.to<JsonObject>();
  jsonRoot["myAnalogValue"] = masterData;
  jsonRoot["time"] = millis();//(millis() * 205 ) >> 11; //millis()/1000;
  serializeJson(doc, Serial);
  // Matlab needs a carrige return for the "readline" function to work
  Serial.println(" ");
}




void setup(){
  // Start serial comms
	Serial.begin(9600);

	while (!Serial) {
		; // Wait for serial to connect
	}

  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.print("Serial Established");
  Serial.println("");

}


void loop(){
  // Check the serial comms to see if the heater setpoint changed
  check_serial();
  
	if (serialRecievedFlag){
    // Output data to serial.
    json_output();
    serialRecievedFlag = false;
	}

   //if (printTempClock.check_trigger()){
   //   // Output data to serial.
   //   json_output();
   //}
 
  //DEL delay(1000);
}
