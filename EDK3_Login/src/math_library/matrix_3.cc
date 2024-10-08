
#include "math_library/matrix_3.h"

Mat3::Mat3() {
  m[0] = 0.0f; m[3] = 0.0f; m[6] = 0.0f;
  m[1] = 0.0f; m[4] = 0.0f; m[7] = 0.0f;
  m[2] = 0.0f; m[5] = 0.0f; m[8] = 0.0f;
}

Mat3::Mat3(float value) {
  m[0] = value; m[3] = value; m[6] = value;
  m[1] = value; m[4] = value; m[7] = value;
  m[2] = value; m[5] = value; m[8] = value;
}

Mat3::Mat3(float* values_array) {
  m[0] = values_array[0]; m[3] = values_array[3]; m[6] = values_array[6];
  m[1] = values_array[1]; m[4] = values_array[4]; m[7] = values_array[7];
  m[2] = values_array[2]; m[5] = values_array[5]; m[8] = values_array[8];
}

Mat3::Mat3(Vec3 a, Vec3 b, Vec3 c) {
  m[0] = a.x; m[3] = b.x; m[6] = c.x;
  m[1] = a.y; m[4] = b.y; m[7] = c.y;
  m[2] = a.z; m[5] = b.z; m[8] = c.z;
}

Mat3::Mat3(const Mat3& copy) {
  m[0] = copy.m[0]; m[3] = copy.m[3]; m[6] = copy.m[6];
  m[1] = copy.m[1]; m[4] = copy.m[4]; m[7] = copy.m[7];
  m[2] = copy.m[2]; m[5] = copy.m[5]; m[8] = copy.m[8];
}

Mat3::~Mat3() {
}

Mat3 Mat3::Translate(const Vec2& mov_vector) {	
  Mat3 aux = Mat3::Identity();
  aux.m[6] = mov_vector.x; 
  aux.m[7] = mov_vector.y; 
	return aux;
}

Mat3 Mat3::Translate(float x, float y) {
  Mat3 aux = Mat3::Identity();
  aux.m[6] = x; 
  aux.m[7] = y; 
	return aux;
}

Mat3 Mat3::Rotate(float rotation){
  Mat3 aux = Mat3::Identity();
  aux.m[0] = (float) cos(rotation);
  aux.m[1] = (float) sin(rotation);
  aux.m[3] = (float) sin(rotation) * -1;
  aux.m[4] = (float) cos(rotation);

  return aux;
}

Mat3 Mat3::Scale(const Vec2 &scale){
  Mat3 aux = Mat3::Identity();
  aux.m[0] = scale.x; 
  aux.m[4] = scale.y; 
	return aux;
}
Mat3 Mat3::Scale(float x, float y){
  Mat3 aux = Mat3::Identity();
  aux.m[0] = x; 
  aux.m[4] = y; 
	return aux;
}