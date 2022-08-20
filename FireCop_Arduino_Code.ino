int LM1 = 8;  // left motor 1 2
int LM2 = 9;
int enA = 3;  // pwm pin for speed control

int RM1 = 10; // right motor 1 2
int RM2 = 11;
int enB = 5;  // pwm pin for speed control

int enW = 6;  // water pump control

int waterPump1 = 0;
int waterPump2 = 1;

// from car front view left, middle, right, analog inputs
#define Left A2
#define Forward A1
#define Right A0

boolean fire = false;

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
  pinMode(Forward, INPUT);
  Serial.begin(9600);
  
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
  analogWrite(enW, 100);  // water pump speed
  digitalWrite(waterPump1, HIGH);
  digitalWrite(waterPump2, LOW);
  fire = false;
}


void loop()
{
  int forwardSensorValue = analogRead(Forward);
  Serial.println(forwardSensorValue);
  // analogRead values are active low, the more the value, higher the fire distance
  
//  if(analogRead(Left) > 500 && analogRead(Right) > 500 && analogRead(Forward) > 500)
  if (analogRead(Forward) > 500)  // car stops
  {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    digitalWrite(waterPump1, LOW);
    digitalWrite(waterPump2, LOW);
    analogWrite(enW, 0);
  }else if(analogRead(Forward) <= 500)
  {
    if(analogRead(Forward) >= 100 && analogRead(Forward) <= 500)  // car moves
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, LOW);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, LOW);
      digitalWrite(waterPump1, HIGH);
      digitalWrite(waterPump2, HIGH);
      analogWrite(enW, 0);
      // setting custom speed test values
      analogWrite(enA, 50);
      analogWrite(enB, 50);

      // setting delay for slow down
      // delay(1000);
      
    }else
    {
      digitalWrite(LM1, HIGH);
      digitalWrite(LM2, HIGH);
      digitalWrite(RM1, HIGH);
      digitalWrite(RM2, HIGH);
      digitalWrite(waterPump1, HIGH);
      digitalWrite(waterPump2, HIGH);
      analogWrite(enW, 0);
      fire = true;

      put_off_fire();
      // delay(3000);
    }
  }
}
  
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
