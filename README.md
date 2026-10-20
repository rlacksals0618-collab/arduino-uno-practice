# Arduino Uno 실습 모음

청년 피지컬 AI 수업에서 만든 Arduino Uno 예제 스케치 모음입니다.
LED 깜빡이기부터 가변저항, 버튼, 인터럽트, 네오픽셀까지 단계별로 정리했습니다.

모든 스케치는 **Arduino Uno** 기준이며, 각 `.ino` 파일 맨 위 주석에 회로 연결 방법이 적혀 있습니다.

## 한눈에 보기

| 폴더 | 목적 | 사용 핀 |
|---|---|---|
| [Blink](Blink/Blink.ino) | 외부 LED 1초 간격 깜빡이기 | LED: A0 |
| [Blink_1s](Blink_1s/Blink_1s.ino) | 내장 LED 1초 간격 깜빡이기 | 내장 LED(13) |
| [Blink_100ms](Blink_100ms/Blink_100ms.ino) | 내장 LED 0.1초 간격 깜빡이기 | 내장 LED(13) |
| [Blink_50ms](Blink_50ms/Blink_50ms.ino) | 내장 LED 0.05초 간격 깜빡이기 | 내장 LED(13) |
| [Blink_5ms](Blink_5ms/Blink_5ms.ino) | 0.005초 깜빡임으로 잔상 효과 확인 | 내장 LED(13) |
| [LED_Pin3](LED_Pin3/LED_Pin3.ino) | 3번 핀 LED 켜고 끄기 | LED: 3 |
| [LED_Sequence_345](LED_Sequence_345/LED_Sequence_345.ino) | LED 3개 순서대로 점등 | LED: 3, 4, 5 |
| [LED_Sequence_678](LED_Sequence_678/LED_Sequence_678.ino) | LED 3개 순서대로 점등 | LED: 6, 7, 8 |
| [Pin_Finder](Pin_Finder/Pin_Finder.ino) | LED가 실제로 꽂힌 핀 찾기 (진단용) | 2 ~ 13 |
| [Potentiometer_A5](Potentiometer_A5/Potentiometer_A5.ino) | 가변저항 값·전압 읽기 | 가변저항: A5 |
| [Potentiometer_Dual](Potentiometer_Dual/Potentiometer_Dual.ino) | 가변저항 2개 동시에 읽기 | 가변저항: A4, A5 |
| [Potentiometer_LED_Brightness](Potentiometer_LED_Brightness/Potentiometer_LED_Brightness.ino) | 가변저항으로 LED 밝기 조절 | 가변저항: A5, LED: 3 |
| [Button_Voltage_A0](Button_Voltage_A0/Button_Voltage_A0.ino) | 버튼 입력 전압 읽기 | 버튼: A0 |
| [Button_Count_Toggle](Button_Count_Toggle/Button_Count_Toggle.ino) | 버튼 누른 횟수 세기 + 5번마다 LED 토글 | 버튼: A0, LED: A5 |
| [Button_Click_Patterns](Button_Click_Patterns/Button_Click_Patterns.ino) | 더블 클릭 / 길게 누르기 / 한 번 누르기 구분 | 버튼: A0, LED: A5 |
| [Traffic_Light_Interrupt](Traffic_Light_Interrupt/Traffic_Light_Interrupt.ino) | 신호등 + 버튼 인터럽트로 모든 불 켜기 | LED: 7, 8, 9, 버튼: 2 |
| [NeoPixel_Gauge](NeoPixel_Gauge/NeoPixel_Gauge.ino) | 가변저항으로 네오픽셀 게이지 채우기 | 가변저항: A0, 네오픽셀: 10 |
| [Sound_Sensor_Toggle](Sound_Sensor_Toggle/Sound_Sensor_Toggle.ino) | 소리가 날 때마다 LED 토글 + 소리 크기 관찰 | 사운드 센서: A0(AO), 2(DO), LED: 9 |
| [SevenSegment_Button_Counter](SevenSegment_Button_Counter/SevenSegment_Button_Counter.ino) | 버튼을 누를 때마다 7세그먼트 숫자 0~9 증가 | 세그먼트: 2~8, 버튼: 10, LED: 11 |

---

## 1. LED 깜빡이기 (Blink)

### Blink
- **목적**: 아두이노의 가장 기본 예제인 Blink를 외부 LED로 실습합니다.
- **동작**: A0 핀에 연결한 LED가 1초 켜지고 1초 꺼지기를 반복합니다. 아날로그 핀(A0)도 `digitalWrite`로 디지털 출력처럼 쓸 수 있다는 것을 보여 줍니다.
- **회로**: A0 → 220Ω → LED(+), LED(−) → GND

