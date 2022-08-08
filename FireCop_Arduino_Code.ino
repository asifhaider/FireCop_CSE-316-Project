int LM1 = 8;
int LM2 = 9;
int enA = 3;

int RM1 = 10;
int RM2 = 11;
int enB = 5;

#define Left 4
#define Right 6
#define Forward 7

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
  
}

void put_off_fire()
{
  delay(500);
  
  digitalWrite(LM1, HIGH);  //move forward for 0.5s
  digitalWrite(LM2, HIGH); 
  digitalWrite(RM1, HIGH); 
  digitalWrite(RM2, HIGH ); 
  digitalWrite(enA, 10); 
  digitalWrite(enB, 100);

  delay(1500);
  fire = false;
}


void loop()
{
  if (digitalRead(Left) ==1 && digitalRead(Right)==1 && digitalRead(Forward) ==1) 
    {
    
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
    
    else if (digitalRead(Forward) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    fire = true;
    }
    
    else if (digitalRead(Right) ==0)
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    }
    
    else if (digitalRead(Left) ==0) 
    {
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);
    }
    
delay(300);//change this value to increase the distance
 
     while (fire == true)
     {
      put_off_fire();
     }
}
