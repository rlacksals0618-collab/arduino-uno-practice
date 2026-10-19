// Arduino Uno - Traffic Light + Interrupt
// 7, 8, 9번 핀 LED로 신호등(초록 → 노랑 → 빨강)을 돌리고,
// 2번 핀 버튼을 누르면 인터럽트로 모든 불을 즉시 켬 (3초 뒤 초록부터 다시 시작)
// 신호등은 delay() 대신 millis()로 돌려서 버튼을 누르면 바로 반응함
//
// [회로]
// 빨강 LED: 7번 핀 → 220Ω 저항 → LED 긴 다리(+),  짧은 다리(−) → GND
// 노랑 LED: 8번 핀 → 220Ω 저항 → LED 긴 다리(+),  짧은 다리(−) → GND
// 초록 LED: 9번 핀 → 220Ω 저항 → LED 긴 다리(+),  짧은 다리(−) → GND
// 버튼:     2번 핀 → 버튼 → GND  (내부 풀업 사용, 저항 필요 없음)

const int RED_PIN = 7;
const int YELLOW_PIN = 8;
const int GREEN_PIN = 9;
const int BUTTON_PIN = 2;                // 우노에서 인터럽트 가능한 핀: 2, 3

const unsigned long GREEN_MS = 5000;     // 초록불 시간
const unsigned long YELLOW_MS = 2000;    // 노란불 시간
const unsigned long RED_MS = 5000;       // 빨간불 시간
const unsigned long ALL_ON_MS = 3000;    // 버튼을 누른 뒤 모든 불이 켜져 있는 시간

enum Light { GREEN, YELLOW, RED };
Light current = GREEN;                   // 지금 켜진 신호
unsigned long stateStart = 0;            // 지금 신호가 시작된 시각

// 인터럽트 함수와 loop()가 같이 쓰는 변수는 volatile로 선언
volatile bool allOnMode = false;
volatile unsigned long allOnStart = 0;

void setAll(int value) {
  digitalWrite(RED_PIN, value);
  digitalWrite(YELLOW_PIN, value);
  digitalWrite(GREEN_PIN, value);
}

void showLight(Light light) {
  digitalWrite(RED_PIN, light == RED ? HIGH : LOW);
  digitalWrite(YELLOW_PIN, light == YELLOW ? HIGH : LOW);
  digitalWrite(GREEN_PIN, light == GREEN ? HIGH : LOW);
}

// 버튼을 누르는 순간 실행되는 인터럽트 함수 (짧게 유지)
void onButton() {
  setAll(HIGH);                          // 모든 불을 즉시 켬
  allOnStart = millis();                 // 다시 누르면 3초를 처음부터 다시 셈
  allOnMode = true;
}

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);     // 안 누르면 HIGH, 누르면 LOW

  // 버튼을 누르는 순간(HIGH → LOW)에 onButton() 실행
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), onButton, FALLING);

  Serial.begin(9600);
  Serial.println("Traffic light start");

  current = GREEN;
  stateStart = millis();
  showLight(current);
}

void loop() {
  static bool wasAllOn = false;
  bool allOnEnded = false;

  // 인터럽트와 겹치지 않게 공유 변수를 확인하고 정리
  noInterrupts();
  bool allOn = allOnMode;
  if (allOn && millis() - allOnStart >= ALL_ON_MS) {
    allOnMode = false;
    allOnEnded = true;
  }
  interrupts();

  if (allOn && !wasAllOn) {
    Serial.println("Button -> ALL ON");
  }
  wasAllOn = allOn && !allOnEnded;

  if (allOnEnded) {
    // 모두 켜짐이 끝나면 초록부터 다시 시작
    Serial.println("Resume -> GREEN");
    current = GREEN;
    stateStart = millis();
    showLight(current);
    return;
  }

  if (allOn) {
    return;                              // 모두 켜져 있는 동안은 신호등을 멈춤
  }

  // 신호등: 정해진 시간이 지나면 다음 신호로 넘어감
  unsigned long elapsed = millis() - stateStart;

  if (current == GREEN && elapsed >= GREEN_MS) {
    current = YELLOW;
    Serial.println("YELLOW");
  } else if (current == YELLOW && elapsed >= YELLOW_MS) {
    current = RED;
    Serial.println("RED");
  } else if (current == RED && elapsed >= RED_MS) {
    current = GREEN;
    Serial.println("GREEN");
  } else {
    return;                              // 아직 바꿀 시간이 아님
  }

  stateStart = millis();
  showLight(current);
}
