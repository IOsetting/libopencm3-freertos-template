#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

/*
 * Handler in case our application overflows the stack
 */
void vApplicationStackOverflowHook(
    TaskHandle_t xTask __attribute__((unused)),
    char *pcTaskName __attribute__((unused))) {

    for (;;);
}

/*
 * Task that toggles LED PB12(blackpill) and PC13(bluepill)
 */
static void task1(void *args __attribute__((unused))) {
    
    for (;;) {
        gpio_toggle(GPIOB, GPIO12);
        gpio_toggle(GPIOC, GPIO13);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/*
 * Main loop, this is where our program starts
 */
int main(void) {
    // Setup main clock, using external 8MHz crystal 
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);

    // Enable clock for GPIO channel B and C
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);

    // Set pinmode for PB12, PC13
    gpio_set_mode(
        GPIOB,
        GPIO_MODE_OUTPUT_2_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL,
        GPIO12);
    gpio_set_mode(
        GPIOC,
        GPIO_MODE_OUTPUT_2_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL,
        GPIO13);

    // Turn LED off
    gpio_set(GPIOB, GPIO12);
    gpio_set(GPIOC, GPIO13);

    // Tell FreeRTOS about our toggle task, and set it's stack and priority
    xTaskCreate(task1, "LED", 100, NULL, 2, NULL);

    // Start RTOS Task scheduler
    vTaskStartScheduler();

    // The task scheduler is blocking, so we should never come here...
    for (;;);
    return 0;
}