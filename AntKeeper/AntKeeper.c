/* LIBRARIES */
// Common libraries
#include <stdio.h>
// Pico SDK libraries
#include "pico/stdlib.h"
#include "hardware/clocks.h"
// Drivers libraries
#include "drivers/ili9341_display.h"

int main(){
    // Run the system clock at 120 MHz (set before stdio so UART/USB
    // clocks are derived from the new frequency).
    set_sys_clock_khz(120000, true);

    // Initialise the display and its backlight control.
    ili9341_init();
    ili9341_fill_screen(BLACK);
    ili9341_print_string(0, 0, "RaspberryPi-Pico-W:RP2050", GREEN, BLACK);
    ili9341_print_string(0, 16, "2.4spi-Display:240x320-ILI9341", GREEN, BLACK);

    while (true){
    }
}
