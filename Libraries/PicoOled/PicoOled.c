#include <string.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

#include "picoOled.h"

const uint8_t ssd1306_font6x8[] =
	{
		0x00, 0x06, 0x08, 0x20,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // sp
		0x00, 0x00, 0x00, 0x2f, 0x00, 0x00, // !
		0x00, 0x00, 0x07, 0x00, 0x07, 0x00, // "
		0x00, 0x14, 0x7f, 0x14, 0x7f, 0x14, // #
		0x00, 0x24, 0x2a, 0x7f, 0x2a, 0x12, // $
		0x00, 0x23, 0x13, 0x08, 0x64, 0x62, // %
		0x00, 0x36, 0x49, 0x55, 0x22, 0x50, // &
		0x00, 0x00, 0x05, 0x03, 0x00, 0x00, // '
		0x00, 0x00, 0x1c, 0x22, 0x41, 0x00, // (
		0x00, 0x00, 0x41, 0x22, 0x1c, 0x00, // )
		0x00, 0x14, 0x08, 0x3E, 0x08, 0x14, // *
		0x00, 0x08, 0x08, 0x3E, 0x08, 0x08, // +
		0x00, 0x00, 0x00, 0xA0, 0x60, 0x00, // ,
		0x00, 0x08, 0x08, 0x08, 0x08, 0x08, // -
		0x00, 0x00, 0x60, 0x60, 0x00, 0x00, // .
		0x00, 0x20, 0x10, 0x08, 0x04, 0x02, // /
		0x00, 0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
		0x00, 0x00, 0x42, 0x7F, 0x40, 0x00, // 1
		0x00, 0x42, 0x61, 0x51, 0x49, 0x46, // 2
		0x00, 0x21, 0x41, 0x45, 0x4B, 0x31, // 3
		0x00, 0x18, 0x14, 0x12, 0x7F, 0x10, // 4
		0x00, 0x27, 0x45, 0x45, 0x45, 0x39, // 5
		0x00, 0x3C, 0x4A, 0x49, 0x49, 0x30, // 6
		0x00, 0x01, 0x71, 0x09, 0x05, 0x03, // 7
		0x00, 0x36, 0x49, 0x49, 0x49, 0x36, // 8
		0x00, 0x06, 0x49, 0x49, 0x29, 0x1E, // 9
		0x00, 0x00, 0x36, 0x36, 0x00, 0x00, // :
		0x00, 0x00, 0x56, 0x36, 0x00, 0x00, // ;
		0x00, 0x08, 0x14, 0x22, 0x41, 0x00, // <
		0x00, 0x14, 0x14, 0x14, 0x14, 0x14, // =
		0x00, 0x00, 0x41, 0x22, 0x14, 0x08, // >
		0x00, 0x02, 0x01, 0x51, 0x09, 0x06, // ?
		0x00, 0x32, 0x49, 0x59, 0x51, 0x3E, // @
		0x00, 0x7C, 0x12, 0x11, 0x12, 0x7C, // A
		0x00, 0x7F, 0x49, 0x49, 0x49, 0x36, // B
		0x00, 0x3E, 0x41, 0x41, 0x41, 0x22, // C
		0x00, 0x7F, 0x41, 0x41, 0x22, 0x1C, // D
		0x00, 0x7F, 0x49, 0x49, 0x49, 0x41, // E
		0x00, 0x7F, 0x09, 0x09, 0x09, 0x01, // F
		0x00, 0x3E, 0x41, 0x49, 0x49, 0x7A, // G
		0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F, // H
		0x00, 0x00, 0x41, 0x7F, 0x41, 0x00, // I
		0x00, 0x20, 0x40, 0x41, 0x3F, 0x01, // J
		0x00, 0x7F, 0x08, 0x14, 0x22, 0x41, // K
		0x00, 0x7F, 0x40, 0x40, 0x40, 0x40, // L
		0x00, 0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
		0x00, 0x7F, 0x04, 0x08, 0x10, 0x7F, // N
		0x00, 0x3E, 0x41, 0x41, 0x41, 0x3E, // O
		0x00, 0x7F, 0x09, 0x09, 0x09, 0x06, // P
		0x00, 0x3E, 0x41, 0x51, 0x21, 0x5E, // Q
		0x00, 0x7F, 0x09, 0x19, 0x29, 0x46, // R
		0x00, 0x46, 0x49, 0x49, 0x49, 0x31, // S
		0x00, 0x01, 0x01, 0x7F, 0x01, 0x01, // T
		0x00, 0x3F, 0x40, 0x40, 0x40, 0x3F, // U
		0x00, 0x1F, 0x20, 0x40, 0x20, 0x1F, // V
		0x00, 0x3F, 0x40, 0x38, 0x40, 0x3F, // W
		0x00, 0x63, 0x14, 0x08, 0x14, 0x63, // X
		0x00, 0x07, 0x08, 0x70, 0x08, 0x07, // Y
		0x00, 0x61, 0x51, 0x49, 0x45, 0x43, // Z
		0x00, 0x00, 0x7F, 0x41, 0x41, 0x00, // [
		0x00, 0x55, 0x2A, 0x55, 0x2A, 0x55, // 55
		0x00, 0x00, 0x41, 0x41, 0x7F, 0x00, // ]
		0x00, 0x04, 0x02, 0x01, 0x02, 0x04, // ^
		0x00, 0x40, 0x40, 0x40, 0x40, 0x40, // _
		0x00, 0x00, 0x01, 0x02, 0x04, 0x00, // '
		0x00, 0x20, 0x54, 0x54, 0x54, 0x78, // a
		0x00, 0x7F, 0x48, 0x44, 0x44, 0x38, // b
		0x00, 0x38, 0x44, 0x44, 0x44, 0x20, // c
		0x00, 0x38, 0x44, 0x44, 0x48, 0x7F, // d
		0x00, 0x38, 0x54, 0x54, 0x54, 0x18, // e
		0x00, 0x08, 0x7E, 0x09, 0x01, 0x02, // f
		0x00, 0x18, 0xA4, 0xA4, 0xA4, 0x7C, // g
		0x00, 0x7F, 0x08, 0x04, 0x04, 0x78, // h
		0x00, 0x00, 0x44, 0x7D, 0x40, 0x00, // i
		0x00, 0x40, 0x80, 0x84, 0x7D, 0x00, // j
		0x00, 0x7F, 0x10, 0x28, 0x44, 0x00, // k
		0x00, 0x00, 0x41, 0x7F, 0x40, 0x00, // l
		0x00, 0x7C, 0x04, 0x18, 0x04, 0x78, // m
		0x00, 0x7C, 0x08, 0x04, 0x04, 0x78, // n
		0x00, 0x38, 0x44, 0x44, 0x44, 0x38, // o
		0x00, 0xFC, 0x24, 0x24, 0x24, 0x18, // p
		0x00, 0x18, 0x24, 0x24, 0x18, 0xFC, // q
		0x00, 0x7C, 0x08, 0x04, 0x04, 0x08, // r
		0x00, 0x48, 0x54, 0x54, 0x54, 0x20, // s
		0x00, 0x04, 0x3F, 0x44, 0x40, 0x20, // t
		0x00, 0x3C, 0x40, 0x40, 0x20, 0x7C, // u
		0x00, 0x1C, 0x20, 0x40, 0x20, 0x1C, // v
		0x00, 0x3C, 0x40, 0x30, 0x40, 0x3C, // w
		0x00, 0x44, 0x28, 0x10, 0x28, 0x44, // x
		0x00, 0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // y
		0x00, 0x44, 0x64, 0x54, 0x4C, 0x44, // z
		0x00, 0x00, 0x08, 0x77, 0x00, 0x00, // {
		0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, // |
		0x00, 0x00, 0x77, 0x08, 0x00, 0x00, // }
		0x00, 0x10, 0x08, 0x10, 0x08, 0x00, // ~
		0x14, 0x14, 0x14, 0x14, 0x14, 0x14, // horiz lines // DEL
		0x00								/* This byte is required for italic type of font */
};

