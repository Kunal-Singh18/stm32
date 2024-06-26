 /*
  * for toggling an led we should locate the port and pin to which led is connected.
refer nucleo guide for the same.
 PD12
 */


#define PERIPH_BASE               (0x40000000UL)

#define AHB1PERIPH_OFFSET         (0x00020000UL)
#define AHB1PERIPH_BASE           (PERIPH_BASE + AHB1PERIPH_OFFSET)

#define GPIOD_OFFSET              (0x0C00UL)
#define GPIOD_BASE                 (AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET                (0x3800UL)
#define RCC_BASE                  (AHB1PERIPH_BASE + RCC_OFFSET)


#define AHB1EN_R_OFFSET            (0x10UL)
#define AHB1EN_R                   (*(volatile unsigned int *)(RCC_BASE + AHB1EN_R_OFFSET)



#define MODE_R_OFFSET                  (0x00UL)
#define GPIOA_MODER_R                 (*(volatile unsigned int *)(GPIOD_BASE + MODE_R_OFFSET)

#define OD_R_OFFSET                 (0x14UL)
#define GPIOS_OD_R                  (*(volatile unsigned int *)(GPIOD_BASE + OD_R_OFFSET)


#define PIN12                       (1U<<12)// used for adjusting value of pin12 in output data register.
#define LED_PIN                      PIN12


#define GPIODEN                   (1U<<3)
// in order to toggle the LED connected to PD12 we need to set the pin to output mode
