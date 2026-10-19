// Arduino Uno - LED Sequence
// 3, 4, 5번 핀 LED를 순서대로 하나씩 깜빡임 (3 → 4 → 5 → 3 ...)
//
// [회로]
// 각 핀 → 220Ω 저항 → LED 긴 다리(+),  짧은 다리(−) → GND

const int LED_PINS[] = {3, 4, 5};
const int NUM_LEDS = 3;
const int ON_MS = 500;                 // 한 LED가 켜져 있는 시간 (0.5초)

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], HIGH);   // i번째 LED 켜기
    delay(ON_MS);
    digitalWrite(LED_PINS[i], LOW);    // 끄고 다음 LED로
  }
}