#define SET_CONTRAST 0x81
#define SET_ENTIRE_ON 0xA4
#define SET_NORM_INV 0xA6
#define SET_DISP 0xAE
#define SET_MEM_ADDR 0x20
#define SET_COL_ADDR 0x21
#define SET_PAGE_ADDR 0x22
#define SET_DISP_START_LINE 0x40
#define SET_SEG_REMAP 0xA0
#define SET_MUX_RATIO 0xA8
#define SET_COM_OUT_DIR 0xC0
#define SET_DISP_OFFSET 0xD3
#define SET_COM_PIN_CFG 0xDA // s10.1.18 page 40
#define SET_DISP_CLK_DIV 0xD5
#define SET_PRECHARGE 0xD9
#define SET_VCOM_DESEL 0xDB
#define SET_CHARGE_PUMP 0x8D

//typedef uint8_t uint8_t;

#define I2C_PORT i2c0

volatile bool animation_timer_fired;

//#define OLED_128x32

/*
#ifdef OLED_128x32
const uint8_t height = 32;
#else
const uint8_t height = 64;
#endif
*/

//const uint8_t SID = (height == 64) ? 0x3C : 0x3D; // different height displays have different addr
const uint8_t SID = 0x3C; // different height displays have different addr
const uint8_t width = 128;
//const int pages = height / 8;
//const bool external_vcc = false;

