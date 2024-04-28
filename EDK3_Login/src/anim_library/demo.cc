#include "demo.h"

#include "game.h"
#include "gsprite.h"
#include "path.h"

DemoET::DemoET(){
  textures_loaded_ = false;
  n_stars_ = 150;
}


bool DemoET::loadDemoTextures(){
    Game *game = Game::getInstance();

    //Import textures
    bike_texture_ = Texture::CreateTexture("./data/textures/demo/et_bike.png");
    if (nullptr != bike_texture_) {
      game->textures_.push_back(bike_texture_);
    }else{
      return false;
    }

    letters_texture_ = Texture::CreateTexture("./data/textures/demo/intro_letters_2.png");
    if (nullptr != letters_texture_) {
      game->textures_.push_back(letters_texture_);
    }else{
      return false;
    }

    enterprise_texture_ = Texture::CreateTexture("./data/textures/demo/enterprise.png");
    if (nullptr != enterprise_texture_) {
      game->textures_.push_back(enterprise_texture_);
    }else{
      return false;
    }

    falcon_texture_ = Texture::CreateTexture("./data/textures/demo/falcon.png");
    if (nullptr != falcon_texture_) {
      game->textures_.push_back(falcon_texture_);
    }else{
      return false;
    }

    xenomorph_texture_ = Texture::CreateTexture("./data/textures/demo/alien.png");
    if (nullptr != xenomorph_texture_) {
      game->textures_.push_back(xenomorph_texture_);
    }else{
      return false;
    }

    unicorn_texture_ = Texture::CreateTexture("./data/textures/demo/unicorn.png");
    if (nullptr != unicorn_texture_) {
      game->textures_.push_back(unicorn_texture_);
    }else{
      return false;
    }

    et_texture_ = Texture::CreateTexture("./data/textures/demo/et_character.png");
    if (nullptr != et_texture_) {
      game->textures_.push_back(et_texture_);
    }else{
      return false;
    }
    

    confuse_texture_ = Texture::CreateTexture("./data/textures/demo/confused.png");
    if (nullptr != confuse_texture_) {
      game->textures_.push_back(confuse_texture_);
    }else{
      return false;
    }
    return true;
}

