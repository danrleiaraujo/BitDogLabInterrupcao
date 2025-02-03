#include <stdio.h>
#include "pico/stdlib.h"

#include "hardware/pio.h"

#include "pico/bootrom.h"

#include "features/PIO.c"
#include "features/desenho.c"


// Definição do número de LEDs e pino.
// Matriz
#define LED_COUNT 25
#define LED_PIN 7 

// Led RGB
const uint LED_B = 11;
const uint LED_G = 12;
const uint LED_R = 13;

// Botoes
#define BUTTON_A 5
#define BUTTON_B 6

volatile bool BUTTON_A_pressionado = false;
volatile bool BUTTON_B_pressionado = false;

void callback_botao(uint gpio, uint32_t events);
void acao(int numero);

int main(){
    int contador = 0;

    // Inicializa entradas e saídas.
    stdio_init_all();

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

    // Inicializa matriz de LEDs NeoPixel.
    npInit(LED_PIN);
    desenhaMatriz(desliga, 0, 0.8);
    //função para iqr
    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_RISE, true, &callback_botao);
    gpio_set_irq_enabled_with_callback(BUTTON_B, GPIO_IRQ_EDGE_RISE, true, &callback_botao);
    

    desenhaMatriz(zero, 2000, 0.8);
    

    while (true){
        gpio_put(LED_R, true);
        sleep_ms(100);
        gpio_put(LED_R, false);
        sleep_ms(100);
        
        // verificação para qual botão está pressionado
        if (BUTTON_A_pressionado){ //botao para subtrair
            if (contador>0){
                contador--;
                printf("Botão Next, %i\n",contador);
                
            }else{                  //como o limite é de 0 a 9, ao fazer 0-9 ele mostra 9
                contador=9;
                printf("Botão Next, %i\n",contador);
            }
            acao(contador);
            BUTTON_A_pressionado = false;
        }

        else if (BUTTON_B_pressionado) {   //botao para somar
            if (contador <9 ){               
                contador++;
                printf("Botão Previous, %i\n",contador);
            }else{                
                contador=0;         //como o limite é de 0 a 9, ao fazer 9+1 ele mostra 0
                printf("Botão Previous, %i\n",contador);
            }
            acao(contador);
            BUTTON_B_pressionado = false;
        }

        sleep_ms(100);

    } // Fim While True
} // Fim main

//selecao de numero para exibir
void acao(int numero){
    switch (numero){
        case 1:
            desenhaMatriz(um, 1, 0.8);
            break;
        case 2:
            desenhaMatriz(dois, 1, 0.8);
            break;
        case 3:
            desenhaMatriz(tres, 1, 0.8);
            break;
        case 4:
            desenhaMatriz(quatro, 1, 0.8);
            break;
        case 5:
            desenhaMatriz(cinco, 1, 0.8);
            break;
        case 6:
            desenhaMatriz(seis, 1, 0.8);
            break;
        case 7:
            desenhaMatriz(sete, 1, 0.8);
            break;
        case 8:
            desenhaMatriz(oito, 1, 0.8);
            break;
        case 9:
            desenhaMatriz(nove, 1, 0.8);
            break;
        case 0:
            desenhaMatriz(zero, 1, 0.8);
            break;
        default:
            desenhaMatriz(zero, 1, 0.8);
            break;
    }
}

//função para indicar que botão está sendo apertado
void callback_botao(uint gpio, uint32_t events){
    if (gpio == BUTTON_A) {
        BUTTON_A_pressionado = true;
    }
    if (gpio == BUTTON_B) {
        BUTTON_B_pressionado = true;
    }
}