### Blink_1s / Blink_100ms / Blink_50ms / Blink_5ms
- **목적**: `delay()` 값만 바꿔서 깜빡이는 속도가 어떻게 달라 보이는지 비교합니다.
- **동작**: 보드에 달린 내장 LED('L', 13번 핀)를 각각 1초, 0.1초, 0.05초, 0.005초 간격으로 깜빡입니다. 배선이 필요 없습니다.
- **관찰 포인트**
  - `Blink_50ms`: 1초에 10번 깜빡여서 빠르지만 눈으로 보입니다.
  - `Blink_5ms`: 1초에 100번 깜빡여서 눈이 따라가지 못하고, 계속 켜진 채 조금 어둡게 보입니다(잔상 효과). `analogWrite`(PWM) 밝기 조절과 같은 원리입니다.

### LED_Pin3
- **목적**: 디지털 핀(3번)에 연결한 외부 LED를 켜고 끕니다.
- **동작**: 3번 핀 LED가 1초 간격으로 깜빡입니다.
- **회로**: 3번 → 220Ω → LED(+), LED(−) → GND

### LED_Sequence_345 / LED_Sequence_678
- **목적**: 여러 개의 LED를 배열과 `for`문으로 다룹니다.
- **동작**: LED 3개가 0.5초씩 하나씩 순서대로 켜지고, 다시 처음부터 반복합니다.
  - `LED_Sequence_345`: 3 → 4 → 5
  - `LED_Sequence_678`: 6 → 7 → 8
- **수정 방법**: `LED_PINS` 배열의 핀 번호를 바꾸거나 추가하고, `NUM_LEDS`와 `ON_MS`(켜져 있는 시간)를 조절하면 됩니다.
- **회로**: 각 핀 → 220Ω → LED(+), LED(−) → GND

### Pin_Finder (진단용)
- **목적**: 특정 LED만 켜지지 않을 때 선이 실제로 몇 번 핀에 꽂혀 있는지 확인합니다.
- **동작**: 2번부터 13번 핀까지 하나씩 1초씩 켜면서, 지금 켜진 핀 번호를 시리얼 모니터에 `Pin N ON`으로 출력합니다. LED가 켜지는 순간 찍힌 번호가 그 LED가 실제로 연결된 핀입니다.
- **사용법**: 업로드한 뒤 시리얼 모니터(9600 baud)를 열고 LED를 지켜봅니다. 헤더에 선이 한 칸 밀려 꽂혔을 때 바로 찾을 수 있습니다.

---

## 2. 가변저항 (아날로그 입력)

### Potentiometer_A5
- **목적**: `analogRead`로 아날로그 값을 읽고 시리얼 모니터에 출력합니다.
- **동작**: A5 가변저항 값(0~1023)과 이를 전압으로 바꾼 값(0~5V)을 0.2초마다 출력합니다.
- **회로**: 가변저항 바깥 다리 → 5V, 가운데 → A5, 다른 바깥 다리 → GND

### Potentiometer_Dual
- **목적**: 아날로그 입력 두 개를 동시에 읽습니다.
- **동작**: A4와 A5 가변저항 값을 `Pot1:값`, `Pot2:값` 형식(탭으로 구분)으로 출력합니다. 이 형식은 **시리얼 플로터**에서 두 개의 선으로 그려집니다.
- **회로**: 가변저항 1 가운데 → A4, 가변저항 2 가운데 → A5, 바깥 다리는 각각 5V와 GND

### Potentiometer_LED_Brightness
- **목적**: 아날로그 입력(`analogRead`)을 PWM 출력(`analogWrite`)으로 연결합니다.
- **동작**: A5 가변저항을 돌리면 3번 핀 LED가 서서히 밝아지거나 어두워집니다. `map()`으로 0~1023을 0~255로 변환합니다.
- **회로**: 가변저항 가운데 → A5, LED: 3번 → 220Ω → LED(+), LED(−) → GND
- **참고**: 밝기 조절은 PWM 핀(`~` 표시: 3, 5, 6, 9, 10, 11)에서만 됩니다.

---

## 3. 버튼 입력

### Button_Voltage_A0
- **목적**: 버튼을 눌렀을 때와 뗐을 때 핀 전압이 어떻게 바뀌는지 확인합니다.
- **동작**: A0 전압을 0.2초마다 시리얼 모니터에 출력합니다. 풀다운 회로에서는 누르면 약 5V, 떼면 약 0V가 나옵니다.
- **회로 (풀다운)**: 5V → 버튼 → A0, A0 → 10kΩ → GND