void DemoET::initDemoEntities(){
  Game *game = Game::getInstance();

  clearDemo();
  
  for (int i = 0; i < n_stars_; i++){
    Path *path;
    AnimationConfig star_config;
    path = new Path();
    path->InitRegularPolygon(10);
    path->transform_.set_position({1.0f*(rand()%1280), 1.0f*(rand()%720)});
    path->transform_.set_rotation(0.0f);
    float scale = 0.5f + rand()%2;
    path->transform_.set_scale({scale,scale});
    for(int i=0;i<path->vertexes_.size();i+=2){
      path->vertexes_[i].x *= 0.5f;
      path->vertexes_[i].y *= 0.5f;
    }
    // game->entities_.push_back(path);
    star_config.is_moving = false;
    star_config.is_rotating = true;
    star_config.is_scaling = rand()%2;
    star_config.rotate_from = 0.0f;
    star_config.rotate_to = 64.2f;
    star_config.rotate_duration = 60.0f + rand()%60;
    star_config.scale_from = scale;
    star_config.scale_to = scale * 2.0f;
    star_config.scale_duration = 60.0f + rand()%60;
    star_config.total_delay = 0.0f;
    star_config.type_ = (InterpolationType)(rand()%(int)InterpolationType_None);

    
    stars_background_entity_.push_back(path);
    stars_background_entity_[stars_background_entity_.size()-1]->playAnimation(star_config);
  }


  letters_intro_ = new Sprite(*letters_texture_,{0.0f,0.0f},{835.0f,161.0f});
  if(nullptr != letters_intro_){
    game->entities_.push_back(letters_intro_);
    letters_intro_->transform_.set_origin({((Sprite*)letters_intro_)->width()*(-0.5f),
                                           ((Sprite*)letters_intro_)->height()*(-0.5f)});
  }

  letters_main_title_ = new Sprite(*letters_texture_,{0.0f,162.0f},{835.0f,161.0f});
  if(nullptr != letters_main_title_){
    game->entities_.push_back(letters_main_title_);
    letters_main_title_->transform_.set_origin({((Sprite*)letters_main_title_)->width()*(-0.5f),
                                                ((Sprite*)letters_main_title_)->height()*(-0.5f)});
  }

  letters_paragraph_1_ = new Sprite(*letters_texture_,{0.0f,422.0f},{855.0f,648.0f});
  if(nullptr != letters_paragraph_1_){
    game->entities_.push_back(letters_paragraph_1_);
    letters_paragraph_1_->transform_.set_origin({((Sprite*)letters_paragraph_1_)->width()*(-0.5f),
                                                 ((Sprite*)letters_paragraph_1_)->height()*(-0.5f)});
  }

  letters_paragraph_2_ = new Sprite(*letters_texture_,{0.0f,1130.0f},{855.0f,648.0f});
  if(nullptr != letters_paragraph_2_){
    game->entities_.push_back(letters_paragraph_2_);
    letters_paragraph_2_->transform_.set_origin({((Sprite*)letters_paragraph_2_)->width()*(-0.5f),
                                                 ((Sprite*)letters_paragraph_2_)->height()*(-0.5f)});
  }

  letters_paragraph_3_ = new Sprite(*letters_texture_,{0.0f,1840.0f},{855.0f,648.0f});
  if(nullptr != letters_paragraph_3_){
    game->entities_.push_back(letters_paragraph_3_);
    letters_paragraph_3_->transform_.set_origin({((Sprite*)letters_paragraph_3_)->width()*(-0.5f),
                                                 ((Sprite*)letters_paragraph_3_)->height()*(-0.5f)});
  }

  letters_paragraph_4_ = new Sprite(*letters_texture_,{0.0f,2540.0f},{855.0f,648.0f});
  if(nullptr != letters_paragraph_1_){
    game->entities_.push_back(letters_paragraph_4_);
    letters_paragraph_4_->transform_.set_origin({((Sprite*)letters_paragraph_4_)->width()*(-0.5f),
                                                 ((Sprite*)letters_paragraph_4_)->height()*(-0.5f)});
  }

  letters_paragraph_5_ = new Sprite(*letters_texture_,{0.0f,3250.0f},{855.0f,648.0f});
  if(nullptr != letters_paragraph_5_){
    game->entities_.push_back(letters_paragraph_5_);
    letters_paragraph_5_->transform_.set_origin({((Sprite*)letters_paragraph_5_)->width()*(-0.5f),
                                                 ((Sprite*)letters_paragraph_5_)->height()*(-0.5f)});
    
  }

  bike_entity_ = new Sprite(*bike_texture_,{0.0f,0.0f},{(float)bike_texture_->width(),(float)bike_texture_->height()});
  if(nullptr != bike_entity_){
    game->entities_.push_back(bike_entity_);
    bike_entity_->transform_.set_origin({((Sprite*)bike_entity_)->width()*(-0.5f),
                                         ((Sprite*)bike_entity_)->height()*(-0.5f)});
    bike_entity_->set_name("Bike");
  }

  falcon_entity_ = new Sprite(*falcon_texture_,{0.0f,0.0f},{(float)falcon_texture_->width(),(float)falcon_texture_->height()});
  if (nullptr != falcon_entity_) {
    game->entities_.push_back(falcon_entity_);
    falcon_entity_->transform_.set_origin({((Sprite *)falcon_entity_)->width() * (-0.5f),
                                           ((Sprite *)falcon_entity_)->height() * (-0.5f)});
    falcon_entity_->set_name("Falcon");
    }

  enterprise_entity_ = new Sprite(*enterprise_texture_, {0.0f, 0.0f}, {(float)enterprise_texture_->width(), (float)enterprise_texture_->height()});
  if(nullptr != enterprise_entity_){
    game->entities_.push_back(enterprise_entity_);
    enterprise_entity_->transform_.set_origin({((Sprite *)enterprise_entity_)->width() * (-0.5f),
                                               ((Sprite *)enterprise_entity_)->height() * (-0.5f)});
    enterprise_entity_->set_name("Enterpise");
  }

  xenomorph_entity_ = new Sprite(*xenomorph_texture_,{0.0f,0.0f},{(float)xenomorph_texture_->width(),(float)xenomorph_texture_->height()});
  if(nullptr != xenomorph_entity_){
    game->entities_.push_back(xenomorph_entity_);
    xenomorph_entity_->transform_.set_origin({((Sprite *)xenomorph_entity_)->width() * (-0.5f),
                                              ((Sprite *)xenomorph_entity_)->height() * (-0.5f)});
    xenomorph_entity_->set_name("Xenomorph");
  }

  unicorn_entity_ = new Sprite(*unicorn_texture_,{0.0f,0.0f},{(float)unicorn_texture_->width(),(float)unicorn_texture_->height()});
  if(nullptr != unicorn_entity_){
    game->entities_.push_back(unicorn_entity_);
    unicorn_entity_->transform_.set_origin({((Sprite *)unicorn_entity_)->width() * (-0.5f),
                                            ((Sprite *)unicorn_entity_)->height() * (-0.5f)});
    unicorn_entity_->set_name("Unicorn");
  }

  et_entity_ = new Sprite(*et_texture_,{0.0f,0.0f},{(float)et_texture_->width(),(float)et_texture_->height()});
  if (nullptr != et_entity_) {
    game->entities_.push_back(et_entity_);
    et_entity_->transform_.set_origin({((Sprite *)et_entity_)->width() * (-0.5f),
                                       ((Sprite *)et_entity_)->height() * (-0.5f)});
    et_entity_->set_name("ET");
  }

  confuse_entity_ = new Sprite(*confuse_texture_, {0.0f, 0.0f}, {(float)confuse_texture_->width(), (float)confuse_texture_->height()});
  if (nullptr != confuse_entity_) {
    game->entities_.push_back(confuse_entity_);
    confuse_entity_->transform_.set_origin({((Sprite *)confuse_entity_)->width() * (-0.5f),
                                            ((Sprite *)confuse_entity_)->height() * (-0.5f)});
    confuse_entity_->set_name("Confuse");
  }

  //Init default values on screen
  letters_main_title_->transform_.set_position({640.0f,360.0f});
  letters_intro_->transform_.set_position({640.0f,360.0f});

  letters_main_title_->transform_.set_position({-1000.0f, -1000.0f});
  letters_paragraph_1_->transform_.set_position({-1000.0f, -1000.0f});
  letters_paragraph_2_->transform_.set_position({-1000.0f, -1000.0f});
  letters_paragraph_3_->transform_.set_position({-1000.0f, -1000.0f});
  letters_paragraph_4_->transform_.set_position({-1000.0f, -1000.0f});
  letters_paragraph_5_->transform_.set_position({-1000.0f, -1000.0f});

  falcon_entity_->transform_.set_position({-1000.0f, -1000.0f});
  enterprise_entity_->transform_.set_position({-1000.0f, -1000.0f});
  xenomorph_entity_->transform_.set_position({-1000.0f, -1000.0f});
  unicorn_entity_->transform_.set_position({-1000.0f, -1000.0f});
  bike_entity_->transform_.set_position({-1000.0f, -1000.0f});
  et_entity_->transform_.set_position({-1000.0f, -1000.0f});
  confuse_entity_->transform_.set_position({-1000.0f, -1000.0f});

  bike_has_reverted_ = false;

  falcon_entity_->transform_.set_scale({0.25f,0.25f});
  enterprise_entity_->transform_.set_scale({0.15f, 0.20f});
  xenomorph_entity_->transform_.set_scale({0.3f, 0.3f});
  et_entity_->transform_.set_scale({0.3f, 0.3f});
  confuse_entity_->transform_.set_position({607.0f,131.0f});
  confuse_entity_->transform_.set_scale({0.0f, 0.0f});
  // confuse_entity_->transform_.set_rotation(6.08f);
  unicorn_entity_->transform_.set_scale({0.15f, 0.18f});

  // letters_main_title_->enabled_ = false;
  // letters_paragraph_1_->enabled_ = false;
  // letters_paragraph_2_->enabled_ = false;
  // letters_paragraph_3_->enabled_ = false;
  // letters_paragraph_4_->enabled_ = false;
  // letters_paragraph_5_->enabled_ = false;
  // falcon_entity_->enabled_ = false;
  // enterprise_entity_->enabled_ = false;
  // xenomorph_entity_->enabled_ = false;
  // unicorn_entity_->enabled_ = false;
  // bike_entity_->enabled_ = false;
  // et_entity_->enabled_ = false;
}

