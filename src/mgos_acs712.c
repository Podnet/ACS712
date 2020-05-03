#include "mgos_acs712.h"

#include "mgos.h"
#include "mgos_adc.h"

int mgos_acs712_zero_point;


void mgos_acs712_setup(uint8_t _pin) {
  mgos_adc_enable(_pin);
  uint16_t acc = 0;
	for (int i = 0; i < 10; i++) {
		acc += mgos_adc_read(_pin);
	}
	mgos_acs712_zero_point = acc / 10;
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
  int16_t acc = 0;
	for (int i = 0; i < 10; i++) {
		acc += mgos_adc_read(_pin) - mgos_acs712_zero_point;
	}
  DBG(("AC712 acc: %d", acc));
	// float I = (float)acc / 10.0 / ADC_SCALE * VREF / sensitivity;
  float I = (float)acc / 10.0 / 4095 * 3.3 / sensitivity;
  DBG(("ACS712 current: %f", I));
  return I;
}


bool mgos_acs712_init(void) {
  return true;
}
