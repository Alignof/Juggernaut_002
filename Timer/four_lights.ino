/*
 * @date		2024 09/14
 * @code name	Juggernaut#002 - four lights
 * @author		Norimasa TAKANA <Alignof@outlook.com>
 * @brief		Educational bomb disposal game
 * @repository	https://github.com/Alignof/Juggernaut
 */ 

//=============================================================================
//  START of giver code (copy the below code you wrote into the specification)
//=============================================================================

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

//=============================================================================
//  END of giver code
//=============================================================================
