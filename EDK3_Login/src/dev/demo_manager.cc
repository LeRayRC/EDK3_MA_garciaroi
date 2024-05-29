
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
  manager->skybox_root.alloc();

  manager->mat_basic.alloc();
  manager->mat_normals.alloc();
  manager->mat_panoramic.alloc();
  manager->mat_wireframe.alloc();
  manager->mat_water.alloc();
  manager->mat_heightlayer.alloc();
  manager->mat_particles.alloc();
  

  manager->light_materials_settings.alloc(6);
  manager->mat_light_settings_general.alloc();
  manager->mat_light_settings_general->use_texture_ = true;
  manager->mat_light_settings = manager->light_materials_settings[0].alloc();
  manager->mat_light_water_settings = manager->light_materials_settings[1].alloc();
  manager->mat_heightlayer_settings = manager->light_materials_settings[2].alloc();
  manager->mat_house_settings = manager->light_materials_settings[3].alloc();
  manager->mat_dolphin_settings = manager->light_materials_settings[4].alloc();
  manager->mat_particles_settings = manager->light_materials_settings[5].alloc();
  manager->mat_panoramic_settings.alloc();

  //Postprocess
  manager->render_target.alloc()->init(kWindowWidth,
      kWindowHeight, 1);
  manager->mat_postprocess.alloc();
  manager->mat_postprocess_settings.alloc();

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
  InitDefaultWindowFlags(&manager->particles_window);


  performance_window.popen = false;
  camera_window.popen = false;

  animation_configs_counter = 0;
  srand((unsigned int)time(NULL));
}

/* Null, because instance will be initialized on demand. */
DemoManager *DemoManager::instance = NULL;