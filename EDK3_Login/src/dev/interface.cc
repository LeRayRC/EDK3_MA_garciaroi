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

      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Demo")) {
        if (ImGui::Button("Load Demo")) {
            printf("Loading Demo\n");
        }
    ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Entities")) {
        if (ImGui::Button("New Empty Entity")) {
            Entity* new_entity = new Entity(true,"EmptyObj");
            new_entity->init();
            manager->entities_.push_back(new_entity);
        }
        if (ImGui::Button("New Terrain")) {
            //Entity* new_entity = new Entity(true, "TerrainObj");
            //manager->entities_.push_back(new_entity);
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
}

void LightsWindow() {
    static const char light_types[60] = { "Directional\0Point\0Spot\0" };
    DemoManager* manager = DemoManager::getInstance();
    manager->lights_window.flags.no_resize = false;
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
            }
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

    ImGui::Checkbox("Enable Postprocess", &manager->enable_postprocess);
    ImGui::Checkbox("Show normals", &manager->show_normals);
    if(ImGui::Checkbox("Wireframe mode", &manager->enable_wireframe)) {
        EDK3::Node* root = manager->root.get();
        for (int i = 0; i < root->num_children(); i++) {
            EDK3::Geometry* geometry = dynamic_cast<EDK3::Drawable*>(root->child(i))->geometry();
            if (geometry) {
                if (manager->enable_wireframe) {
                    geometry->setDrawMode(EDK3::dev::GPUManager::DrawMode::kDrawMode_Lines);
                }
                else {
                    geometry->setDrawMode(EDK3::dev::GPUManager::DrawMode::kDrawMode_Triangles);
                }
            }
        }
        
    }
    if (ImGui::Button("Activate boat animation")) {
        manager->entity_boat_->playAnimation(manager->anim_config_boat_);
    }
                
    ImGui::End();
}

