#ifndef ILI9341_DISPLAY_H
#define ILI9341_DISPLAY_H

#include <stdint.h>
#include "hardware/spi.h"

// SPI peripheral and pin mapping for the ILI9341 display.
#define ILI9341_SPI_PORT   spi0
#define ILI9341_SPI_BAUD   (20 * 1000 * 1000)  // 20 MHz

#define ILI9341_PIN_MISO   16  // SPI0 RX
#define ILI9341_PIN_CS     17  // Chip select (software controlled)
#define ILI9341_PIN_SCK    18  // SPI0 SCK
#define ILI9341_PIN_MOSI   19  // SPI0 TX
#define ILI9341_PIN_DC     20  // Data/command select
#define ILI9341_PIN_RST    21  // Reset (active low)
#define ILI9341_PIN_BL     22  // Backlight

// Panel resolution (native portrait orientation).
#define ILI9341_WIDTH      240
#define ILI9341_HEIGHT     320
// ILI9341 command set (subset used during initialisation).
#define CMD_SWRESET    0x01
#define CMD_SLPOUT     0x11
#define CMD_GAMMASET   0x26
#define CMD_DISPON     0x29
#define CMD_MADCTL     0x36
#define CMD_PIXFMT     0x3A
#define CMD_FRMCTR1    0xB1
#define CMD_DFUNCTR    0xB6
#define CMD_PWCTR1     0xC0
#define CMD_PWCTR2     0xC1
#define CMD_VMCTR1     0xC5
#define CMD_VMCTR2     0xC7
#define CMD_GMCTRP1    0xE0
#define CMD_GMCTRN1    0xE1


//***** RGB565 basic color format *****//
#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xFC18

// Initialise the SPI0 peripheral at 20 MHz on GPIO 16-19.
// Returns the actual baud rate (Hz) the hardware was configured to.
uint32_t spi0_init(void);

// Bring up the ILI9341 240x320 panel: configures the bus (via spi0_init),
// performs a hardware reset, runs the power-on/gamma sequence and turns the
// display and backlight on. Call once before drawing.
void ili9341_init(void);

// Fill the entire 240x320 panel with a single RGB565 colour using DMA.
void ili9341_fill_screen(uint16_t color);

// Draw an 8x16 font string at pixel (x, y) with foreground/background RGB565
// colours, streamed with one DMA request. Prints as many characters as fit on
// the row from x to the right edge (at most 30, the width of one DMA line).
void ili9341_print_string(uint16_t x, uint16_t y, const char *str,
                          uint16_t fg, uint16_t bg);

// Draw a signed integer at pixel (x, y) using the 8x16 font.
void ili9341_print_int(uint16_t x, uint16_t y, int value,
                       uint16_t fg, uint16_t bg);

// Draw a floating-point value at pixel (x, y) with `decimals` digits after the
// point (clamped to 7), using the 8x16 font.
void ili9341_print_float(uint16_t x, uint16_t y, float value, uint8_t decimals,
                         uint16_t fg, uint16_t bg);

#endif // ILI9341_DISPLAY_H
