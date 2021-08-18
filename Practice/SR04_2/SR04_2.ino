const int trigPin = 11;
const int echoPin = 12;

const int red = 3;
const int green = 5;
const int blue = 6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long timeDistance = pulseIn(echoPin, HIGH);
  long distance = (timeDistance/2) / 29.1;

  Serial.print(distance);
  Serial.println("cm"); 
  
  if(distance <= 5){
    analogWrite(red, 255);
    analogWrite(green, 0);
    analogWrite(blue,0);
    delay(1000);
  }
  else if(distance <= 10){
    analogWrite(red, 0);
    analogWrite(green, 255);
    analogWrite(blue,0);
    delay(1000);
  }
  else{
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue,255);
    delay(1000);
  }
}
