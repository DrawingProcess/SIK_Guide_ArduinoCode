const int passiveB = 10;
int bt[8] = {2,3,4,5,6,7,8,9};//도레미파솔라시도 버튼
int melody[8] = {262, 294, 330, 349, 393, 440, 494, 523};//도레미파솔라시도 음계

void setup() {
  // put your setup code here, to run once:

  for(int i=0; i<8; i++){
    pinMode(bt[i], INPUT);  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(bt[0]) == HIGH){
    tone(passiveB, melody[0]);
  }
  else if(digitalRead(bt[1]) == HIGH){
    tone(passiveB, melody[1]);
  }
  else if(digitalRead(bt[2]) == HIGH){
    tone(passiveB, melody[2]);
  }
  else if(digitalRead(bt[3]) == HIGH){
    tone(passiveB, melody[3]);
  }
  else if(digitalRead(bt[4]) == HIGH){
    tone(passiveB, melody[4]);
  }
  else if(digitalRead(bt[5]) == HIGH){
    tone(passiveB, melody[5]);
  }
  else if(digitalRead(bt[6]) == HIGH){
    tone(passiveB, melody[6]);
  }
  else if(digitalRead(bt[7]) == HIGH){
    tone(passiveB, melody[7]);
  }
  else{
    noTone(passiveB);
  }
}
