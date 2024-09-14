#import "../style/spec.typ": *
#show: style.with(
  title: "装置との距離感",
  number: "#002-004",
  author: (
      name: "Norimasa TAKANA",
      organization: [University of Tsukuba],
      email: "alignof@outlook.com"
  ),
  date: datetime(year: 2024, month: 9, day: 14),
  time_limit: datetime(hour: 0, minute: 10, second: 0),
)

#let quote_block(body) = {
  block(
    width: 100%,
    fill: silver,
    inset: 8pt,
    body
  )
}

= 作問者より一言
近くても遠くてもダメ．それが距離感．

= 回路
回路の写真を @circuit に示す．
#figure(
  image("../images/circuit_004.jpg"),
  caption: [回路の写真],
)<circuit>

回路を構成する部品を @parts に示す．
#figure(
  table(
    stroke: (x: none),
    columns: 3,
    table.header([部品名], [個数], [データシート]),
    [???], [1], [#link("https://akizukidenshi.com/goodsaffix/hc-sr04_v20.pdf")]
  ),
  caption: [部品一覧],
)<parts>

= ソースコード
装置に書き込まれたプログラムを以下に示す．
```cpp
struct Challenge Distance = {
    .gaming = distance,
    .setup_pin = setup_dist,
    .time_limit = 900,
};

// giver pin assgin
const uint8_t TRIG = 16;
const uint8_t ECHO = 17;
const uint8_t LEFT_BUTTON = 15;
const uint8_t RIGHT_BUTTON = 19;

void setup_dist(void) {
    pinMode(TRIG,  OUTPUT);
    pinMode(ECHO, INPUT);
    pinMode(LEFT_BUTTON,  INPUT_PULLUP);
    pinMode(RIGHT_BUTTON, INPUT_PULLUP);
}

void distance(void *pvParameters) {
    bool flag1 = false;
    bool flag2 = false;
    bool flag3 = false;
    long duration, cm;

    digitalWrite(TRIG, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    while(1) {
        flag1 = (digitalRead(RIGHT_BUTTON)  == LOW);
        flag2 = (digitalRead(LEFT_BUTTON) == LOW);

        duration = pulseIn(ECHO, HIGH);
        cm = (duration/2) / 29.1;

        if (flag1 && 7 < cm && cm < 11) {
            flag3 = true;
        }
        
        // succeeded
        if(flag3) {
            succeeded();
        }

        // failed
        if(flag1 && flag2) {
            failed();
        }
    }
}
```<program>
