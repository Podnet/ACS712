#pragma once

extern "C" {

    #define ADC_SCALE 1023.0
    #define VREF 5.0
    #define DEFAULT_FREQUENCY 50

    enum ACS712_type {ACS712_05B, ACS712_20A, ACS712_30A};
    int mgos_acs712_setup(uint8_t _pin);
    float mgos_acs712_get_current_dc(ACS712_type type, uint8_t _pin);
}