### Button_Count_Toggle
- **목적**: `millis()`를 이용한 디바운싱과, 현재값과 과거값을 비교하는 엣지 검출을 익힙니다.
- **동작**: A0 버튼을 누른 횟수를 시리얼 모니터에 출력하고, **5번 누를 때마다** A5 LED를 켜짐과 꺼짐으로 번갈아 바꿉니다.
- **핵심 알고리즘**
  - 현재값이 과거값과 다르면 시간을 다시 잽니다.
  - 50ms 동안 값이 유지되면 진짜 입력으로 인정합니다(디바운싱).
  - 안 눌림에서 눌림으로 바뀌는 순간에만 횟수를 셉니다.
- **조절 값**: `TOGGLE_EVERY`(토글 간격), `DEBOUNCE_MS`, `PRESSED`(풀업 회로면 `LOW`)
- **회로**: 버튼 풀다운 → A0, LED: A5 → 220Ω → LED(+), LED(−) → GND

### Button_Click_Patterns
- **목적**: 버튼 하나로 여러 가지 입력(클릭 패턴)을 구분합니다.
- **동작**

  | 입력 | 결과 |
  |---|---|
  | 빠르게 두 번 누르기 (0.4초 안에) | A5 LED 켜짐 |
  | 길게 누르기 (1초 이상) | A5 LED 꺼짐 |
  | 한 번만 누르기 | 아무것도 안 함 |

- **핵심 알고리즘**: 누른 시각과 뗀 시각을 `millis()`로 기록합니다. 누른 시간으로 롱 프레스를 판단하고, 뗀 뒤 대기 시간 안의 클릭 수로 더블 클릭과 싱글 클릭을 구분합니다.
- **조절 값**: `DOUBLE_GAP_MS`, `LONG_PRESS_MS`, `PRESSED`
- **회로**: Button_Count_Toggle과 같음

---

## 4. 인터럽트

### Traffic_Light_Interrupt
- **목적**: 하드웨어 인터럽트(`attachInterrupt`)로 버튼 입력에 즉시 반응합니다.
- **동작**
  - 평소에는 초록(5초) → 노랑(2초) → 빨강(5초) 신호등이 반복됩니다.
  - 2번 핀 버튼을 누르면 인터럽트가 발생해 **모든 불이 즉시 켜집니다**.
  - 3초 뒤 초록불부터 신호등이 다시 시작합니다.
- **핵심 포인트**
  - 신호등을 `delay()` 대신 `millis()`로 돌려서, 인터럽트로 켠 불이 바로 덮어써지지 않게 했습니다.
  - 인터럽트와 `loop()`가 같이 쓰는 변수는 `volatile`로 선언하고, `noInterrupts()`와 `interrupts()` 사이에서 읽습니다.
  - Uno에서 인터럽트를 쓸 수 있는 핀은 2번과 3번뿐입니다.
- **회로**
  - 빨강 7번, 노랑 8번, 초록 9번: 각 핀 → 220Ω → LED(+), LED(−) → GND
  - 버튼: 2번 → 버튼 → GND (내부 풀업 `INPUT_PULLUP` 사용, 저항 필요 없음)

---

## 5. 네오픽셀

### NeoPixel_Gauge
- **목적**: 가변저항 값을 네오픽셀(WS2812) 8구 게이지로 표시합니다.
- **동작**: A0 가변저항을 돌리면 0칸부터 8칸까지 게이지가 차오릅니다. 색은 초록 → 노랑 → 빨강으로 바뀌고, 마지막 칸은 차는 정도만큼 밝기가 변해서 부드럽게 채워집니다.
- **필요 라이브러리**: Adafruit NeoPixel (IDE의 **도구 → 라이브러리 관리**에서 설치)
- **회로**
  - 가변저항 가운데 → A0, 바깥 다리 → 5V와 GND
  - 네오픽셀 DIN → 10번, 5V → 5V, GND → GND
- **참고**: USB 전원으로도 안정적으로 동작하도록 `BRIGHTNESS = 50`으로 낮춰 두었습니다. 색이 뒤바뀌어 보이면 `NEO_GRB`를 `NEO_RGB`로 바꿔 보세요.

---

## 6. 사운드 센서

### Sound_Sensor_Toggle
- **목적**: 사운드 센서 모듈의 디지털 출력(DO)과 아날로그 출력(AO)을 함께 사용합니다. DO로는 소리 이벤트를 감지하고, AO로는 소리 크기를 관찰합니다.
- **동작**
  - 소리가 모듈의 기준값을 넘는 순간 9번 LED가 켜짐과 꺼짐으로 번갈아 바뀌고, 반응 횟수(`Count`)가 1 올라갑니다.
  - 0.1초마다 시리얼 모니터에 AO 값, 소리 크기(Peak), DO 상태, LED 상태, 반응 횟수를 출력합니다.
