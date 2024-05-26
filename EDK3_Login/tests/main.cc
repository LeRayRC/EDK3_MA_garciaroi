//
// PR03_00_Template.cc
// Ivan Sancho, Escuela Superior de Arte y Tecnologia
// Programacion Grafica
// ESAT 2022-2023
//

#include <stdio.h>
#include <math.h>
#include "ESAT/window.h"
#include "ESAT/input.h"
#include "ESAT/draw.h"
#include "ESAT/time.h"

#include "EDK3/geometry.h"
#include "EDK3/camera.h"
#include "EDK3/drawable.h"
#include "EDK3/matdiffusetexture.h"
#include "EDK3/rendertarget.h"
#include "EDK3/texture.h"
#include "EDK3/dev/gpumanager.h"

#include "ESAT_extra/imgui.h"
#include "EDK3/dev/opengl.h"

#include "material_custom.h"
#include "geometry_custom_terrain.h"
#include "geometry_custom_surface.h"
#include "geometry_custom_sphere.h"
#include "geometry_custom_cube.h"
#include "geometry_custom_quad.h"
#include "camera_custom.h"
#include "math_library/vector_3.h"
#include "math_library/vector_2.h"
#include "demo_manager.h"
#include "interface.h"
#include "scene.h"
#include "anim_library/entity.h"
#include "dev/custom_gpu_manager.h"

Vec3 EDK3::MaterialCustom::LightSettings::ambient_color_ = Vec3(0.0f, 0.0f, 0.0f);

//const int kWindowWidth = 1280;
//const int kWindowHeight = 768;
//const int kNTorusPoints = 10;
//const int kNTreePoints = 16;

void InitScene() {
    DemoManager* manager = DemoManager::getInstance();
    InitSceneTextures();
    InitSceneGeometries();
    InitSceneMaterials();
    InitSceneEntities();

    //Allocating and initializing the camera:
    manager->camera.alloc();

    float pos[] = { -1.0, 25.0f, -130.0f };
    manager->camera->set_position(pos);
    manager->camera->initViewTarget(kWindowWidth, kWindowHeight);
    manager->camera->setSensitibity(1.0f);
    manager->camera->setSpeed(0.25f);
    manager->camera->setSpeedModifier(0.01f);
    manager->camera->set_position(pos);
    manager->camera->accum_mouse_offset_ = { 1600.0f,586.0f };
    manager->camera->setDirectionWithAccum(manager->camera->window_size().x,
    manager->camera->window_size().y);
    manager->camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);

    EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void UpdateFn() {
    DemoManager* manager = DemoManager::getInstance();

    manager->time_ = (float)ESAT::Time() / 1000.0f;

    manager->camera->set_clear_color(manager->clear_rgba[0], manager->clear_rgba[1], manager->clear_rgba[2], manager->clear_rgba[3]);
    manager->camera->update(manager->dt, manager->camera->window_size().x,
        manager->camera->window_size().y);
    EDK3::Node* root = manager->root.get();

    //const float* camera_pos = manager->camera->position();
    //manager->skybox_entity_->set_position({ camera_pos[0], camera_pos[1], camera_pos[2] });
    //manager->skybox_entity_->drawable_->set_position(camera_pos);
    //manager->skybox_entity_->set_position({ 0.0f,0.0f,0.0f });
    //manager->skybox_entity_->drawable_->set_position(0.0f, 0.0f, 0.0f);
    //manager->skybox_entity_->drawable_->set_rotation_xyz(0.0f, 0.0f, 0.0f);
    //manager->skybox_entity_->update();
    //manager->skybox_entity_->drawable_->set_position(camera_pos);

    for (unsigned int i = 0; i < manager->entities_.size(); i++) {
        manager->entities_[i]->update();
    }

    //Update lights scoped array
    for (unsigned int i = 0; i < manager->light_materials_settings.size(); i++) {
        manager->light_materials_settings[i]->ambient_color_ =
            manager->mat_light_settings_general->ambient_color_;
        for (int j = 0; j < 8; j++) {
            manager->light_materials_settings[i]->light_confs_[j] =
                manager->mat_light_settings_general->light_confs_[j];
        }
        manager->light_materials_settings[i]->use_texture_ =
            manager->mat_light_settings_general->use_texture_;
    }

    manager->mat_light_water_settings->time_ = manager->time_;
}

void RenderFn() {
    DemoManager* manager = DemoManager::getInstance();
    
    manager->GPU.enableCullFaces(EDK3::dev::GPUManager::FaceType::kFace_Back);
    //manager->GPU.disableCullFaces();
    manager->GPU.enableDepthTest(EDK3::dev::GPUManager::CompareFunc::kCompareFunc_Less);

    //For every frame... determine what's visible:
    manager->camera->doCull(manager->root.get());

    //EDK3::dev::GPUManager::CheckGLError("begin Render-->");
    
    manager->camera->doRender();
    //EDK3::dev::GPUManager::CheckGLError("end Render-->");
    
}

void RenderSkybox() {
    DemoManager* manager = DemoManager::getInstance();

    manager->GPU.disableCullFaces();
    manager->GPU.enableDepthTest(EDK3::dev::GPUManager::CompareFunc::kCompareFunc_LessOrEqual);

    //For every frame... determine what's visible:
    manager->camera->doCull(manager->skybox_root.get());
    manager->camera->doRender();

}



int ESAT::main(int argc, char** argv) {
    //EDK3::dev::CustomGPUManager GPU;
    DemoManager* manager = DemoManager::getInstance();
    EDK3::dev::GPUManager::ReplaceGPUManagerImplementation(&manager->GPU);
    ESAT::WindowInit(kWindowWidth, kWindowHeight);
    manager->init();
    InitScene();
    double last_time = ESAT::Time();
    while (!ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape) &&
        ESAT::WindowIsOpened()) {
        //manager->GPU.enableCullFaces(EDK3::dev::GPUManager::FaceType::kFace_Back);
        UpdateFn();
        manager->GPU.enableBlend(manager->blend_src, manager->blend_dst, manager->blend_op, manager->blend_black);
        manager->GPU.clearFrameBuffer(manager->clear_rgba);
        if (manager->enable_wireframe) {
            manager->GPU.draw_mode_ = EDK3::dev::CustomGPUManager::DrawMode::kDrawMode_Lines;
        }
        else {
            manager->GPU.draw_mode_ = EDK3::dev::CustomGPUManager::DrawMode::kDrawMode_Triangles;
        }
        if (manager->enable_postprocess) {
            manager->render_target->begin();
            manager->GPU.clearFrameBuffer(manager->clear_rgba);
        }

        RenderSkybox();
        RenderFn();

        if (manager->enable_postprocess) {
            manager->render_target->end();
            manager->mat_postprocess->drawFullScreenQuad(manager->mat_postprocess_settings.get());
        }



        manager->dt = ESAT::Time() - last_time;
        last_time = ESAT::Time();
        manager->GPU.draw_mode_ = EDK3::dev::CustomGPUManager::DrawMode::kDrawMode_Triangles;
        WindowsController();
        ImGui::Render();
        ESAT::WindowFrame();
    }
    return 0;
}




