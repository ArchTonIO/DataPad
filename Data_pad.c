#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "serial.h"
#include "internal_routines.h"

void do_once()
{
    stdio_init_all();
    internal_routines_init();
    multicore_launch_core1(internal_routines_run);
}

void do_in_loop()
{
    while (true)
    {
        send_data_over_usb();
    }
}

int main()
{
    do_once();
    do_in_loop();
    return 0;
}