- **특징**
  - **엣지 검출**: 현재 DO 상태(`active`)와 직전 상태(`wasActive`)를 비교해서, 소리가 기준을 **넘어서는 순간**에만 반응합니다. 소리가 계속 나도 LED가 마구 깜빡이지 않습니다.
  - **쿨다운**: 한 번 반응한 뒤 `COOLDOWN_MS`(0.25초) 동안은 무시합니다. 박수 한 번에 여러 번 반응하는 것을 막습니다.
  - **Peak-to-Peak 측정**: 마이크 AO는 0을 중심으로 흔들리는 파형이라 한 번 읽은 값만으로는 소리 크기를 알기 어렵습니다. 그래서 20ms 구간의 최댓값에서 최솟값을 뺀 값(`Peak`)으로 소리 크기를 나타냅니다.
  - **`F()` 매크로**: 시리얼로 출력하는 문자열을 RAM이 아닌 플래시 메모리에 저장해서 메모리를 아낍니다.
- **회로**
  - 사운드 센서: AO → A0, DO → 2번, VCC → 5V, GND → GND
  - LED: 9번 → 220Ω → LED(+), LED(−) → GND
- **조절 방법**
  - 소리가 없는데 LED가 계속 바뀌면 모듈의 감도 조절 나사(파란 가변저항)를 돌려 기준값을 높입니다.
  - 소리를 내도 반응이 없으면 모듈의 DO 방향이 반대일 수 있으니 `ACTIVE_LEVEL`을 `HIGH`로 바꿉니다.
- **참고**: 출력에서 `"Peak:"` 앞에 띄어쓰기가 없어 `AO:512Peak:30`처럼 붙어서 나옵니다. 시리얼 플로터로 볼 때는 `F(" Peak:")`로 고치면 두 값이 나뉘어 그려집니다.

---

## 7. 7세그먼트 디스플레이

### SevenSegment_Button_Counter
- **목적**: 한 자리 7세그먼트 디스플레이에 숫자를 표시하고, 버튼 입력으로 숫자를 바꿉니다.
- **동작**
  - 처음에는 0이 표시되고, 버튼을 누를 때마다 1씩 올라갑니다. 9 다음에는 다시 0으로 돌아갑니다.
  - 11번 LED는 숫자가 **0일 때만** 켜집니다.
  - 시리얼 모니터에 `Digit:3`처럼 지금 숫자를 출력합니다.
- **특징**
  - **비트 패턴 표**: 숫자 0~9마다 켜야 할 세그먼트를 1바이트(`DIGITS[]`)로 저장합니다. 각 비트가 A~G 세그먼트 하나에 해당합니다. 예: `0x06` = `0b0000110` → B, C만 켜서 숫자 1을 표시합니다.
  - **`bitRead()`**: 패턴에서 비트를 하나씩 꺼내 해당 세그먼트 핀에 그대로 출력합니다. 숫자마다 `if`문을 쓰지 않아도 됩니다.
  - **디바운싱**: 버튼 값이 35ms 동안 그대로 유지돼야 진짜 입력으로 인정하고, 눌리는 순간(HIGH → LOW)에만 숫자를 올립니다.
  - **나머지 연산**: `(number + 1) % 10`으로 9 다음을 0으로 되돌립니다.
- **회로**
  - 7세그먼트 A, B, C, D, E, F, G → 2, 3, 4, 5, 6, 7, 8번 (각각 330Ω 저항을 거쳐 연결)
  - 7세그먼트 COM → GND (**공통 캐소드** 기준)
  - 버튼: 10번 → 버튼 → GND (내부 풀업 `INPUT_PULLUP` 사용, 저항 필요 없음)
  - LED: 11번 → 220Ω → LED(+), LED(−) → GND
- **문제 해결**
  - 세그먼트가 전부 꺼져 있거나 반대로 켜지면 **공통 애노드** 제품일 수 있습니다. 이 코드는 공통 캐소드용입니다.
  - 숫자 모양이 이상하면 A~G 핀 순서가 바뀌어 꽂혔는지 확인합니다.

---

## 업로드 방법

### Arduino IDE
1. 원하는 폴더의 `.ino` 파일을 엽니다. 폴더 이름과 파일 이름이 같아야 합니다.
2. **도구 → 보드**에서 `Arduino Uno`를, **도구 → 포트**에서 연결된 COM 포트를 고릅니다.
3. 업로드 버튼을 누릅니다.
4. 시리얼 출력이 있는 스케치는 시리얼 모니터 속도를 **9600 baud**로 맞춥니다.

### Arduino CLI
```bash
arduino-cli board list                                         # 연결된 보드와 포트 확인
arduino-cli compile --fqbn arduino:avr:uno --upload -p COM4 Blink_1s
```

> 경로에 한글이 포함되어 있으면 arduino-cli 컴파일이 실패할 수 있습니다. 그럴 때는 스케치 폴더를 영어 경로로 복사한 뒤 실행하세요.