int pages() { return height / 8; }

//uint8_t scr[pages*width+1]; // extra byte holds data send instruction
uint8_t scr[1025]; // being: 8 pages (max) * 128 width + 1 I2C command byte

void write_cmd(uint8_t cmd);

void display_clear()
{
	memset(scr, 0, sizeof(scr));
}

void send_data(uint8_t *data, int nbytes)
{
	i2c_write_blocking(I2C_PORT, SID, data, nbytes, false);
}

void send2(uint8_t v1, uint8_t v2)
{
	uint8_t buf[2];
	buf[0] = v1;
	buf[1] = v2;
	send_data(buf, 2);
}

void display_update()
{

	write_cmd(SET_MEM_ADDR); // 0x20
	write_cmd(0b01);		 // vertical addressing mode

	write_cmd(SET_COL_ADDR); // 0x21
	write_cmd(0);
	write_cmd(127);

	write_cmd(SET_PAGE_ADDR); // 0x22
	write_cmd(0);
	write_cmd(pages() - 1);

	scr[0] = 0x40; // the data instruction
	int size = pages() * width + 1;
	send_data(scr, size);
}

void write_cmd(uint8_t cmd)
{
	send2(0x80, cmd);
}

void poweroff() { write_cmd(SET_DISP | 0x00); }

void poweron() { write_cmd(SET_DISP | 0x01); }

void contrast(uint8_t contrast)
{
	write_cmd(SET_CONTRAST);
	write_cmd(contrast);
}

void invert(uint8_t invert) { write_cmd(SET_NORM_INV | (invert & 1)); }

static void init_i2c()
{
	// This example will use I2C0 on GPIO4 (SDA) and GPIO5 (SCL)
	i2c_init(I2C_PORT, 100 * 1000);
	gpio_set_function(4, GPIO_FUNC_I2C);
	gpio_set_function(5, GPIO_FUNC_I2C);
	gpio_pull_up(4);
	gpio_pull_up(5);
}

