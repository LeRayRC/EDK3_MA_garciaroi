
#include "anim_library/entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "anim_library/animationinstance.h"
#include "demo_manager.h"

int Entity::next_entity_id = 0;

Entity::Entity() {
  tag_ = 0;
  enabled_ = true;
  name_ = "EntityObj";
  temp_name_ = name_;
  id_ = Entity::next_entity_id;
  Entity::next_entity_id++;
  animation_config_selected = 0;
  anim_instance_ = nullptr;
  play_animation_ = true;
  drawable_.alloc();
}

Entity::Entity(int tag, bool enabled, std::string name) {
  tag_ = tag;
  enabled_ = enabled;
  id_ = Entity::next_entity_id;
  Entity::next_entity_id++;
  name_ = name;
  temp_name_ = name;
  animation_config_selected = 0;
  anim_instance_ = nullptr;
  play_animation_ = true;
  drawable_.alloc();
}

Entity::Entity(const Entity &other) {
  tag_ = other.tag_;
  enabled_ = other.enabled_;
  name_ = other.name_;
  temp_name_ = other.name_;
  animation_config_selected = other.animation_config_selected;
  anim_instance_ = nullptr;
  id_ = Entity::next_entity_id;
  Entity::next_entity_id++;
  drawable_ = other.drawable_;
}

Entity::~Entity() {}

bool Entity::enable(bool enable) {
  enabled_ = enable;

  return enabled_;
}

int Entity::set_tag(int new_tag) {
  tag_ = new_tag;

  return tag_;
}

int Entity::set_play_animation(bool value) {
  play_animation_ = value;

  return play_animation_;
}

std::string Entity::set_name(std::string new_name) {
  name_ = new_name;
  return name_;
}

void Entity::update() {
    if (enabled_ && play_animation_) {
        if (nullptr != anim_instance_) {
            anim_instance_->update();
            if (anim_instance_->isEnded()) {
                stopAnimation();
            }
        }
    }
}

void Entity::playAnimation(const AnimationConfig &anim_config) {
  stopAnimation();

  AnimationInstance *anim_instance = new AnimationInstance();
  anim_instance->set_entity(this);
  anim_instance->init(anim_config);
  set_play_animation(true);
  anim_instance_ = anim_instance;
}

void Entity::stopAnimation() {
  if (nullptr != anim_instance_) {
    delete anim_instance_;
    anim_instance_ = nullptr;
  }
}

void Entity::SetupDrawable(EDK3::Geometry* geo,
    EDK3::MaterialCustom* mat,
    EDK3::MaterialSettings* mat_settings,
    Vec3& pos, Vec3& scale, Vec3& rot) {
        DemoManager* manager = DemoManager::getInstance();
        drawable_->set_geometry(geo);
        drawable_->set_material(mat);
        drawable_->set_material_settings(mat_settings);
        drawable_->set_rotation_xyz(rot.x, rot.y, rot.z);
        drawable_->set_position(pos.x, pos.y, pos.z);
        drawable_->set_scale(scale.x, scale.y, scale.z);
        manager->root->addChild(drawable_.get());
}
