
#include <stdint.h>

#ifndef JOYSTICK_H
#define JOYSTICK_H

/*Joystick methods*/
void joystick_init();
uint16_t joystick_read_x_axis();
uint16_t joystick_read_y_axis();

#endif