#include "impulse_counter.h"

//#include "hardware/timer.h"
//#include "hardware/gpio.h"
//#include "hardware/clocks.h"
#include "pico/stdlib.h"

#include <stdio.h>

#define IMP0 8
#define IMP1 9
#define CNT_FREQ_US 1000

// statics counting
int counter[2];
int last_state[2];
repeating_timer_t speed_timer;


static bool speed_callback(repeating_timer_t *rt)
{
    int s0 = gpio_get(IMP0);
    if( s0 != last_state[0])
    {
        counter[0]++;
        last_state[0] = s0;
    }
    s0 = gpio_get(IMP1);
    if( s0 != last_state[1])
    {
        counter[1]++;
        last_state[1] = s0;
    }
    return true;
}

void speed_init(void)
{
    counter[0] = 0;
    counter[1] = 0;
    gpio_init(IMP0 );
    gpio_init(IMP1 );
    gpio_set_dir(IMP0, false);
    gpio_set_dir(IMP1, false);

    add_repeating_timer_us(CNT_FREQ_US, speed_callback, NULL, &speed_timer);
}


void speed_get(int results[2])
{
    results[0] = counter[0];
    results[1] = counter[1];
}
