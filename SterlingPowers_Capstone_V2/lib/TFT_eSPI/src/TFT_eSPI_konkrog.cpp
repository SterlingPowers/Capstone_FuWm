/* TFT_eSPI_konkrog library by Bodmer
 */

#include "TFT_eSPI_konkrog.h"

/**
 * Constructor.
 */
TFT_eSPI_konkrog::TFT_eSPI_konkrog()
{
  // be sure not to call anything that requires hardware be initialized here, put those in begin()
}

/**
 * Example method.
 */
void TFT_eSPI_konkrog::begin()
{
    // initialize hardware
    Serial.println("called begin");
}

/**
 * Example method.
 */
void TFT_eSPI_konkrog::process()
{
    // do something useful
    Serial.println("called process");
    doit();
}

/**
* Example private method
*/
void TFT_eSPI_konkrog::doit()
{
    Serial.println("called doit");
}
