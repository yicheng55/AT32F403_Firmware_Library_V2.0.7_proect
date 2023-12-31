/**
  ******************************************************************************
  * @file     xmc_psram.h
  * @brief    header file for the psram configuration.
  ******************************************************************************
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

/* define to prevent recursive inclusion -------------------------------------*/
#ifndef __XMC_PSRAM_H
#define __XMC_PSRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "at32f403_clock.h"

/** @addtogroup AT32F403_periph_examples
  * @{
  */

/** @addtogroup 403_XMC_psram
  * @{
  */

/** @defgroup XMC_psram_functions
  * @{
  */

void sram_init(void);
void sram_writebuffer(uint16_t* pbuffer, uint32_t write_addr, uint32_t num_halfword_to_write);
void sram_readbuffer(uint16_t* pbuffer, uint32_t read_addr, uint32_t num_halfword_to_read);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif

