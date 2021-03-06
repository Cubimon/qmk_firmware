/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#ifndef _MCUCONF_H_
#define _MCUCONF_H_

/*
 * HAL driver system settings.
 */

#if 0
/* PEE mode - 120MHz system clock driven by external crystal. */
#define KINETIS_MCG_MODE             KINETIS_MCG_MODE_PEE
#define KINETIS_PLLCLK_FREQUENCY     180000000UL
#define KINETIS_SYSCLK_FREQUENCY     180000000UL
#define KINETIS_BUSCLK_FREQUENCY     60000000UL
#define KINETIS_FLASHCLK_FREQUENCY   25714285UL
#define KINETIS_FLEXBUSCLK_FREQUENCY 60000000UL
#endif

#if 0
/* PEE mode - 120MHz system clock driven by external crystal. */
#define KINETIS_MCG_MODE             KINETIS_MCG_MODE_PEE
#define KINETIS_PLLCLK_FREQUENCY     120000000UL
#define KINETIS_SYSCLK_FREQUENCY     120000000UL
#define KINETIS_BUSCLK_FREQUENCY     60000000UL
#define KINETIS_FLASHCLK_FREQUENCY   24000000UL
#define KINETIS_FLEXBUSCLK_FREQUENCY 60000000UL
#endif

#if 0
/* PEE mode - 96MHz system clock driven by external crystal. */
#define KINETIS_MCG_MODE             KINETIS_MCG_MODE_PEE
#define KINETIS_PLLCLK_FREQUENCY     96000000UL
#define KINETIS_SYSCLK_FREQUENCY     96000000UL
#define KINETIS_BUSCLK_FREQUENCY     48000000UL
#define KINETIS_FLASHCLK_FREQUENCY   24000000UL
#define KINETIS_FLEXBUSCLK_FREQUENCY 96000000UL
#endif

#if 0
/* PEE mode - 48MHz system clock driven by external crystal. */
#define KINETIS_MCG_MODE             KINETIS_MCG_MODE_PEE
#define KINETIS_PLLCLK_FREQUENCY     48000000UL
#define KINETIS_SYSCLK_FREQUENCY     48000000UL
#define KINETIS_BUSCLK_FREQUENCY     48000000UL
#define KINETIS_FLASHCLK_FREQUENCY   24000000UL
#define KINETIS_FLEXBUSCLK_FREQUENCY 48000000UL
#endif

#if 1
/* FEI mode - 48 MHz with internal 32.768 kHz crystal */
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEI
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         1           /* 1464x FLL factor */
#define KINETIS_SYSCLK_FREQUENCY    47972352UL  /* 32.768 kHz * 1464 (~48 MHz) */
#define KINETIS_CLKDIV1_OUTDIV1     1
#define KINETIS_CLKDIV1_OUTDIV2     1
#define KINETIS_CLKDIV1_OUTDIV3     2
#define KINETIS_CLKDIV1_OUTDIV4     2
#define KINETIS_BUSCLK_FREQUENCY    KINETIS_SYSCLK_FREQUENCY
#define KINETIS_FLASHCLK_FREQUENCY  KINETIS_SYSCLK_FREQUENCY/2
#endif

#if 0
/* FEI mode - 96 MHz with internal 32.768 kHz crystal */
#define KINETIS_MCG_MODE            KINETIS_MCG_MODE_FEI
#define KINETIS_MCG_FLL_DMX32       1           /* Fine-tune for 32.768 kHz */
#define KINETIS_MCG_FLL_DRS         1           /* 2929x FLL factor */
#define KINETIS_SYSCLK_FREQUENCY    95977472UL  /* 32.768 kHz * 2929 (~96 MHz) */
#define KINETIS_CLKDIV1_OUTDIV1     1
#define KINETIS_CLKDIV1_OUTDIV2     2 /* ~48MHz bus clock */
#define KINETIS_CLKDIV1_OUTDIV3     2 /* ~48MHz FlexBus clock */
#define KINETIS_CLKDIV1_OUTDIV4     4 /* ~24MHz flash clock */
#define KINETIS_BUSCLK_FREQUENCY    KINETIS_SYSCLK_FREQUENCY/2
#define KINETIS_FLASHCLK_FREQUENCY  KINETIS_SYSCLK_FREQUENCY/4
#endif

/*
 * SERIAL driver system settings.
 */
#define KINETIS_SERIAL_USE_UART0              TRUE

/*
 * USB driver settings
 */
#define KINETIS_USB_USE_USB0                  TRUE

/*
 * I2C settings
 */
#define KINETIS_I2C_USE_I2C0                  TRUE

/*
 * ADC settings
 */
#define KINETIS_ADC_USE_ADC0                  TRUE

/*
 * EXT driver system settings.
 */
#define KINETIS_EXTI_NUM_CHANNELS         1
#define KINETIS_EXT_PORTA_IRQ_PRIORITY          12
#define KINETIS_EXT_PORTB_IRQ_PRIORITY          12
#define KINETIS_EXT_PORTC_IRQ_PRIORITY          12
#define KINETIS_EXT_PORTD_IRQ_PRIORITY          12
#define KINETIS_EXT_PORTE_IRQ_PRIORITY          12

/* K20 64pin  */
#define KINETIS_EXT_PORTA_WIDTH                 20
#define KINETIS_EXT_PORTB_WIDTH                 20
#define KINETIS_EXT_PORTC_WIDTH                 12
#define KINETIS_EXT_PORTD_WIDTH                 8
#define KINETIS_EXT_PORTE_WIDTH                 2

/*
 * GPT driver system settings.
 */
#define KINETIS_GPT_USE_PIT0                TRUE
#define KINETIS_GPT_PIT0_IRQ_PRIORITY       8

/*
 * PWM driver system settings.
 */
#define KINETIS_PWM_USE_FTM0                  TRUE

/*
 * SPI driver system settings.
 */
#define KINETIS_SPI_USE_SPI0                TRUE
#define KINETIS_SPI_SPI0_IRQ_PRIORITY       8

#endif
