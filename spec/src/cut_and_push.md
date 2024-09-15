---
listings: True
codeBlockCaptions: True
---

\begin{table}[ht!]
    \centering
    \large
    \begin{tabular}{p{2cm}|p{13cm}} \hline
        装置名          & cut and push             \\\hline
        装置番号        & 001-003           \\\hline
        作問者          & Norimasa TAKANA   \\\hline
        作問日          & 2023 12/22        \\\hline
        制限時間        & 15m00s            \\\hline
    \end{tabular}
\end{table}

# 作問者より一言
ボタンとワイヤのシンプルな構成．
とにかく落ち着いて！

# 回路
回路の全体の写真を[@fig:circuit]に示す．

![回路全体の写真](./images/circuit_003.jpg){#fig:circuit}

また，回路に使用する部品の一覧を[@tbl:parts]に示す．

部品名          個数        データシート
------          ------      ------------
タクトスイッチ  2           https://akizukidenshi.com/catalog/g/gP-09828/

: 回路に使用する部品の一覧 {#tbl:parts}

# ソースコード
[@lst:code]に競技に使用するソースコードを示す．
```{.cpp #lst:code caption="競技に使用するソースコード" title="timer.ino"}
struct Challenge CutAndPush = {
    .gaming = cut_and_push,
    .setup_pin = setup_ws,
    .time_limit = 900,
};

// giver pin assgin
const uint8_t ORANGE_WIRE = 23;
const uint8_t GREEN_WIRE = 18;
const uint8_t YELLOW_WIRE = 16;

void setup_cap(void) {
	pinMode(ORANGE_WIRE,  INPUT_PULLUP);
	pinMode(GREEN_WIRE, INPUT_PULLUP);
	pinMode(YELLOW_WIRE, INPUT_PULLUP);
}

void cut_and_push(void *pvParameters) {
	bool flag1 = false;
	bool flag2 = false;
	bool flag3 = false;

	while(1) {
		flag1 = (digitalRead(ORANGE_WIRE)  == LOW);
		flag2 = (digitalRead(GREEN_WIRE) == LOW);
		flag3 = (digitalRead(YELLOW_WIRE) == LOW);
		
		// succeeded
		if(flag1 && flag2) {
            succeeded();
		}

		// failed
		if(flag3) {
            failed();
		}
	}
}
```