void DemoET::initDemoAnimationConfigs(){
  // Game *game = Game::getInstance();
  // Intro
  intro_config_.name           = "Intro";
  intro_config_.is_moving      = true;
  intro_config_.is_rotating    = false;
  intro_config_.is_scaling     = false;
  intro_config_.move_from.x    = 640.0f;
  intro_config_.move_to.x      = 640.0f;
  intro_config_.move_from.y    = 360.0f;
  intro_config_.move_to.y      = -75.0f;
  intro_config_.move_duration  = 10.0f;
  intro_config_.scale_from     = 1.0f;
  intro_config_.scale_to       = 0.0f;
  intro_config_.scale_duration = 15.0f;
  intro_config_.total_delay    = 5.0f;
  intro_config_.type_ = InterpolationType_ExpoEaseIn;  

  //Main title
  main_title_config_.name           = "ParagraphMovement";
  main_title_config_.is_moving      = true;
  main_title_config_.is_rotating    = false;
  main_title_config_.is_scaling     = true;
  main_title_config_.move_from.x    = 640.0f;
  main_title_config_.move_to.x      = 640.0f;
  main_title_config_.move_from.y    = 360.0f;
  main_title_config_.move_to.y      = -75.0f;
  main_title_config_.move_duration  = 8.0f;
  main_title_config_.scale_from     = 1.0f;
  main_title_config_.scale_to       = 0.0f;
  main_title_config_.scale_duration = 15.0f;
  main_title_config_.total_delay    = 19.0f;
  main_title_config_.type_ = InterpolationType_Linear;               

  //Paragraphs
  anim_config_paragraphs_.name           = "ParagraphMovement";
  anim_config_paragraphs_.is_moving      = true;
  anim_config_paragraphs_.is_rotating    = false;
  anim_config_paragraphs_.is_scaling     = true;
  anim_config_paragraphs_.move_from.x    = 660.0f;
  anim_config_paragraphs_.move_to.x      = 660.0f;
  anim_config_paragraphs_.move_from.y    = 1025.0f;
  anim_config_paragraphs_.move_to.y      = -200.0f;
  anim_config_paragraphs_.move_duration  = 30.0f;
  anim_config_paragraphs_.scale_from     = 1.0f;
  anim_config_paragraphs_.scale_to       = 0.0f;
  anim_config_paragraphs_.scale_duration = 30.0f;
  anim_config_paragraphs_.type_ = InterpolationType_Linear;

  //Bike
  bike_anim_config_.name            = "BikeMovement";
  bike_anim_config_.is_moving       = true;
  bike_anim_config_.is_rotating     = false;
  bike_anim_config_.is_scaling      = true;
  bike_anim_config_.move_from.x     = -100.0f;
  bike_anim_config_.move_to.x       = 320.0f;
  bike_anim_config_.move_from.y     = 0.0f;
  bike_anim_config_.move_to.y       = 325.0f;
  bike_anim_config_.move_duration   = 10.0f;
  bike_anim_config_.scale_from      = 0.1f;
  bike_anim_config_.scale_to        = 0.1f;
  bike_anim_config_.scale_duration  = 0.0f;
  bike_anim_config_.total_delay     = 20.0f;
  bike_anim_config_.type_           = InterpolationType_BounceEaseOut;

  // falcon
  falcon_anim_config_.name            = "FalconMovement";
  falcon_anim_config_.is_moving       = true;
  falcon_anim_config_.is_rotating     = false;
  falcon_anim_config_.is_scaling      = false;
  falcon_anim_config_.move_from.x     = 1400.0f;
  falcon_anim_config_.move_to.x       = -200.0f;
  falcon_anim_config_.move_from.y     = 100.0f;
  falcon_anim_config_.move_to.y       = 100.0f;
  falcon_anim_config_.move_duration   = 15.0f;
  falcon_anim_config_.scale_from      = 0.250f;
  falcon_anim_config_.scale_to        = 0.250f;
  falcon_anim_config_.scale_duration  = 0.1f;
  falcon_anim_config_.total_delay     = 40.0f;
  falcon_anim_config_.type_           = InterpolationType_CubicEaseOut;

  // enterprise
  enterprise_anim_config_.name = "EnterpriseMovement";
  enterprise_anim_config_.is_moving       = true;
  enterprise_anim_config_.is_rotating     = false;
  enterprise_anim_config_.is_scaling      = false;
  enterprise_anim_config_.move_from.x     = -100.0f;
  enterprise_anim_config_.move_to.x       = 1500.0f;
  enterprise_anim_config_.move_from.y     = 575.0f;
  enterprise_anim_config_.move_to.y       = 575.0f;
  enterprise_anim_config_.move_duration   = 13.0f;
  enterprise_anim_config_.scale_from      = 0.1f;
  enterprise_anim_config_.scale_to        = 0.1f;
  enterprise_anim_config_.scale_duration  = 0.0f;
  enterprise_anim_config_.total_delay     = 40.0f;
  enterprise_anim_config_.type_           = InterpolationType_CubicEaseOut;

  // xenomorph
  xenomorph_anim_config_.name             = "XenomorphMovement";
  xenomorph_anim_config_.is_moving        = true;
  xenomorph_anim_config_.is_rotating      = false;
  xenomorph_anim_config_.is_scaling       = false;
  xenomorph_anim_config_.move_from.x      = 157.0f;
  xenomorph_anim_config_.move_to.x        = 480.0f;
  xenomorph_anim_config_.move_from.y      = 366.0f;
  xenomorph_anim_config_.move_to.y        = 366.0f;
  xenomorph_anim_config_.move_duration    = 15.0f;
  xenomorph_anim_config_.scale_from       = 0.1f;
  xenomorph_anim_config_.scale_to         = 0.1f;
  xenomorph_anim_config_.scale_duration   = 0.0f;
  xenomorph_anim_config_.total_delay      = 55.0f;
  xenomorph_anim_config_.type_ = InterpolationType_ExpoEaseIn;

  // unicorn
  unicorn_anim_config_.name             = "UnicornMovement";
  unicorn_anim_config_.is_moving        = true;
  unicorn_anim_config_.is_rotating      = true;
  unicorn_anim_config_.is_scaling       = false;
  unicorn_anim_config_.move_from.x      = 169.0f;
  unicorn_anim_config_.move_to.x        = 169.0f;
  unicorn_anim_config_.move_from.y      = -100.0f;
  unicorn_anim_config_.move_to.y        = 680.0f;
  unicorn_anim_config_.move_duration    = 8.0f;
  unicorn_anim_config_.rotate_from      = 0.0f;
  unicorn_anim_config_.rotate_to        = 6.24f;
  unicorn_anim_config_.rotate_duration  = 8.0f;
  unicorn_anim_config_.scale_from       = 0.1f;
  unicorn_anim_config_.scale_to         = 0.1f;
  unicorn_anim_config_.scale_duration   = 0.0f;
  unicorn_anim_config_.total_delay      = 38.0f;
  unicorn_anim_config_.type_            = InterpolationType_BounceEaseOut;

  // et
  et_anim_config_.name = "ETMovement";
  et_anim_config_.is_moving       = true;
  et_anim_config_.is_rotating     = false;
  et_anim_config_.is_scaling      = false;
  et_anim_config_.move_from.x     = 1133.0f;
  et_anim_config_.move_to.x       = 805.0f;
  et_anim_config_.move_from.y     = 375.0f;
  et_anim_config_.move_to.y       = 375.0f;
  et_anim_config_.move_duration   = 15.0f;
  et_anim_config_.scale_from      = 0.1f;
  et_anim_config_.scale_to        = 0.1f;
  et_anim_config_.scale_duration  = 0.0f;
  et_anim_config_.total_delay     = 55.0f;
  et_anim_config_.type_           = InterpolationType_ExpoEaseIn;

  // confuse
  confuse_anim_config_.name = "ConfuseMovement";
  confuse_anim_config_.is_moving = false;
  confuse_anim_config_.is_rotating = true;
  confuse_anim_config_.is_scaling = true;
  confuse_anim_config_.move_from.x = 1133.0f;
  confuse_anim_config_.move_to.x = 805.0f;
  confuse_anim_config_.move_from.y = 375.0f;
  confuse_anim_config_.move_to.y = 375.0f;
  confuse_anim_config_.move_duration = 3.0f;
  confuse_anim_config_.rotate_from = 0.0f;
  confuse_anim_config_.rotate_to = 6.08f;
  confuse_anim_config_.rotate_duration = 3.0f;
  confuse_anim_config_.scale_from = 0.0f;
  confuse_anim_config_.scale_to = 0.5f;
  confuse_anim_config_.scale_duration = 3.0f;
  confuse_anim_config_.total_delay = 72.0f;
  confuse_anim_config_.type_ = InterpolationType_Linear;
}

