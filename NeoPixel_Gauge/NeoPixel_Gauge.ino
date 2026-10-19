// Arduino Uno - NeoPixel Gauge
// A0 핀 가변저항 값에 따라 네오픽셀 8구를 게이지처럼 채움
// 채워지는 색은 초록 → 노랑 → 빨강 순서, 마지막 칸은 밝기로 중간값까지 표현
// 필요한 라이브러리: Adafruit NeoPixel (라이브러리 매니저에서 설치)
//
// [회로]
// 가변저항: 바깥 다리 → 5V, 가운데 다리 → A0, 다른 바깥 다리 → GND
// 네오픽셀: DIN → 10번 핀,  5V → 5V,  GND → GND

#include <Adafruit_NeoPixel.h>

const int POT_PIN = A0;
const int PIXEL_PIN = 10;
const int NUM_PIXELS = 8;
const int BRIGHTNESS = 50;               // 전체 밝기 (0 ~ 255), USB 전원이면 낮게 유지

Adafruit_NeoPixel strip(NUM_PIXELS, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();                          // 시작할 때 모두 끄기

  Serial.begin(9600);                    // 시리얼 통신 시작 (9600bps)
}

// i번째 칸의 색: 앞쪽은 초록, 가운데는 노랑, 끝은 빨강
uint32_t gaugeColor(int i) {
  int red = map(i, 0, NUM_PIXELS - 1, 0, 255);
  int green = 255 - red;
  return strip.Color(red, green, 0);
}

void loop() {
  int potValue = analogRead(POT_PIN);                    // 0 ~ 1023 값 읽기
  long level = map(potValue, 0, 1023, 0, NUM_PIXELS * 255); // 0 ~ 8칸을 255단계로 쪼갠 값

  for (int i = 0; i < NUM_PIXELS; i++) {
    long fill = level - i * 255L;        // 이 칸이 얼마나 찼는지
    fill = constrain(fill, 0, 255);

    // 꽉 찬 칸은 원래 색, 반쯤 찬 칸은 그만큼 어둡게, 빈 칸은 끔
    uint32_t color = gaugeColor(i);
    uint8_t r = (uint8_t)(color >> 16) * fill / 255;
    uint8_t g = (uint8_t)(color >> 8) * fill / 255;
    uint8_t b = (uint8_t)color * fill / 255;
    strip.setPixelColor(i, r, g, b);
  }
  strip.show();

  Serial.print("Pot: ");
  Serial.print(potValue);
  Serial.print("  Pixels: ");
  Serial.println(level / 255.0, 1);      // 몇 칸 찼는지 (소수점 한 자리)

  delay(20);
}
