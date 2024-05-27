#ifndef __MATH_HELPERS_
#define __MATH_HELPERS_ 1

#include "ESAT/math.h"
//
ESAT::Vec3 Vec3Normalize(ESAT::Vec3 vec);
ESAT::Vec3 Vec3CrossProduct(ESAT::Vec3 u, ESAT::Vec3 v);
float ClampFloat(float value, float min, float max);


float GetTexelValue(unsigned char* data, unsigned int nchannels, unsigned int width, unsigned int height, int x, int y, int max_x, int max_y);

#endif