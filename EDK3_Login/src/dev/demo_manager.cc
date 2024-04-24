
#include "demo_manager.h"

#include "interface.h"
#include "time.h"

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
  manager->mat_light_settings.alloc();
  manager->mat_basic_settings.alloc();

  manager->dt = 0.0f;

  InitDefaultWindowFlags(&manager->settings_window);
  InitDefaultWindowFlags(&manager->lights_window);
  InitDefaultWindowFlags(&manager->performance_window);
  InitDefaultWindowFlags(&manager->hierachy_window);

  srand((unsigned int)time(NULL));
}

/* Null, because instance will be initialized on demand. */
DemoManager *DemoManager::instance = NULL;