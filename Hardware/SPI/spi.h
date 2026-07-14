#ifndef __SPI_H
#define __SPI_H

#include <stdint.h>

/* SPI1 引脚定义 */

#define SPI1_SCK_GPIO_PORT              GPIOB
#define SPI1_SCK_GPIO_PIN               GPIO_Pin_3
#define SPI1_SCK_GPIO_CLK_ENABLE()      do{ RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); }while(0)

#define SPI1_MISO_GPIO_PORT             GPIOB
#define SPI1_MISO_GPIO_PIN              GPIO_Pin_4
#define SPI1_MISO_GPIO_CLK_ENABLE()     do{ RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); }while(0)

#define SPI1_MOSI_GPIO_PORT             GPIOB
#define SPI1_MOSI_GPIO_PIN              GPIO_Pin_5
#define SPI1_MOSI_GPIO_CLK_ENABLE()     do{ RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); }while(0)

#define SPI1_CS_GPIO_PORT               GPIOB
#define SPI1_CS_GPIO_PIN                GPIO_Pin_14
#define SPI1_CS_GPIO_CLK_ENABLE()       do{ RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); }while(0)

/* SPI1相关定义 */
#define SPI1_SPI                        SPI1
#define SPI1_SPI_CLK_ENABLE()           do{ RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE); }while(0)

/* SPI总线速度设置 */
#define SPI_SPEED_2         0
#define SPI_SPEED_4         1
#define SPI_SPEED_8         2
#define SPI_SPEED_16        3
#define SPI_SPEED_32        4
#define SPI_SPEED_64        5
#define SPI_SPEED_128       6
#define SPI_SPEED_256       7

/* 片选控制宏 */
#define SPI1_CS(x)          do{ (x) ? \
                                  GPIO_SetBits(SPI1_CS_GPIO_PORT, SPI1_CS_GPIO_PIN) : \
                                  GPIO_ResetBits(SPI1_CS_GPIO_PORT, SPI1_CS_GPIO_PIN); \
                            }while(0)

void spi1_init(void);
void spi1_set_speed(uint8_t speed);
uint8_t spi1_read_write_byte(uint8_t txdata);

#endif