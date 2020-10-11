/**************************************************************************************************
 * board.cpp
 * @brief Specification/Implementation file
 **************************************************************************************************
 * $Revision$
 * $LastChangedDate$
 * $Author$
 **************************************************************************************************/

#include "board.h"

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_spi.h"
#include "system_stm32f4xx.h"

static const LL_GPIO_InitTypeDef suPinsLEDs_InitStruct_s = { .Pin = LL_GPIO_PIN_13 | LL_GPIO_PIN_14,
                                                             .Mode = LL_GPIO_MODE_OUTPUT,
                                                             .Speed = LL_GPIO_SPEED_FREQ_LOW,
                                                             .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                                             .Pull = LL_GPIO_PULL_NO
};
static const LL_GPIO_InitTypeDef suPinChipSelectSPI5_InitStruct_s = { .Pin = LL_GPIO_PIN_1,
                                                                      .Mode = LL_GPIO_MODE_OUTPUT,
                                                                      .Speed = LL_GPIO_SPEED_FREQ_LOW,
                                                                      .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                                                      .Pull = LL_GPIO_PULL_NO
};
static const LL_GPIO_InitTypeDef suPinsClockMisoMosiSPI5_InitStruct_s = { .Pin = LL_GPIO_PIN_7 | LL_GPIO_PIN_8 | LL_GPIO_PIN_9,
                                                                          .Mode = LL_GPIO_MODE_ALTERNATE,
                                                                          .Speed = LL_GPIO_SPEED_FREQ_LOW,
                                                                          .OutputType = LL_GPIO_OUTPUT_PUSHPULL,
                                                                          .Pull = LL_GPIO_PULL_NO,
                                                                          .Alternate = LL_GPIO_AF_5
};
static const LL_SPI_InitTypeDef suSPI5_InitStruct_s = { .TransferDirection = LL_SPI_FULL_DUPLEX,
                                                        .Mode = LL_SPI_MODE_MASTER,
                                                        .DataWidth = LL_SPI_DATAWIDTH_8BIT,
                                                        .ClockPolarity = LL_SPI_POLARITY_LOW,
                                                        .ClockPhase = LL_SPI_PHASE_1EDGE,
                                                        .NSS = LL_SPI_NSS_SOFT,
                                                        .BaudRate = LL_SPI_BAUDRATEPRESCALER_DIV16,
                                                        .BitOrder = LL_SPI_MSB_FIRST
};

void InitGPIOs() {
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOF);
  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOG);

  LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_1);

  LL_GPIO_Init(GPIOG, (LL_GPIO_InitTypeDef*) &suPinsLEDs_InitStruct_s);
  LL_GPIO_Init(GPIOC, (LL_GPIO_InitTypeDef*) &suPinChipSelectSPI5_InitStruct_s);
  LL_GPIO_Init(GPIOF, (LL_GPIO_InitTypeDef*) &suPinsClockMisoMosiSPI5_InitStruct_s);
}

void InitSPIs() {
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI5);

  LL_SPI_Init(SPI5, (LL_SPI_InitTypeDef*) &suSPI5_InitStruct_s);
}

void busy_wait_ms(unsigned long ms) {
  unsigned long i;
  for (i = 0; i < ms; i++) {
    unsigned long j;
    for (j = 0; j < 10000; j++) {
      __asm ("");
    }
  }
}

void BlinkLEDs() {
  for (;;) {
    LL_GPIO_SetOutputPin(GPIOG, LL_GPIO_PIN_13);
    LL_GPIO_ResetOutputPin(GPIOG, LL_GPIO_PIN_14);
    busy_wait_ms(500);
    LL_GPIO_ResetOutputPin(GPIOG, LL_GPIO_PIN_13);
    LL_GPIO_SetOutputPin(GPIOG, LL_GPIO_PIN_14);
    busy_wait_ms(500);
  }
}
