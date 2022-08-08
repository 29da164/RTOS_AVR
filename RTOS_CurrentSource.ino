#define THRESHOLD 50
int iTarget = 80;

int iPWM = 128;
bool bRelay = 0;
bool flg = true;

void setup(){
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.println("PWM, Monitor");
}

void loop(){

  int iMonitor = analogRead(A1);

  iPWM = iPWM - (int)((float)(iMonitor-iTarget)/4.5);
  if(iPWM<THRESHOLD-1)flg=true;
  if(iPWM>THRESHOLD)flg=false;
  
  switch (flg){
    case true:
      digitalWrite(4, HIGH);
      break;
    case false:
      digitalWrite(4, LOW);
      break;
  }

  if(iPWM > 255)iPWM = 255;
  if(iPWM < 0)iPWM = 0;
  
  analogWrite(3,iPWM);
  //Serial.print(iPWM);
  //Serial.print(", ");
  //Serial.println(iMonitor);
  //delay(50);

}
