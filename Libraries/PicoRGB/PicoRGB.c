#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "picoRGB.h"
#include "/home/antonio/Progetti/picoProjects/DataPad/pins.h"

typedef struct led
{ //structure RGB_led to store each led R, G, and B values

    uint8_t R_value;
    uint8_t G_value;
    uint8_t B_value;

} RGB_led;

RGB_led led_strip[NUMLEDS];

uint8_t strip_brightness;

static inline void set_led(uint32_t pixel_grb)
{

    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t pack_rgb(uint8_t r, uint8_t g, uint8_t b)
{

    return ((uint32_t)(r) << 8) |
           ((uint32_t)(g) << 16) |
           (uint32_t)(b);
}

void strip_init()
{

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    char str[12];
    ws2812_program_init(pio, sm, offset, STRIP_PIN, 800000, false);
    strip_brightness = 3;
}

void strip_set_led_color(uint8_t led_number, uint8_t R, uint8_t G, uint8_t B)
{

    led_strip[led_number].R_value = R;
    led_strip[led_number].G_value = G;
    led_strip[led_number].B_value = B;
}

void strip_clear()
{

    for (uint8_t i = 0; i < NUMLEDS; i++)
    {

        strip_set_led_color(i, 0, 0, 0);
    }
}

void strip_increase_brightness()
{

    strip_brightness++;

    if (strip_brightness == 3)
    {

        return;
    }

    for (uint8_t i = 0; i < NUMLEDS; i++)
    {

        if (led_strip[i].R_value == 255)
        {

            led_strip[i].R_value = 255; //unchanged
        }
        else
        {

            led_strip[i].R_value = led_strip[i].R_value + (led_strip[i].R_value / 3);
        }

        if (led_strip[i].G_value == 255)
        {

            led_strip[i].G_value = 255; //unchanged
        }
        else
        {

            led_strip[i].G_value = led_strip[i].G_value + (led_strip[i].G_value / 3);
        }

        if (led_strip[i].G_value == 255)
        {

            led_strip[i].B_value = 255; //unchanged
        }
        else
        {

            led_strip[i].B_value = led_strip[i].B_value + (led_strip[i].B_value / 3);
        }
    }
}

void strip_decrease_brightness()
{

    strip_brightness--;

    if (strip_brightness == 0)
    {

        return;
    }

    for (uint8_t i = 0; i < NUMLEDS; i++)
    {

        if (led_strip[i].R_value == 0)
        {

            led_strip[i].R_value = 0; //unchanged
        }
        else
        {

            led_strip[i].R_value = led_strip[i].R_value - 50;
        }

        if (led_strip[i].G_value == 0)
        {

            led_strip[i].G_value = 0; //unchanged
        }
        else
        {

            led_strip[i].G_value = led_strip[i].G_value - 50;
        }

        if (led_strip[i].G_value == 0)
        {

            led_strip[i].B_value = 0; //unchanged
        }
        else
        {

            led_strip[i].B_value = led_strip[i].B_value - 50;
        }

        printf("R_value: %d,", led_strip[i].R_value);
        printf("G_value: %d,", led_strip[i].G_value);
        printf("B_value: %d\n", led_strip[i].B_value);
    }
}

void strip_update()
{

    for (uint8_t i = 0; i < NUMLEDS; i++)
    {

        set_led(pack_rgb(led_strip[i].R_value, led_strip[i].G_value, led_strip[i].B_value));
    }
}

void strip_print_debug(uint16_t time_between_prints)
{

    for (uint8_t i = 0; i < NUMLEDS; i++)
    {

        printf("LED %d values: --> ", i);
        printf("R: %hu || ", led_strip[i].R_value);
        printf("G: %hu || ", led_strip[i].G_value);
        printf("B: %hu || \n", led_strip[i].B_value);
        sleep_ms(time_between_prints);
    }
}