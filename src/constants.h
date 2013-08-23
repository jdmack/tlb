#include <string>
#include "grid.h"

#ifndef TEITRUS_CONSTANTS_H_
#define TEITRUS_CONSTANTS_H_

/* Screen Attributes */
const int kScreenWidth        = 740;
const int kScreenHeight       = 840;
const int kScreenBitsPerPixel = 32;

/* Strings */
const std::string kName = "Teitrus";

const Uint32 kRedMask   = 0xff000000;
const Uint32 kGreenMask = 0x00ff0000;
const Uint32 kBlueMask  = 0x0000ff00;
const Uint32 kAlphaMask = 0x000000ff;

const int kTitleX = 550;
const int kTitleY = 100;

#endif
