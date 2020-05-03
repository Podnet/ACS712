#pragma once

#ifdef __cplusplus
extern "C" {
#endif

    #include <stdint.h>

    #define ADC_SCALE 1023.0
    #define VREF 5.0
    #define DEFAULT_FREQUENCY 50

    enum ACS712_type {ACS712_05B, ACS712_20A, ACS712_30A};
    void mgos_acs712_setup(uint8_t _pin);
    float mgos_acs712_get_current_dc(enum ACS712_type type, uint8_t _pin);

#ifdef __cplusplus
}
#endif