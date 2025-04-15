/* TFT_eSPI library by Bodmer
 */

#include "TFT_eSPI.h"

/**
 * Constructor.
 */
TFT_eSPI::TFT_eSPI()
{
  // be sure not to call anything that requires hardware be initialized here, put those in begin()
}

/**
 * Example method.
 */
void TFT_eSPI::begin()
{
    // initialize hardware
    Serial.println("called begin");
}

/**
 * Example method.
 */
void TFT_eSPI::process()
{
    // do something useful
    Serial.println("called process");
    doit();
}

/**
* Example private method
*/
void TFT_eSPI::doit()
{
    Serial.println("called doit");
}
