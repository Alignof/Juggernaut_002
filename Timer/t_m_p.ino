//=============================================================================
//  START of giver code (copy the below code you wrote into the specification)
//=============================================================================

struct Challenge TMP = {
    .gaming = t_m_p,
    .setup_pin = setup_pin_tmp,
    .time_limit = 600,
};

// giver pin assgin
const uint8_t BUTTON = 23;
const uint8_t SENSOR = 2;

void setup_pin_tmp(void) {

	pinMode(BUTTON, INPUT_PULLUP);
	pinMode(SENSOR, ANALOG);
}

void t_m_p(void *pvParameters) {
    int sensor_value = 0;
    float tmv, tmp;
	bool flag1 = false;
	bool flag2 = false;

	while(1) {
        sensor_value = analogRead(SENSOR);    
        tmv = (3300.0/4096.0)*sensor_value;
        tmp = (tmv - 500.0)/10.0;

		flag1 = (tmp > 35.0);
		flag2 = (digitalRead(BUTTON) == LOW);
		
		// succeeded
		if(flag1) {
            succeeded();
		}

		// failed
		if(flag2) {
            failed();
		}
	}
}

//=============================================================================
//  END of giver code
//=============================================================================
