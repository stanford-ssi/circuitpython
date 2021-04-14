#define MICROPY_HW_BOARD_NAME "Pimoroni PicoSystem"
#define MICROPY_HW_MCU_NAME "rp2040"

#define MICROPY_HW_VBUS_DETECT (&pin_GPIO2)

#define MICROPY_HW_LCD_RESET (&pin_GPIO4)
#define MICROPY_HW_LCD_CS (&pin_GPIO5)
#define MICROPY_HW_LCD_SCLK (&pin_GPIO6)
#define MICROPY_HW_LCD_MOSI (&pin_GPIO7)
#define MICROPY_HW_LCD_VSYNC (&pin_GPIO8)
#define MICROPY_HW_LCD_DS (&pin_GPIO9)

#define MICROPY_HW_AUDIO (&pin_GPIO11)
#define MICROPY_HW_BACKLIGHT (&pin_GPIO12)
#define MICROPY_HW_VBUS_DETECT (&pin_GPIO2)

#define MICROPY_HW_LED_G (&pin_GPIO13)
#define MICROPY_HW_LED_R (&pin_GPIO14)
#define MICROPY_HW_LED_B (&pin_GPIO15)

#define MICROPY_HW_SW_Y (&pin_GPIO16)
#define MICROPY_HW_SW_X (&pin_GPIO17)
#define MICROPY_HW_SW_A (&pin_GPIO18)
#define MICROPY_HW_SW_B (&pin_GPIO19)

#define MICROPY_HW_SW_DOWN (&pin_GPIO20)
#define MICROPY_HW_SW_RIGHT (&pin_GPIO21)
#define MICROPY_HW_SW_LEFT (&pin_GPIO22)
#define MICROPY_HW_SW_UP (&pin_GPIO23)

#define MICROPY_HW_CHARGE_STAT (&pin_GPIO24)

#define MICROPY_HW_BAT_SENSE (&pin_GPIO26)

#define DEFAULT_SPI_BUS_SCK (&pin_GPIO6)
#define DEFAULT_SPI_BUS_MOSI (&pin_GPIO7)

#define DEFAULT_UART_BUS_RX (&pin_GPIO1)
#define DEFAULT_UART_BUS_TX (&pin_GPIO0)

// These pins are unconnected
#define IGNORE_PIN_GPIO3    1
#define IGNORE_PIN_GPIO10   1
#define IGNORE_PIN_GPIO25   1
#define IGNORE_PIN_GPIO27   1
#define IGNORE_PIN_GPIO28   1
#define IGNORE_PIN_GPIO29   1
