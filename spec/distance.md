---
listings: True
codeBlockCaptions: True
---

\begin{table}[ht!]
    \centering
    \large
    \begin{tabular}{p{2cm}|p{13cm}} \hline
        装置名          &         \\\hline
        装置番号        & 002-004           \\\hline
        作問者          & Norimasa TAKANA   \\\hline
        作問日          & 2024 09/13        \\\hline
        制限時間        & 15m00s            \\\hline
    \end{tabular}
\end{table}

# 作問者より一言
やっぱり最初は定番のこれ！
落ち着いてよくプログラムを読めばどっちを切るべきか分かるはずです．
ピンの設定がプルアップになっていることに注意！

# 回路
回路の全体の写真を[@fig:circuit]に示す．

![回路全体の写真](./images/circuit_000.jpg){#fig:circuit}

また，回路に使用する部品の一覧を[@tbl:parts]に示す．

部品名          個数        データシート
------          ------      ------------
HC-SR04         1           ???

: 回路に使用する部品の一覧 {#tbl:parts}

# ソースコード
[@lst:code]に競技に使用するソースコードを示す．
```{.cpp #lst:code caption="競技に使用するソースコード" title="timer.ino"}
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
	bool flag4 = false;
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

        if (flag1 && cm < 8) {
            flag3 = true;
        }
		
        if (flag2 && cm > 10) {
            flag4 = true;
        }
		
		// succeeded
		if(flag3 || flag4) {
            succeeded();
		}

		// failed
		if(flag1 && flag2) {
            failed();
		}
	}
}
```
