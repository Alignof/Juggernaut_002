#import "../style/spec.typ": *
#show: style.with(
  title: "enJoyStick",
  number: "#002-006",
  author: (
      name: "Norimasa TAKANA",
      organization: [University of Tsukuba],
      email: "alignof@outlook.com"
  ),
  date: datetime(year: 2024, month: 9, day: 14),
  time_limit: datetime(hour: 0, minute: 15, second: 0),)

#let quote_block(body) = {
  block(
    width: 100%,
    fill: silver,
    inset: 8pt,
    body
  )
}

= 作問者より一言
ジョイスティックを使った問題です．楽しんで！

= 回路
回路の写真を @circuit に示す．
#figure(
  image("../images/circuit_006.jpg"),
  caption: [回路の写真],
)<circuit>

回路を構成する部品を @parts に示す．
#figure(
  table(
    stroke: (x: none),
    columns: 3,
    table.header([部品名], [個数], [データシート]),
    [KY-023], [1], [#link("https://naylampmechatronics.com/img/cms/Datasheets/000036%20-%20datasheet%20KY-023-Joy-IT.pdf")],
    [LED], [4], [],
  ),
  caption: [部品一覧],
)<parts>

= ソースコード
装置に書き込まれたプログラムを以下に示す．
```cpp
struct Challenge EnJoy = {
    .gaming = enjoy,
    .setup_pin = setup_ej,
    .time_limit = 900,
};

// giver pin assgin
const uint8_t VRx = 15;
const uint8_t VRy = 2;
const uint8_t SW = 4;
const uint8_t LED_UP = 18;
const uint8_t LED_RIGHT = 23;
const uint8_t LED_DOWN = 22;
const uint8_t LED_LEFT = 17;

const uint8_t LED_NUM = 5;
const uint8_t STAGE_NUM = 5;
const uint8_t MISS_NUM = 5;

enum direction {
    Up,
    Right,
    Down,
    Left,
    Neutral,
};

uint8_t led_pin_assign[LED_NUM] = {LED_UP, LED_RIGHT, LED_DOWN, LED_LEFT};
bool led_map[STAGE_NUM][LED_NUM] = {
    {true, false, false, false},
    {false, true, false, false},
    {false, false, false, true},
    {false, false, true, false},
    {true, false, false, false},
};

void setup_ej(void) {
	pinMode(VRx, ANALOG);
	pinMode(VRy, ANALOG);
	pinMode(SW, INPUT_PULLUP);
	pinMode(LED_UP, OUTPUT);
	pinMode(LED_DOWN, OUTPUT);
	pinMode(LED_RIGHT, OUTPUT);
	pinMode(LED_LEFT, OUTPUT);
}


void enjoy(void *pvParameters) {
    uint16_t x = 0;
    uint16_t y = 0;
    uint8_t stage = 0;
    uint8_t miss = 0;
    enum direction dir = Neutral;

	while(1) {
        for (int i = 0; i < LED_NUM; i++) {
            if (led_map[stage][i]) digitalWrite(led_pin_assign[i], HIGH);
            else digitalWrite(led_pin_assign[i], LOW);
        }

        x = analogRead(VRx);
        y = analogRead(VRy);

        dir = Neutral;
        if (x >= 3500) dir = Up;
        if (y >= 3500) dir = Right;
        if (x <= 500) dir = Down;
        if (y <= 500) dir = Left;

        if (dir != Neutral) {
            if (led_map[stage][dir]) {
                stage++;
                delay(500);
            } else {
                miss++;
                delay(500);
            }
        }

		// succeeded
		if(stage == STAGE_NUM) {
            succeeded();
		}

		// failed
		if(miss == MISS_NUM) {
            failed();
		}
	}
}
```<program>

