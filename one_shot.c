#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

//macros dos pinos
#define BUTTON 5
#define GREEN_LED 11
#define BLUE_LED 12
#define RED_LED 13

//boleano para indicar se todos os leds já estão desligados
volatile bool all_leds_off = 1;

//função callback do alarme para desligar os leds
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    //variável para indicar quais leds devem ser desligados
    static uint8_t estados = 0;
    switch (estados)
    {
    case 0:
        estados++;
        //desliga led verde
        gpio_put(GREEN_LED, 0);
        //cria novo temporizador de 3 s
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        break;
    
    case 1:
        estados++;
        //desliga led azul
        gpio_put(BLUE_LED, 0);
        //cria novo temporizador de 3 s
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
        break;

    case 2:
        estados = 0;
        //desliga ultimo led - vermelho
        gpio_put(RED_LED, 0);
        //seta flag para indicar que todos os leds estão desligados
        all_leds_off = 1;
        break;
    
    }
    return 0;
}

//função de callback da temporizador repetitivo para verificar se o botão foi pressionado
bool repeating_timer_callback(struct repeating_timer *t){
    //liga leds e inicia temporizador alarme se:
    //-> botão for pressionado
    //-> e todos os leds já estiverem desligados
    if (!gpio_get(BUTTON) && all_leds_off)
    {
        //liga todos os leds
        gpio_put(GREEN_LED, 1);
        gpio_put(RED_LED, 1);
        gpio_put(BLUE_LED, 1);

        //indica que os não estão leds mais desligados
        all_leds_off = false;

        //seta alarme para 3s
        alarm_id_t alarm = add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
    return true;
}



int main()
{
    //inicializa pinos GPIO
    gpio_init(BUTTON);
    gpio_init(RED_LED);
    gpio_init(BLUE_LED);
    gpio_init(GREEN_LED);

    //coloca pinos dos leds como saída
    gpio_set_dir(BLUE_LED, GPIO_OUT);
    gpio_set_dir(RED_LED, GPIO_OUT);
    gpio_set_dir(GREEN_LED, GPIO_OUT);

    //garante que os leds estarão apagados
    gpio_put(RED_LED, 0);
    gpio_put(BLUE_LED, 0);
    gpio_put(GREEN_LED, 0);

    //coloca pino do botão como entrada e pull-up
    gpio_set_dir(BUTTON, GPIO_IN);
    gpio_pull_up(BUTTON);

    //habilita timer repetitivo para verificar o botão a cada 50 ms
    struct repeating_timer timer;
    add_repeating_timer_ms(50, repeating_timer_callback, NULL, &timer);

    while (true) {
        //função para otimizar loop vazio com baixo consumo de cpu
        tight_loop_contents(); 
    }
}