void display_init()
{
	init_i2c();

	static uint8_t cmds[] = {
		SET_DISP | 0x00, // display off 0x0E | 0x00

		SET_MEM_ADDR, // 0x20
		0x00,		  // horizontal

		//# resolution and layout
		SET_DISP_START_LINE | 0x00, // 0x40
		SET_SEG_REMAP | 0x01,		//# column addr 127 mapped to SEG0

		SET_MUX_RATIO, // 0xA8
		(uint8_t)(height - 1),

		SET_COM_OUT_DIR | 0x08, //# scan from COM[N] to COM0  (0xC0 | val)
		SET_DISP_OFFSET,		// 0xD3
		0x00,

		//SET_COM_PIN_CFG, // 0xDA
		//0x02 if self.width > 2 * self.height else 0x12,
		//width > 2*height ? 0x02 : 0x12,
		SET_COM_PIN_CFG, (uint8_t)(height == 32 ? 0x02 : 0x12),

		//# timing and driving scheme
		SET_DISP_CLK_DIV, // 0xD5
		0x80,

		SET_PRECHARGE, // 0xD9
		//0x22 if self.external_vcc else 0xF1,
		//external_vcc ? 0x22 : 0xF1,
		0xF1,

		SET_VCOM_DESEL, // 0xDB
		//0x30,  //# 0.83*Vcc
		0x40, // changed by mcarter

		//# display
		SET_CONTRAST, // 0x81
		0xFF,		  //# maximum

		SET_ENTIRE_ON, //# output follows RAM contents // 0xA4
		SET_NORM_INV,  //# not inverted 0xA6

		SET_CHARGE_PUMP, // 0x8D
		//0x10 if self.external_vcc else 0x14,
		//external_vcc ? 0x10 : 0x14,
		0x14,

		SET_DISP | 0x01};

	// write all the commands
	for (int i = 0; i < sizeof(cmds); i++)
		write_cmd(cmds[i]);
	display_clear();
	display_update();
}

void draw_pixel(int16_t x, int16_t y, int color)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	int page = y / 8;
	//page = y/pages;
	int bit = 1 << (y % 8);
	int xincr = 8;
	xincr = height / 8;
	uint8_t *ptr = scr + x * xincr + page + 1;

	switch (color)
	{
	case 1: // white
		*ptr |= bit;
		break;
	case 0: // black
		*ptr &= ~bit;
		break;
	case -1: //inverse
		*ptr ^= bit;
		break;
	}
}

void display_draw_bitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w,
						 int16_t h, uint16_t color)
{
	int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
	uint8_t byte = 0;

	for (int16_t j = 0; j < h; j++, y++)
	{
		for (int16_t i = 0; i < w; i++)
		{
			if (i & 7)
				byte <<= 1;
			else
				byte = bitmap[j * byteWidth + i / 8];
			if (byte & 0x80)
				draw_pixel(x + i, y, color);
		}
	}
}

int64_t animation_alarm_callback(alarm_id_t id, void *user_data)
{
	animation_timer_fired = true;
	return 0;
}

void display_draw_animation(int16_t x, int16_t y, const uint8_t bitmaps_array[][1024], int16_t w,
							int16_t h, uint16_t color, uint8_t frames_number, uint16_t duration_ms)

{
	animation_timer_fired = false;	
	add_alarm_in_ms(duration_ms, animation_alarm_callback, NULL, false);

	while (!animation_timer_fired)
	{

		for (uint16_t i = 0; i < frames_number; i++)
		{

			display_draw_bitmap(x, y, bitmaps_array[i], w, h, color);
			display_update();
			display_clear();
		}
	}
}

void display_draw_letter_at(uint8_t x, uint8_t y, char c)
{
	if (c < ' ' || c > 0x7F)
		c = '?'; // 0x7F is the DEL key

	int offset = 4 + (c - ' ') * 6;
	for (int col = 0; col < 6; col++)
	{
		uint8_t line = ssd1306_font6x8[offset + col];
		for (int row = 0; row < 8; row++)
		{
			draw_pixel(x + col, y + row, line & 1);
			line >>= 1;
		}
	}

	for (int row = 0; row < 8; row++)
	{
		draw_pixel(x + 6, y + row, 0);
		draw_pixel(x + 7, y + row, 0);
	}
}

// void draw_letter(char c) { draw_letter_at(0, 0, c); }

static int cursorx = 0, cursory = 0;
void display_print(const char *str)
{
	char c;
	while (c = *str)
	{
		str++;
		if (c == '\n')
		{
			cursorx = 0;
			cursory += 8;
			continue;
		}
		display_draw_letter_at(cursorx, cursory, c);
		cursorx += 8;
	}
}

void display_set_x_cursor(int x)
{
	const int pos = 8;
	cursorx = pos * x;
}

void display_set_y_cursor(int y)
{
	const int pos = 8;
	cursory = pos * y;
}
