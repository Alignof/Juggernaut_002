/*
 * @date		2024 09/14
 * @code name	Juggernaut#002 - button-wire-button
 * @author		Norimasa TAKANA <Alignof@outlook.com>
 * @brief		Educational bomb disposal game
 * @repository	https://github.com/Alignof/Juggernaut
 */ 

//=============================================================================
//  START of giver code (copy the below code you wrote into the specification)
//=============================================================================

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

//=============================================================================
//  END of giver code
//=============================================================================
