#include <Wire.h>
#include <UnoWiFiDevEd.h>

char Input = "";
#define LDIR 4
#define LPWM 5
#define RPWM 6
#define RDIR 7

void setup() {
 pinMode(LDIR, OUTPUT);
 pinMode(LPWM, OUTPUT); 
 pinMode(RPWM, OUTPUT);
 pinMode(RDIR, OUTPUT);

        Wifi.begin();
        Serial.begin(9600);
        Wifi.println("Rover Control Server");
        Serial.println("Rover Control Serial");
        
}

void loop() {

  Input = Wifi.read();
  if(Wifi.read() < 0){
    
  }else{
    Serial.print(Input);
    if(Input == "w"){
      digitalWrite(LDIR, HIGH);
      digitalWrite(RDIR, HIGH);
      analogWrite(LPWM, 255);
      analogWrite(RPWM, 255);
    delay(500);
    }

  }

 //        delay(5000);


}
