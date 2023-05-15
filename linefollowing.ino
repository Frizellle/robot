#include <Servo.h>

const int PIN_Motor_PWMA = 5;
const int PIN_Motor_PWMB = 6;
const int PIN_Motor_BIN_1 = 8;
const int PIN_Motor_AIN_1 = 7;
const int PIN_Motor_STBY = 3;
const int IRright = A0;
const int IRmid = A1;
const int IRleft = A2;
const int lIR = A8;
const int rIR = A10;
const int US = 10;
int curLine = 0;
bool incrementable = true;


Servo claw;
Servo arm;

void setup() {
  pinMode(IRright, INPUT);
  pinMode(IRmid, INPUT);
  pinMode(IRleft, INPUT);
  Serial.begin(9600);
  claw.attach(25);
  arm.attach(22);
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT);
}


void loop() {
  int IRr = analogRead(IRright);
  int IRm = analogRead(IRmid);
  int IRl = analogRead(IRleft);
  int leftIR = analogRead(lIR);
  int rightIR = analogRead(rIR);
  int us = analogRead(US);
  int prevLine = 500;
  
  
  //Serial.println(IRr);
  //Serial.println(IRm);
  //Serial.println(IRl);
  //Serial.println(leftIR);
  //Serial.println(rightIR);

  //if (IRr < 700) adjustLeft();
  //else if (IRl < 700) adjustRight();
  //Serial.println(leftIR);
  if (leftIR > 1000 && incrementable) 
  {
    Serial.println("incrementing");
    //Serial.println(leftIR);
    curLine++;
    Serial.println(curLine);
    incrementable = false;//turnLeft();
  }
  else 
  {
    if (IRr < 700) adjustLeft();
    else if (IRl < 700) adjustRight();
    else goStraight();
  }
  incrementable = (leftIR < 300);
}

/*void hold
{
  int IR = analogRead(IRsensor);
  Serial.println("hi");
  Serial.println(IR);
  if (IR > 900)
  {
    Serial.println(IR);
    claw.write(0);
    delay(2000);
    claw.write(180);
    delay(700);
  }
  delay(100);
}*/

void adjustRight()
{
  analogWrite(PIN_Motor_PWMA, 75);
  analogWrite(PIN_Motor_PWMB, 50);
  digitalWrite(PIN_Motor_AIN_1, HIGH); // reverses right hand wheels when off
  digitalWrite(PIN_Motor_BIN_1, HIGH); // reverses left hand wheels when off
  digitalWrite(PIN_Motor_STBY, HIGH); // disables all when off
}

void adjustLeft()
{
  analogWrite(PIN_Motor_PWMA, 50);
  analogWrite(PIN_Motor_PWMB, 75);
  digitalWrite(PIN_Motor_AIN_1, HIGH); // reverses right hand wheels when off
  digitalWrite(PIN_Motor_BIN_1, HIGH); // reverses left hand wheels when off
  digitalWrite(PIN_Motor_STBY, HIGH); // disables all when off
}

void goStraight()
{
  analogWrite(PIN_Motor_PWMA, 75);
  analogWrite(PIN_Motor_PWMB, 75);
  digitalWrite(PIN_Motor_AIN_1, HIGH); // reverses right hand wheels when off
  digitalWrite(PIN_Motor_BIN_1, HIGH); // reverses left hand wheels when off
  digitalWrite(PIN_Motor_STBY, HIGH); // disables all when off
}

void turnLeft()
{
  
  analogWrite(PIN_Motor_PWMA, 75);
  analogWrite(PIN_Motor_PWMB, 75);
  digitalWrite(PIN_Motor_AIN_1, HIGH); // reverses right hand wheels when off
  digitalWrite(PIN_Motor_BIN_1, LOW); // reverses left hand wheels when off
  digitalWrite(PIN_Motor_STBY, HIGH); // disables all when off
}

