/*
 * @date		2024 09/15
 * @code name	Juggernaut#002 - enJoy!
 * @author		Norimasa TAKANA <Alignof@outlook.com>
 * @brief		Educational bomb disposal game
 * @repository	https://github.com/Alignof/Juggernaut
 */ 

//=============================================================================
//  START of giver code (copy the below code you wrote into the specification)
//=============================================================================

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

//=============================================================================
//  END of giver code
//=============================================================================

