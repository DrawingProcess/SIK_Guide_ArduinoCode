int analogInputPin = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    analogInputPin = Serial.parseInt();
  }
  int analogInputPinValue = analogRead(analogInputPin);

  Serial.print(analogInputPin);
  Serial.print(":");
  Serial.print(analogInputPinValue);
  Serial.println("");

  delay(50);
}
