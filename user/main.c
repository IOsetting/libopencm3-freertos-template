#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#ifndef ARRAY_LEN
#define ARRAY_LEN(array) (sizeof((array))/sizeof((array)[0]))
#endif

#define LED1_PORT   GPIOC
#define LED1_PIN    GPIO13

static void gpio_setup(void)
{
    /* Enable GPIO clock for leds. */
    rcc_periph_clock_enable(RCC_GPIOC);
    /* Enable led as output */
    gpio_set_mode(
        LED1_PORT,
        GPIO_MODE_OUTPUT_50_MHZ,
        GPIO_CNF_OUTPUT_PUSHPULL,
        LED1_PIN);
    gpio_set(LED1_PORT, LED1_PIN);
}

static void tim_setup(void)
{
    /* Enable TIM2 clock. */
    rcc_periph_clock_enable(RCC_TIM2);

    /* Enable TIM2 interrupt. */
    nvic_enable_irq(NVIC_TIM2_IRQ);

    /* Reset TIM2 peripheral to defaults. */
    rcc_periph_reset_pulse(RST_TIM2);

    /* Timer global mode:
     * - No divider
     * - Alignment edge
     * - Direction up
     * (These are actually default values after reset above, so this call
     * is strictly unnecessary, but demos the api for alternative settings)
     */
    timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

    /* Disable preload. */
    timer_disable_preload(TIM2);
    timer_continuous_mode(TIM2);
    timer_set_prescaler(TIM2, 36000); // Clock counts every 0.5 msec
    timer_set_period(TIM2, 2000); // 2000 * 0.5 msec => 1 sec

    /* Counter enable. */
    timer_enable_counter(TIM2);

    /* Enable Channel 1 compare interrupt to recalculate compare values */
    timer_enable_irq(TIM2, TIM_DIER_CC1IE);
}

/**
 * ISR method defined in libopencm3/include/libopencm3/stm32/f1/nvic.h
*/
void tim2_isr(void)
{
    if (timer_get_flag(TIM2, TIM_SR_CC1IF))
    {
        /* Clear compare interrupt flag. */
        timer_clear_flag(TIM2, TIM_SR_CC1IF);
        /* Toggle LED to indicate compare event. */
        gpio_toggle(LED1_PORT, LED1_PIN);
    }
}

int main(void)
{
    // Setup main clock, using external 8MHz crystal 
    //rcc_clock_setup_in_hse_8mhz_out_72mhz();
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    gpio_setup();
    tim_setup();

    while (1);
    return 0;
}