void DemoET::animateDemoEntities(){
  letters_intro_->playAnimation(intro_config_);
  
  
  letters_main_title_->playAnimation(main_title_config_);

  anim_config_paragraphs_.total_delay = 14.5f;
  anim_config_paragraphs_.move_duration = 20.0f;
  letters_paragraph_1_->playAnimation(anim_config_paragraphs_);
  
  anim_config_paragraphs_.total_delay = 24.0f;
  letters_paragraph_2_->playAnimation(anim_config_paragraphs_);

  anim_config_paragraphs_.total_delay = 33.5f;
  letters_paragraph_3_->playAnimation(anim_config_paragraphs_);

  anim_config_paragraphs_.total_delay = 42.0f;
  letters_paragraph_4_->playAnimation(anim_config_paragraphs_);

  anim_config_paragraphs_.total_delay = 51.5f;
  letters_paragraph_5_->playAnimation(anim_config_paragraphs_);

  bike_entity_->playAnimation(bike_anim_config_);
  falcon_entity_->playAnimation(falcon_anim_config_);
  enterprise_entity_->playAnimation(enterprise_anim_config_);
  xenomorph_entity_->playAnimation(xenomorph_anim_config_);
  et_entity_->playAnimation(et_anim_config_);
  confuse_entity_->playAnimation(confuse_anim_config_);
  unicorn_entity_->playAnimation(unicorn_anim_config_);

  
}

