/*
 * @date		2024 09/14
 * @code name	Juggernaut#002 - distance
 * @author		Norimasa TAKANA <Alignof@outlook.com>
 * @brief		Educational bomb disposal game
 * @repository	https://github.com/Alignof/Juggernaut
 */ 

//=============================================================================
//  START of giver code (copy the below code you wrote into the specification)
//=============================================================================

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

//=============================================================================
//  END of giver code
//=============================================================================
