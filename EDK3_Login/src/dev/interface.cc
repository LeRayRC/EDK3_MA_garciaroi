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
  // ImGui::Begin("Settings", NULL, manager->settings_window.window_flags);
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

      if (ImGui::BeginMenu("Control")) {
          ImGui::Checkbox("Opened", &manager->control_window.popen);
          ImGui::Checkbox("No Titlebar", &manager->control_window.flags.no_titlebar);
          ImGui::Checkbox("No Resize", &manager->control_window.flags.no_resize);
          ImGui::Checkbox("No Move", &manager->control_window.flags.no_move);
          ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Entities")) {
          ImGui::Checkbox("Opened", &manager->entities_window.popen);
          ImGui::Checkbox("No Titlebar", &manager->entities_window.flags.no_titlebar);
          ImGui::Checkbox("No Resize", &manager->entities_window.flags.no_resize);
          ImGui::Checkbox("No Move", &manager->entities_window.flags.no_move);
          ImGui::EndMenu();
      }

      ImGui::EndMenu();
    }
    /*if (ImGui::BeginMenu("Demo")) {
        if (ImGui::Button("Load Demo")) {
            printf("Loading Demo\n");
        }
    ImGui::EndMenu();
    }*/

    if (ImGui::BeginMenu("Entities")) {
        if (ImGui::Button("New Empty Entity")) {
            Entity* new_entity = new Entity(true,"EmptyObj");
            new_entity->init();
            auto it = manager->entities_.begin();
            manager->entities_.insert(it,new_entity);
        }
        if (ImGui::Button("New Terrain")) {
            //Entity* new_entity = new Entity(true, "TerrainObj");
            //manager->entities_.push_back(new_entity);
        }
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Animation Configs")) {
        if (ImGui::Button("New Empty Animation Config")) {
            AnimationConfig anim_config;
            snprintf(anim_config.name, 16, "Anim Config %d", manager->animation_configs_counter);
            snprintf(anim_config.temp_name, 16, "%s", anim_config.name);
            ResetAnimationConfig(anim_config);
            manager->animation_configs_.push_back(anim_config);
            manager->animation_configs_counter++;
            UpdateAnimationConfigsString();
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
  if (manager->entities_window.popen) {
      EntitiesManagerWindow();
  }
  if (manager->control_window.popen) {
      ControlWindow();
  }

  if (manager->animationconfigs_window.popen) {
      AnimationConfigsManagerWindow();
  }
  
}

void LightsWindow() {
    static const char light_types[60] = { "Directional\0Point\0Spot\0" };
    DemoManager* manager = DemoManager::getInstance();
    manager->lights_window.flags.no_resize = false;
    SetFlags(&manager->lights_window);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Lights Config", &manager->lights_window.popen, manager->lights_window.window_flags);
    WindowMenu(&manager->lights_window);

    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> selected_light_settings = manager->mat_light_settings_general;
    char name[10];
    ImGui::DragFloat3("Ambient Color", &EDK3::MaterialCustom::LightSettings::ambient_color_.x, 0.01f, 0.0f, 1.0f);
    ImGui::Checkbox("Use Texture", &selected_light_settings->use_texture_);
    ImGui::DragFloat("Water Transparency", &manager->mat_light_water_settings->alpha_, 0.01f, 0.0f, 1.0f);
    ImGui::DragFloat2("Water Speed", &manager->mat_light_water_settings->water_speed_.x, 0.01f, 0.0f, 5.0f);
    for (int i = 0; i < 8; i++) {
        ImGui::PushID(i);
        sprintf(name, "Light %d\0", i + 1);
        if (ImGui::TreeNode(name)) {
            ImGui::Checkbox("Enabled", &selected_light_settings->light_confs_[i].enabled_);
            
            ImGui::Combo("Type", &selected_light_settings->light_confs_[i].type_,
                light_types, 3);
            if (&selected_light_settings->light_confs_[i] != 0) {
                ImGui::DragFloat3("Position", &selected_light_settings->light_confs_[i].pos_.x, 0.1f, -100.0f, 100.0f);
            }

            if (selected_light_settings->light_confs_[i].type_ == 0) {
                ImGui::DragFloat3("Direction", &selected_light_settings->light_confs_[i].dir_.x, 0.1f, -1.0f, 1.0f);
            }
            if (selected_light_settings->light_confs_[i].type_ == 2) {
                ImGui::DragFloat3("Spot Direction", &selected_light_settings->light_confs_[i].spot_dir_.x, 0.01f, -1.0f, 1.0f);
            }
            ImGui::DragFloat3("Diffuse Color", &selected_light_settings->light_confs_[i].diff_color_.x, 0.01f, 0.0f, 1.0f);
            ImGui::Separator();
            ImGui::DragFloat3("Specular Color", &selected_light_settings->light_confs_[i].spec_color_.x, 0.01f, 0.0f, 1.0f);
            ImGui::DragFloat3("Camera pos", &selected_light_settings->light_confs_[i].camera_pos_.x, 0.1f, -100.0f, 100.0f);
            ImGui::InputFloat("Linear att", &selected_light_settings->light_confs_[i].linear_att_);
            ImGui::InputFloat("Quadratic att", &selected_light_settings->light_confs_[i].quadratic_att_);
            ImGui::InputFloat("Constant att", &selected_light_settings->light_confs_[i].constant_att_);
            ImGui::InputFloat("Shininess", &selected_light_settings->light_confs_[i].shininess_);
            ImGui::InputFloat("Strength", &selected_light_settings->light_confs_[i].strength_);
            if (selected_light_settings->light_confs_[i].type_ == 2) {
                ImGui::DragFloat("Cutoff", &selected_light_settings->light_confs_[i].cutoff_,0.01f,-1.0f,1.0f);
                ImGui::DragFloat("Outer Cutoff", &selected_light_settings->light_confs_[i].outer_cutoff_, 0.01f, -1.0f, 1.0f);
            }
        ImGui::TreePop();
        }
        ImGui::PopID();
    }
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

void ControlWindow() {
    DemoManager* manager = DemoManager::getInstance();
    manager->control_window.flags.no_resize = false;
    SetFlags(&manager->control_window);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
    ImGui::Begin("Control Window", &manager->control_window.popen, manager->control_window.window_flags);
    WindowMenu(&manager->control_window);
    if (!manager->enable_wireframe) {
        ImGui::Checkbox("Enable Postprocess", &manager->enable_postprocess);
    }
    if (ImGui::Checkbox("Show normals", &manager->show_normals)) {
        EDK3::ref_ptr<EDK3::MaterialCustom> mat_selected;
        if (manager->show_normals) {
            mat_selected = manager->mat_normals;
        }
        else {
            mat_selected = manager->mat_basic;
        }
        for (unsigned int i = 0; i < manager->root->num_children(); i++) {
            EDK3::Drawable* drawable = dynamic_cast<EDK3::Drawable*>(manager->root->child(i));
            drawable->set_material(mat_selected.get());
        }
        if (!manager->show_normals) {
          manager->water_entity_->drawable_->set_material(manager->mat_water.get());
        }
        
    }
    if (!manager->enable_postprocess) {
        if(ImGui::Checkbox("Wireframe mode", &manager->enable_wireframe)){
            EDK3::ref_ptr<EDK3::MaterialCustom> mat_selected;
            if (manager->enable_wireframe) {
                mat_selected = manager->mat_wireframe;
            }
            else {
                mat_selected = manager->mat_basic;
                
            }
            for (unsigned int i = 0; i < manager->root->num_children(); i++) {
                EDK3::Drawable* drawable = dynamic_cast<EDK3::Drawable*>(manager->root->child(i));
                drawable->set_material(mat_selected.get());
            }
            manager->water_entity_->drawable_->set_material(manager->mat_water.get());
        }
    }
    ImGui::DragFloat4("Framebuffer color", manager->clear_rgba, 0.01f, 0.0f, 1.0f);
                
    ImGui::End();
}

void EntitiesManagerWindow() {
  static const char drawable_types[60] = { "Cube\0Quad\0Sphere\0Terrain\0Donut\0Tree\0House\0Boat\0Water" };
  DemoManager* manager = DemoManager::getInstance();
  SetFlags(&manager->entities_window);
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);

  ImGui::Begin("Entities Manager", &manager->entities_window.popen, manager->entities_window.window_flags);
  WindowMenu(&manager->entities_window);
  // ImGui::Text("There will be entities here");
  for (unsigned int i = 0; i < manager->entities_.size(); i++) {
    ImGui::PushID(i);
    if (ImGui::TreeNode(manager->entities_[i]->name_)) {
       if(ImGui::Checkbox("Enable", &manager->entities_[i]->enabled_)){
           manager->entities_[i]->drawable_->set_visible(manager->entities_[i]->enabled_);
       }
      ImGui::InputText(" ", manager->entities_[i]->temp_name_,15);
      ImGui::SameLine();

      

      if (ImGui::Button("Update name")) {
          snprintf(manager->entities_[i]->name_, 16, "%s\0", manager->entities_[i]->temp_name_);
      }
      
      if (ImGui::Combo("Mesh", &manager->entities_[i]->drawableAttached_,drawable_types, 10)) {
          manager->entities_[i]->attachDrawable((DrawableAttached)manager->entities_[i]->drawableAttached_, manager->root.get());
      }
      
      ImGui::DragFloat3("Position", &manager->entities_[i]->position_.x, 0.1f, -500.0f, 500.0f);
      ImGui::DragFloat3("Rotation", &manager->entities_[i]->rotation_.x, 0.1f, 0.0f, 360.0f);
      ImGui::DragFloat3("Scale", &manager->entities_[i]->scale_.x, 0.1f, 0.0f, 500.0f);
      
      

      if (manager->animation_configs_.size() >= 1) {
          if (ImGui::Combo("AnimationConfig", &manager->entities_[i]->animation_config_selected,
              manager->animation_configs_names_.get(), 4)) {
              if (manager->entities_[i]->animation_config_selected >= manager->animation_configs_.size()) {
                  manager->entities_[i]->animation_config_selected = manager->animation_configs_.size() - 1;
              }
        }

        if (ImGui::Button("Animate!")) {
          manager->entities_[i]->playAnimation(manager->animation_configs_[manager->entities_[i]->animation_config_selected]);
        }
        ImGui::SameLine();
        if (ImGui::Button("Stop")) {
          manager->entities_[i]->stopAnimation();
        }
        ImGui::SameLine();
        if (ImGui::Button("Play")) {
          manager->entities_[i]->set_play_animation(true);
        }
        ImGui::SameLine();
        if (ImGui::Button("Pause")) {
          manager->entities_[i]->set_play_animation(false);
        }

        ImGui::SameLine();

        if (nullptr != manager->entities_[i]->anim_instance_) {
          if (ImGui::Checkbox("revert", &manager->entities_[i]->anim_instance_->revert_)) {
            if (manager->entities_[i]->anim_instance_->config_.is_moving) {
              manager->entities_[i]->anim_instance_->set_animation_status(AnimationStatusOption_Position, false);
            }
            if (manager->entities_[i]->anim_instance_->config_.is_rotating) {
              manager->entities_[i]->anim_instance_->set_animation_status(AnimationStatusOption_Rotation, false);
            }
            if (manager->entities_[i]->anim_instance_->config_.is_scaling) {
              manager->entities_[i]->anim_instance_->set_animation_status(AnimationStatusOption_Scale, false);
            }
          }

          // Vec2 barSize(200, 20);

          // ImU32 color = IM_COL32(static_cast<unsigned char>(255 * &manager->entities_[i]->anim_instance_->get_progress(0).percent_), 0, 0, 255);
          // ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(0.0f, 0.0f), ImVec2(100.0f, 100.0f),
          //                                           color);

          // ImGui::SliderFloat("Variable", &manager->entities_[i]->anim_instance_->get_progress(0).percent_, 0.0f, 1.0f);
          if (manager->entities_[i]->anim_instance_->get_progress(0) > 0) {
            ImGui::Text("Movement Progress: ");
            ImGui::SameLine();
            // ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(41.0f, 74.0f, 122.0f, 1.0f));
            ImGui::ProgressBar(manager->entities_[i]->anim_instance_->get_progress(0), ImVec2(200.0f, 20.0f));
            // ImGui::PopStyleColor();
          }
          if (manager->entities_[i]->anim_instance_->get_progress(1) > 0) {
            ImGui::Text("Rotation Progress: ");
            ImGui::SameLine();
            ImGui::ProgressBar(manager->entities_[i]->anim_instance_->get_progress(1), ImVec2(200.0f, 20.0f));
          }
          if (manager->entities_[i]->anim_instance_->get_progress(2) > 0) {
            ImGui::Text("Scale Progress:    ");
            ImGui::SameLine();
            ImGui::ProgressBar(manager->entities_[i]->anim_instance_->get_progress(2), ImVec2(200.0f, 20.0f));
          }
          if (manager->entities_[i]->anim_instance_->config_.total_delay > 0.0f && manager->entities_[i]->anim_instance_->config_.current_delay < manager->entities_[i]->anim_instance_->config_.total_delay) {
            ImGui::Text("Delay Progress:    ");
            ImGui::SameLine();
            ImGui::ProgressBar(manager->entities_[i]->anim_instance_->config_.current_delay/manager->entities_[i]->anim_instance_->config_.total_delay, ImVec2(200.0f, 20.0f));
          }
        } 
        else {
          if (ImGui::Button("Inverse")) {
            manager->entities_[i]->playAnimation(manager->animation_configs_[manager->entities_[i]->animation_config_selected]);
            manager->entities_[i]->anim_instance_->revert_ = true;
            manager->entities_[i]->anim_instance_->set_elapsed_time(0, manager->entities_[i]->anim_instance_->get_duration(0));
            manager->entities_[i]->anim_instance_->set_elapsed_time(1, manager->entities_[i]->anim_instance_->get_duration(1));
            manager->entities_[i]->anim_instance_->set_elapsed_time(2, manager->entities_[i]->anim_instance_->get_duration(2));
          }
        }
      }

      if (nullptr == manager->entities_[i]->anim_instance_){
        if (ImGui::Button("Delete Entity")) {
            //Clear from vector and then delete
            for (unsigned int j = 0; j < manager->root->num_children(); j++) {
                EDK3::Node* node = manager->root->child(j);
                if (node == manager->entities_[i]->drawable_.get()) {
                    manager->root->removeChild(node);
                    break;
                }
            }
            delete manager->entities_[i];
            manager->entities_.erase(manager->entities_.begin() + i);
        }
      }
        
      ImGui::TreePop();
      }
      
      
    ImGui::PopID();
    }
  ImGui::End();
  }



void AnimationConfigsManagerWindow() {
  DemoManager *manager = DemoManager::getInstance();
  SetFlags(&manager->animationconfigs_window);
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);
  
  ImGui::Begin("Animations Config Manager", &manager->animationconfigs_window.popen, manager->animationconfigs_window.window_flags);
  WindowMenu(&manager->animationconfigs_window);

  for (unsigned int i = 0; i < manager->animation_configs_.size(); i++) {
    bool deletable=true;
    ImGui::PushID(i);
    if (ImGui::TreeNode(manager->animation_configs_[i].name)) {
      ImGui::Checkbox("Is Moving", &manager->animation_configs_[i].is_moving);
      if (manager->animation_configs_[i].is_moving) {
        ImGui::InputFloat3("Move from", &manager->animation_configs_[i].move_from.x);
        ImGui::InputFloat3("Move To", &manager->animation_configs_[i].move_to.x);
        ImGui::DragFloat("Move duration", &manager->animation_configs_[i].move_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
      }

      ImGui::Checkbox("Is Rotating", &manager->animation_configs_[i].is_rotating);
      if (manager->animation_configs_[i].is_rotating) {
        ImGui::InputFloat3("rotate from", &manager->animation_configs_[i].rotate_from.x);
        ImGui::InputFloat3("rotate to", &manager->animation_configs_[i].rotate_to.x);
        ImGui::DragFloat("rotate duration", &manager->animation_configs_[i].rotate_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
      }

      ImGui::Checkbox("Is Scaling", &manager->animation_configs_[i].is_scaling);
      if (manager->animation_configs_[i].is_scaling) {
        ImGui::InputFloat3("scale from", &manager->animation_configs_[i].scale_from.x);
        ImGui::InputFloat3("scale to", &manager->animation_configs_[i].scale_to.x);
        ImGui::DragFloat("scale duration", &manager->animation_configs_[i].scale_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
      }

      /*
      if (ImGui::BeginCombo("Interpolation", Interpolate::GetInterpolationTypeName(manager->animation_configs_[i].type_))) {
        for (int j = 0; j < (int)InterpolationType_None; j++) {
          InterpolationType type = static_cast<InterpolationType>(j);
          const bool is_selected = (manager->animation_configs_[i].type_ == type);

          if (ImGui::Selectable(Interpolate::GetInterpolationTypeName(type), is_selected)) {
            manager->animation_configs_[i].type_ = type;
          }

          if (is_selected)
            ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
      }

      */

      ImGui::DragFloat("Delay", &manager->animation_configs_[i].total_delay, 0.1f, 0.0f, 10.0f);

      ImGui::InputText(" ", manager->animation_configs_[i].temp_name,16);
      ImGui::SameLine();

      if (ImGui::Button("Update name")) {
          snprintf(manager->animation_configs_[i].name,16, "%s", manager->animation_configs_[i].temp_name);
      }

      for(unsigned int j=0;j<manager->entities_.size() && deletable;j++){
        deletable = strcmp(manager->animation_configs_[manager->entities_[j]->animation_config_selected].name, manager->animation_configs_[i].name);
      }

      if (ImGui::Button("Delete")) {
        if(deletable){
          
          //game->animation_configs_.erase(game->animation_configs_.begin() + i);
          //if(manager->db_.deleteAnimation(&manager->animation_configs_[i], &manager->animation_configs_db_[i])){
            manager->animation_configs_.erase(manager->animation_configs_.begin() + i);
            for(unsigned int j = 0; j < manager->entities_.size(); j++){
              if (manager->entities_[j]->animation_config_selected > i) {
                manager->entities_[j]->animation_config_selected--;
              }
            }
          //}
        }
        // manager->animation_configs_[i].name = manager->animation_configs_[i].temp_name;
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

/*

void NewAnimationConfigWindow() {
  manager *manager = manager::getInstance();
  bool unique = true;
  static AnimationConfig temp_anim_config;
  SetFlags(&manager->newanimationconfig_window);
  ImGui::SetNextWindowPos(ImVec2(200, 200), ImGuiCond_FirstUseEver);

  ImGui::Begin("New Animation Config", &manager->newanimationconfig_window.popen, manager->newanimationconfig_window.window_flags);
  WindowMenu(&manager->newanimationconfig_window);
  ImGui::Text("New animation config window");

  ImGui::Checkbox("Is Moving", &temp_anim_config.is_moving);
  if (temp_anim_config.is_moving) {
    ImGui::InputFloat2("Move from", &temp_anim_config.move_from.x);
    ImGui::InputFloat2("Move To", &temp_anim_config.move_to.x);
    ImGui::DragFloat("Move duration", &temp_anim_config.move_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
    ImGui::NewLine();
  }

  ImGui::Checkbox("Is Rotating", &temp_anim_config.is_rotating);
  if (temp_anim_config.is_rotating) {
    ImGui::InputFloat("rotate from", &temp_anim_config.rotate_from);
    ImGui::InputFloat("rotate to", &temp_anim_config.rotate_to);
    ImGui::DragFloat("rotate duration", &temp_anim_config.rotate_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
    ImGui::NewLine();
  }

  ImGui::Checkbox("Is Scaling", &temp_anim_config.is_scaling);
  if (temp_anim_config.is_scaling) {
    ImGui::InputFloat2("scale from", &temp_anim_config.scale_from.x);
    ImGui::InputFloat2("scale to", &temp_anim_config.scale_to.x);
    ImGui::DragFloat("scale duration", &temp_anim_config.scale_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
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

  for(int i = 0; i < manager->animation_configs_.size() && unique;i++){
        unique = strcmp(manager->animation_configs_[i].name.c_str(),  temp_anim_config.name.c_str());
  }

  if (ImGui::Button("Create new configuration")) {
    if (unique) {
      manager->db_.insertAnimation(temp_anim_config);
      manager->animation_configs_.clear();
      manager->animation_configs_db_.clear();

      if (manager->db_.runQuery("SELECT * from animations;", manager->db_.processAnimations, 0) != SQLITE_OK) {
        printf("%s\n", manager->db_.err_msg);
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
*/