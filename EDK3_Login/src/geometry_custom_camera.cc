/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "camera_custom.h"

#include "ESAT/math.h"
#include "EDK3/dev/gpumanager.h"
#include "EDK3/dev/gpumanager.h"
#include "Perlin/SimplexNoise.h"
#include "ESAT/input.h"
#include "math_helpers.h"
#include "math_library/vector_2.h"


//#define STB_IMAGE_IMPLEMENTATION
#include "stbi_image.h"

namespace EDK3 {

  //IMPORTANT!!!
  //TODO constructors, destructor and =operator here!!!
  CameraCustom::CameraCustom(){}
  CameraCustom::~CameraCustom(){}
  

  void CameraCustom::initViewTarget(const float window_width,
    const float window_height) {
    window_size_ = { window_width, window_height };
    view_dir_ = {0.0f,0.0f,1.0f};
    last_wheel_value_ = 0.0;
    set_view_direction(&view_dir_.x);
  }

  Vec2 CameraCustom::window_size() const{
    return window_size_;
  }

  void CameraCustom::setSpeed(const float speed) {
    speed_ = speed;
  }

  void CameraCustom::setSpeedModifier(const float speed_modifier){
    speed_modifier_ = speed_modifier;
  }

  void CameraCustom::setSensitibity(const float sensitivity){
    sensitivity_ = sensitivity;
  }

  const float CameraCustom::speed() const {
      return speed_;
  }
  const float CameraCustom::sensitivity() const {
      return sensitivity_;
  }

  Vec3 CameraCustom::direction() const {
      return view_dir_;
  }

  void CameraCustom::setDirectionWithAccum(const float window_width,const float window_height) {
    float alpha = ((window_size_.y - accum_mouse_offset_.y) / window_height) * 3.14f;
    float omega = (accum_mouse_offset_.x / window_width) * 6.28f;

    if (alpha > 3.14f) alpha = 3.14f;
    if (alpha < 0.0f) alpha = 0.0f;

    Vec3 camera_pos = {
      cosf(omega) * cosf(alpha - 1.57f) * sensitivity_,
      sinf(alpha - 1.57f) ,
      sinf(omega) * cosf(alpha - 1.57f) * sensitivity_
    };

    view_dir_ = camera_pos.Normalized();
    set_view_direction(&view_dir_.x);
  }

  void CameraCustom::update(const double dt, const float window_width,
      const float window_height){
    float alpha;
    float omega;
    
    
    if(ESAT::MouseWheelY() > last_wheel_value_){
      speed_ += speed_modifier_;
    }else if(ESAT::MouseWheelY() < last_wheel_value_){
      speed_ -= speed_modifier_;
    }
    speed_ = speed_ < 0.0f ? 0.0f : speed_;
    last_wheel_value_ = ESAT::MouseWheelY();

    if (ESAT::MouseButtonDown(1)) {
        last_mouse_position_ = {(float)ESAT::MousePositionX(), (float)ESAT::MousePositionY()};
        current_mouse_position_ = last_mouse_position_;
    }

    if (ESAT::MouseButtonPressed(1)) {
      current_mouse_position_ = {(float)ESAT::MousePositionX(), (float)ESAT::MousePositionY()};
      const float* position_ = position();
      Vec3 current_position = Vec3(position_[0], position_[1], position_[2]);
      Vec3 new_position;
      if (ESAT::IsKeyPressed('W')) {
        new_position = current_position + view_dir_ * (speed_ * (float)dt);
        set_position(&new_position.x);
        position_ = position();
        current_position = Vec3(position_[0], position_[1], position_[2]);
      }


      if (ESAT::IsKeyPressed('S')) {
        new_position = current_position - (view_dir_ * (speed_ * (float)dt));
        set_position(&new_position.x);
        position_ = position();
        current_position = Vec3(position_[0], position_[1], position_[2]);
      }
      if (ESAT::IsKeyPressed('A')) {
        Vec3 right = Vec3::CrossProduct(view_dir_,Vec3(0.0f,1.0f,0.0f));
        new_position = current_position - (right.Normalized() * (speed_ * (float)dt));
        set_position(&new_position.x);
        position_ = position();
        current_position = Vec3(position_[0], position_[1], position_[2]);
      }
      if (ESAT::IsKeyPressed('D')) {
        Vec3 right = Vec3::CrossProduct(view_dir_, Vec3(0.0f, 1.0f, 0.0f));
        new_position = current_position + (right.Normalized() * (speed_ * (float)dt));
        set_position(&new_position.x);
        position_ = position();
        current_position = Vec3(position_[0], position_[1], position_[2]);
      }

      if (ESAT::IsKeyPressed('E')) {
          new_position = current_position + (Vec3(0.0, 1.0f, 0.0f) * (speed_ * (float)dt));
          set_position(&new_position.x);
      }

      if (ESAT::IsKeyPressed('Q')) {
          new_position = current_position + (Vec3(0.0,-1.0f,0.0f) * (speed_ * (float)dt));
          set_position(&new_position.x);
      }

      Vec2 dm = (current_mouse_position_ - last_mouse_position_);
      accum_mouse_offset_ += dm;

      last_mouse_position_ = current_mouse_position_;

      alpha = ((window_size_.y-accum_mouse_offset_.y) / window_height) * 3.14f;
      omega = (accum_mouse_offset_.x / window_width) * 6.28f;

      if (alpha > 3.14f) alpha = 3.14f;
      if (alpha < 0.0f) alpha = 0.0f;

      Vec3 camera_pos = {
        cosf(omega) * cosf(alpha - 1.57f) * sensitivity_,
        sinf(alpha - 1.57f) ,
        sinf(omega) * cosf(alpha - 1.57f) * sensitivity_
      };

      view_dir_ = camera_pos.Normalized();
      set_view_direction(&view_dir_.x);
    }
  }
} //EDK3
