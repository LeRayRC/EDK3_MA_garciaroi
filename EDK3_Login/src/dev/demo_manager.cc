
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
  //game->current_time = 0.0f;
  //game->last_time = 0.0f;
  //game->dt = 0.0f;
  //game->fps_timer = 0.0f;
  //game->refresh_fps_cooldown = 1.0f;
  //game->framerate = 0.0f;
  //game->demo_running_ = false;
  //
  //game->temp_handle_index = 0;
  //game->temp_handle = nullptr;
  //game->temp_handle_2 = nullptr;

  manager->dt = 0.0f;

  InitDefaultWindowFlags(&manager->settings_window);
  InitDefaultWindowFlags(&manager->lights_window);
  InitDefaultWindowFlags(&manager->performance_window);
  //InitDefaultWindowFlags(&game->animationconfigs_window);
  //InitDefaultWindowFlags(&game->newpath_window, false);
  //InitDefaultWindowFlags(&game->newtexture_window, false);
  //InitDefaultWindowFlags(&game->newsprite_window, false);
  //InitDefaultWindowFlags(&game->newanimationconfig_window, false);
  
  //game->db_.connect("./data/db/internal.db");
  //game->db_.runQuery("SELECT * from animations;", game->db_.processAnimations, 0);
  srand((unsigned int)time(NULL));
}

//void Game::update() {
//  Game *game = Game::getInstance();
//  for (int i = 0; i < game->entities_.size(); i++) {
//    game->entities_[i]->update();
//  }
//  if(game->demo_running_){
//    game->demo_et_.updateDemo();
//  }
//}
//
//void Game::draw() {
//  Game *game = Game::getInstance();
//  if(game->demo_running_){
//    game->demo_et_.drawDemo();
//  }
//  for (int i = 0; i < game->entities_.size(); i++) {
//    game->entities_[i]->draw();
//  }
//  
//}
//
//void Game::end() {
//  Game::getInstance()->window.windowDestroy();
//}

/* Null, because instance will be initialized on demand. */
DemoManager *DemoManager::instance = NULL;