void DemoET::runDemo(){
  elapsed_time_ = 0.0f;
  if(!textures_loaded_){
    textures_loaded_ = loadDemoTextures();
  }

  if(textures_loaded_){
    //Create Sprites from textures and Paths
    initDemoEntities();
    //Create AnimationConfigs for every Sprite
    initDemoAnimationConfigs();
    //Run AnimationInstances
    animateDemoEntities();
  }
}

void DemoET::updateDemo(){
  Game *game = Game::getInstance();
  elapsed_time_ += game->dt;
  if(elapsed_time_ >= 90.0f){
    elapsed_time_ = 0.0f;
    game->demo_running_ = false;
    clearDemo();

  } else {
    for(int i=0;i<stars_background_entity_.size();i++){
      stars_background_entity_[i]->update();
    }


    if(bike_entity_->anim_instance_ == nullptr && !bike_has_reverted_){
      bike_anim_config_.total_delay = 4.0f;
      bike_entity_->playAnimation(bike_anim_config_);
      bike_entity_->anim_instance_->revert_ = true;
      bike_entity_->anim_instance_->set_elapsed_time(0, bike_entity_->anim_instance_->get_duration(0));
      bike_entity_->anim_instance_->set_elapsed_time(1, bike_entity_->anim_instance_->get_duration(1));
      bike_entity_->anim_instance_->set_elapsed_time(2, bike_entity_->anim_instance_->get_duration(2));
      bike_has_reverted_ = true;
    }
  }
}

