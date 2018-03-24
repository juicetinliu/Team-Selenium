/*
  Arduino Uno WiFi Wifi2Serial example
 This example for the Arduino Uno WiFi shows how to use the
 board as a simple bridge trough the WiFi and the serial monitor.
 Open the Arduino IDE Serial Monitor, select Both NL & CR on the bottom right
 and connect to the WiFi via a telnet client at the address 192.168.240.1:23
 where 192.168.240.1 is the IP of your  Arduino Uno Wifi and 23 is the port.
 Otherwise you can send commands from you browser
 http://192.168.240.1/arduino/custom/yourpersonalmessage
 This example code is part of the public domain
 */
#include <Wire.h>
#include <UnoWiFiDevEd.h>

#define LDIR 4
#define LPWM 5
#define RPWM 6
#define RDIR 7


int LSpeed = 255;
int RSpeed = 0;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete


void setup() {

 pinMode(LDIR, OUTPUT);
 pinMode(LPWM, OUTPUT); 
 pinMode(RPWM, OUTPUT);
 pinMode(RDIR, OUTPUT);

    digitalWrite(LDIR, HIGH);
    digitalWrite(RDIR, HIGH);
  
    //Initialize the Wifi
    Wifi.begin();
    Wifi.println("Rover Control: ");
    // initialize serial:
    Serial.begin(9600);

    // reserve 200 bytes for the inputString:
    inputString.reserve(200);
    
}

void loop() {

  while(Wifi.available()){
    Serial.write(Wifi.read());
  }
  delay(50);

    if(inputString == "w"){
    analogWrite(LPWM, LSpeed);
    delay(1000);
  }
  
  // print the string when a newline arrives:
  if (stringComplete) {


    
    Wifi.print(inputString);
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
