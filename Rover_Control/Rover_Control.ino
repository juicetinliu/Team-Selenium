//4 and 7 are L & R DIR respectively, 5 and 6 are L & R PWM respectively

#define LDIR 4
#define LPWM 5
#define RPWM 6
#define RDIR 7

int xaxis = 0;
int yaxis = 0;

int Lspeed = 0;
int Rspeed = 0;

void setup() {
 pinMode(A0, INPUT);
 pinMode(A1, INPUT);
 pinMode(LDIR, OUTPUT);
 pinMode(LPWM, OUTPUT); 
 pinMode(RPWM, OUTPUT);
 pinMode(RDIR, OUTPUT);
}

void loop() {
  
  yaxis = analogRead(A0);
  xaxis = analogRead(A1);

  if (yaxis < 526) {
  
    digitalWrite(LDIR, LOW);
    digitalWrite(RDIR, LOW);
    Lspeed = map(yaxis, 526, 0, 0, 255);
    Rspeed = map(yaxis, 526, 0, 0, 255);
      
  }else if(yaxis > 527){
  
    digitalWrite(LDIR, HIGH);
    digitalWrite(RDIR, HIGH);
    Lspeed = map(yaxis, 527, 1023, 0, 255);
    Rspeed = map(yaxis, 527, 1023, 0, 255);
    
  }else{
    Lspeed = 0;
    Rspeed = 0;
  }
  
  if(xaxis < 526){
  
    int x = map(xaxis, 526, 0, 0, 255);
    Lspeed = Lspeed - x;
    Rspeed = Rspeed + x;
      if(Lspeed < 0){
        Lspeed = 0;
      }
      if(Rspeed > 255){
        Rspeed = 255;
    } 
  }
  
  if(xaxis > 527){
    int x = map(xaxis, 527, 1023, 0, 255);
    Lspeed = Lspeed + x;
    Rspeed = Rspeed - x;
      if(Lspeed > 255){
        Lspeed = 255;
      }
      if(Rspeed < 0){
        Rspeed = 0;
      }
  }

      if (Lspeed < 11){
        Lspeed = 0;
      }
      if (Rspeed < 11){
        Rspeed = 0;
      }
  
  analogWrite(LPWM, Lspeed);
  analogWrite(RPWM, Rspeed);
}

