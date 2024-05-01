
#include "anim_library/animationinstance.h"

//#include "game.h"
#include "demo_manager.h"
#include "math_library/vector_3.h"

AnimationInstance::AnimationInstance() {}

bool AnimationInstance::isEnded() {
  return ((position_status_.ended_ || !config_.is_moving) && (rotation_status_.ended_ || !config_.is_rotating) && (scale_status_.ended_ || !config_.is_scaling));
}

void AnimationInstance::init(AnimationConfig config, Entity *ent) {
  // Assign entity pointer of the animation
  entity_ = ent;
  config_ = config;

  // Assign position in animation
  position_status_.ended_ = false;
  position_status_.percent_ = 0.0f;
  position_status_.elapsed_time_ = 0.0f;

  // Assign rotation in animation
  rotation_status_.ended_ = false;
  rotation_status_.percent_ = 0.0f;
  rotation_status_.elapsed_time_ = 0.0f;

  // Assign scale in animation
  scale_status_.ended_ = false;
  scale_status_.percent_ = 0.0f;
  scale_status_.elapsed_time_ = 0.0f;

  revert_ = false;
}

void AnimationInstance::init(AnimationConfig config) {
  config_ = config;

  // Assign position in animation
  position_status_.ended_ = false;
  position_status_.percent_ = 0.0f;
  position_status_.elapsed_time_ = 0.0f;

  // Assign rotation in animation
  rotation_status_.ended_ = false;
  rotation_status_.percent_ = 0.0f;
  rotation_status_.elapsed_time_ = 0.0f;

  // Assign scale in animation
  scale_status_.ended_ = false;
  scale_status_.percent_ = 0.0f;
  scale_status_.elapsed_time_ = 0.0f;

  revert_ = false;
}

void AnimationInstance::set_entity(Entity *ent) {
  entity_ = ent;
}

void AnimationInstance::set_revert(bool revert) {
  revert_ = revert;
}

float AnimationInstance::get_progress(int status) {
  switch (status) {
  case 0:
    return position_status_.percent_;
    break;
  case 1:
    return rotation_status_.percent_;
    break;
  case 2:
    return scale_status_.percent_;
    break;
  default:
    return 0;
    break;
  }
}

void AnimationInstance::set_elapsed_time(int status, float time) {
  switch (status) {
  case 0:
    position_status_.elapsed_time_ = time;
    break;
  case 1:
    rotation_status_.elapsed_time_ = time;
    break;
  case 2:
    scale_status_.elapsed_time_ = time;
    break;
  default:;
    break;
  }
}

float AnimationInstance::get_duration(int status) {
  switch (status) {
  case 0:
    return config_.move_duration;
    break;
  case 1:
    return config_.rotate_duration;
    break;
  case 2:
    return config_.scale_duration;
    break;
  default:
    return 0;
    break;
  }
}

AnimationInstance::~AnimationInstance() {}

