#include "gsprite.h"

#include "animationinstance.h"

void Sprite::update() {
  if (enabled_ && play_animation_) {
    if (nullptr != anim_instance_) {

      anim_instance_->update();
      if (anim_instance_->isEnded()) {
        stopAnimation();
        // delete anim_instance_;
        // anim_instance_ = nullptr;
      }
    }
  }
}