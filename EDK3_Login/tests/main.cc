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

Vec3 EDK3::MaterialCustom::LightSettings::ambient_color_ = Vec3(0.0f, 0.0f, 0.0f);

//const int kWindowWidth = 1280;
//const int kWindowHeight = 768;
//const int kNTorusPoints = 10;
//const int kNTreePoints = 16;

void InitScene() {
    DemoManager* manager = DemoManager::getInstance();
    //Allocating root node:
    EDK3::Node* root = manager->root.get();

    //Calculate torus surface

    //Entity basic_entity = Entity();

    //Init Geometries

    //load geometry

    //InitTerrain();
    InitSceneGeometries();

    InitSceneMaterials();

    SetupDrawable(manager->terrain_custom.get(),
                  manager->mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(0.0f, -100.0f, 0.0f));


    SetupDrawable(manager->custom_tree.get(),
                  manager->mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(0.97f, -90.0f, -5.0f));

    SetupDrawable(manager->custom_sphere.get(),
                  manager->mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(-12.0f, -42.0f, 100.0f));

    SetupDrawable(manager->custom_cube.get(),
                  manager->mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(-95.0f, -40.0f, -88.0f));

    SetupDrawable(manager->custom_torus.get(),
                  manager->mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(26.0f, -30.0f, -28.0f));

    SetupDrawable(manager->custom_quad.get(),
                  manager->mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(80.0f, -15.0f, 0.0f));

    SetupDrawable(manager->house_geometry[4].get(),
                  manager->mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(18.0f, -85.0f, -9.0f),
                  Vec3(0.5f, 0.5f,0.5f));

    SetupDrawable(manager->boat_geometry[0].get(),
                  manager->mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(40.0f, -98.0f, 100.0f),
                  Vec3(3.0f, 3.0f, 3.0f));

    manager->entity_boat_.SetupDrawable(
        manager->boat_geometry[0].get(),
        manager->mat_selected.get(),
        manager->mat_light_settings.get(),
        Vec3(00.0f, 0.0f, 0.0f),
        Vec3(3.0f, 3.0f, 3.0f));

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
    manager->camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
    manager->camera->update(manager->dt, manager->camera->window_size().x,
        manager->camera->window_size().y);
    EDK3::Node* root = manager->root.get();

    EDK3::ref_ptr<EDK3::MaterialCustom> mat_selected;
    if (manager->show_normals) {
      mat_selected = manager->mat_normals;
    }
    else {
      mat_selected = manager->mat_basic;
    }
    for (int i = 0; i < root->num_children(); i++) {
      EDK3::Drawable* drawable = dynamic_cast<EDK3::Drawable*>(root->child(i));
      //root->child(i)->
      const float* drawable_position = drawable->position();
      Vec3 position = { drawable_position[0],drawable_position[1],drawable_position[2] };
      UpdateDrawable(drawable, mat_selected.get(), manager->mat_light_settings.get(),position );
    }


    EDK3::Node* drawable = root->child(6);
    drawable->set_rotation_y(180.0f);

    manager->entity_boat_.update();
}

void RenderFn() {
    DemoManager* manager = DemoManager::getInstance();
    //For every frame... determine what's visible:
    manager->camera->doCull(manager->root.get());

    if (manager->enable_postprocess) {
        manager->render_target->begin();
    }
    //Rendering the scene:
    EDK3::dev::GPUManager::CheckGLError("begin Render-->");
    manager->camera->doRender();
    EDK3::dev::GPUManager::CheckGLError("end Render-->");
    if (manager->enable_postprocess) {
        manager->render_target->end();
        manager->mat_postprocess->drawFullScreenQuad(manager->mat_postprocess_settings.get());
    }
}




int ESAT::main(int argc, char** argv) {
    DemoManager* manager = DemoManager::getInstance();
    ESAT::WindowInit(kWindowWidth, kWindowHeight);
    manager->init();
    InitScene();
    double last_time = ESAT::Time();
    while (!ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape) &&
        ESAT::WindowIsOpened()) {
        UpdateFn();
        RenderFn();
        manager->dt = ESAT::Time() - last_time;
        last_time = ESAT::Time();
        WindowsController();
        ImGui::Render();
        ESAT::WindowFrame();
    }
    return 0;
}




