#include <Arduino_FreeRTOS.h>
#define THRESHOLD 50
#define RELAY_TIME 0
int iTarget = 80;

int iPWM = 128;
bool bRelay = 0;
bool flg = true;
bool previous_flag = true;

void TaskA( void *pvParameters );
void TaskB( void *pvParameters );

void setup() {
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  Serial.begin(9600);
  
  xTaskCreate(
    TaskRelay
    ,  "TaskRelay"   // A name just for humans
    ,  128       // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2         // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );
  xTaskCreate(
    TaskPWM
    ,  "TaskPWM"
    ,  128       // Stack size
    ,  NULL
    ,  1         // Priority
    ,  NULL );
}

void loop(){}

void TaskRelay(void *pvParameters){ //Relay control
  (void) pvParameters;
  for (;;){
    if(iPWM<THRESHOLD-1)flg=true;
    if(iPWM>THRESHOLD)flg=false;
    switch (flg){
      case true:
        digitalWrite(4, HIGH);
        if(previous_flag==false){
          vTaskDelay( RELAY_TIME / portTICK_PERIOD_MS );;
          previous_flag=true;
          Serial.println("RELAY Control");
        } 
        break;
      case false:
        digitalWrite(4, LOW);
        if(previous_flag==true){
          vTaskDelay(RELAY_TIME);
          previous_flag=false;
          Serial.println("RELAY Control");
        } 
        break;
    }
    vTaskDelay(1);
  }
}

void TaskPWM(void *pvParameters){ //PWM control
  (void) pvParameters;
  for (;;){
    int iMonitor = analogRead(A1);
    iPWM = iPWM - (int)((float)(iMonitor-iTarget)/12.5);
    if(iPWM > 255)iPWM = 255;
    if(iPWM < 0)iPWM = 0;  
    analogWrite(3,iPWM);
    //Serial.println("PWM Control");
    vTaskDelay(RELAY_TIME);
  }
}
