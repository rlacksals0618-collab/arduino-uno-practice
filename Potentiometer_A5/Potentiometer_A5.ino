// Arduino Uno - Potentiometer Read
// A5 핀에 연결한 가변저항 값을 읽어서 시리얼 모니터에 출력

const int POT_PIN = A5;

void setup() {
  Serial.begin(9600);                  // 시리얼 통신 시작 (9600bps)
}

void loop() {
  int value = analogRead(POT_PIN);     // 0 ~ 1023 값 읽기
  float voltage = value * 5.0 / 1023;  // 전압(0 ~ 5V)으로 변환

  Serial.print("Value: ");
  Serial.print(value);
  Serial.print("  Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");

  delay(200);                          // 0.2초마다 출력
}
