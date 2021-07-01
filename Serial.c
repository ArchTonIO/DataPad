#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "buttons.h"
#include "joystick.h"
#include "serial.h"

void send_data_over_usb()
{

    buttons_update();
    buttons_print();
    printf(" %hu", joystick_read_x_axis());
    printf(" ");
    printf("%hu", joystick_read_y_axis());
    printf("\n");
    sleep_ms(data_stream_interval);
}
