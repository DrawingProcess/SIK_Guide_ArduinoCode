const int LED_R_PIN = 10;
const int LED_G_PIN = 11;
const int LED_B_PIN = 9;
const int SOUND_PIN = A2;
// 전역변수
boolean sound_is_activate = true; // 버튼 활성화 상태, 한번 길게 터치로 여러번 실행되는것을 막는다.
int sound_step = 0; // 버튼 정지(0)
int SOUND_THRESHOLD = 500;
float red = 0; //0~255의 밝기 값
float blue = 170;
float green = 85;
float bright_control = 0.1;
float red_bright_control = 0.1;
float blue_bright_control = 0.1;
float green_bright_control = 0.1;
float x = 0;

void sound_pressed() {
  if (sound_step == 0) { //꺼짐
    analogWrite(LED_R_PIN, 255);
    analogWrite(LED_G_PIN, 255);
    analogWrite(LED_B_PIN, 255);
    delay(1);
    return;
  }
  else if (sound_step == 1) { //흰색 켜짐
    analogWrite(LED_R_PIN, 0);
    analogWrite(LED_G_PIN, 0);
    analogWrite(LED_B_PIN, 0);
    delay(1);
    return;
  }
  else if (sound_step == 2) { //흰색 밝기변화
    analogWrite(LED_R_PIN, 0);
    analogWrite(LED_G_PIN, 0);
    analogWrite(LED_B_PIN, 1);
    delay(1);
  }
  else if (sound_step == 3) { //3색숨쉬는LED
    analogWrite(LED_R_PIN, red);
    analogWrite(LED_G_PIN, green);
    analogWrite(LED_B_PIN, blue);
    delay(1);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(SOUND_PIN, INPUT);
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

void loop() {
  sound_pressed();
  int temp = analogRead(SOUND_PIN);
  if(temp < 800)
    Serial.println(temp);
  if (temp < SOUND_THRESHOLD) {
    if (sound_is_activate) {
      sound_step++;
      if (sound_step >= 4) {
        sound_step = 0;
      }
      sound_is_activate = false; // 한번만 실행될 수 있게 버튼 비활성화
      Serial.println(sound_step);
    }
    delay(300);
  }
  else {
    sound_is_activate = true;
    delay(1);
  }
}
