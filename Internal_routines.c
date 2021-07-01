/*this file is a bridge between RGBkeypad and oled*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "joystick.h"
#include "RGBkeypad.h"
#include "Libraries/PicoOled/picoOled.h"
#include "animations.h"
#include "buttons.h"
#include "internal_routines.h"

char *btn_names[NUMBUTTONS] = {

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

/*button name in the final use*/

char *btn_first_function_names[NUMBUTTONS] = {
    "POINTER         ",
    "POINT           ",
    "POLYLINE        ",
    "PLANAR_SRF      ",
    "EXTRUDE_CRV     ",
    "JOIN            ",
    "SLPIT           ",
    "GROUP           ",
    "MOVE            ",
    "ROTATE_3D       ",
    "BOOLEAN_UNION   ",
    "SOLID_FILLET    ",
    "HOLE_FROM_CRV   ",
    "OFFSET          ",
    "DUP_EDGE        ",
    "CENT_MARKER     ",
    "ALIGN           ",
    "UNDO            ",
    "COPY            ",
    "ENTER           ",
    "FN              "};

char *btn_second_function_names[NUMBUTTONS] = {
    "LEDS            ",
    "                ",
    "CIRCLE          ",
    "SRF_FROM_CRV    ",
    "EXTRUDE_SRF     ",
    "EXPLODE         ",
    "TRIM            ",
    "UNGROUP         ",
    "DISTANCE        ",
    "ROTATE_2D       ",
    "BOOLEAN_DIFF    ",
    "CRV_FILLET      ",
    "ROUND_HOLE      ",
    "DIVIDE          ",
    "DUP_FACE_BORDER ",
    "LENGHT          ",
    "                ",
    "REDO            ",
    "PASTE           ",
    "DEBUG_MODE      ",
    "                "};

void oled_display_boot_screen();

uint8_t oled_activity_calls;

char last_joystick_x_state[4];
char last_joystick_y_state[4];

bool boot_failed;

void internal_routines_init()
{
    keypad_init();
    display_init();
    joystick_init();
    boot_failed = false;
    oled_display_boot_screen();

    oled_activity_calls = 0;
}

void handle_button_error(char *button)
{
    display_clear();
    display_set_x_cursor(0);
    display_set_y_cursor(0);
    display_print("DATAPAD V 1.0\n");
    display_print("Hardware check\n");
    display_set_x_cursor(0);
    display_set_y_cursor(2);
    display_print("[ERR]     ");
    display_print(button);
    display_set_x_cursor(0);
    display_set_y_cursor(7);
    display_print("-PLEASE REBOOT-");
    display_update();
    return;
}

void hardware_check()
{
    uint8_t counter = 0;

    if (joystick_read_x_axis() < 2500 && joystick_read_x_axis() > 1500)
    {
        display_print("[OK] Joystick_x\n");
        display_update();
    }
    else
    {
        display_print("[ERR] Joystick_x\n");
        display_print("\n\n\n-PLEASE REBOOT-");
        display_update();
        boot_failed = true;
        return;
    }

    if (joystick_read_y_axis() < 2500 && joystick_read_y_axis() > 1500)
    {
        display_print("[OK] Joystick_y\n");
        display_update();
    }
    else
    {
        display_print("[ERR] Joystick_y\n");
        display_print("\n\n\n-PLEASE REBOOT-");
        display_update();
        boot_failed = true;
        return;
    }

    for (uint8_t i = 0; i < 4; i++)
    {

        if (buttons_is_pressed(btn_names[i]) == false)
        {
            display_print("[OK] ");
            display_print(btn_names[i]);
            display_print("\n");
            display_update();
        }
        else
        {
            display_print("[ERR] ");
            display_print(btn_names[i]);
            display_print("\n\n\n-please reboot-");
            display_update();
            boot_failed = true;
        }
    }

    /*mad algorithm to scroll the check messages*/

    uint8_t raws_counter = 2;
    uint8_t i_lower = 0;
    uint8_t i_higher = 4;
    uint8_t buttons_counter = 4;

    for (uint8_t i = 0; i < 17; i++)
    {

        for (uint8_t i = i_lower; i < i_higher; i++)
        {
            display_set_x_cursor(0);
            display_set_y_cursor(raws_counter);
            display_print("[OK] ");
            display_print(btn_names[i]);
            display_print("             ");
            raws_counter++;
        }
        i_lower++;
        i_higher++;

        display_set_x_cursor(0);
        display_set_y_cursor(7);

        if (buttons_is_pressed(btn_names[buttons_counter]) == false)
        {
            display_print("[OK] ");
            display_print(btn_names[buttons_counter]);
            display_print("\n");
            display_update();
        }
        else
        {
            display_print("[ERR] ");
            display_print(btn_names[buttons_counter]);
            display_print("\n-please reboot-");
            display_update();
            handle_button_error(btn_names[buttons_counter]);
            boot_failed = true;
            return;
        }

        buttons_counter++;
        raws_counter = 3;
    }

    /*end algorithm*/

    display_clear();
    display_update();
}

void oled_display_boot_screen()
{
    display_draw_animation(0, 0, loading_bar_animation_12832, 128, 64, 1, 12, 1000);
    display_set_x_cursor(2);
    display_set_y_cursor(0);
    display_print("DATAPAD V 1.0\n");
    display_print("Hardware check\n");
    display_update();
    hardware_check();
    if (boot_failed == false)
    {
        display_draw_animation(0, 0, boot_logo_distorted_animation, 128, 64, 1, 20, 1000);
        display_draw_bitmap(0, 0, boot_logo, 128, 64, 1);
        display_update();
        sleep_ms(2000);
    }
    else
    {
        //donothing
    }
}

void oled_activity()
{

    if (oled_activity_calls == 0)
    {
        display_set_x_cursor(3);
        display_set_y_cursor(0);
        display_print("DEBUG MODE");
        display_update();
        oled_activity_calls++;
    }

    display_set_x_cursor(0);
    display_set_y_cursor(2);
    display_print(">");

    for (uint8_t i = 0; i < NUMBUTTONS; i++)
    {
        if (buttons_is_pressed(btn_names[i]) == true)
        {
            display_print(btn_names[i]);
            display_print("  ");
            display_print("\n");
            display_print("          \n");
            display_print(btn_first_function_names[i]);
            display_print("\n\n");
            display_print(btn_second_function_names[i]);
        }
    }
    if (joystick_read_x_axis() > 2500 || joystick_read_x_axis() < 1500 || joystick_read_y_axis() > 2500 || joystick_read_y_axis() < 1500)
    {

        display_print("JOYSTICK");
        display_print("\n\n");
        display_print("X: ");
        sprintf(last_joystick_x_state, "%hu", joystick_read_x_axis());
        display_print(last_joystick_x_state);
        display_print("                ");
        display_print("\n\n");
        display_print("Y: ");
        sprintf(last_joystick_y_state, "%hu", joystick_read_y_axis());
        display_print(last_joystick_y_state);
        display_print("                ");
    }
    display_update();
}

void internal_routines_run()
{
    while (true)
    {

        keypad_listen();

        /* the debug mode button combo has been re-pressed,so if you want to recall the debug mode
        you had to set oled_activity_calls to 0 or the first part will not be executed*/

        if (keypad_is_debug_mode_true() == false)
        {
            oled_activity_calls = 0;

            if (boot_failed == false)
            {
                display_clear();
                //display_draw_bitmap(0, 0, boot_logo, 128, 64, 1);
                display_update();
            }
            else
            {
                display_clear();
            }
        }
        else
        {
            oled_activity();
        }
    }
}