void AnimationInstance::update() {
  Vec3 new_position;
  Vec3 new_scale;
  Vec3 new_rotation;
  
  DemoManager* manager = DemoManager::getInstance();

  if (config_.current_delay >= config_.total_delay){  
    if (revert_) {
      // Update position if animation is moving and not ended
      if (config_.is_moving && !position_status_.ended_) {

        // decrease elapsed time
        if (position_status_.elapsed_time_)
        {
          position_status_.elapsed_time_ -= manager->dt;
        }
        
        
        if (position_status_.elapsed_time_ <= 0.0f)
          position_status_.elapsed_time_ = 0.0f;
        // calculate percentage between [0,1]

        if (config_.move_duration != 0) {
          position_status_.percent_ = position_status_.elapsed_time_ / config_.move_duration;
          new_position.x = Interpolate::Easing(config_.type_,position_status_.percent_, config_.move_from.x,config_.move_to.x);
          new_position.y = Interpolate::Easing(config_.type_,position_status_.percent_, config_.move_from.y,config_.move_to.y);
          new_position.z = Interpolate::Easing(config_.type_, position_status_.percent_, config_.move_from.z, config_.move_to.z);
        } else {
          position_status_.percent_ = 0.0f;
          // new_position = config_.move_from;
        }
        // Interpolate and set new position
        entity_->drawable_->set_position(&new_position.x);

        // Check if the animation has ended
        if (position_status_.percent_ <= 0.0f) {
          position_status_.ended_ = true;
        }
      }
      // Update rotation if animation is rotating and not ended
      if (config_.is_rotating && !rotation_status_.ended_) {
        // increase elapsed time
        rotation_status_.elapsed_time_ -= manager->dt;
        if (rotation_status_.elapsed_time_ <= 0.0f) {
          rotation_status_.elapsed_time_ = 0.0f;
        }

        // calculate percentage between [0,1]
        if (config_.rotate_duration != 0.0f) {
          rotation_status_.percent_ = rotation_status_.elapsed_time_ / config_.rotate_duration;
          new_rotation.x = Interpolate::Easing(config_.type_,rotation_status_.percent_, config_.rotate_from.x, config_.rotate_to.x);
          new_rotation.y = Interpolate::Easing(config_.type_, rotation_status_.percent_, config_.rotate_from.y, config_.rotate_to.y);
          new_rotation.z = Interpolate::Easing(config_.type_, rotation_status_.percent_, config_.rotate_from.z, config_.rotate_to.z);
          // new_rotation = config_.rotate_from + (config_.rotate_from - config_.rotate_to) * rotation_status_.percent_;
        } else {
          rotation_status_.percent_ = 0.0f;
          new_rotation = config_.rotate_from;
        }
        // Interpolate and set new rotation
        entity_->drawable_->set_rotation_xyz(&new_rotation.x);
        //entity_->transform_.set_rotation(new_rotation);

        // Check if the animation has ended
        if (rotation_status_.percent_ <= 0.0f) {
          rotation_status_.ended_ = true;
        }
      }
      // Update scale if animation is scaling and not ended
      if (config_.is_scaling && !scale_status_.ended_) {
        // increase elapsed time
        scale_status_.elapsed_time_ -= manager->dt;
        if (scale_status_.elapsed_time_ <= 0.0f) {
          scale_status_.elapsed_time_ = 0.0f;
        }

        if (config_.scale_duration != 0.0f) {
          scale_status_.percent_ = scale_status_.elapsed_time_ / config_.scale_duration;
          new_scale.x = Interpolate::Easing(config_.type_,scale_status_.percent_, config_.scale_from.x,config_.scale_to.x);
          new_scale.y = Interpolate::Easing(config_.type_,scale_status_.percent_, config_.scale_from.y,config_.scale_to.y);
          new_scale.z = Interpolate::Easing(config_.type_, scale_status_.percent_, config_.scale_from.z, config_.scale_to.z);
          // new_scale = Vec2::Lerp(config_.scale_from, config_.scale_to, scale_status_.percent_);
        } else {
          scale_status_.percent_ = 0.0f;
          new_scale = config_.scale_from;
        }
        // calculate percentage between [0,1]

        // Interpolate and set new scale
        entity_->drawable_->set_scale(&new_scale.x);

        // Check if the animation has ended
        if (scale_status_.percent_ <= 0.0f) {
          scale_status_.ended_ = true;
        }
      }
    } else {
      // Update position if animation is moving and not ended
      if (config_.is_moving && !position_status_.ended_) {
        // increase elapsed time
        position_status_.elapsed_time_ += manager->dt;
        if (position_status_.elapsed_time_ >= config_.move_duration) {
          position_status_.elapsed_time_ = config_.move_duration;
        }
        // calculate percentage between [0,1]
        if (config_.move_duration != 0.0f) {
          position_status_.percent_ = position_status_.elapsed_time_ / config_.move_duration;
          new_position.x = Interpolate::Easing(config_.type_,position_status_.percent_, config_.move_from.x,config_.move_to.x);
          new_position.y = Interpolate::Easing(config_.type_,position_status_.percent_, config_.move_from.y,config_.move_to.y);
          new_position.z = Interpolate::Easing(config_.type_, position_status_.percent_, config_.move_from.z, config_.move_to.z);
        } else {
          position_status_.percent_ = 1.0f;
          new_position = config_.move_to;
        }
        // Interpolate and set new position
        entity_->drawable_->set_position(&new_position.x);

        // Check if the animation has ended
        if (position_status_.percent_ >= 1.0f) {
          position_status_.ended_ = true;
        }
      }
      // Update rotation if animation is rotating and not ended
      if (config_.is_rotating && !rotation_status_.ended_) {
        Vec3 new_rotation;
        // increase elapsed time
        rotation_status_.elapsed_time_ += manager->dt;
        if (rotation_status_.elapsed_time_ >= config_.rotate_duration) {
          rotation_status_.elapsed_time_ = config_.rotate_duration;
        }
        // calculate percentage between [0,1]
        if (config_.rotate_duration != 0.0f) {
          rotation_status_.percent_ = rotation_status_.elapsed_time_ / config_.rotate_duration;
          new_rotation.x = Interpolate::Easing(config_.type_,rotation_status_.percent_, config_.rotate_from.x, config_.rotate_to.x);
          new_rotation.y = Interpolate::Easing(config_.type_, rotation_status_.percent_, config_.rotate_from.y, config_.rotate_to.y);
          new_rotation.z = Interpolate::Easing(config_.type_, rotation_status_.percent_, config_.rotate_from.z, config_.rotate_to.z);
        } else {
          rotation_status_.percent_ = 1.0f;
          new_rotation = config_.rotate_to;
        }
        // Interpolate and set new rotation
        entity_->drawable_->set_rotation_xyz(&new_rotation.x);

        // Check if the animation has ended
        if (rotation_status_.percent_ >= 1.0f) {
          rotation_status_.ended_ = true;
        }
      }
      // Update scale if animation is scaling and not ended
      if (config_.is_scaling && !scale_status_.ended_) {
        // Check if the animation has ended
        if (scale_status_.percent_ >= 1.0f){
          scale_status_.percent_ = 1.0f;
          scale_status_.ended_ = true;
          // entity_->transform_.set_scale(config_.scale_to);
        }
        
        // increase elapsed time
        scale_status_.elapsed_time_ += manager->dt;
        if (scale_status_.elapsed_time_ >= config_.scale_duration) {
          scale_status_.elapsed_time_ = config_.scale_duration;
        }
        // calculate percentage between [0,1]
        if (config_.scale_duration != 0.0f) {
          scale_status_.percent_ = scale_status_.elapsed_time_ / config_.scale_duration;
          new_scale.x = Interpolate::Easing(config_.type_,scale_status_.percent_, config_.scale_from.x,config_.scale_to.x);
          new_scale.y = Interpolate::Easing(config_.type_,scale_status_.percent_, config_.scale_from.y,config_.scale_to.y);
          new_scale.z = Interpolate::Easing(config_.type_, scale_status_.percent_, config_.scale_from.z, config_.scale_to.z);
        } else {
          scale_status_.percent_ = 1.0f;
          new_scale = config_.scale_to;
        }

        // Interpolate and set new scale
        entity_->drawable_->set_scale(&new_scale.x);

        // Check if the animation has ended
        // if (scale_status_.percent_ >= 1.0f) {
        //   scale_status_.percent_ = 1.0f;
        //   scale_status_.ended_ = true;
        //   entity_->transform_.set_scale(config_.scale_to);
        // }
      }
    }
  }
  else{
    config_.current_delay += manager->dt;
  }
}

void AnimationInstance::set_animation_status(const AnimationStatusOption option, bool status) {
  switch (option) {
  case AnimationStatusOption_Position:
    position_status_.ended_ = status;
    /* code */
    break;
  case AnimationStatusOption_Rotation:
    rotation_status_.ended_ = status;
    /* code */
    break;
  case AnimationStatusOption_Scale:
    scale_status_.ended_ = status;
    /* code */
    break;
  default:
    break;
  }
}