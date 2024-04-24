#include "interface.h"

#include "demo_manager.h"
#include "material_custom.h"


//const char* GetLightTypeName(LightType type) {
//    switch (type)
//    {
//    case Directional:
//        return "Directional";
//        break;
//    case Point:
//        return "Point";
//        break;
//    case Spot:
//        return "Spot";
//        break;
//    default:
//        break;
//    }
//}

void SetFlags(ImGuiWindow *window) {
  window->window_flags = 0;
  if (window->flags.no_titlebar)
    window->window_flags |= ImGuiWindowFlags_NoTitleBar;
  if (window->flags.no_scrollbar)
    window->window_flags |= ImGuiWindowFlags_NoScrollbar;
  if (!window->flags.no_menu)
    window->window_flags |= ImGuiWindowFlags_MenuBar;
  if (window->flags.no_move)
    window->window_flags |= ImGuiWindowFlags_NoMove;
  if (window->flags.no_resize)
    window->window_flags |= ImGuiWindowFlags_NoResize;
  if (window->flags.no_collapse)
    window->window_flags |= ImGuiWindowFlags_NoCollapse;
  if (window->flags.no_bring_to_front)
    window->window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
}

void WindowSettings() {
  DemoManager* manager = DemoManager::getInstance();
  manager->settings_window.flags.no_resize = false;
  SetFlags(&manager->settings_window);
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
  // ImGui::Begin("Settings", NULL, game->settings_window.window_flags);
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("Windows")) {
      if (ImGui::BeginMenu("Settings")) {
        ImGui::Checkbox("No Titlebar", &manager->settings_window.flags.no_titlebar);
        ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Lights")) {
        ImGui::Checkbox("Opened", &manager->lights_window.popen);
        ImGui::Checkbox("No Titlebar", &manager->lights_window.flags.no_titlebar);
        ImGui::Checkbox("No Resize", &manager->lights_window.flags.no_resize);
        ImGui::Checkbox("No Move", &manager->lights_window.flags.no_move);
        ImGui::EndMenu();
      }
      

      if (ImGui::BeginMenu("Performance")) {
        ImGui::Checkbox("Opened", &manager->performance_window.popen);
        ImGui::Checkbox("No Titlebar", &manager->performance_window.flags.no_titlebar);
        ImGui::Checkbox("No Resize", &manager->performance_window.flags.no_resize);
        ImGui::Checkbox("No Move", &manager->performance_window.flags.no_move);
        ImGui::EndMenu();
      } 

      if (ImGui::BeginMenu("Camera")) {
          ImGui::Checkbox("Opened", &manager->camera_window.popen);
          ImGui::Checkbox("No Titlebar", &manager->camera_window.flags.no_titlebar);
          ImGui::Checkbox("No Resize", &manager->camera_window.flags.no_resize);
          ImGui::Checkbox("No Move", &manager->camera_window.flags.no_move);
          ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Hierachy")) {
          ImGui::Checkbox("Opened", &manager->hierachy_window.popen);
          ImGui::Checkbox("No Titlebar", &manager->hierachy_window.flags.no_titlebar);
          ImGui::Checkbox("No Resize", &manager->hierachy_window.flags.no_resize);
          ImGui::Checkbox("No Move", &manager->hierachy_window.flags.no_move);
          ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Demo")) {
        if (ImGui::Button("Load Demo")) {
            printf("Loading Demo\n");
        }
    ImGui::EndMenu();
    }
    
    ImGui::EndMainMenuBar();
  }
  // ImGui::End();
}

void InitDefaultWindowFlags(ImGuiWindow *window, bool default_opened) {
  window->flags.no_titlebar = false;
  window->flags.no_scrollbar = false;
  window->flags.no_menu = false;
  window->flags.no_move = false;
  window->flags.no_resize = false;
  window->flags.no_collapse = false;
  window->popen = default_opened;
}

void WindowMenu(ImGuiWindow *window) {
  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("Options")) {
      ImGui::Checkbox("Opened", &window->popen);
      ImGui::Checkbox("No Titlebar", &window->flags.no_titlebar);
      ImGui::Checkbox("No Resize", &window->flags.no_resize);
      ImGui::Checkbox("No Move", &window->flags.no_move);
      ImGui::EndMenu();
    }

    ImGui::EndMenuBar();
  }
}

