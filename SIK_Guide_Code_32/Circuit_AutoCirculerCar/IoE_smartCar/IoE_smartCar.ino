#include "ControlMotor.h"//모터제어 라이브러리를 사용합니다.
// 아두이노 보드에서 사용할 핀을 설정합니다.
ControlMotor control(2,3,7,4,5,6); // 우측모터1,우측모터2,좌측모터1,좌측모터2,우측PWM,좌측PWM

#include "Ultrasonic.h"//HC-SR04 초음파센서 라이브러리를 사용합니다.
Ultrasonic sensor(9,8,30000); // (Trig핀, Echo핀, 최대거리 단위는 us) 즉 30000us = 약 5미터

int mesurement_speed = 5;//센서 측정 속도를 조정합니다.
long int distance = 0; //거리를 저장할 변수를 선언합니다.
int random_value = 0;//랜덤값을 저장합니다. 

void setup() 
{ 
Serial.begin(9600);//시리얼포트를 초기화합니다.
 
} 
 
void loop() 
{ 
 
  
  control.Motor(150,1);//150의 속도로 자동차가 전진합니다.
  distance=sensor.Ranging(CM);//거리를 측정하고 distance 변수에 저장합니다.

  delay(mesurement_speed);//센서측정 속도를 제어하기 위한 딜레이.
 
 //다음은 장애물이 없는 경우에 해당합니다.
 Serial.print("No obstacle ");//장애물이 없다고 시리얼 모니터에 출력합니다.
 Serial.println(distance);//거리를 출력합니다.
 Serial.print("Random ");//"Random"을 출력합니다.
 Serial.println(random_value);//랜덤값을 출력합니다.

 random_value = random (2);//자동차가 한쪽 방향으로만 회전하는 것을 막기 위해 랜덤값을 만듭니다.
  
  
  while(distance<30){//장애물과의 거리가 30cm이하일 경우에 적용됩니다.
        
  
  delay(mesurement_speed);//센서측정 속도를 제어하기 위한 딜레이.
  control.Motor(0,1);//모터를 정지시킵니다.
  distance = sensor.Ranging(CM);
  delay(1000);

  if(random_value==0){// 랜덤값이 0인경우에 해당됩니다.
 Serial.print("Distance ");//"Distance "를 시리얼모니터에 출력합니다.
 Serial.println(distance);//거리를 출력합니다.
 Serial.print("Random ");//"Random"을 출력합니다.
 Serial.println(random_value);//랜덤값을 출력합니다.
 
  control.Motor(170,100);//자동차가 0.4초동안 오른쪽으로 회전합니다.
  delay(400);}
  
  else if (random_value==1){//랜덤값이 1인경우에 해당됩니다.
 Serial.print("Distance ");//"Distance "를 시리얼모니터에 출력합니다.
 Serial.println(distance);//거리를 출력합니다.
 Serial.print("Random ");//"Random"을 출력합니다.
 Serial.println(random_value);//랜덤값을 출력합니다.
 
  control.Motor(170,-100);//자동차가 0.4초동안 왼쪽으로 회전합니다.
  delay(400);}
  }
} 
