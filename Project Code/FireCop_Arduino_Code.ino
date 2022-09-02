#include<Servo.h>
Servo s1;

int LM1 = 2;  // left motor 1 2
int LM2 = 4;  
int enA = 3;  // pwm pin for speed control

int RM1 = 7; // right motor 1 2
int RM2 = 8;
int enB = 6;  // pwm pin for speed control

int enW = 11;  // water pump control  


int waterPump1 = 12;
int waterPump2 = 13;

int servoMotor = 9;
int buzzer = 10;

// from car front view left, middle, right, analog inputs
#define Left A2
int FireSensor =5;
#define Right A0

boolean fire = false;
int servoDirection=0;

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
  pinMode(FireSensor, INPUT);
  s1.attach(9); //loop er vitor s1.write
  Serial.begin(9600);
  pinMode(enW, OUTPUT);
  pinMode(waterPump1, OUTPUT);
  pinMode(waterPump2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
}

void rotateServoWhileFire()
{
  int minDeg, maxDeg;
  if(0 < servoDirection-30)
  {
    minDeg = servoDirection-30;
  }else
  {
    minDeg = 0;
  }
  if(180 < servoDirection+30)
  {
    maxDeg = 180;
  }else
  {
    maxDeg = servoDirection+30;
  }

  for(int dir = servoDirection; dir <= maxDeg; dir++)
  {
    s1.write(dir);
    delay(5);
  }
  
  for(int dir = maxDeg; dir >= minDeg; dir--)
  {
    s1.write(dir);
    delay(5);
  }
  for(int dir= minDeg; dir<=servoDirection; dir++)
  {
    s1.write(dir);
    delay(5);
  }
}

void rotateServo()
{
  for(servoDirection = 30; servoDirection<=360; servoDirection++)
  {
    s1.write(servoDirection);
    delay(5);
    if(digitalRead(FireSensor)==0)
    {
      fire = true;
      put_off_fire();  
    }
  }
  for(servoDirection = 360; servoDirection >=30; servoDirection--)
  {
    s1.write(servoDirection);
    delay(5);
    if(digitalRead(FireSensor)==0)
    {
      fire = true;
      put_off_fire();
    }
  }

}

void put_off_fire()
{
  // all high and all low means stand still
  digitalWrite(LM1, HIGH);  //move forward for 0.5s
  digitalWrite(LM2, HIGH); 
  digitalWrite(RM1, HIGH); 
  digitalWrite(RM2, HIGH ); 
  digitalWrite(buzzer, HIGH);
  analogWrite(enA, 0);  // stop
  analogWrite(enB, 0);  // stop
  analogWrite(enW,180);  // water pump speed
  digitalWrite(waterPump1, HIGH);
  digitalWrite(waterPump2, LOW);

  while(digitalRead(FireSensor)==0)
  {
    //rotateServoWhileFire();
  }

  delay(500);
  fire = false;
  analogWrite(enW, 0);
  digitalWrite(waterPump1, LOW);
  digitalWrite(waterPump2, LOW);
  digitalWrite(buzzer, LOW);
  delay(5);
}

void loop()
{
  digitalWrite(buzzer, LOW);
  analogWrite(enA, 70);
  analogWrite(enB, 70);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  delay(200);
  for(int j=0; j<1; j++)
  {
  rotateServo();
  }
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  rotateServo();

  analogWrite(enA, 70);
  analogWrite(enB, 70);
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  delay(200);
  for(int k=0; k<1; k++)
  {
  rotateServo();
  }

  

  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  rotateServo();
  
}
