#define DELAY_MS 1
const int statusPin = 2;
const int ledPin = 7;
const int speakerPin = 9;
bool status = true;

void setup() {
  pinMode(statusPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  int led_status = 1;
  int led_time = 0;
  Serial.begin(9600);

  while(1){
    status = digitalRead(statusPin);
    ledBlink(100, status, &led_status, &led_time);
    if(status != digitalRead(statusPin)) {
      buzz(255,300);
    }
    else{
      led_time = 0;
    }
  }

}

void ledBlink(int millisec, bool status, 
              int *led_status, int *led_time) {
  
  bool itrpt = 0;
  
  if(*led_status){
    digitalWrite(ledPin, HIGH);
    for(int i= *led_time;i<millisec;i++){
      if(itrpt) break;
      if(digitalRead(statusPin) != status){
        *led_status = true;
        *led_time = i;
        itrpt = true;
        break;
      }
      else{
        //Serial.println("1");
        delay(DELAY_MS);
      }
    }
    if(!itrpt) digitalWrite(ledPin, LOW);
    for(int i=0;i<millisec;i++){
      if(itrpt) break;
      if(digitalRead(statusPin) != status){
        *led_status = false;
        *led_time = i;
        itrpt = 1;
        break;
      }
      else{
        //Serial.println("0");
        delay(DELAY_MS);
      }
    }
  }
  else{
    digitalWrite(ledPin, LOW);
    for(int i= *led_time;i<millisec;i++){
      if(itrpt) break;
      if(digitalRead(statusPin) != status){
        *led_status = false;
        *led_time = i;
        itrpt = 1;
        break;
      }
      else{
        //Serial.println("0");
        delay(DELAY_MS);
      }
    }
    if(!itrpt) digitalWrite(ledPin, HIGH);
    for(int i=0;i<millisec;i++){
      if(itrpt) break;
      if(digitalRead(statusPin) != status){
        *led_status = true;
        *led_time = i;
        itrpt = 1;
        break;
      }
      else{
        //Serial.println("1");
        delay(DELAY_MS);
      }
    }
  }
}

void buzz(long frequency, long millisec){
  long duration = frequency*millisec/1000;
  tone(speakerPin, 255, 300);
  /*
  for(long i=0;i<duration;i++){
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(1E6/frequency);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(1E6/frequency);
  }
  */
}

void loop(){
}