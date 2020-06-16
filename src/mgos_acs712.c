#include "mgos_acs712.h"

#include "mgos.h"
#include "mgos_adc.h"

int mgos_acs712_zero_point;


void mgos_acs712_setup(uint8_t _pin) {
    // Enabling ADC on pin
    mgos_adc_enable(_pin);

    int acc = 0;
	for (int i = 0; i < 10; i++) {
		DBG(("ACS712 acc value old: %d", acc));
		acc = acc + mgos_adc_read(_pin);
		// Wait for sometime then read the ADC values, otherwise read value will always be 0
		mgos_msleep(50);
		DBG(("ACS712 acc value new: %d", acc));
	}
	mgos_acs712_zero_point = acc / 10;
	DBG(("ACS712 Calibration value : %d", mgos_acs712_zero_point));
}


float mgos_acs712_get_current(enum ACS712_type type, uint8_t _pin) {
  float sensitivity = 0.0;
  switch (type) {
		case ACS712_05B:
			sensitivity = 0.185;
			break;
		case ACS712_20A:
			sensitivity = 0.100;
			break;
		case ACS712_30A:
			sensitivity = 0.066;
			break;
  }
  DBG(("ACS712 sensitivity: %f", sensitivity));
  DBG(("ACS712 zero point: %d", mgos_acs712_zero_point));

  int adc_reading = mgos_adc_read(_pin);
  int16_t acc = 0;
	for (int i = 0; i < 10; i++) {
		acc += adc_reading - mgos_acs712_zero_point;
	}
  
  DBG(("ACS712 adc reading: %d", adc_reading));
  DBG(("AC712 acc: %d", (int)acc));
  
  // float I = (float)acc / 10.0 / ADC_SCALE * VREF / sensitivity;
  float I = (float)acc / 10.0 / 4095 * 3.3 / sensitivity;
  DBG(("ACS712 current: %f", I));
  
  return I;
}


