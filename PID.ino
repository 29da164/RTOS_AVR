#define THRESHOLD 50
#define fCoeff_P 0.2
#define fCoeff_I 0.2
#define fCoeff_D 0.4

int iTarget = 80;

int iPWM = 128;
float fP_error = 0.0;
float fI_error = 0.0;
float fD_error = 0.0;
float fP_error_previous = 0.0;
bool bRelay = 0;
bool flg = true;

void setup(){
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop(){

  int iMonitor = analogRead(A1);

  fP_error =  fCoeff_P*(float)(iMonitor-iTarget)/1.5;
  fI_error += fCoeff_I*fI_error;
  fD_error =  fCoeff_D*(fP_error - fP_error_previous);
  fP_error_previous = fP_error;
  
  iPWM -= (int)(fP_error + fI_error + fD_error);
  
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
  Serial.println(iMonitor);
  delay(100);

}