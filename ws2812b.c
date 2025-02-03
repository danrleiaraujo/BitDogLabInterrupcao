#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/pio.h"
#include "pico/bootrom.h"

#include "features/PIO.c"
#include "features/desenho.c"
#include "features/funcoes.c"


// Definição do número de LEDs e pino.
// Matriz
#define LED_COUNT 25
#define LED_PIN 7 

// Led RGB
#define LED_B 11 
#define LED_G 12
#define LED_R 13

// Botoes
#define BUTTON_A 5
#define BUTTON_B 6

volatile bool botaoA_pressionado = false;
volatile bool botaoB_pressionado = false;

void callback_botao(uint gpio, uint32_t events);
bool alterna_led(struct repeating_timer *t);
void acao(int numero);

int main(){
    struct repeating_timer timer;
    int contador = 0;


    // Inicializa entradas e saídas.
    stdio_init_all();
    waitUSB();
    menu();

    // Inicializa matriz de LEDs NeoPixel.
    npInit(LED_PIN);
    desenhaMatriz(desliga, 0, 0.8);

    gpio_init(LED_B);
    gpio_set_dir(LED_B, GPIO_OUT);

    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    gpio_init(LED_R);
    gpio_set_dir(LED_R, GPIO_OUT);

    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(BUTTON_B);
    gpio_set_dir(BUTTON_B, GPIO_IN);
    gpio_pull_up(BUTTON_B);

    //função para iqr
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_RISE, true, &callback_botao);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_RISE, true, &callback_botao);
    
    //função para a led funcionar independente 
    add_repeating_timer_ms(-100, alterna_led, NULL, &timer); 

    desenhaMatriz(zero, 2000, 0.8);
    
    while (true){
    // verificação para qual botão está pressionado
    if (botaoA_pressionado){ //botao para subtrair
        if (contador>0){
            contador--;
            printf("Botão Next, %i\n",contador);
            
        }else{                  //como o limite é de 0 a 9, ao fazer 0-9 ele mostra 9
            contador=9;
            printf("Botão Next, %i\n",contador);
        }
        acao(contador);
        botaoA_pressionado = false;
    }

    else if (botaoB_pressionado) {   //botao para somar
        if (contador <9 ){               
            contador++;
            printf("Botão Previous, %i\n",contador);
        }else{                
            contador=0;         //como o limite é de 0 a 9, ao fazer 9+1 ele mostra 0
            printf("Botão Previous, %i\n",contador);
        }
        acao(contador);
        botaoB_pressionado = false;
    }

        sleep_ms(100);

    } // Fim While True
} // Fim main

//selecao de numero para exibir
void acao(int numero){
    switch (numero){
        case 1:
            desenhaMatriz(um, 2000, 0.8);
            break;
        case 2:
            desenhaMatriz(dois, 2000, 0.8);
            break;
        case 3:
            desenhaMatriz(tres, 2000, 0.8);
            break;
        case 4:
            desenhaMatriz(quatro, 2000, 0.8);
            break;
        case 5:
            desenhaMatriz(cinco, 2000, 0.8);
            break;
        case 6:
            desenhaMatriz(seis, 2000, 0.8);
            break;
        case 7:
            desenhaMatriz(sete, 2000, 0.8);
            break;
        case 8:
            desenhaMatriz(oito, 2000, 0.8);
            break;
        case 9:
            desenhaMatriz(nove, 2000, 0.8);
            break;
        case 0:
            desenhaMatriz(zero, 2000, 0.8);
            break;
        default:
            desenhaMatriz(zero, 2000, 0.8);
            break;
    }
}

//função para indicar que botão está sendo apertado
void callback_botao(uint gpio, uint32_t events){
    if (gpio == BUTTON_A) {
        botaoA_pressionado = true;
    }
    if (gpio == BUTTON_B) {
        botaoB_pressionado = true;
    }
}

//piscar a led
bool alterna_led(struct repeating_timer *t) {
    if(gpio_get(LED_R) == true){
        gpio_put(LED_R, !gpio_get(LED_R));
        gpio_put(LED_B, !gpio_get(LED_B));
    }
    else if (gpio_get(LED_B) == true){
        gpio_put(LED_B, !gpio_get(LED_B));
        gpio_put(LED_G, !gpio_get(LED_G));
    }
    else if (gpio_get(LED_G) == true){
        gpio_put(LED_G, !gpio_get(LED_G));
        gpio_put(LED_R, !gpio_get(LED_R));
    }
    else
        gpio_put(LED_R, !gpio_get(LED_R));
    return true;
}

