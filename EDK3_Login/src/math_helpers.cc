#include "math_helpers.h"

#include <math.h>

ESAT::Vec3 Vec3Normalize(ESAT::Vec3 vec){
    float magnitude = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
    if(0 != magnitude ){
        return {vec.x / magnitude, vec.y / magnitude, vec.z / magnitude};

    }else{
        return {0.0f,0.0f,0.0f};
    }
}

ESAT::Vec3 Vec3CrossProduct(ESAT::Vec3 u, ESAT::Vec3 v){
    return {u.y * v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x};
}



float GetTexelValue(unsigned char* data, unsigned int nchannels, unsigned int width, unsigned int height, int x, int y, int max_x, int max_y) {
  if (x == max_x) x--;
  if (y == max_y) y--;
    int texture_coord_x = (x * width / max_x);
    int texture_coord_y = (y * height / max_y);

    unsigned char* texel = data + (texture_coord_x + width * texture_coord_y) * nchannels;

    float value = (float)(*texel) / 255.0f;
    return value;
}

float ClampFloat(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}