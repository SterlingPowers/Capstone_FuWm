// Example usage for TFT_eSPI_konkrog library by Bodmer.

#include "TFT_eSPI_konkrog.h"

// Initialize objects from the lib
TFT_eSPI_konkrog tFT_eSPI_konkrog;

void setup() {
    // Call functions on initialized library objects that require hardware
    tFT_eSPI_konkrog.begin();
}

void loop() {
    // Use the library's initialized objects and functions
    tFT_eSPI_konkrog.process();
}
