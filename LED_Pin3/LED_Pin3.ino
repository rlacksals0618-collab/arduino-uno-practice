// Arduino Uno - LED On/Off
// 3번 핀에 연결한 LED를 1초 간격으로 켰다 껐다 반복

const int LED_PIN = 3;

void setup() {
  pinMode(LED_PIN, OUTPUT);    // 3번 핀을 출력으로 설정
}

void loop() {
  digitalWrite(LED_PIN, HIGH); // LED 켜기
  delay(1000);                 // 1초 대기
  digitalWrite(LED_PIN, LOW);  // LED 끄기
  delay(1000);                 // 1초 대기
}
