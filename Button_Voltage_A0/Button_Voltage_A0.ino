// Arduino Uno - Button Voltage Read
// A0 핀에 연결한 버튼의 전압을 읽어서 시리얼 모니터에 출력
//
// [회로 - 풀다운]
// 5V → 버튼 → A0
// A0 → 10kΩ 저항 → GND
// 버튼을 누르면 약 5V, 떼면 약 0V

const int BUTTON_PIN = A0;

void setup() {
  Serial.begin(9600);                     // 시리얼 통신 시작 (9600bps)
}

void loop() {
  int value = analogRead(BUTTON_PIN);     // 0 ~ 1023 값 읽기
  float voltage = value * 5.0 / 1023;     // 전압(0 ~ 5V)으로 변환

  Serial.print("Value: ");
  Serial.print(value);
  Serial.print("  Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(200);                             // 0.2초마다 출력
}
