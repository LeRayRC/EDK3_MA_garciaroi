#include "transform.h"

#include <stdio.h>

#include "math_lib/matrix_3.h"
#include "math_lib/vector_3.h"

Transform2D::Transform2D() {
  position_ = {0.0f, 0.0f};
  rotation_ = 0.0f;
  scale_ = {1.0f, 1.0f};
}

Transform2D::Transform2D(Vec2 position, float rotation, Vec2 scale) {
  position_ = position;
  rotation_ = rotation;
  scale_ = scale;
}

Transform2D::~Transform2D() {}

void Transform2D::operator=(const Transform2D &other) {
  position_.x = other.position_.x;
  position_.y = other.position_.y;

  rotation_ = other.rotation_;

  scale_.x = other.scale_.x;
  scale_.y = other.scale_.y;
}

void Transform2D::set_scale(Vec2 scale) {
  scale_.x = scale.x;
  scale_.y = scale.y;
}

void Transform2D::set_rotation(float rotation) {
  rotation_ = rotation;
}

void Transform2D::set_position(Vec2 position) {
  position_.x = position.x;
  position_.y = position.y;
}

void Transform2D::set_origin(Vec2 origin) {
  origin_.x = origin.x;
  origin_.y = origin.y;
}

void Transform2D::print() {

  printf("pos: {%f, %f} \n", position_.x, position_.y);
  printf("rot: {%f}  \n", rotation_);
  printf("scale: {%f, %f} \n", scale_.x, scale_.y);
}

Mat3 Transform2D::calculateMatrix() const {
  Mat3 temp_matrix = Mat3::Identity();

  temp_matrix = Mat3::Translate(origin_.x, origin_.y).Multiply(temp_matrix);
  temp_matrix = Mat3::Scale(scale_.x, scale_.y).Multiply(temp_matrix);
  temp_matrix = Mat3::Rotate(rotation_).Multiply(temp_matrix);
  temp_matrix = Mat3::Translate(position_.x, position_.y).Multiply(temp_matrix);

  return temp_matrix;
}

void Transform2D::transformPoints(const std::vector<Vec2> &in, std::vector<Vec2> &out) const {
  Mat3 transform_matrix = calculateMatrix();
  Vec3 *transformed_points = (Vec3 *)calloc(in.size(), sizeof(Vec3));
  out.clear();
  for (int i = 0; i < in.size(); i++) {
    //
    transformed_points[i].x = in[i].x;
    transformed_points[i].y = in[i].y;
    transformed_points[i].z = 1.0f;
    //
    transformed_points[i] = transform_matrix.TransformVec3(transformed_points[i]);
    //
    out.push_back({transformed_points[i].x, transformed_points[i].y});
  }
  free(transformed_points);
}
