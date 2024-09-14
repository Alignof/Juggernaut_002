/*
 * @date		2024 09/14
 * @code name	Juggernaut#002 - what sensor?
 * @author		Norimasa TAKANA <Alignof@outlook.com>
 * @brief		Educational bomb disposal game
 * @repository	https://github.com/Alignof/Juggernaut
 */ 

//=============================================================================
//  START of giver code (copy the below code you wrote into the specification)
//=============================================================================

struct Challenge WhatSensor = {
    .gaming = what_sensor,
    .setup_pin = setup_ws,
    .time_limit = 600,
};

// giver pin assgin
const uint8_t UNKNOWN_WIRE = 18;

void setup_ws(void) {
	pinMode(UNKNOWN_WIRE, INPUT);
}

void what_sensor(void *pvParameters) {
	bool flag1 = false;

	while(1) {
		flag1 = (digitalRead(UNKNOWN_WIRE) == HIGH);
		
		// succeeded
		if(flag1) {
            succeeded();
		}
	}
}

//=============================================================================
//  END of giver code
//=============================================================================
