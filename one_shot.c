#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define BUTTON 5

#define GREEN_LED 11
#define BLUE_LED 12
#define RED_LED 13

volatile bool all_leds_off = 1;

int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    static uint8_t estados = 0;
    switch (estados)
    {
    case 0:
        estados++;
        gpio_put(GREEN_LED, 0);
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        break;
    
    case 1:
        estados++;
        gpio_put(BLUE_LED, 0);
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        break;

    case 2:
        estados = 0;
        all_leds_off = 1;
        gpio_put(RED_LED, 0);
        break;
    
    }
    return 0;
}

bool repeating_timer_callback(struct repeating_timer *t){
    bool botao = !gpio_get(BUTTON);
    static absolute_time_t last_time = 0;

    if (botao && all_leds_off && absolute_time_diff_us(last_time, get_absolute_time()) > 200000 )
    {
        last_time = get_absolute_time();
        gpio_put(GREEN_LED, 1);
        gpio_put(RED_LED, 1);
        gpio_put(BLUE_LED, 1);
        all_leds_off = false;
        alarm_id_t alarm = add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
}



int main()
{
    gpio_init(BUTTON);
    gpio_init(RED_LED);
    gpio_init(BLUE_LED);
    gpio_init(GREEN_LED);

    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(GREEN_LED, GPIO_OUT);

    gpio_put(RED_LED, 0);
    gpio_put(BLUE_LED, 0);
    gpio_put(GREEN_LED, 0);

    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    struct repeating_timer timer;
    add_repeating_timer_ms(50, repeating_timer_callback, NULL, &timer);

    while (true) {
        tight_loop_contents(); 
    }
}
