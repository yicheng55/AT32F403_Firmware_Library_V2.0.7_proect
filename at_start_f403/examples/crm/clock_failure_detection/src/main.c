/**
  **************************************************************************
  * @file     main.c
  * @brief    main program
  **************************************************************************
  *                       Copyright notice & Disclaimer
  *
  * The software Board Support Package (BSP) that is made available to
  * download from Artery official website is the copyrighted work of Artery.
  * Artery authorizes customers to use, copy, and distribute the BSP
  * software and its related documentation for the purpose of design and
  * development in conjunction with Artery microcontrollers. Use of the
  * software is governed by this copyright notice and the following disclaimer.
  *
  * THIS SOFTWARE IS PROVIDED ON "AS IS" BASIS WITHOUT WARRANTIES,
  * GUARANTEES OR REPRESENTATIONS OF ANY KIND. ARTERY EXPRESSLY DISCLAIMS,
  * TO THE FULLEST EXTENT PERMITTED BY LAW, ALL EXPRESS, IMPLIED OR
  * STATUTORY OR OTHER WARRANTIES, GUARANTEES OR REPRESENTATIONS,
  * INCLUDING BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, OR NON-INFRINGEMENT.
  *
  **************************************************************************
  */

#include "at32f403_board.h"
#include "at32f403_clock.h"

/** @addtogroup AT32F403_periph_examples
  * @{
  */

/** @addtogroup 403_CRM_clock_failure_detection CRM_clock_failure_detection
  * @{
  */

static void clkout_config(void);
static void sclk_192m_hick_config(void);
static void wait_stbl(uint32_t delay);
void clock_failure_detection_handler(void);

/**
  * @brief  delay to wait for stable.
  * @note   this function should be used before reading stable flag.
  * @param  none
  * @retval none
  */
static void wait_stbl(uint32_t delay)
{
  volatile uint32_t i;

  for(i = 0; i < delay; i++);
}

/**
  * @brief  clkout configuration.
  * @param  none
  * @retval none
  */
static void clkout_config(void)
{
  gpio_init_type gpio_init_struct;

  /* enable gpio port clock */
  crm_periph_clock_enable(CRM_GPIOA_PERIPH_CLOCK, TRUE);

  /* set default parameter */
  gpio_default_para_init(&gpio_init_struct);

  /* clkout gpio init */
  gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
  gpio_init_struct.gpio_mode = GPIO_MODE_MUX;
  gpio_init_struct.gpio_pins = GPIO_PINS_8;
  gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
  gpio_init(GPIOA, &gpio_init_struct);

  /* config clkout clock */
  crm_clock_out_set(CRM_CLKOUT_PLL_DIV_4);
}

/**
  * @brief  clock failure detection handler.
  * @param  none
  * @retval none
  */
void clock_failure_detection_handler(void)
{
  /* check clock failure detection flag */
  if(crm_flag_get(CRM_CLOCK_FAILURE_INT_FLAG) != RESET)
  {
    /* disable clock failure detection */
    crm_clock_failure_detection_enable(FALSE);

    /* config system clock */
    sclk_192m_hick_config();

    /* clear clock failure detection flag */
    crm_flag_clear(CRM_CLOCK_FAILURE_INT_FLAG);
  }
}

/**
  * @brief  config sclk 192 mhz with hick clock source.
  * @note   the system clock is configured as follow:
  *         system clock (sclk)   = hick / 2 * pll_mult
  *         system clock source   = pll (hick)
  *         - hick                = HICK_VALUE
  *         - sclk                = 192000000
  *         - ahbdiv              = 1
  *         - ahbclk              = 192000000
  *         - apb2div             = 2
  *         - apb2clk             = 96000000
  *         - apb1div             = 2
  *         - apb1clk             = 96000000
  *         - pll_mult            = 48
  *         - pll_range           = GT72MHZ (greater than 72 mhz)
  * @param  none
  * @retval none
  */
static void sclk_192m_hick_config(void)
{
  /* reset crm */
  crm_reset();

  crm_clock_source_enable(CRM_CLOCK_SOURCE_HICK, TRUE);

   /* wait till hick is ready */
  while(crm_flag_get(CRM_HICK_STABLE_FLAG) != SET)
  {
  }

  /* config pll clock resource */
  crm_pll_config(CRM_PLL_SOURCE_HICK, CRM_PLL_MULT_48, CRM_PLL_OUTPUT_RANGE_GT72MHZ);

  /* enable pll */
  crm_clock_source_enable(CRM_CLOCK_SOURCE_PLL, TRUE);

  /* wait till pll is ready */
  while(crm_flag_get(CRM_PLL_STABLE_FLAG) != SET)
  {
  }

  /* 1step: config ahbclk div8 */
  crm_ahb_div_set(CRM_AHB_DIV_8);

  crm_apb2_div_set(CRM_APB2_DIV_2);

  crm_apb1_div_set(CRM_APB1_DIV_2);

  /* select pll as system clock source */
  crm_sysclk_switch(CRM_SCLK_PLL);

  /* wait till pll is used as system clock source */
  while(crm_sysclk_switch_status_get() != CRM_SCLK_PLL)
  {
  }

  /* delay */
  wait_stbl(PLL_STABLE_DELAY);

  /* 2step: config ahbclk div2 */
  crm_ahb_div_set(CRM_AHB_DIV_2);

  /* delay */
  wait_stbl(PLL_STABLE_DELAY);

  /* 3step: config ahbclk to target div */
  crm_ahb_div_set(CRM_AHB_DIV_1);

  /* update system_core_clock global variable */
  system_core_clock_update();

  /* config systick delay */
  delay_init();

  /* config clkout */
  clkout_config();
}

/**
  * @brief  main function.
  * @param  none
  * @retval none
  */
int main(void)
{
  system_clock_config();

  at32_board_init();

  /* clkout config */
  clkout_config();

  /* enable clock failure detection */
  crm_clock_failure_detection_enable(TRUE);

  while(1)
  {
    at32_led_toggle(LED2);
    delay_ms(200);
  }
}

/**
  * @}
  */

/**
  * @}
  */