void WindowsController() {
  DemoManager* manager = DemoManager::getInstance();
  //Game *game = Game::getInstance();
  if (manager->settings_window.popen) {
    WindowSettings();
  }
  if (manager->lights_window.popen) {
    LightsWindow();
  }
  if (manager->performance_window.popen) {
      PerformanceWindow(manager->dt);
  }
  if (manager->camera_window.popen) {
      CameraWindow();
  }
  if (manager->hierachy_window.popen) {
      HierachyWindow();
  }
  /*
  if (game->animationconfigs_window.popen) {
    AnimationConfigsManagerWindow();
  }
  if (game->newpath_window.popen) {
    NewPathWindow();
  }
  if (game->newanimationconfig_window.popen) {
    NewAnimationConfigWindow();
  }
  if (game->newtexture_window.popen) {
    NewTextureWindow();
  }
  if (game->newsprite_window.popen) {
    NewSpriteWindow();
  }*/
}

void LightsWindow() {
    static const char light_types[60] = { "Directional\0Point\0Spot\0" };
    DemoManager* manager = DemoManager::getInstance();
    manager->settings_window.flags.no_resize = false;
    SetFlags(&manager->lights_window);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Lights Config", &manager->lights_window.popen, manager->lights_window.window_flags);
    WindowMenu(&manager->lights_window);

    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> selected_light_settings = manager->mat_light_settings.get();
    char name[10];
    ImGui::DragFloat3("Ambient Color", &EDK3::MaterialCustom::LightSettings::ambient_color_.x, 0.01f, 0.0f, 1.0f);
    for (int i = 0; i < 8; i++) {
        bool deletable = true;
        ImGui::PushID(i);
        sprintf(name, "Light %d\0", i + 1);
        if (ImGui::TreeNode(name)) {
            ImGui::Checkbox("Enabled", &selected_light_settings->light_confs_[i].enabled_);
            if (selected_light_settings->light_confs_[i].enabled_) {
                ImGui::Text("Enabled");
                
                //ImGui::DragFloat3(selected_light_settings->)
            }
            //if (game->animation_configs_[i].is_moving) {
            //    ImGui::InputFloat2("Move from", &game->animation_configs_[i].move_from.x);
            //    ImGui::InputFloat2("Move To", &game->animation_configs_[i].move_to.x);
            //    ImGui::DragFloat("Move duration", &game->animation_configs_[i].move_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
            //    ImGui::NewLine();
            //}

            /*
            ImGui::Checkbox("Is Rotating", &game->animation_configs_[i].is_rotating);
            if (game->animation_configs_[i].is_rotating) {
                ImGui::InputFloat("rotate from", &game->animation_configs_[i].rotate_from);
                ImGui::InputFloat("rotate to", &game->animation_configs_[i].rotate_to);
                ImGui::DragFloat("rotate duration", &game->animation_configs_[i].rotate_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
                ImGui::NewLine();
            }

            ImGui::Checkbox("Is Scaling", &game->animation_configs_[i].is_scaling);
            if (game->animation_configs_[i].is_scaling) {
                ImGui::InputFloat2("scale from", &game->animation_configs_[i].scale_from.x);
                ImGui::InputFloat2("scale to", &game->animation_configs_[i].scale_to.x);
                ImGui::DragFloat("scale duration", &game->animation_configs_[i].scale_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
            }

            */
            
            ImGui::Combo("Type", &selected_light_settings->light_confs_[i].type_,
                light_types, 3);
            if (&selected_light_settings->light_confs_[i] != 0) {
                ImGui::DragFloat3("Position", &selected_light_settings->light_confs_[i].pos_.x, 0.1f, -100.0f, 100.0f);
            }
            
            ImGui::DragFloat3("Direction", &selected_light_settings->light_confs_[i].dir_.x, 0.1f, -1.0f, 1.0f);
            ImGui::DragFloat3("Diffuse Color", &selected_light_settings->light_confs_[i].diff_color_.x, 0.01f, 0.0f, 1.0f);
            ImGui::Separator();
            ImGui::DragFloat3("Specular Color", &selected_light_settings->light_confs_[i].spec_color_.x, 0.01f, 0.0f, 1.0f);
            ImGui::DragFloat3("Camera pos", &selected_light_settings->light_confs_[i].camera_pos_.x, 0.1f, -100.0f, 100.0f);
            ImGui::InputFloat("Linear att", &selected_light_settings->light_confs_[i].linear_att_);
            ImGui::InputFloat("Quadratic att", &selected_light_settings->light_confs_[i].quadratic_att_);
            ImGui::InputFloat("Constant att", &selected_light_settings->light_confs_[i].constant_att_);
            ImGui::InputFloat("Shininess", &selected_light_settings->light_confs_[i].shininess_);
            ImGui::InputFloat("Strength", &selected_light_settings->light_confs_[i].strength_);
            ImGui::TreePop();

        }
        ImGui::PopID();
    }




    ImGui::End();
}