void DemoET::drawDemo(){
  for(int i=0;i<stars_background_entity_.size();i++){
    stars_background_entity_[i]->draw();
  } 
}

void DemoET::clearDemo(){
  Game *game = Game::getInstance();

  for(int i=0;i<game->entities_.size();i++){
    if(nullptr != game->entities_[i]->anim_instance_){
      game->entities_[i]->stopAnimation();
    }
  }

  for(int i=0;i<stars_background_entity_.size();i++){
    if(nullptr != stars_background_entity_[i]->anim_instance_){
      stars_background_entity_[i]->stopAnimation();
    }
    if(nullptr != stars_background_entity_[i]){
      delete stars_background_entity_[i];
    }
  }
  
  if(nullptr != letters_intro_){
    delete letters_intro_; 
    letters_intro_ = nullptr;
  }
  if(nullptr != letters_paragraph_1_){
    delete letters_paragraph_1_; 
    letters_paragraph_1_ = nullptr;
  }
  if(nullptr != letters_paragraph_2_){
    delete letters_paragraph_2_;
    letters_paragraph_2_ = nullptr;
  }
  if(nullptr != letters_paragraph_3_){
    delete letters_paragraph_3_;
    letters_paragraph_3_ = nullptr;
  }
  if(nullptr != letters_paragraph_4_){
    delete letters_paragraph_4_;
    letters_paragraph_4_ = nullptr;
  }
  if(nullptr != letters_paragraph_5_){
    delete letters_paragraph_5_;
    letters_paragraph_5_ = nullptr;
  } 
  if(nullptr != falcon_entity_){ 
    delete  falcon_entity_;
    falcon_entity_ = nullptr;
  }
  if(nullptr != enterprise_entity_){
    delete  enterprise_entity_;
    enterprise_entity_ = nullptr;
  }
  if(nullptr != xenomorph_entity_){ 
    delete xenomorph_entity_;
    xenomorph_entity_ = nullptr;
  }
  if(nullptr != unicorn_entity_){ 
    delete unicorn_entity_;
    unicorn_entity_ = nullptr;
  }
  if(nullptr != bike_entity_){ 
    delete  bike_entity_;
    bike_entity_ = nullptr;
  }
  if(nullptr != et_entity_){ 
    delete et_entity_;
    et_entity_ = nullptr;
  }
  if(nullptr != confuse_entity_){
    delete confuse_entity_;
    confuse_entity_ = nullptr;
  }
  game->entities_.clear();
  stars_background_entity_.clear();
}


