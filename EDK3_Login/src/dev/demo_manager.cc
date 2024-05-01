
#include "demo_manager.h"

#include "interface.h"
#include "time.h"
#include "anim_library/interpolate.h"

DemoManager * DemoManager::getInstance() {
  if (NULL == instance) {
    instance = new DemoManager();
  }
  return instance;
}

DemoManager::DemoManager() {}

void DemoManager::init() {
  DemoManager *manager = DemoManager::getInstance();

  manager->enable_postprocess = false;
  manager->root.alloc();

  manager->mat_basic.alloc();
  manager->mat_normals.alloc();
  manager->mat_light_settings.alloc();

  manager->dt = 0.0f;
  manager->show_normals = false;

  entity_boat_ = Entity();
  anim_config_boat_.is_moving = true;
  anim_config_boat_.is_rotating = true;
  anim_config_boat_.is_scaling = true;
  anim_config_boat_.total_delay = 0.0f;
  anim_config_boat_.move_duration = 10000.0f;
  anim_config_boat_.move_from = Vec3(0.0f, 0.0f, 0.0f);
  anim_config_boat_.move_to = Vec3(0.0, -50.0f, 0.0f);
  anim_config_boat_.scale_duration = 10000.0f;
  anim_config_boat_.scale_from = Vec3(3.0f, 3.0f, 3.0f);
  anim_config_boat_.scale_to = Vec3(60.0, 60.0f, 60.0f);
  anim_config_boat_.rotate_duration = 10000.0f;
  anim_config_boat_.rotate_from = Vec3(0.0f, 0.0f, 0.0f);
  anim_config_boat_.rotate_to = Vec3(0.0, 180.0f, 0.0f);
  anim_config_boat_.type_ = InterpolationType_Linear;

  InitDefaultWindowFlags(&manager->settings_window);
  InitDefaultWindowFlags(&manager->lights_window);
  InitDefaultWindowFlags(&manager->performance_window);
  InitDefaultWindowFlags(&manager->hierachy_window);
  InitDefaultWindowFlags(&manager->camera_window);
  InitDefaultWindowFlags(&manager->control_window);

  srand((unsigned int)time(NULL));
}

/* Null, because instance will be initialized on demand. */
DemoManager *DemoManager::instance = NULL;