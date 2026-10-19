// Arduino Uno - Button Click Patterns
// A0 버튼 입력을 구분해서 A5 LED를 제어
//   - 빠르게 두 번 누르기(더블 클릭) → LED 켜기
//   - 길게 누르기(롱 프레스)          → LED 끄기
//   - 한 번만 누르기(싱글 클릭)        → 아무것도 안 함
// millis()로 디바운싱하고, 현재값과 과거값을 비교해서 눌림/떼짐 순간을 잡음
//
// [회로]
// 버튼(풀다운): 5V → 버튼 → A0,  A0 → 10kΩ 저항 → GND
// LED:          A5 → 220Ω 저항 → LED 긴 다리(+),  LED 짧은 다리(−) → GND

const int BUTTON_PIN = A0;
const int LED_PIN = A5;

const int PRESSED = HIGH;                // 풀다운이면 HIGH, 풀업 회로면 LOW로 변경
const unsigned long DEBOUNCE_MS = 50;    // 이 시간 동안 값이 그대로여야 진짜 입력으로 인정
const unsigned long DOUBLE_GAP_MS = 400; // 첫 클릭을 뗀 뒤 이 시간 안에 다시 눌러야 더블 클릭
const unsigned long LONG_PRESS_MS = 1000;// 이 시간 이상 누르고 있으면 롱 프레스

int lastReading = !PRESSED;              // 과거값: 직전 loop에서 읽은 값
int buttonState = !PRESSED;              // 디바운싱이 끝난 안정된 버튼 상태
unsigned long lastChangeTime = 0;        // 읽은 값이 마지막으로 바뀐 시각

unsigned long pressStartTime = 0;        // 버튼을 누르기 시작한 시각
unsigned long lastReleaseTime = 0;       // 마지막으로 짧게 눌렀다 뗀 시각
bool longPressHandled = false;           // 이번 누름에서 롱 프레스를 이미 처리했는지
int clickCount = 0;                      // 더블 클릭을 기다리는 동안 쌓인 짧은 클릭 수

void setup() {
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);                    // 시리얼 통신 시작 (9600bps)
  Serial.println("Ready");
}

void loop() {
  unsigned long now = millis();
  int reading = digitalRead(BUTTON_PIN); // 현재값

  // 현재값이 과거값과 다르면 접점이 흔들리는 중일 수 있으니 시간을 다시 잼
  if (reading != lastReading) {
    lastChangeTime = now;
  }

  // 값이 DEBOUNCE_MS 동안 그대로 유지됐고, 안정된 상태와 다르면 진짜 변화로 인정
  if (now - lastChangeTime > DEBOUNCE_MS && reading != buttonState) {
    buttonState = reading;

    if (buttonState == PRESSED) {
      // 눌린 순간
      pressStartTime = now;
      longPressHandled = false;
    } else if (!longPressHandled) {
      // 짧게 눌렀다 뗀 순간
      clickCount++;
      lastReleaseTime = now;

      if (clickCount == 2) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Double click -> LED ON");
        clickCount = 0;
      }
    }
  }

  // 누르고 있는 시간이 LONG_PRESS_MS를 넘으면 뗄 때까지 기다리지 않고 바로 처리
  if (buttonState == PRESSED && !longPressHandled && now - pressStartTime >= LONG_PRESS_MS) {
    longPressHandled = true;
    clickCount = 0;                      // 앞에 있던 짧은 클릭은 무시
    digitalWrite(LED_PIN, LOW);
    Serial.println("Long press -> LED OFF");
  }

  // 한 번 누른 뒤 DOUBLE_GAP_MS 안에 다시 안 누르면 싱글 클릭으로 끝냄
  if (clickCount == 1 && buttonState != PRESSED && now - lastReleaseTime > DOUBLE_GAP_MS) {
    Serial.println("Single click -> ignored");
    clickCount = 0;
  }

  lastReading = reading;                 // 현재값을 다음 loop의 과거값으로 저장
}
