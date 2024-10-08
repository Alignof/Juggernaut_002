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
    long duration, cm;

	while(1) {
		flag1 = (digitalRead(RIGHT_BUTTON)  == LOW);
		flag2 = (digitalRead(LEFT_BUTTON) == LOW);

        digitalWrite(TRIG, LOW);
        delayMicroseconds(5);
        digitalWrite(TRIG, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIG, LOW);

        //duration = read_pulse(ECHO);
        duration = pulseIn(ECHO, HIGH);
        cm = (duration/2) / 29.1;

        if (flag1 && 10 <= cm && cm < 11) {
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

//=============================================================================
//  END of giver code
//=============================================================================
