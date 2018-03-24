/*
  WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your board (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the built in LED.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * Arduino Primo or STAR OTTO or Uno WiFi Developer Edition (with WiFi Link firmware running)

 created 25 Nov 2012
 by Tom Igoe
 modified 10 March 2017
 by Sergio Tomasello and Andrea CannistrÃ¡
 */


#include <WiFiLink.h>
#define STA_MODE  //Comment out this line if you want to use the Arduino's WiFi access point

char ssid[] = "EEERover";      //  your network SSID (name)
char pass[] = "exhibition";   // your network password
int keyIndex = 0;                 // your network key Index number (needed only for WEP)
IPAddress ip(192,168,0,17);    // unique ip address to access this Arduino - MODIFY THIS

int PWML = 6;
int PWMR = 5;
int ML = 4; //DIRL
int MR = 3; //DIRR

int status = WL_IDLE_STATUS;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);      // initialize serial communication
  pinMode(PWML, OUTPUT);
  pinMode(PWMR, OUTPUT);
  pinMode(ML, OUTPUT);
  pinMode(MR, OUTPUT);      // set motors pin mode

  //Check if communication with the wifi module has been established
  if (WiFi.status() == WL_NO_WIFI_MODULE_COMM) {
    Serial.println("Communication with WiFi module not established.");
    while (true); // don't continue:
  }

  WiFi.config(ip);

  // attempt to connect to Wifi network:
  #ifdef STA_MODE
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to Network named: ");
      Serial.println(ssid);                   // print the network name (SSID);
  
      // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
      status = WiFi.begin(ssid, pass);
      // wait 10 seconds for connection:
      delay(10000);
    }
  #endif
  server.begin();                           // start the web server on port 80
  printWifiStatus();                        // you're connected now, so print out the status
}


void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        //Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/F\">here</a> Move the rover forward<br>");
            client.print("Click <a href=\"/L\">here</a> Turn the rover left<br>");
            client.print("Click <a href=\"/R\">here</a> Turn the rover right<br>");
            client.print("Click <a href=\"/S\">here</a> Stop the rover hehe<br>");
            client.print("Click <a href=\"/B\">here</a> Move the rover backwards<br>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /F")) {
          analogWrite(PWML, 255);
          analogWrite(PWMR, 255);
          digitalWrite(ML, LOW);
          digitalWrite(MR, LOW);
          delay(1000);
        }else if (currentLine.endsWith("GET /B")) {
          analogWrite(PWML, 255);
          analogWrite(PWMR, 255);
          digitalWrite(ML, HIGH);
          digitalWrite(MR, HIGH);
          delay(1000);
        }else if (currentLine.endsWith("GET /L")) {
          analogWrite(PWML, 255);
          analogWrite(PWMR, 255);
          digitalWrite(ML, LOW);
          digitalWrite(MR, HIGH);
          delay(1000);
        }else if (currentLine.endsWith("GET /R")) {
          analogWrite(PWML, 255);
          analogWrite(PWMR, 255);
          digitalWrite(ML, HIGH);
          digitalWrite(MR, LOW);
          delay(1000);  
        }else {
          analogWrite(PWML, 0);
          analogWrite(PWMR, 0);
          digitalWrite(ML, LOW);
          digitalWrite(MR, LOW);
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
