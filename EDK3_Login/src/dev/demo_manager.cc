
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

  manager->root.alloc();

  manager->mat_basic.alloc();
  manager->mat_normals.alloc();
  manager->mat_light_settings.alloc();

  manager->dt = 0.0f;
  manager->show_normals = false;
  manager->enable_postprocess = false;
  manager->enable_wireframe = false;

  InitDefaultWindowFlags(&manager->settings_window);
  InitDefaultWindowFlags(&manager->lights_window);
  InitDefaultWindowFlags(&manager->performance_window);
  InitDefaultWindowFlags(&manager->camera_window);
  InitDefaultWindowFlags(&manager->control_window);
  InitDefaultWindowFlags(&manager->entities_window);
  InitDefaultWindowFlags(&manager->animationconfigs_window);
  performance_window.popen = false;
  camera_window.popen = false;

  animation_configs_counter = 0;
  srand((unsigned int)time(NULL));
}

/* Null, because instance will be initialized on demand. */
DemoManager *DemoManager::instance = NULL;