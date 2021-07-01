/*this file is used to manage the rgb animation of the buttons*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "buttons.h"
#include "Libraries/PicoRGB/picoRGB.h"

char *buttons[NUMBUTTONS] = {

    BTN_0,
    BTN_1,
    BTN_2,
    BTN_3,
    BTN_4,
    BTN_5,
    BTN_6,
    BTN_7,
    BTN_8,
    BTN_9,
    BTN_10,
    BTN_11,
    BTN_12,
    BTN_13,
    BTN_14,
    BTN_15,
    BTN_16,
    BTN_17,
    BTN_18,
    BTN_19,
    BTN_20

};

const uint8_t COLORSNUM = 9;
const uint8_t LIGHTMODESNUM = 12;
const uint8_t TINYDELAY = 1;

uint8_t colors_values[9][3] = {

    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {255, 0, 255},
    {128, 0, 128},
    {0, 255, 255},
    {255, 65, 0},
    {255, 255, 0},
    {0, 255, 255}

};

char *colors_names[] = {

    "RED",
    "GREEN",
    "BLUE",
    "MAGENTA",
    "PURPLE",
    "CYAN",
    "ORANGE",
    "YELLOW",
    "LIME"

};

char *light_modes[] = {

    "uniform_color_red",
    "uniform_color_green",
    "uniform_color_blue",
    "uniform_color_magenta",
    "uniform_color_purple",
    "uniform_color_cyan",
    "uniform_color_orange",
    "uniform_color_yellow",
    "uniform_color_lime",
    "lightup_pressed_button_red",
    "lightup_pressed_button_green",
    "lightup_pressed_button_blue"

};

typedef struct RGB_button
{

    char *btn_name;
    uint8_t led_number;
    bool btn_state;

} RGB_button;

RGB_button RGB_keypad[NUMBUTTONS];

uint8_t btn_combo_pressed_times;
char *current_light_mode;

bool debug_mode;
bool debug_deactivator;

void keypad_init()
{

    buttons_init();
    strip_init();

    btn_combo_pressed_times = 10; // not so elegant but it works, to set the default light mode at "lightup_pressed_buttons_green" on startup
    current_light_mode = 0;       // probabily useless
    debug_mode = false;
    debug_deactivator = false;

    for (uint8_t i = 0; i < NUMBUTTONS; i++)
    {

        RGB_keypad[i].btn_name = buttons[i];
        RGB_keypad[i].led_number = i;
        RGB_keypad[i].btn_state = 0;
    }
}

void keypad_set_uniform_color(char *selected_color)
{

    uint8_t color[3];

    for (uint8_t i = 0; i < COLORSNUM; i++)
    {

        if (selected_color == colors_names[i])
        {

            color[0] = colors_values[i][0];
            color[1] = colors_values[i][1];
            color[2] = colors_values[i][2];
        }
    }

    for (uint8_t i = 0; i < NUMBUTTONS; i++)
    {

        strip_set_led_color(RGB_keypad[i].led_number, color[0], color[1], color[2]);
    }

    strip_update();
}

void keypad_lightup_pressed_buttons(uint8_t color_index)
{

    for (uint8_t i = 0; i < NUMBUTTONS; i++)
    {

        RGB_keypad[i].btn_state = buttons_is_pressed(RGB_keypad[i].btn_name);

        if (RGB_keypad[i].btn_state == 1)
        {

            if (color_index == 9)
            {

                strip_set_led_color(RGB_keypad[i].led_number, 255, 0, 0);
            }

            if (color_index == 10)
            {

                strip_set_led_color(RGB_keypad[i].led_number, 0, 255, 0);
            }

            if (color_index == 11)
            {

                strip_set_led_color(RGB_keypad[i].led_number, 0, 0, 255);
            }

            strip_update();
            sleep_ms(TINYDELAY); //tiny delay requiered to light up the leds
        }
        else
        {

            strip_set_led_color(RGB_keypad[i].led_number, 0, 0, 0);
            strip_update();
            sleep_ms(TINYDELAY); //tiny delay requiered to turn off the leds
        }
    }
}

void keypad_change_light_mode(char *light_mode)
{

    uint8_t index = 0;

    for (uint8_t i = 0; i < LIGHTMODESNUM; i++)
    {

        if (light_mode == light_modes[i])
        {

            index = i;
        }
    }

    if (index < 9)
    { // the set_uniorm_color_colorname option is chosen

        char *selected_color;
        selected_color = colors_names[index];
        keypad_set_uniform_color(selected_color);
    }
    else
    {

        keypad_lightup_pressed_buttons(index);
    }
}

void keypad_listen()
{ //function to trigger all internal features related to the keypad and keys combo

    if (buttons_is_pressed(RGB_keypad[20].btn_name) == 1)
    {

        if (buttons_is_pressed(RGB_keypad[0].btn_name) == 1)
        {

            btn_combo_pressed_times++;
            sleep_ms(200);

            if (btn_combo_pressed_times == LIGHTMODESNUM)
            {

                btn_combo_pressed_times = 0;
            }
        }

        if (buttons_is_pressed(RGB_keypad[18].btn_name) == 1)
        {
            if (debug_deactivator == true)// debug deactivator is used in order to exit from debug mode and recall it later
            {
                debug_mode = false;
                debug_deactivator = false;
            }
            else
            {
                debug_mode = true;
                debug_deactivator = true;
            }
        }
        
    }

    sleep_ms(TINYDELAY);
    
    current_light_mode = light_modes[btn_combo_pressed_times];
    keypad_change_light_mode(current_light_mode);
}

bool keypad_is_debug_mode_true()
{
    return debug_mode;
}