void EntitiesManagerWindow() {
  static const char drawable_types[60] = { "Cube\0Quad\0Sphere\0Terrain\0Donut\0Tree\0House\0Boat" };
  DemoManager* manager = DemoManager::getInstance();
  SetFlags(&manager->entities_window);
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_FirstUseEver);

  ImGui::Begin("Entities Manager", &manager->entities_window.popen, manager->entities_window.window_flags);
  WindowMenu(&manager->entities_window);
  // ImGui::Text("There will be entities here");
  for (int i = 0; i < manager->entities_.size(); i++) {
    ImGui::PushID(i);
    if (ImGui::TreeNode(manager->entities_[i]->name_)) {
      ImGui::Checkbox("Enable", &manager->entities_[i]->enabled_);
      ImGui::InputText(" ", manager->entities_[i]->temp_name_,15);
      ImGui::SameLine();

      

      if (ImGui::Button("Update name")) {
          snprintf(manager->entities_[i]->name_, 16, "%s\0", manager->entities_[i]->temp_name_);
      }
      
      if (ImGui::Combo("Mesh", &manager->entities_[i]->drawableAttached_,drawable_types, 10)) {
          manager->entities_[i]->attachDrawable((DrawableAttached)manager->entities_[i]->drawableAttached_);
      }
      /*
      
      ImGui::DragFloat2("Position", &manager->entities_[i]->transform_.position_.x, 1.0f, 0.0f, 1280.0f);
      ImGui::DragFloat("Rotation", &manager->entities_[i]->transform_.rotation_, 0.1f, 0.0f, 6.28f);
      if(manager->entities_[i]->type_ == EntityType_Sprite){
        ImGui::DragFloat2("Scale", &manager->entities_[i]->transform_.scale_.x, 0.01f, 0.0f, 2.0f);
      }
      else{
        ImGui::DragFloat2("Scale", &manager->entities_[i]->transform_.scale_.x, 1.0f, 1.0f, 500.0f);
      }
      
      if (manager->entities_[i]->type_ == EntityType_Sprite) {
        Sprite *sprite = (Sprite *)manager->entities_[i];
        ImGui::DragFloat("Origin X", &manager->entities_[i]->transform_.origin_.x, 1.0f, -1.0f * sprite->width(), 0.0f);
        ImGui::DragFloat("Origin Y", &manager->entities_[i]->transform_.origin_.y, 1.0f, -1.0f * sprite->height(), 0.0f);
        if(ImGui::Button("Center")){
          sprite->transform_.set_origin({sprite->width()*(-0.5f),
                                        sprite->height()*(-0.5f)});
        }
      }else{
        ImGui::Checkbox("Solid",&((Path*)manager->entities_[i])->solid_);
        static ImVec4 fill_color = ImVec4((float)(((Path *)(manager->entities_[i]))->fill_color_.red_/255.0f),
                                    (float)(((Path *)(manager->entities_[i]))->fill_color_.green_/255.0f),
                                    (float)(((Path *)(manager->entities_[i]))->fill_color_.blue_/255.0f),
                                    1.0f);
        if(fill_color.w > 255.0f) fill_color.w = 255.0f;
        ImGui::ColorEdit4("Fill Color", &fill_color.x);
        ((Path *)(manager->entities_[i]))->set_fill_color((unsigned char)(fill_color.x*255),
                                                        (unsigned char)(fill_color.y*255),
                                                        (unsigned char)(fill_color.z*255),
                                                        (unsigned char)(fill_color.w*255));

        static ImVec4 border_color = {(float)(((Path *)(manager->entities_[i]))->border_color_.red_/255.0f),
                                      (float)(((Path *)(manager->entities_[i]))->border_color_.green_/255.0f),
                                      (float)(((Path *)(manager->entities_[i]))->border_color_.blue_/255.0f),
                                      (float)(((Path *)(manager->entities_[i]))->border_color_.alpha_/255.0f)};
        if(border_color.w > 255.0f) border_color.w = 255.0f;
        ImGui::ColorEdit4("Border Color", &border_color.x);
        ((Path *)(manager->entities_[i]))->set_border_color((unsigned char)(border_color.x*255),
                                                        (unsigned char)(border_color.y*255),
                                                        (unsigned char)(border_color.z*255),
                                                        (unsigned char)(border_color.w*255));
      }

      if (manager->animation_configs_.size() >= 1) {
        if (ImGui::BeginCombo("Animation Config", &manager->animation_configs_[manager->entities_[i]->animation_config_selected].name[0])) {
          for (int j = 0; j < manager->animation_configs_.size(); j++) {
            const bool is_selected = (manager->entities_[i]->animation_config_selected == j);
            if (manager->animation_configs_[j].name.length() == 0) {
              if (ImGui::Selectable(" ", is_selected))
                manager->entities_[i]->animation_config_selected = j;
            } else {
              if (ImGui::Selectable(&manager->animation_configs_[j].name[0], is_selected))
                manager->entities_[i]->animation_config_selected = j;
            }

            // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
            if (is_selected)
              ImGui::SetItemDefaultFocus();
          }
          ImGui::EndCombo();
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
          if(ImGui::Button("Delete Entity")){
          //Clear from vector and then delete
            delete manager->entities_[i];
            manager->entities_.erase(manager->entities_.begin()+i);
          }
        }
        
      }
      
      */
      ImGui::TreePop();
    }
    ImGui::PopID();
  }
  ImGui::End();
}
/*

void AnimationConfigsManagerWindow() {
  manager *manager = manager::getInstance();
  SetFlags(&manager->animationconfigs_window);
  ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
  
  ImGui::Begin("Animations Config Manager", &manager->animationconfigs_window.popen, manager->animationconfigs_window.window_flags);
  WindowMenu(&manager->animationconfigs_window);

  for (int i = 0; i < manager->animation_configs_.size(); i++) {
    bool deletable=true;
    ImGui::PushID(i);
    if (ImGui::TreeNode(&manager->animation_configs_[i].name[0])) {
      ImGui::Checkbox("Is Moving", &manager->animation_configs_[i].is_moving);
      if (manager->animation_configs_[i].is_moving) {
        ImGui::InputFloat2("Move from", &manager->animation_configs_[i].move_from.x);
        ImGui::InputFloat2("Move To", &manager->animation_configs_[i].move_to.x);
        ImGui::DragFloat("Move duration", &manager->animation_configs_[i].move_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
        ImGui::NewLine();
      }

      ImGui::Checkbox("Is Rotating", &manager->animation_configs_[i].is_rotating);
      if (manager->animation_configs_[i].is_rotating) {
        ImGui::InputFloat("rotate from", &manager->animation_configs_[i].rotate_from);
        ImGui::InputFloat("rotate to", &manager->animation_configs_[i].rotate_to);
        ImGui::DragFloat("rotate duration", &manager->animation_configs_[i].rotate_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
        ImGui::NewLine();
      }

      ImGui::Checkbox("Is Scaling", &manager->animation_configs_[i].is_scaling);
      if (manager->animation_configs_[i].is_scaling) {
        ImGui::InputFloat2("scale from", &manager->animation_configs_[i].scale_from.x);
        ImGui::InputFloat2("scale to", &manager->animation_configs_[i].scale_to.x);
        ImGui::DragFloat("scale duration", &manager->animation_configs_[i].scale_duration, 0.1f, 0.0f, manager->kMaxAnimationDuration);
      }

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

      ImGui::DragFloat("Delay", &manager->animation_configs_[i].total_delay, 0.1f, 0.0f, 10.0f);

      ImGui::InputText(" ", &manager->animation_configs_[i].temp_name);
      ImGui::SameLine();

      if (ImGui::Button("Update name")) {
        manager->animation_configs_[i].name = manager->animation_configs_[i].temp_name;
      }
      if (ImGui::Button("Save")) {
        // manager->animation_configs_[i].name = manager->animation_configs_[i].temp_name;
        manager->db_.saveAnimation(manager->animation_configs_[i], manager->animation_configs_db_[i]);
        manager::getInstance()->animation_configs_.clear();
        manager::getInstance()->animation_configs_db_.clear();
        manager->db_.runQuery("SELECT * from animations;", manager->db_.processAnimations, 0);
      }
      
      for(int j=0;j<manager->entities_.size() && deletable;j++){
        deletable = strcmp(manager->animation_configs_[manager->entities_[j]->animation_config_selected].name.c_str(), manager->animation_configs_[i].name.c_str());
      }

      if (ImGui::Button("Delete")) {
        if(deletable){
          
          if(manager->db_.deleteAnimation(&manager->animation_configs_[i], &manager->animation_configs_db_[i])){
            for(int j = 0; j < manager->entities_.size(); j++){
              if (manager->entities_[j]->animation_config_selected > i) {
                manager->entities_[j]->animation_config_selected--;
              }
            }
          }
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

void NewPathWindow() {
  manager *manager = manager::getInstance();
  static bool is_regular = true;
  static int n_vertexes = manager->kMinPathVertexes;
  static Vec2 vertexes[manager->kMaxPathVertexes];
  static Vec2 position;
  static float rotation;
  static Vec2 scale;
  static char n_vertexes_char[20];
  SetFlags(&manager->newpath_window);
  ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_FirstUseEver);
  ImGui::Begin("New Path", &manager->newpath_window.popen, manager->newpath_window.window_flags);
  WindowMenu(&manager->newpath_window);
  ImGui::Text("New path");

  ImGui::Checkbox("Is regular", &is_regular);
  ImGui::DragInt("Num vertexes", &n_vertexes, 1.0f, manager->kMinPathVertexes, manager->kMaxPathVertexes);
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
    manager->entities_.push_back(path);
  }
  ImGui::End();
}

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

void NewTextureWindow() {
  manager *manager = manager::getInstance();
  static std::string path_to_sprite;
  static bool failed_to_import = false;
  static bool valid_path = false;
  SetFlags(&manager->newtexture_window);
  ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_FirstUseEver);
  ImGui::Begin("New Texture", &manager->newtexture_window.popen, manager->newtexture_window.window_flags);
  WindowMenu(&manager->newtexture_window);

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
          manager->textures_.push_back(texture);
          failed_to_import = false;
          manager->newtexture_window.popen = false;
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
  manager *manager = manager::getInstance();
  static int texture_selected = 0;
  static Vec2 position;
  static Vec2 size;
  static Vec2 window_size;

  SetFlags(&manager->newsprite_window);
  ImGui::SetNextWindowPos(ImVec2(640, 360), ImGuiCond_FirstUseEver);
  ImGui::Begin("New Sprite", &manager->newsprite_window.popen, manager->newsprite_window.window_flags);
  WindowMenu(&manager->newsprite_window);

  if (manager->textures_.size() > 0) {

    // const char* last_separator = strrchr(manager->textures_[texture_selected]->path_.c_str(),'\\');
    // if( last_separator != nullptr){
    // if (ImGui::BeginCombo("Select Texture", last_separator+1)){
    if (ImGui::BeginCombo("Select Texture", manager->textures_[texture_selected]->path_.c_str())) {
      for (int j = 0; j < manager->textures_.size(); j++) {
        const bool is_selected = (texture_selected == j);
        if (ImGui::Selectable(&manager->textures_[j]->path_[0], is_selected))
          texture_selected = j;
        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
        if (is_selected)
          ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }

    ImGui::DragFloat("Pos X:", &position.x, 1.0f, -1.0f * manager->textures_[texture_selected]->width(), 0.0f);
    ImGui::DragFloat("Pos Y:", &position.y, 1.0f, -1.0f * manager->textures_[texture_selected]->height(), 0.0f);

    if (size.x > (manager->textures_[texture_selected]->width() + position.x)) {
      size.x = manager->textures_[texture_selected]->width() + position.x;
    }
    if (size.y > (manager->textures_[texture_selected]->height() + position.y)) {
      size.y = manager->textures_[texture_selected]->height() + position.y;
    }
    ImGui::DragFloat("Size X", &size.x, 1.0f, 0.0f, (float)(manager->textures_[texture_selected]->width() + position.x));
    ImGui::DragFloat("Size Y", &size.y, 1.0f, 0.0f, (float)(manager->textures_[texture_selected]->height() + position.y));

    ImGui::BeginChild("TextureToLoad", ImVec2(size.x, size.y), true, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
    ImGui::SetCursorPos(ImVec2(position.x, position.y));
    ImageFromTexture(manager->textures_[texture_selected]->handle_);
    // }else{
    //   ImGui::Text("Error getting textures");
    // }

    ImGui::EndChild();

    if (ImGui::Button("Create")) {
      Sprite *sprite = new Sprite(*manager->textures_[texture_selected], (int)(position.x * -1.0f),
                                  (int)(position.y * -1.0f),
                                  (int)size.x,
                                  (int)size.y);
      if (nullptr != sprite) {
        manager->entities_.push_back(sprite);
      }
    }

  } else {
    ImGui::Text("There are no textures imported");
  }

  ImGui::End();
}

*/