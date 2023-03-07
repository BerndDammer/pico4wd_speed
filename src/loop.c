#include "loop.h"
#include "blinker.h"
#include "impulse_counter.h"

#include <stdio.h>
#include "pico/stdlib.h"
//#include "hardware/timer.h"
//#include "hardware/watchdog.h"
//#include "hardware/clocks.h"

#define CONSOLE_TIMEOUT 1000000

void menu(void)
{
    printf("------------------------------------\n");
    printf("nothing to select\n");
    printf("------------------------------------\n");
}

void loop(void)
{
    volatile int c; // make visible in debugger; avoid optimize out
    int counter;
    int results[2];
    speed_init();
    menu();

    for (;;)
    {
        c = getchar_timeout_us(CONSOLE_TIMEOUT);
        blinker_toggle();

        if (c == PICO_ERROR_TIMEOUT)
        {
            speed_get(results);
            printf(">>>> %9i        >>>>> %9i\n", //
                    results[0], results[1]);
            counter++;
        }
        else
        {
            switch (c)
            {
            case ' ':
            case '0':
                printf("OOPs\n");
                break;
            default:
                menu();
                break;
            }
        }
    }
}
