// Arduino Uno - Dual Potentiometer Read
// A4, A5 핀에 연결한 가변저항 2개의 값을 각각 읽어서 시리얼 모니터에 출력
//
// [회로]
// 가변저항 1: 바깥 다리 → 5V, 가운데 다리 → A4, 다른 바깥 다리 → GND
// 가변저항 2: 바깥 다리 → 5V, 가운데 다리 → A5, 다른 바깥 다리 → GND

const int POT1_PIN = A4;
const int POT2_PIN = A5;

void setup() {
  Serial.begin(9600);                // 시리얼 통신 시작 (9600bps)
}

void loop() {
  int pot1 = analogRead(POT1_PIN);   // 가변저항 1 값 (0 ~ 1023)
  int pot2 = analogRead(POT2_PIN);   // 가변저항 2 값 (0 ~ 1023)

  // "이름:값" 형식이라 시리얼 플로터에서도 두 선으로 보임
  Serial.print("Pot1:");
  Serial.print(pot1);
  Serial.print("\t");
  Serial.print("Pot2:");
  Serial.println(pot2);

  delay(200);                        // 0.2초마다 출력
}
