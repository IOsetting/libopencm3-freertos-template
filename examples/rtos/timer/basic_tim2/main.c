#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/*
 * Handler in case our application overflows the stack
 */
void vApplicationStackOverflowHook(
    TaskHandle_t xTask __attribute__((unused)),
    char *pcTaskName __attribute__((unused))) 
{
    for (;;);
}

/*********************************************************************
 * The SYSCLK runs at 72 MHz and the AHB prescaler = 1. The input
 * to the APB1 prescaler is thus also 72 MHz. Because the APB1 bus
 * must not exceed 36 MHz, this APB1 prescaler divides by 2, giving
 * 36 MHz. However, since the APB1 prescaler is not equal to 1, the
 * clock going to TIM2, 3 and 4 is doubled and thus is 72 MHz (Figure
 * 8 of section 7.2 of RM0008). This sets CK_INT = 72 Mhz in Figure
 * 100 of section 15.2.
 *
 * Setting the prescaler TIM2_PSC = 36000, produces a CK_CNT at every 
 * 0.5 msec (1/72000000/36000). To generate a timer event at 100ms, we
 * thus configure the counter and OC2 count to 200 (200 * 0.5 msec).
 *********************************************************************/
static void timer_setup(void)
{
    rcc_periph_clock_enable(RCC_TIM2);
    rcc_periph_reset_pulse(RST_TIM2);
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT_MUL_4, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
    timer_set_prescaler(TIM2, 36000); // Clock counts every 0.5 msec
    timer_one_shot_mode(TIM2);
    timer_set_period(TIM2, 200); // 200 * 0.5 msec => 100 msec
}

/*********************************************************************
 * This delays approx 100us, for programming 27C512 etc.
 *********************************************************************/
static void delay_100ms(void)
{
    timer_clear_flag(TIM2,TIM_SR_UIF);    // UIF=0
    timer_enable_counter(TIM2);        // Start timer
    while ( !timer_get_flag(TIM2,TIM_SR_UIF) );                // Until UIF=1
}

/*********************************************************************
 * Task to initialize and repeatedly generate a pulse
 *********************************************************************/
static void timer_task(void *arg __attribute__((unused)))
{
    gpio_clear(GPIOC,GPIO13);
    timer_setup();

    for (;;) {
        // Generate 100us Pulse on C13
        gpio_set(GPIOC,GPIO13);
        delay_100ms();            // 100 usec delay
        gpio_clear(GPIOC,GPIO13);
        vTaskDelay(1);            // Delay 1 systick
    }
}

/*
 * Main program: Device initialization etc.
 */
int main(void)
{
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    rcc_periph_clock_enable(RCC_GPIOC);

    gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_50_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO13);

    xTaskCreate(timer_task,"timer",300,NULL,configMAX_PRIORITIES-1,NULL);

    vTaskStartScheduler();
    for (;;);
}
