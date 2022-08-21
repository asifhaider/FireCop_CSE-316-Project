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
  
  
}

void rotateServo()
{
  for(servoDirection = 0; servoDirection<=180; servoDirection++)
  {
    s1.write(servoDirection);
    delay(5);
    if(digitalRead(FireSensor)==0)
    {
      fire = true;
      put_off_fire();
    }
  }
  for(servoDirection = 180; servoDirection >=0; servoDirection--)
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
  analogWrite(enA, 0);  // stop
  analogWrite(enB, 0);  // stop
  analogWrite(enW,100);  // water pump speed
  digitalWrite(waterPump1, HIGH);
  digitalWrite(waterPump2, LOW);
  
  for(int i=servoDirection; i<= servoDirection+30; i++)
  {
    s1.write(i);
    delay(10);
  }
  for(int i=servoDirection+30; i>=servoDirection-30; i--)
  {
    s1.write(i);
    delay(5);
  }
  fire = false;
}

void loop()
{

  for(int j=0; j<2; j++)
  {
   analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, HIGH);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, HIGH);
  rotateServo();
  }
  digitalWrite(LM1, LOW);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, LOW);
  digitalWrite(RM2, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  rotateServo();
  rotateServo();
  
  for(int k=0; k<2; k++)
  {
     analogWrite(enA, 150);
  analogWrite(enB, 150);
  digitalWrite(LM1, HIGH);
  digitalWrite(LM2, LOW);
  digitalWrite(RM1, HIGH);
  digitalWrite(RM2, LOW);
  delay(1000);
  rotateServo();
  }
  
}


//void loop()
//{
//  int forwardSensorValue = analogRead(Forward);
//  Serial.println(forwardSensorValue);
//  // analogRead values are active low, the more the value, higher the fire distance
//  
////  if(analogRead(Left) > 500 && analogRead(Right) > 500 && analogRead(Forward) > 500)
//  if (analogRead(Forward) > 500)  // car stops
//  {
//    digitalWrite(LM1, HIGH);
//    digitalWrite(LM2, HIGH);
//    digitalWrite(RM1, HIGH);
//    digitalWrite(RM2, HIGH);
//    digitalWrite(waterPump1, LOW);
//    digitalWrite(waterPump2, LOW);
//    analogWrite(enW, 0);
//  }else if(analogRead(Forward) <= 500)
//  {
//    if(analogRead(Forward) >= 100 && analogRead(Forward) <= 500)  // car moves
//    {
//      digitalWrite(LM1, HIGH);
//      digitalWrite(LM2, LOW);
//      digitalWrite(RM1, HIGH);
//      digitalWrite(RM2, LOW);
//      digitalWrite(waterPump1, HIGH);
//      digitalWrite(waterPump2, HIGH);
//      analogWrite(enW, 0);
//      // setting custom speed test values
//      analogWrite(enA, 50);
//      analogWrite(enB, 50);
//
//      // setting delay for slow down
//      // delay(1000);
//      
//    }else
//    {
//      digitalWrite(LM1, HIGH);
//      digitalWrite(LM2, HIGH);
//      digitalWrite(RM1, HIGH);
//      digitalWrite(RM2, HIGH);
//      digitalWrite(waterPump1, HIGH);
//      digitalWrite(waterPump2, HIGH);
//      analogWrite(enW, 0);
//      fire = true;
//
//      put_off_fire();
//      // delay(3000);
//    }
//  }
//}
  
//  else if(analogRead(Left) <=500)
//  {
//    if(analogRead(Left) >= 100 && analogRead(Left) <= 500)
//    {
//      digitalWrite(LM1, HIGH);
//      digitalWrite(LM2, HIGH);
//      digitalWrite(RM1, HIGH);
//      digitalWrite(RM2, LOW);
//      digitalWrite(waterPump1, HIGH);
//      digitalWrite(waterPump2, HIGH);
//      analogWrite(enW, 0);
//      // setting custom speed test values
//      analogWrite(enA, 100);
//      analogWrite(enB, 100);
//      fire = true;
//      delay(1000);
//    }else
//    {
//      digitalWrite(LM1, HIGH);
//      digitalWrite(LM2, HIGH);
//      digitalWrite(RM1, HIGH);
//      digitalWrite(RM2, HIGH);
//      digitalWrite(waterPump1, HIGH);
//      digitalWrite(waterPump2, HIGH);
//      digitalWrite(enW, 0);
//      put_off_fire();
//      // delay(3000);
//    }
//  }else if(analogRead(Right) <= 500)
//  {
//    if(analogRead(Right) >= 100 && analogRead(Right) <= 500)
//    {
//      digitalWrite(LM1, HIGH);
//      digitalWrite(LM2, LOW);
//      digitalWrite(RM1, HIGH);
//      digitalWrite(RM2, HIGH);
//      digitalWrite(waterPump1, HIGH);
//      digitalWrite(waterPump2, HIGH);
//      
//      analogWrite(enW, 0);
//      // setting custom speed test values
//      analogWrite(enA, 100);
//      analogWrite(enB, 100);
//      fire = true;
//    }else
//    {
//      digitalWrite(LM1, HIGH);
//      digitalWrite(LM2, HIGH);
//      digitalWrite(RM1, HIGH);
//      digitalWrite(RM2, HIGH);
//      digitalWrite(waterPump1, HIGH);
//      digitalWrite(waterPump2, HIGH);
//      digitalWrite(enW, 0);
//      put_off_fire();
//      // delay(3000);
//    }
//  }
//}


//void loop()
//{
//  if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
//    {
//    
//    digitalWrite(LM1, HIGH);
//    digitalWrite(LM2, HIGH);
//    digitalWrite(RM1, HIGH);
//    digitalWrite(RM2, HIGH);
//    }
//    
//    else if (digitalRead(Forward) ==0) 
//    {
//    digitalWrite(LM1, HIGH);
//    digitalWrite(LM2, LOW);
//    digitalWrite(RM1, HIGH);
//    digitalWrite(RM2, LOW);
//    fire = true;
//    }
//    
//    else if (digitalRead(Right) ==0)
//    {
//    digitalWrite(LM1, HIGH);
//    digitalWrite(LM2, LOW);
//    digitalWrite(RM1, HIGH);
//    digitalWrite(RM2, HIGH);
//    }
//    
//    else if (digitalRead(Left) ==0) 
//    {
//    digitalWrite(LM1, HIGH);
//    digitalWrite(LM2, HIGH);
//    digitalWrite(RM1, HIGH);
//    digitalWrite(RM2, LOW);
//    }
//    
//     delay(200);//change this value to increase the distance
// 
//     while (fire == true)
//     {
//      put_off_fire();
//     }
//}
