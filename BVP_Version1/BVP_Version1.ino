/*
The MIT License (MIT)

Copyright (c) 2013 Rami Alshafi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include <Servo.h>
Servo Servo1;
Servo Servo2;
int index1 = 0;
int index2 = 0;
int Loc1, Loc2;
int Data1, Data2;
void setup(){
}
void loop(){
  Data1+= rawDataCollection(2);
  if (index1 >= 5){
  Loc1=DataAna(Data1, index1, 1);
  servoCommandor(6, 1, Loc1);
  index1 = 0; 
  Data1 = 0;
  }else{
    index1++;
  }
Data2+= rawDataCollection(3);
if (index2 >= 5){
  Loc2=DataAna(Data2, index2, 2);
  servoCommandor(7, 2, Loc2);
  index2 = 0;
  Data2 = 0;
}else{
  index2++;
}
}
int rawDataCollection(int pingPin){

  unsigned long duration;
  int cm;
  do{
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH); 
  cm = 0.017*duration;
  }while(cm == 0 );
  return cm;
}
int DataAna(int data, int index, int servo){
  int mean, result;
  mean = data/index;
  if(servo == 1){
    result=map(mean,2,300,110, 180);
  }else if(servo == 2){
    result=map(mean,2,300,70,0);
  }
  return result;
}
void servoCommandor(int servoPin, int serv, int Loc){

  if(serv == 1){
  Servo1.attach(servoPin);
  delay(10);
  Servo1.write(Loc);
  delay(50);
  Servo1.detach(); 
  }else if(serv == 2){
  Servo2.attach(servoPin);
  delay(10);
  Servo2.write(Loc);
  delay(50);
 Servo2.detach();

  }
}

