const int activeB =10;

void setup() {
  // put your setup code here, to run once:
  pinMode(activeB, OUTPUT);

  for(int i =0; i<3; i++){
    digitalWrite(activeB, HIGH);
    delay(2000);
    digitalWrite(activeB, LOW);
    delay(2000);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
