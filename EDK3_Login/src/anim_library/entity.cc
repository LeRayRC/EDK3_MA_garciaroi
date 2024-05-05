
#include "anim_library/entity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "anim_library/animationinstance.h"
#include "demo_manager.h"

int Entity::next_entity_id = 0;

Entity::Entity() {
  enabled_ = true;
  snprintf(name_, 16, "\0");
  snprintf(temp_name_, 16, "\0");
  id_ = Entity::next_entity_id;
  Entity::next_entity_id++;
  animation_config_selected = 0;
  anim_instance_ = nullptr;
  play_animation_ = true;
  attached_ = false;
  position_ = { 0.0f,0.0f,0.0f };
  rotation_ = { 0.0f,0.0f,0.0f };
  scale_ = { 1.0f,1.0f,1.0f };
  drawable_.alloc();
  drawable_->set_name(name_);
}

Entity::Entity(bool enabled, char *name) {
  enabled_ = enabled;
  id_ = Entity::next_entity_id;
  Entity::next_entity_id++;
  snprintf(name_, 16, "%s\0", name);
  snprintf(temp_name_, 16, "%s\0", name);
  animation_config_selected = 0;
  anim_instance_ = nullptr;
  play_animation_ = true;
  attached_ = false;
  position_ = { 0.0f,0.0f,0.0f };
  rotation_ = { 0.0f,0.0f,0.0f };
  scale_ = { 1.0f,1.0f,1.0f };
  drawable_.alloc();
  drawable_->set_name(name_);
}

Entity::Entity(const Entity &other) {
  enabled_ = other.enabled_;
  snprintf(name_, 16, "%s\0", other.name_);
  snprintf(temp_name_, 16, "%s\0", other.name_);
  animation_config_selected = other.animation_config_selected;
  anim_instance_ = nullptr;
  id_ = Entity::next_entity_id;
  attached_ = other.attached_;
  Entity::next_entity_id++;
  position_ = other.position_;
  rotation_ = other.rotation_;
  scale_ = other.scale_;
  drawable_ = other.drawable_;
  drawable_->set_name(other.name_);
}


Entity::~Entity() {
}

bool Entity::enable(bool enable) {
  enabled_ = enable;

  return enabled_;
}

int Entity::set_play_animation(bool value) {
  play_animation_ = value;

  return play_animation_;
}

std::string Entity::set_name(char* new_name) {
  strcpy(name_, new_name);
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
    drawable_->set_position(position_.x, position_.y, position_.z);
    drawable_->set_rotation_xyz(rotation_.x, rotation_.y, rotation_.z);
    drawable_->set_scale(scale_.x, scale_.y, scale_.z);
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

void Entity::init() {
    position_ = Vec3(0.0f, 0.0f, 0.0f);
    scale_ = Vec3(1.0f, 1.0f, 1.0f);
    rotation_ = Vec3(0.0f, 0.0f, 0.0f);
}

void Entity::set_position(Vec3 pos) {
    position_ = pos;
    
}

void Entity::set_rotation(Vec3 rot) {
    rotation_ = rot;
}

void Entity::set_scale(Vec3 scale) {
    scale_ = scale;
}

Vec3 Entity::position() const {
    return position_;
}

Vec3 Entity::rotation() const {
    return rotation_;
}

Vec3 Entity::scale() const {
    return scale_;
}



void Entity::setupDrawable(EDK3::Geometry* geo,
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

void Entity::attachDrawable(DrawableAttached drawableAttached) {
    DemoManager* manager = DemoManager::getInstance();
    drawableAttached_ = drawableAttached;
    switch (drawableAttached)
    {
    case DrawableAttached_Cube:
        drawable_->set_geometry(manager->custom_cube.get());
        break;
    case DrawableAttached_Quad:
        drawable_->set_geometry(manager->custom_quad.get());
        break;
    case DrawableAttached_Sphere:
        drawable_->set_geometry(manager->custom_sphere.get());
        break;
    case DrawableAttached_Terrain:
        drawable_->set_geometry(manager->terrain_custom.get());
        break;
    case DrawableAttached_Donut:
        drawable_->set_geometry(manager->custom_torus.get());
        break;
    case DrawableAttached_Tree:
        drawable_->set_geometry(manager->custom_tree.get());
        break;
    case DrawableAttached_House:
        drawable_->set_geometry(manager->house_geometry[4].get());
        break;
    case DrawableAttached_Boat:
        drawable_->set_geometry(manager->boat_geometry[0].get());
        break;
    }
    drawable_->set_material(manager->mat_selected.get());
    drawable_->set_material_settings(manager->mat_light_settings.get());
    if (!attached_) {
        manager->root->addChild(drawable_.get());
        attached_ = true;
    }
}
