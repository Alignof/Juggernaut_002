---
listings: True
codeBlockCaptions: True
---

\begin{table}[ht!]
    \centering
    \large
    \begin{tabular}{p{2cm}|p{13cm}} \hline
        装置名          & four lights   \\\hline
        装置番号        & 001-001           \\\hline
        作問者          & Norimasa TAKANA   \\\hline
        作問日          & 2023 12/22        \\\hline
        制限時間        & 15m00s            \\\hline
    \end{tabular}
\end{table}

# 作問者より一言
何やら難しい式が書かれてる……
でも LED がヒントになるかも？

# 回路
回路の全体の写真を[@fig:circuit]に示す．

![回路全体の写真](./images/circuit_001.jpg){#fig:circuit}

また，回路に使用する部品の一覧を[@tbl:parts]に示す．

部品名          個数        データシート
------          ------      ------------
LED             4           
タクトスイッチ  4           https://akizukidenshi.com/catalog/g/gP-09828/

: 回路に使用する部品の一覧 {#tbl:parts}

# ソースコード
[@lst:code]に競技に使用するソースコードを示す．
```{.cpp #lst:code caption="競技に使用するソースコード" title="timer.ino"}
struct Challenge FourLights = {
    .gaming = four_lights,
    .setup_pin = setup_fl,
    .time_limit = 900,
};


// giver pin assgin
const uint8_t BLACK_BUTTON1 = 15;
const uint8_t BLACK_BUTTON2 = 16;
const uint8_t BLACK_BUTTON3 = 19;
const uint8_t BLACK_BUTTON4 = 22;
const uint8_t BLACK_LED1 = 2;
const uint8_t BLACK_LED2 = 17;
const uint8_t BLACK_LED3 = 21;
const uint8_t BLACK_LED4 = 23;

const uint8_t blue_led_pins[4] = {BLACK_LED1, BLACK_LED2, BLACK_LED3, BLACK_LED4};
const uint8_t black_button_pins[4] = {BLACK_BUTTON1, BLACK_BUTTON2, BLACK_BUTTON3, BLACK_BUTTON4};

void setup_fl(void) {
	pinMode(BLACK_BUTTON1, INPUT_PULLUP);
	pinMode(BLACK_BUTTON2, INPUT_PULLUP);
	pinMode(BLACK_BUTTON3, INPUT_PULLUP);
	pinMode(BLACK_BUTTON4, INPUT_PULLUP);
	pinMode(BLACK_LED1, OUTPUT);
	pinMode(BLACK_LED2, OUTPUT);
	pinMode(BLACK_LED3, OUTPUT);
	pinMode(BLACK_LED4, OUTPUT);
}

void four_lights(void *pvParameters) {
    bool next_step = false;
    uint8_t step = 0;
    uint8_t miss = 0;
    uint8_t ans[5] = {0, 0, 0, 0, 0};

    // ???
    ans[0] = (44049 * 3213 / 0xff + 012411) % 4;
    ans[1] = (2449 + 3123 / 0xbb + 0177213) % 4;
    ans[2] = (2147 + 1323 - 0xcb + 01670) % 4;
    ans[3] = (5489 - 3132 + 0x3d + 01732) % 4;
    ans[4] = (119 + 3132 + 0x1d + 01731) % 4;

	while (1) {
        next_step = false;

        for (int i = 0; i < 4; i++) {
            if (i == ans[step]) {
                // bright if 'i' is correct button number
                digitalWrite(blue_led_pins[i], HIGH);
            } else {
                digitalWrite(blue_led_pins[i], LOW);
            }
        }

        delay(1000);
		
        while (1) {
            for (int i = 0; i < 4; i++) {
                if (digitalRead(black_button_pins[i]) == LOW) {
                    if (i == ans[step]) {
                        // correct! go next step
                        step++;
                        next_step = true;
                    } else {
                        // wrong! step is reset
                        // start over from the first step.
                        step = 0;
                        miss++;
                        next_step = true;
                    }

                    break;
                }
            }

            if (next_step) break;
        }

		// succeeded
		if(step >= 5) {
            succeeded();
		}

		// failed
		if(miss >= 3) {
            failed();
		}
	}
}
```
