#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pins.h"
#include "buttons.h"

/*global variables*/

uint8_t button_number;

uint8_t buttons_array[NUMBUTTONS] = {

	BTN_0_PIN,
	BTN_1_PIN,
	BTN_2_PIN,
	BTN_3_PIN,
	BTN_4_PIN,
	BTN_5_PIN,
	BTN_6_PIN,
	BTN_7_PIN,
	BTN_8_PIN,
	BTN_9_PIN,
	BTN_10_PIN,
	BTN_11_PIN,
	BTN_12_PIN,
	BTN_13_PIN,
	BTN_14_PIN,
	BTN_15_PIN,
	BTN_16_PIN,
	BTN_17_PIN,
	BTN_18_PIN,
	BTN_19_PIN,
	BTN_20_PIN,

};

bool buttons_states[NUMBUTTONS];

char *button_names[NUMBUTTONS] = {

	"BTN_0",
	"BTN_1",
	"BTN_2",
	"BTN_3",
	"BTN_4",
	"BTN_5",
	"BTN_6",
	"BTN_7",
	"BTN_8",
	"BTN_9",
	"BTN_10",
	"BTN_11",
	"BTN_12",
	"BTN_13",
	"BTN_14",
	"BTN_15",
	"BTN_16",
	"BTN_17",
	"BTN_18",
	"BTN_19",
	"BTN_20",

};

void buttons_init()
{

	gpio_init(BTN_0_PIN);
	gpio_set_dir(BTN_0_PIN, GPIO_IN);
	gpio_pull_down(BTN_0_PIN);

	gpio_init(BTN_1_PIN);
	gpio_set_dir(BTN_1_PIN, GPIO_IN);
	gpio_pull_down(BTN_1_PIN);

	gpio_init(BTN_2_PIN);
	gpio_set_dir(BTN_2_PIN, GPIO_IN);
	gpio_pull_down(BTN_2_PIN);

	gpio_init(BTN_3_PIN);
	gpio_set_dir(BTN_3_PIN, GPIO_IN);
	gpio_pull_down(BTN_3_PIN);

	gpio_init(BTN_4_PIN);
	gpio_set_dir(BTN_4_PIN, GPIO_IN);
	gpio_pull_down(BTN_4_PIN);

	gpio_init(BTN_5_PIN);
	gpio_set_dir(BTN_5_PIN, GPIO_IN);
	gpio_pull_down(BTN_5_PIN);

	gpio_init(BTN_6_PIN);
	gpio_set_dir(BTN_6_PIN, GPIO_IN);
	gpio_pull_down(BTN_6_PIN);

	gpio_init(BTN_7_PIN);
	gpio_set_dir(BTN_7_PIN, GPIO_IN);
	gpio_pull_down(BTN_7_PIN);

	gpio_init(BTN_8_PIN);
	gpio_set_dir(BTN_8_PIN, GPIO_IN);
	gpio_pull_down(BTN_8_PIN);

	gpio_init(BTN_9_PIN);
	gpio_set_dir(BTN_9_PIN, GPIO_IN);
	gpio_pull_down(BTN_9_PIN);

	gpio_init(BTN_10_PIN);
	gpio_set_dir(BTN_10_PIN, GPIO_IN);
	gpio_pull_down(BTN_10_PIN);

	gpio_init(BTN_11_PIN);
	gpio_set_dir(BTN_11_PIN, GPIO_IN);
	gpio_pull_down(BTN_11_PIN);

	gpio_init(BTN_12_PIN);
	gpio_set_dir(BTN_12_PIN, GPIO_IN);
	gpio_pull_down(BTN_12_PIN);

	gpio_init(BTN_13_PIN);
	gpio_set_dir(BTN_13_PIN, GPIO_IN);
	gpio_pull_down(BTN_13_PIN);

	gpio_init(BTN_14_PIN);
	gpio_set_dir(BTN_14_PIN, GPIO_IN);
	gpio_pull_down(BTN_14_PIN);

	gpio_init(BTN_15_PIN);
	gpio_set_dir(BTN_15_PIN, GPIO_IN);
	gpio_pull_down(BTN_15_PIN);

	gpio_init(BTN_16_PIN);
	gpio_set_dir(BTN_16_PIN, GPIO_IN);
	gpio_pull_down(BTN_16_PIN);

	gpio_init(BTN_17_PIN);
	gpio_set_dir(BTN_17_PIN, GPIO_IN);
	gpio_pull_down(BTN_17_PIN);

	gpio_init(BTN_18_PIN);
	gpio_set_dir(BTN_18_PIN, GPIO_IN);
	gpio_pull_down(BTN_18_PIN);

	gpio_init(BTN_19_PIN);
	gpio_set_dir(BTN_19_PIN, GPIO_IN);
	gpio_pull_down(BTN_19_PIN);

	gpio_init(BTN_20_PIN);
	gpio_set_dir(BTN_20_PIN, GPIO_IN);
	gpio_pull_down(BTN_20_PIN);
}

void buttons_update()
{

	for (int i = 0; i < NUMBUTTONS; i++)
	{

		buttons_states[i] = gpio_get(buttons_array[i]); //fill buttons_states array with readings
	}
}

void buttons_print()
{

	for (int i = 0; i < NUMBUTTONS; i++)
	{

		printf("%i", buttons_states[i]);
	}
}

bool buttons_is_pressed(char *button_name)
{

	buttons_update();

	

	for (uint8_t i = 0; i < NUMBUTTONS; i++)
	{

		if (button_names[i] == button_name)
		{
			button_number = i;
		}
	}

	return buttons_states[button_number];
}