void HierachyWindow() {
    DemoManager* manager = DemoManager::getInstance();
    manager->hierachy_window.flags.no_resize = false;
    SetFlags(&manager->hierachy_window);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Hierachy Window", &manager->hierachy_window.popen, manager->hierachy_window.window_flags);
    WindowMenu(&manager->hierachy_window);



    ImGui::End();
}


void PerformanceWindow(double dt) {
    DemoManager* manager = DemoManager::getInstance();
    manager->performance_window.flags.no_resize = false;
    SetFlags(&manager->performance_window);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Performance", &manager->performance_window.popen, manager->performance_window.window_flags);
    WindowMenu(&manager->performance_window);

    ImGui::Text("FPS: %0.1f", 1000.0 / dt);
    ImGui::Text("Delta time: %0.3f ms", dt);
    ImGui::End();

}

void CameraWindow() {
    DemoManager* manager = DemoManager::getInstance();
    manager->camera_window.flags.no_resize = false;
    SetFlags(&manager->camera_window);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Camera", &manager->camera_window.popen, manager->camera_window.window_flags);
    WindowMenu(&manager->camera_window);

    const float* camera_position = manager->camera->position();
    Vec3 camera_direction = manager->camera->direction();
    ImGui::Text("Position: ");
    ImGui::SameLine();
    ImGui::Text("x: %f, y: %f, z: %f", camera_position[0], camera_position[1], camera_position[2]);
    ImGui::Separator();
    ImGui::Text("Direction: ");
    ImGui::SameLine();
    ImGui::Text("x: %f, y: %f, z: %f", camera_direction.x, camera_direction.y, camera_direction.z);
    ImGui::Text("Accum mouse offset: %f %f", manager->camera->accum_mouse_offset_.x , manager->camera->accum_mouse_offset_.y);
    ImGui::Separator();
    ImGui::Text("Speed: %f", manager->camera->speed());
    ImGui::Text("Sensitivity: %f", manager->camera->sensitivity());
    ImGui::End();
}

