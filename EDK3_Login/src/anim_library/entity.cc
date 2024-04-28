
#include "entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "animationinstance.h"

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
}

Entity::Entity(const Entity &other) {
  tag_ = other.tag_;
  enabled_ = other.enabled_;
  name_ = other.name_;
  temp_name_ = other.name_;
  transform_ = other.transform_;
  animation_config_selected = other.animation_config_selected;
  anim_instance_ = nullptr;
  id_ = Entity::next_entity_id;
  Entity::next_entity_id++;
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

void Entity::draw() const {}
void Entity::update() {}

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
