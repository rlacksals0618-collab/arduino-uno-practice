// Arduino Uno - Pin Finder (진단용)
// 2번부터 13번 핀까지 하나씩 1초씩 켜면서, 지금 켜진 핀 번호를 시리얼 모니터에 출력
// LED가 켜지는 순간 시리얼 모니터에 찍힌 번호가 그 LED가 실제로 꽂힌 핀

const int FIRST_PIN = 2;
const int LAST_PIN = 13;
const int ON_MS = 1000;

void setup() {
  for (int pin = FIRST_PIN; pin <= LAST_PIN; pin++) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
  }
  Serial.begin(9600);
  Serial.println("Pin finder start");
}

void loop() {
  for (int pin = FIRST_PIN; pin <= LAST_PIN; pin++) {
    Serial.print("Pin ");
    Serial.print(pin);
    Serial.println(" ON");

    digitalWrite(pin, HIGH);
    delay(ON_MS);
    digitalWrite(pin, LOW);
  }
  Serial.println("----");
}
