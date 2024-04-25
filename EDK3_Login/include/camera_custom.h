/**
 *
 * @brief Custom camera header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __CAMERA_CUSTOM_H__
#define __CAMERA_CUSTOM_H__ 1

#include "EDK3/camera.h"
#include "ESAT/math.h"
#include "math_library/vector_2.h"
#include "math_library/vector_3.h"


namespace EDK3 {

class CameraCustom : public EDK3::Camera {
 public:
  CameraCustom();

  void initViewTarget(const float window_width,
                      const float window_height);

  void update(const double dt, const float window_width,
              const float window_height);

  void setEnabled(const bool enabled);
  void setSpeed(const float speed);
  void setSensitibity(const float sensitivity);
  void setSpeedModifier(const float speed_modifier);
  void setDirectionWithAccum(const float window_width, const float window_height);

  const bool enabled() const;
  const float speed() const;
  const float sensitivity() const;
  Vec3 direction() const;
  Vec2 window_size() const;
  //TODO something in the future:
  //virtual void doCull(const Node* root_node) override;
  //virtual void doRender() const override; 

  Vec2 accum_mouse_offset_;
 protected:
  virtual ~CameraCustom(); 

  //TODO anything with these vars, these vars can be changed:
  Vec2 window_size_;
  Vec2 current_mouse_position_;
  Vec2 last_mouse_position_;
  bool enabled_;
  float speed_;
  float sensitivity_;
  Vec3 view_dir_;
  double last_wheel_value_;
  float speed_modifier_;

 private:
  CameraCustom(const CameraCustom&);
  //CameraCustom(CameraCustom&&);
  CameraCustom& operator=(const CameraCustom&);
};

} //EDK3

#endif //__CAMERA_CUSTOM_H__
