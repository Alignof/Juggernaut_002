/*
 * @date		2024 09/14
 * @code name	Juggernaut#002 - flip side
 * @author		Norimasa TAKANA <Alignof@outlook.com>
 * @brief		Educational bomb disposal game
 * @repository	https://github.com/Alignof/Juggernaut
 */ 

//=============================================================================
//  START of giver code (copy the below code you wrote into the specification)
//=============================================================================

#include <Wire.h>
struct Challenge FlipSide = {
    .gaming = distance,
    .setup_pin = setup_fs,
    .time_limit = 600,
};

uint8_t acce_data[6];
const uint8_t DEVICE_ADDRESS = 0x1D;

// giver pin assgin
const uint8_t mySCL  = 22;
const uint8_t mySDA  = 23;

void setup_fs(void) {
	pinMode(mySCL, INPUT_PULLUP);
	pinMode(mySDA, INPUT_PULLUP);

    Wire.begin(mySDA, mySCL);
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x31);
	Wire.write(0x0B);
	Wire.endTransmission();
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x2d);
	Wire.write(0x08);
	Wire.endTransmission();
}

void getAccelerationData(void) {
	Wire.beginTransmission(DEVICE_ADDRESS);
	Wire.write(0x32);
	Wire.endTransmission();

	Wire.requestFrom(DEVICE_ADDRESS, 6);

	for(int i = 0; i < 6; i++) {
		delay(1);
		acce_data[i] = Wire.read();
	}
}

void flip_side(void *pvParameters) {
    bool flag1 = false;
    bool flag2 = false;
    double ax = 0;
    double ay = 0;
    double az = 0;

	while(1) {
        getAccelerationData();
        ax = (int16_t)((acce_data[1] << 8) | acce_data[0]) * 0.0392266;
        ay = (int16_t)((acce_data[3] << 8) | acce_data[2]) * 0.0392266;
        az = (int16_t)((acce_data[5] << 8) | acce_data[4]) * 0.0392266;

        Serial.printf("ax: %g, ay: %g, az: %g\n", ax, ay, az);
        flag1 = az > -9.0;
        flag2 = az > 12.0;
		
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

