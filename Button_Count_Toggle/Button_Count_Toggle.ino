// Arduino Uno - Button Press Counter + LED Toggle
// A0 버튼을 누른 횟수를 시리얼 모니터에 출력하고, 5번 누를 때마다 A5 LED를 토글
// millis()로 디바운싱하고, 현재값과 과거값을 비교해서 눌리는 순간만 셈
//
// [회로]
// 버튼(풀다운): 5V → 버튼 → A0,  A0 → 10kΩ 저항 → GND
// LED:          A5 → 220Ω 저항 → LED 긴 다리(+),  LED 짧은 다리(−) → GND

const int BUTTON_PIN = A0;
const int LED_PIN = A5;

const int PRESSED = HIGH;               // 풀다운이면 HIGH, 풀업 회로면 LOW로 변경
const unsigned long DEBOUNCE_MS = 50;   // 이 시간 동안 값이 그대로여야 진짜 입력으로 인정
const int TOGGLE_EVERY = 5;             // 몇 번마다 LED를 토글할지

int lastReading = !PRESSED;             // 과거값: 직전 loop에서 읽은 값
int buttonState = !PRESSED;             // 디바운싱이 끝난 안정된 버튼 상태
unsigned long lastChangeTime = 0;       // 읽은 값이 마지막으로 바뀐 시각

int pressCount = 0;
bool ledOn = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);                   // 시리얼 통신 시작 (9600bps)
  Serial.println("Ready");
}

void loop() {
  int reading = digitalRead(BUTTON_PIN);  // 현재값

  // 현재값이 과거값과 다르면 접점이 흔들리는 중일 수 있으니 시간을 다시 잼
  if (reading != lastReading) {
    lastChangeTime = millis();
  }

  // 값이 DEBOUNCE_MS 동안 그대로 유지됐고, 안정된 상태와 다르면 진짜 변화로 인정
  if (millis() - lastChangeTime > DEBOUNCE_MS && reading != buttonState) {
    buttonState = reading;

    // 안 눌림 → 눌림으로 바뀌는 순간에만 카운트
    if (buttonState == PRESSED) {
      pressCount++;
      Serial.print("Press count: ");
      Serial.println(pressCount);

      if (pressCount % TOGGLE_EVERY == 0) {
        ledOn = !ledOn;
        digitalWrite(LED_PIN, ledOn ? HIGH : LOW);
        Serial.print("LED toggled: ");
        Serial.println(ledOn ? "ON" : "OFF");
      }
    }
  }

  lastReading = reading;                 // 현재값을 다음 loop의 과거값으로 저장
}
