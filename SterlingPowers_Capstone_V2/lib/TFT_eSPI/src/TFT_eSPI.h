#pragma once

/* TFT_eSPI library by Bodmer
 */

// This will load the definition for common Particle variable types
#include "Particle.h"

// This is your main class that users will import into their application
class TFT_eSPI
{
public:
  /**
   * Constructor
   */
  TFT_eSPI();

  /**
   * Example method
   */
  void begin();

  /**
   * Example method
   */
  void process();

private:
  /**
   * Example private method
   */
  void doit();
};
