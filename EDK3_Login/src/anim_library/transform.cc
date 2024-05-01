#include "anim_library/transform.h"

#include <stdio.h>

#include "math_library/matrix_3.h"
#include "math_library/vector_3.h"

Transform::Transform() {
  position_ = {0.0f, 0.0f, 0.0f};
  rotation_ = {0.0f, 0.0f, 0.0f};
  scale_ = {1.0f, 1.0f, 1.0f};
}

Transform::Transform(Vec3 position, Vec3 rotation, Vec3 scale) {
  position_ = position;
  rotation_ = rotation;
  scale_ = scale;
}

Transform::~Transform() {}

void Transform::operator=(const Transform &other) {
  position_ = other.position_;
  rotation_ = other.rotation_;
  scale_ = other.scale_;
}

void Transform::set_scale(Vec3 scale) {
  scale_.x = scale.x;
  scale_.y = scale.y;
  scale_.z = scale.z;
}

void Transform::set_rotation(Vec3 rotation) {
  rotation_ = rotation;
}

void Transform::set_position(Vec3 position) {
  position_.x = position.x;
  position_.y = position.y;
  position_.z = position.z;
}

void Transform::set_origin(Vec3 origin) {
  origin_.x = origin.x;
  origin_.y = origin.y;
  origin_.z = origin.z;
}

void Transform::print() {

  printf("pos: {%f, %f} \n", position_.x, position_.y);
  printf("rot: {%f}  \n", rotation_.x);
  printf("scale: {%f, %f} \n", scale_.x, scale_.y);
}

// Mat3 Transform::calculateMatrix() const {
  // Mat3 temp_matrix = Mat3::Identity();
// 
  // temp_matrix = Mat3::Translate(origin_.x, origin_.y).Multiply(temp_matrix);
  // temp_matrix = Mat3::Scale(scale_.x, scale_.y).Multiply(temp_matrix);
  // temp_matrix = Mat3::Rotate(rotation_).Multiply(temp_matrix);
  // temp_matrix = Mat3::Translate(position_.x, position_.y).Multiply(temp_matrix);
// 
  // return temp_matrix;
// }

// void Transform2D::transformPoints(const std::vector<Vec2> &in, std::vector<Vec2> &out) const {
//   Mat3 transform_matrix = calculateMatrix();
//   Vec3 *transformed_points = (Vec3 *)calloc(in.size(), sizeof(Vec3));
//   out.clear();
//   for (int i = 0; i < in.size(); i++) {
//     //
//     transformed_points[i].x = in[i].x;
//     transformed_points[i].y = in[i].y;
//     transformed_points[i].z = 1.0f;
//     //
//     transformed_points[i] = transform_matrix.TransformVec3(transformed_points[i]);
//     //
//     out.push_back({transformed_points[i].x, transformed_points[i].y});
//   }
//   free(transformed_points);
// }
