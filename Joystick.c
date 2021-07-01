#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pins.h"
#include "joystick.h"

void joystick_init()
{
    adc_init();
    adc_gpio_init(JOYSTICK_X_AXIS_GPIO_PIN);
    adc_gpio_init(JOYSTICK_Y_AXIS_GPIO_PIN);
}

uint16_t joystick_read_x_axis()
{

    adc_select_input(JOYSTICK_X_AXIS_ADC_PIN);
    return adc_read();
}

uint16_t joystick_read_y_axis()
{

    adc_select_input(JOYSTICK_Y_AXIS_ADC_PIN);
    return adc_read();
}
