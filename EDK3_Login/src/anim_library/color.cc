
#include "color.h"

Color ::Color() {
  red_ = 0;
  green_ = 0;
  blue_ = 0;
  alpha_ = 255;
}

Color ::Color(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a) {
  red_ = r;
  green_ = g;
  blue_ = b;
  alpha_ = a;
}

Color ::~Color() {}
