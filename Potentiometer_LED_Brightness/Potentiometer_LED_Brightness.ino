// Arduino Uno - Potentiometer LED Brightness
// A5 핀 가변저항 값으로 3번 핀 LED 밝기를 조절 (PWM)
//
// [회로]
// 가변저항: 바깥 다리 → 5V, 가운데 다리 → A5, 다른 바깥 다리 → GND
// LED:      3번 핀 → 220Ω 저항 → LED 긴 다리(+),  짧은 다리(−) → GND
// LED는 PWM(~ 표시) 핀에 꽂아야 밝기 조절이 됨: 3, 5, 6, 9, 10, 11

const int POT_PIN = A5;
const int LED_PIN = 3;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);                             // 시리얼 통신 시작 (9600bps)
}

void loop() {
  int potValue = analogRead(POT_PIN);             // 0 ~ 1023 값 읽기
  int brightness = map(potValue, 0, 1023, 0, 255); // PWM 범위(0 ~ 255)로 변환

  analogWrite(LED_PIN, brightness);               // LED 밝기 설정

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Brightness: ");
  Serial.println(brightness);

  delay(50);                                      // 0.05초마다 갱신
}
