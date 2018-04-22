
#include <Wire.h>
#include <UnoWiFiDevEd.h>

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
    Serial.println("\n Begin connection");

}

void loop() {

  while(Wifi.available()){
    dir(Wifi.read());
  }
  delay(50);

}

void dir (char inputString){
  if(inputString == 'w'){
      digitalWrite(LDIR, LOW);
      digitalWrite(RDIR, LOW);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
      delay(500);
    }else if(inputString == 's'){
      digitalWrite(LDIR, HIGH);
      digitalWrite(RDIR, HIGH);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
      Serial.print("move");
      delay(500);
    }else if(inputString == 'a'){
      digitalWrite(LDIR, HIGH);
      digitalWrite(RDIR, LOW);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
      delay(500);
    }else if(inputString == 'd'){
      digitalWrite(LDIR, LOW);
      digitalWrite(RDIR, HIGH);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
      delay(500);
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

