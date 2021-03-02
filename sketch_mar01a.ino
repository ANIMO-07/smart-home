#include <Servo.h>

int Input_Byte;
const int tubelight = 8;        //pins for the relays to the various appliances
const int fan = 9;
const int heater = 10;
const int charger = 11;

int tubelight_state = 0;        //0 is open, 1 is closed
int fan_state = 0;
int heater_state = 0;
int charger_state = 0;
int latch_state = 0;

Servo myservo;

int pos = 45;                   //servo position initialised

void setup() {
  pinMode(tubelight, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(heater, OUTPUT);
  pinMode(charger, OUTPUT);
  myservo.attach(6);
  Serial.begin(38400);
}

void loop() {
  if(Serial.available() > 0){
    Input_Byte = Serial.read();
  }

  int states[5] = {tubelight_state, fan_state, heater_state, charger_state, latch_state};
  int devices[4] = {tubelight, fan, heater, charger};

  if (Input_Byte < 6 && Input_Byte>0){
    //app configured to give inputs 1,2,3,4,5 corresponding to different things
    Input_Byte --;
    if (states[Input_Byte] == 0) states[Input_Byte] = 1;
    else states[Input_Byte] = 1;

    if (Input_Byte == 4){
      if (latch_state == 1){
        for (pos = 45; pos <= 135; pos += 1) { // goes from 45 degrees to 135 degrees
        // in steps of 1 degree
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(50);                       // waits 50ms for the servo to reach the position
        }
      }
      else {
        for (pos = 135; pos >= 45; pos -= 1) { // goes from 135 degrees to 45 degrees
          myservo.write(pos);              // tell servo to go to position in variable 'pos'
          delay(50);                       // waits 50ms for the servo to reach the position
        }
      }
    }
    else{
      if (states[Input_Byte] == 0) digitalWrite(devices[Input_Byte], LOW);
      else digitalWrite(devices[Input_Byte], HIGH);
    }

    Input_Byte = 0;
  }
}
