#ifndef STX7105_UTILS_H
#define STX7105_UTILS_H

#include <stdint.h>

void init_led(PIO_TypeDef *gpiox, uint8_t pin, uint8_t init_value);
void set_led(PIO_TypeDef *gpiox, uint8_t pin, uint8_t val);

void delay_ms(uint32_t msec);

#endif