/*
void EntitiesManagerWindow() {
  Game *game = Game::getInstance();
  SetFlags(&game->entities_window);
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);

  ImGui::Begin("Entities Manager", &game->entities_window.popen, game->entities_window.window_flags);
  WindowMenu(&game->entities_window);
  // ImGui::Text("There will be entities here");
  for (int i = 0; i < game->entities_.size(); i++) {
    ImGui::PushID(i);
    if (ImGui::TreeNode(&game->entities_[i]->name_[0])) {
      ImGui::InputText(" ", &game->entities_[i]->temp_name_);
      ImGui::SameLine();

      ImGui::Checkbox("Enable", &game->entities_[i]->enabled_);

      if (ImGui::Button("Update name")) {
        game->entities_[i]->name_ = game->entities_[i]->temp_name_;
      }

      ImGui::DragFloat2("Position", &game->entities_[i]->transform_.position_.x, 1.0f, 0.0f, 1280.0f);
      ImGui::DragFloat("Rotation", &game->entities_[i]->transform_.rotation_, 0.1f, 0.0f, 6.28f);
      if(game->entities_[i]->type_ == EntityType_Sprite){
        ImGui::DragFloat2("Scale", &game->entities_[i]->transform_.scale_.x, 0.01f, 0.0f, 2.0f);
      }
      else{
        ImGui::DragFloat2("Scale", &game->entities_[i]->transform_.scale_.x, 1.0f, 1.0f, 500.0f);
      }
      
      if (game->entities_[i]->type_ == EntityType_Sprite) {
        Sprite *sprite = (Sprite *)game->entities_[i];
        ImGui::DragFloat("Origin X", &game->entities_[i]->transform_.origin_.x, 1.0f, -1.0f * sprite->width(), 0.0f);
        ImGui::DragFloat("Origin Y", &game->entities_[i]->transform_.origin_.y, 1.0f, -1.0f * sprite->height(), 0.0f);
        if(ImGui::Button("Center")){
          sprite->transform_.set_origin({sprite->width()*(-0.5f),
                                        sprite->height()*(-0.5f)});
        }
      }else{
        ImGui::Checkbox("Solid",&((Path*)game->entities_[i])->solid_);
        static ImVec4 fill_color = ImVec4((float)(((Path *)(game->entities_[i]))->fill_color_.red_/255.0f),
                                    (float)(((Path *)(game->entities_[i]))->fill_color_.green_/255.0f),
                                    (float)(((Path *)(game->entities_[i]))->fill_color_.blue_/255.0f),
                                    1.0f);
        if(fill_color.w > 255.0f) fill_color.w = 255.0f;
        ImGui::ColorEdit4("Fill Color", &fill_color.x);
        ((Path *)(game->entities_[i]))->set_fill_color((unsigned char)(fill_color.x*255),
                                                        (unsigned char)(fill_color.y*255),
                                                        (unsigned char)(fill_color.z*255),
                                                        (unsigned char)(fill_color.w*255));

        static ImVec4 border_color = {(float)(((Path *)(game->entities_[i]))->border_color_.red_/255.0f),
                                      (float)(((Path *)(game->entities_[i]))->border_color_.green_/255.0f),
                                      (float)(((Path *)(game->entities_[i]))->border_color_.blue_/255.0f),
                                      (float)(((Path *)(game->entities_[i]))->border_color_.alpha_/255.0f)};
        if(border_color.w > 255.0f) border_color.w = 255.0f;
        ImGui::ColorEdit4("Border Color", &border_color.x);
        ((Path *)(game->entities_[i]))->set_border_color((unsigned char)(border_color.x*255),
                                                        (unsigned char)(border_color.y*255),
                                                        (unsigned char)(border_color.z*255),
                                                        (unsigned char)(border_color.w*255));
      }

      if (game->animation_configs_.size() >= 1) {
        if (ImGui::BeginCombo("Animation Config", &game->animation_configs_[game->entities_[i]->animation_config_selected].name[0])) {
          for (int j = 0; j < game->animation_configs_.size(); j++) {
            const bool is_selected = (game->entities_[i]->animation_config_selected == j);
            if (game->animation_configs_[j].name.length() == 0) {
              if (ImGui::Selectable(" ", is_selected))
                game->entities_[i]->animation_config_selected = j;
            } else {
              if (ImGui::Selectable(&game->animation_configs_[j].name[0], is_selected))
                game->entities_[i]->animation_config_selected = j;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
              ImGui::SetItemDefaultFocus();
          }
          ImGui::EndCombo();
        }

        if (ImGui::Button("Animate!")) {
          game->entities_[i]->playAnimation(game->animation_configs_[game->entities_[i]->animation_config_selected]);
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
          game->entities_[i]->stopAnimation();
        }
        ImGui::SameLine();
        if (ImGui::Button("Play")) {
          game->entities_[i]->set_play_animation(true);
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause")) {
          game->entities_[i]->set_play_animation(false);
        }

        ImGui::SameLine();

        if (nullptr != game->entities_[i]->anim_instance_) {
          if (ImGui::Checkbox("revert", &game->entities_[i]->anim_instance_->revert_)) {
            if (game->entities_[i]->anim_instance_->config_.is_moving) {
              game->entities_[i]->anim_instance_->set_animation_status(AnimationStatusOption_Position, false);
            }
            if (game->entities_[i]->anim_instance_->config_.is_rotating) {
              game->entities_[i]->anim_instance_->set_animation_status(AnimationStatusOption_Rotation, false);
            }
            if (game->entities_[i]->anim_instance_->config_.is_scaling) {
              game->entities_[i]->anim_instance_->set_animation_status(AnimationStatusOption_Scale, false);
            }
          }

          // Vec2 barSize(200, 20);

          // ImU32 color = IM_COL32(static_cast<unsigned char>(255 * &game->entities_[i]->anim_instance_->get_progress(0).percent_), 0, 0, 255);
          // ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0.0f, 0.0f), ImVec2(100.0f, 100.0f),
          //                                           color);

          // ImGui::SliderFloat("Variable", &game->entities_[i]->anim_instance_->get_progress(0).percent_, 0.0f, 1.0f);
          if (game->entities_[i]->anim_instance_->get_progress(0) > 0) {
            ImGui::Text("Movement Progress: ");
            ImGui::SameLine();
            // ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(41.0f, 74.0f, 122.0f, 1.0f));
            ImGui::ProgressBar(game->entities_[i]->anim_instance_->get_progress(0), ImVec2(200.0f, 20.0f));
            // ImGui::PopStyleColor();
          }
          if (game->entities_[i]->anim_instance_->get_progress(1) > 0) {
            ImGui::Text("Rotation Progress: ");
            ImGui::SameLine();
            ImGui::ProgressBar(game->entities_[i]->anim_instance_->get_progress(1), ImVec2(200.0f, 20.0f));
          }
          if (game->entities_[i]->anim_instance_->get_progress(2) > 0) {
            ImGui::Text("Scale Progress:    ");
            ImGui::SameLine();
            ImGui::ProgressBar(game->entities_[i]->anim_instance_->get_progress(2), ImVec2(200.0f, 20.0f));
          }
          if (game->entities_[i]->anim_instance_->config_.total_delay > 0.0f && game->entities_[i]->anim_instance_->config_.current_delay < game->entities_[i]->anim_instance_->config_.total_delay) {
            ImGui::Text("Delay Progress:    ");
            ImGui::SameLine();
            ImGui::ProgressBar(game->entities_[i]->anim_instance_->config_.current_delay/game->entities_[i]->anim_instance_->config_.total_delay, ImVec2(200.0f, 20.0f));
          }
        } 
        else {
          if (ImGui::Button("Inverse")) {
            game->entities_[i]->playAnimation(game->animation_configs_[game->entities_[i]->animation_config_selected]);
            game->entities_[i]->anim_instance_->revert_ = true;
            game->entities_[i]->anim_instance_->set_elapsed_time(0, game->entities_[i]->anim_instance_->get_duration(0));
            game->entities_[i]->anim_instance_->set_elapsed_time(1, game->entities_[i]->anim_instance_->get_duration(1));
            game->entities_[i]->anim_instance_->set_elapsed_time(2, game->entities_[i]->anim_instance_->get_duration(2));
          }
          if(ImGui::Button("Delete Entity")){
          //Clear from vector and then delete
            delete game->entities_[i];
            game->entities_.erase(game->entities_.begin()+i);
          }
        }
        
      }
      ImGui::TreePop();
    }
    ImGui::PopID();
  }
  ImGui::End();
}

void AnimationConfigsManagerWindow() {
  Game *game = Game::getInstance();
  SetFlags(&game->animationconfigs_window);
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
  
  ImGui::Begin("Animations Config Manager", &game->animationconfigs_window.popen, game->animationconfigs_window.window_flags);
  WindowMenu(&game->animationconfigs_window);

  for (int i = 0; i < game->animation_configs_.size(); i++) {
    bool deletable=true;
    ImGui::PushID(i);
    if (ImGui::TreeNode(&game->animation_configs_[i].name[0])) {
      ImGui::Checkbox("Is Moving", &game->animation_configs_[i].is_moving);
      if (game->animation_configs_[i].is_moving) {
        ImGui::InputFloat2("Move from", &game->animation_configs_[i].move_from.x);
        ImGui::InputFloat2("Move To", &game->animation_configs_[i].move_to.x);
        ImGui::DragFloat("Move duration", &game->animation_configs_[i].move_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
        ImGui::NewLine();
      }

      ImGui::Checkbox("Is Rotating", &game->animation_configs_[i].is_rotating);
      if (game->animation_configs_[i].is_rotating) {
        ImGui::InputFloat("rotate from", &game->animation_configs_[i].rotate_from);
        ImGui::InputFloat("rotate to", &game->animation_configs_[i].rotate_to);
        ImGui::DragFloat("rotate duration", &game->animation_configs_[i].rotate_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
        ImGui::NewLine();
      }

      ImGui::Checkbox("Is Scaling", &game->animation_configs_[i].is_scaling);
      if (game->animation_configs_[i].is_scaling) {
        ImGui::InputFloat2("scale from", &game->animation_configs_[i].scale_from.x);
        ImGui::InputFloat2("scale to", &game->animation_configs_[i].scale_to.x);
        ImGui::DragFloat("scale duration", &game->animation_configs_[i].scale_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
      }

      if (ImGui::BeginCombo("Interpolation", Interpolate::GetInterpolationTypeName(game->animation_configs_[i].type_))) {
        for (int j = 0; j < (int)InterpolationType_None; j++) {
          InterpolationType type = static_cast<InterpolationType>(j);
          const bool is_selected = (game->animation_configs_[i].type_ == type);

          if (ImGui::Selectable(Interpolate::GetInterpolationTypeName(type), is_selected)) {
            game->animation_configs_[i].type_ = type;
          }

          if (is_selected)
            ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
      }

      ImGui::DragFloat("Delay", &game->animation_configs_[i].total_delay, 0.1f, 0.0f, 10.0f);

      ImGui::InputText(" ", &game->animation_configs_[i].temp_name);
      ImGui::SameLine();

      if (ImGui::Button("Update name")) {
        game->animation_configs_[i].name = game->animation_configs_[i].temp_name;
      }
      if (ImGui::Button("Save")) {
        // game->animation_configs_[i].name = game->animation_configs_[i].temp_name;
        game->db_.saveAnimation(game->animation_configs_[i], game->animation_configs_db_[i]);
        Game::getInstance()->animation_configs_.clear();
        Game::getInstance()->animation_configs_db_.clear();
        game->db_.runQuery("SELECT * from animations;", game->db_.processAnimations, 0);
      }
      
      for(int j=0;j<game->entities_.size() && deletable;j++){
        deletable = strcmp(game->animation_configs_[game->entities_[j]->animation_config_selected].name.c_str(), game->animation_configs_[i].name.c_str());
      }

      if (ImGui::Button("Delete")) {
        if(deletable){
          
          if(game->db_.deleteAnimation(&game->animation_configs_[i], &game->animation_configs_db_[i])){
            for(int j = 0; j < game->entities_.size(); j++){
              if (game->entities_[j]->animation_config_selected > i) {
                game->entities_[j]->animation_config_selected--;
              }
            }
          }
        }
        // game->animation_configs_[i].name = game->animation_configs_[i].temp_name;
      }
      ImGui::SameLine();
      if (deletable) {
        // ImGui::Text("Name available");
        ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Can be deleted");
      } else {
        ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Config in use");
        // ImGui::Text("Name not available");
      }
      ImGui::TreePop();
    }
    ImGui::PopID();
  }

  ImGui::End();
}

void NewPathWindow() {
  Game *game = Game::getInstance();
  static bool is_regular = true;
  static int n_vertexes = game->kMinPathVertexes;
  static Vec2 vertexes[game->kMaxPathVertexes];
  static Vec2 position;
  static float rotation;
  static Vec2 scale;
  static char n_vertexes_char[20];
  SetFlags(&game->newpath_window);
  ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_FirstUseEver);
  ImGui::Begin("New Path", &game->newpath_window.popen, game->newpath_window.window_flags);
  WindowMenu(&game->newpath_window);
  ImGui::Text("New path");

  ImGui::Checkbox("Is regular", &is_regular);
  ImGui::DragInt("Num vertexes", &n_vertexes, 1.0f, game->kMinPathVertexes, game->kMaxPathVertexes);
  ImGui::InputFloat2("Position", &position.x);
  ImGui::DragFloat("Rotation", &rotation, 0.1f, 0.0f, 6.28f);
  ImGui::InputFloat2("Scale", &scale.x);

  if (!is_regular) {
    ImGui::NewLine();
    ImGui::Text("Vertexes values");
    for (int i = 0; i < n_vertexes; i++) {
      ImGui::PushID(i);
      snprintf(n_vertexes_char, 20, "Vertex %d", i);
      ImGui::DragFloat2(n_vertexes_char, &vertexes[i].x, 0.01f, -1.0f, 1.0f);
      ImGui::PopID();
    }
  }
  if (ImGui::Button("Create Path")) {
    Path *path;
    if (is_regular) {
      path = new Path();
      path->InitRegularPolygon(n_vertexes);
      path->transform_.set_position(position);
      path->transform_.set_rotation(rotation);
      path->transform_.set_scale(scale);
    } else {
      path = new Path(Color(255, 255, 255), Color(), false, vertexes, n_vertexes);
      path->transform_.set_position(position);
      path->transform_.set_rotation(rotation);
      path->transform_.set_scale(scale);
    }
    game->entities_.push_back(path);
  }
  ImGui::End();
}

void NewAnimationConfigWindow() {
  Game *game = Game::getInstance();
  bool unique = true;
  static AnimationConfig temp_anim_config;
  SetFlags(&game->newanimationconfig_window);
  ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver);

  ImGui::Begin("New Animation Config", &game->newanimationconfig_window.popen, game->newanimationconfig_window.window_flags);
  WindowMenu(&game->newanimationconfig_window);
  ImGui::Text("New animation config window");

  ImGui::Checkbox("Is Moving", &temp_anim_config.is_moving);
  if (temp_anim_config.is_moving) {
    ImGui::InputFloat2("Move from", &temp_anim_config.move_from.x);
    ImGui::InputFloat2("Move To", &temp_anim_config.move_to.x);
    ImGui::DragFloat("Move duration", &temp_anim_config.move_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
    ImGui::NewLine();
  }

  ImGui::Checkbox("Is Rotating", &temp_anim_config.is_rotating);
  if (temp_anim_config.is_rotating) {
    ImGui::InputFloat("rotate from", &temp_anim_config.rotate_from);
    ImGui::InputFloat("rotate to", &temp_anim_config.rotate_to);
    ImGui::DragFloat("rotate duration", &temp_anim_config.rotate_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
    ImGui::NewLine();
  }

  ImGui::Checkbox("Is Scaling", &temp_anim_config.is_scaling);
  if (temp_anim_config.is_scaling) {
    ImGui::InputFloat2("scale from", &temp_anim_config.scale_from.x);
    ImGui::InputFloat2("scale to", &temp_anim_config.scale_to.x);
    ImGui::DragFloat("scale duration", &temp_anim_config.scale_duration, 0.1f, 0.0f, game->kMaxAnimationDuration);
  }
  ImGui::NewLine();

  if (ImGui::BeginCombo("Interpolation", Interpolate::GetInterpolationTypeName(temp_anim_config.type_)))
  {
    for (int j = 0; j < (int)InterpolationType_None; j++)
    {
      InterpolationType type = static_cast<InterpolationType>(j);
      const bool is_selected = (temp_anim_config.type_ == type);

      if (ImGui::Selectable(Interpolate::GetInterpolationTypeName(type), is_selected))
      {
        temp_anim_config.type_ = type;
      }

      if (is_selected)
        ImGui::SetItemDefaultFocus();
    }
    ImGui::EndCombo();
  }
  ImGui::DragFloat("Delay", &temp_anim_config.total_delay, 0.1f, 0.0f, 10.0f);

  ImGui::InputText("Name", &temp_anim_config.name);

  for(int i = 0; i < game->animation_configs_.size() && unique;i++){
        unique = strcmp(game->animation_configs_[i].name.c_str(),  temp_anim_config.name.c_str());
  }

  if (ImGui::Button("Create new configuration")) {
    if (unique) {
      game->db_.insertAnimation(temp_anim_config);
      game->animation_configs_.clear();
      game->animation_configs_db_.clear();

      if (game->db_.runQuery("SELECT * from animations;", game->db_.processAnimations, 0) != SQLITE_OK) {
        printf("%s\n", game->db_.err_msg);
      }
    }
  }
  ImGui::SameLine();
  if(unique){
    // ImGui::Text("Name available");
    ImGui::TextColored(ImVec4(0.0f,1.0f,0.0f,1.0f),"Name available");
  }
  else{
    ImGui::TextColored(ImVec4(1.0f,0.0f,0.0f,1.0f),"Name already exist");
    // ImGui::Text("Name not available");
  }

  ImGui::End();
}

void NewTextureWindow() {
  Game *game = Game::getInstance();
  static std::string path_to_sprite;
  static bool failed_to_import = false;
  static bool valid_path = false;
  SetFlags(&game->newtexture_window);
  ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_FirstUseEver);
  ImGui::Begin("New Texture", &game->newtexture_window.popen, game->newtexture_window.window_flags);
  WindowMenu(&game->newtexture_window);

  if (path_to_sprite.size() > 0) {
    ImGui::Text("%s", &path_to_sprite[0]);
  } else {
    ImGui::Text(" ");
  }

  if (ImGui::Button("Browse")) {
    auto f = pfd::open_file("Choose files to read", pfd::path::home(),
                            {"Text Files (.png .jpg)", "*.png *.jpg",
                             "All Files", "*"},
                            pfd::opt::none);
    for (std::string const &name : f.result()) {
      for (int i = 0; i < name.size(); i++) {
        if (name[i] < 32) {
          valid_path = false;
          break;
        } else {
          valid_path = true;
        }
      }
      if (valid_path) {
        path_to_sprite = name;
      }
    }
  }
  ImGui::SameLine();
  if (valid_path) {
    if (ImGui::Button("Import")) {
      if (path_to_sprite.size() > 0) {
        Texture *texture = Texture::CreateTexture(path_to_sprite.c_str());
        if (nullptr != texture) {
          game->textures_.push_back(texture);
          failed_to_import = false;
          game->newtexture_window.popen = false;
        } else {
          failed_to_import = true;
        }
      }
    }
    if (failed_to_import) {
      ImGui::Text("Failed to import texture");
    }
  } else {
    ImGui::Text("Path no valid, browse again");
  }

  ImGui::End();
}

void NewSpriteWindow() {
  Game *game = Game::getInstance();
  static int texture_selected = 0;
  static Vec2 position;
  static Vec2 size;
  static Vec2 window_size;

  SetFlags(&game->newsprite_window);
  ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_FirstUseEver);
  ImGui::Begin("New Sprite", &game->newsprite_window.popen, game->newsprite_window.window_flags);
  WindowMenu(&game->newsprite_window);

  if (game->textures_.size() > 0) {

    // const char* last_separator = strrchr(game->textures_[texture_selected]->path_.c_str(),'\\');
    // if( last_separator != nullptr){
    // if (ImGui::BeginCombo("Select Texture", last_separator+1)){
    if (ImGui::BeginCombo("Select Texture", game->textures_[texture_selected]->path_.c_str())) {
      for (int j = 0; j < game->textures_.size(); j++) {
        const bool is_selected = (texture_selected == j);
        if (ImGui::Selectable(&game->textures_[j]->path_[0], is_selected))
          texture_selected = j;
        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
        if (is_selected)
          ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }

    ImGui::DragFloat("Pos X:", &position.x, 1.0f, -1.0f * game->textures_[texture_selected]->width(), 0.0f);
    ImGui::DragFloat("Pos Y:", &position.y, 1.0f, -1.0f * game->textures_[texture_selected]->height(), 0.0f);

    if (size.x > (game->textures_[texture_selected]->width() + position.x)) {
      size.x = game->textures_[texture_selected]->width() + position.x;
    }
    if (size.y > (game->textures_[texture_selected]->height() + position.y)) {
      size.y = game->textures_[texture_selected]->height() + position.y;
    }
    ImGui::DragFloat("Size X", &size.x, 1.0f, 0.0f, (float)(game->textures_[texture_selected]->width() + position.x));
    ImGui::DragFloat("Size Y", &size.y, 1.0f, 0.0f, (float)(game->textures_[texture_selected]->height() + position.y));

    ImGui::BeginChild("TextureToLoad", ImVec2(size.x, size.y), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::SetCursorPos(ImVec2(position.x, position.y));
    ImageFromTexture(game->textures_[texture_selected]->handle_);
    // }else{
    //   ImGui::Text("Error getting textures");
    // }

    ImGui::EndChild();

    if (ImGui::Button("Create")) {
      Sprite *sprite = new Sprite(*game->textures_[texture_selected], (int)(position.x * -1.0f),
                                  (int)(position.y * -1.0f),
                                  (int)size.x,
                                  (int)size.y);
      if (nullptr != sprite) {
        game->entities_.push_back(sprite);
      }
    }

  } else {
    ImGui::Text("There are no textures imported");
  }

  ImGui::End();
}

*/