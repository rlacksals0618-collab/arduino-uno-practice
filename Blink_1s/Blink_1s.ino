// Arduino Uno - Blink (1초 간격)
// 내장 LED(13번 핀)를 1초 간격으로 켰다 껐다 반복

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // 13번 핀을 출력으로 설정
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); // LED 켜기
  delay(1000);                     // 1초 대기
  digitalWrite(LED_BUILTIN, LOW);  // LED 끄기
  delay(1000);                     // 1초 대기
}
