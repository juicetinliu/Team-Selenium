/*
  Arduino Uno WiFi Wifi2Serial example
 This example for the Arduino Uno WiFi shows how to use the
 board as a simple bridge trough the WiFi and the serial monitor.
 Open the Arduino IDE Serial Monitor, select Both NL & CR on the bottom right
 and connect to the WiFi via a telnet client at the address 192.168.240.1:23
 where 192.168.240.1 is the IP of your  Arduino Uno Wifi and 23 is the port.
 Otherwise you can send commands from you browser
 http://172.20.10.7/arduino/custom/custom message
 This example code is part of the public domain
 */
#include <Wire.h>
#include <UnoWiFiDevEd.h>
#include <XBOXUSB.h>

//String inputString = "";         // a string to hold incoming data
//boolean stringComplete = false;  // whether the string is complete
char inputchar = ' ';

#define LDIR 4
#define LPWM 5
#define RPWM 6
#define RDIR 7

void setup() {
    pinMode(LDIR, OUTPUT);
    pinMode(LPWM, OUTPUT); 
    pinMode(RPWM, OUTPUT);
    pinMode(RDIR, OUTPUT);
    //Initialize the Wifi
    Wifi.begin();
    Wifi.println("REST Server is up");
    // initialize serial:
    Serial.begin(9600);
    Serial.println("Begin connection");

    // reserve 200 bytes for the inputString:
    //inputString.reserve(200);
}

void loop() {

  while(Wifi.available()){
    //inputchar = Wifi.read();
    //Serial.write(Wifi.read());
    //Serial.write(" ");
    dir(Wifi.read());
  }
  delay(50);
  
  // print the string when a newline arrives:
  /*if(stringComplete) {
    Serial.write("done");
    Wifi.print(inputString);
    dir(inputString);
    Serial.println("gotdata");
    // clear the string:
    inputString = "";
    stringComplete = false;
  }*/

}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
/*void serialEvent() {
  Serial.println("what");
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    Serial.println("what");
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      Serial.println("true");
    }
  }
}*/

void dir (char inputString){
  if(inputString == 'w'){
      digitalWrite(LDIR, LOW);
      digitalWrite(RDIR, LOW);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
      //delay(50);
    }else if(inputString == 's'){
      digitalWrite(LDIR, HIGH);
      digitalWrite(RDIR, HIGH);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
      Serial.print("move");
      //delay(50);
    }else if(inputString == 'a'){
      digitalWrite(LDIR, HIGH);
      digitalWrite(RDIR, LOW);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
      //delay(50);
    }else if(inputString == 'd'){
      digitalWrite(LDIR, LOW);
      digitalWrite(RDIR, HIGH);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
      //delay(50);
    /*}else if(inputString == "."){
      digitalWrite(LDIR, HIGH);
      digitalWrite(RDIR, HIGH);
      analogWrite(LPWM, 0);
      analogWrite(RPWM, 0);
      Serial.print("stop");*/
    }else{
      digitalWrite(LDIR, LOW);
      digitalWrite(RDIR, LOW);
      analogWrite(LPWM, 0);
      analogWrite(RPWM, 0);
    }
  
}

