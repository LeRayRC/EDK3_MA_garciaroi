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
#include "EDK3/texture.h"
#include "EDK3/dev/gpumanager.h"

#include "ESAT_extra/imgui.h"
#include "EDK3/dev/opengl.h"

#include "material_custom.h"
#include "geometry_custom_terrain.h"
#include "geometry_custom_surface.h"
#include "camera_custom.h"
#include "math_library/vector_3.h"
#include "math_library/vector_2.h"
#include "demo_manager.h"
#include "interface.h"

Vec3 EDK3::MaterialCustom::LightSettings::ambient_color_ = Vec3(1.0f, 0.0f, 0.0f);

const int kWindowWidth = 1280;
const int kWindowHeight = 768;
const int kNTorusPoints = 10;
const int kNTreePoints = 16;

void InitScene() {
    DemoManager* manager = DemoManager::getInstance();
    EDK3::scoped_array<char> error_log;
    //Allocating root node:
    EDK3::Node* root = manager->root.alloc();

    Vec2 tree_points[kNTreePoints + 1];

    //tree_points[0] = Vec2(0.00f, 1.00f);
    //tree_points[1] = Vec2(0.30f, 1.00f);
    //tree_points[2] = Vec2(0.23f, 0.59f);
    //tree_points[3] = Vec2(0.45f, 0.56f);
    //tree_points[4] = Vec2(0.71f, 0.55f);
    //tree_points[5] = Vec2(0.80f, 0.47f);
    //tree_points[6] = Vec2(0.92f, 0.40f);
    //tree_points[7] = Vec2(1.00f, 0.33f);
    //tree_points[8] = Vec2(0.89f, 0.24f);
    //tree_points[9] = Vec2(0.77f, 0.21f);
    //tree_points[10] = Vec2(0.67f, 0.11f);
    //tree_points[11] = Vec2(0.50f, 0.09f);
    //tree_points[12] = Vec2(0.26f, 0.01f);
    //tree_points[13] = Vec2(0.09f, 0.00f);
    //
    //tree_points[0] = Vec2(0.00, 0.00);
    //tree_points[1] = Vec2(0.26, 0.00);
    //tree_points[2] = Vec2(0.19, 0.40);
    //tree_points[3] = Vec2(0.44, 0.43);
    //tree_points[4] = Vec2(0.74, 0.47);
    //tree_points[5] = Vec2(0.55, 0.57);
    //tree_points[6] = Vec2(0.39, 0.61);
    //tree_points[7] = Vec2(0.69, 0.61);
    //tree_points[8] = Vec2(0.90, 0.61);
    //tree_points[9] = Vec2(1.00, 0.68);
    //tree_points[10] = Vec2(0.95, 0.75);
    //tree_points[11] = Vec2(0.77, 0.78);
    //tree_points[12] = Vec2(0.85, 0.88);
    //tree_points[13] = Vec2(0.79, 0.94);
    //tree_points[14] = Vec2(0.58, 0.96);
    //tree_points[15] = Vec2(0.42, 0.90);
    //tree_points[16] = Vec2(0.23, 0.98);
    //tree_points[17] = Vec2(0.02, 1.00);


    tree_points[0] = Vec2(0.00f, 0.01f);
    tree_points[1] = Vec2(0.30f, 0.00f);
    tree_points[2] = Vec2(0.22f, 0.41f);
    tree_points[3] = Vec2(0.38f, 0.44f);
    tree_points[4] = Vec2(0.67f, 0.47f);
    tree_points[5] = Vec2(0.81f, 0.51f);
    tree_points[6] = Vec2(0.81f, 0.57f);
    tree_points[7] = Vec2(1.00f, 0.63f);
    tree_points[8] = Vec2(1.00f, 0.72f);
    tree_points[9] = Vec2(0.84f, 0.79f);
    tree_points[10] = Vec2(0.72f, 0.80f);
    tree_points[11] = Vec2(0.78f, 0.86f);
    tree_points[12] = Vec2(0.75f, 0.90f);
    tree_points[13] = Vec2(0.62f, 0.92f);
    tree_points[14] = Vec2(0.47f, 0.91f);
    tree_points[15] = Vec2(0.31f, 0.95f);
    tree_points[16] = Vec2(0.001f, 1.0f);

    //Calculate torus surface
    Vec2 points[kNTorusPoints + 1];
    float alpha = 6.28f / kNTorusPoints;
    float offset = 3.0f;
    for (int i = 0; i <= kNTorusPoints; i++) {
        if (i == kNTorusPoints) {
            points[i] = points[0];
        }
        else {
            points[i] = Vec2(cosf(alpha * i - 1.57f) + offset,
                sinf(alpha * i - 1.57f));
        }
    }

    EDK3::ref_ptr<EDK3::SurfaceCustom> surface_custom;
    surface_custom.alloc();
    //surface_custom->init(points, kNTorusPoints, 40, 2.0f,2.0f);
    surface_custom->init(tree_points, kNTreePoints, 40, 10.0f, 3.0f);
    //EDK3::ref_ptr<EDK3::TerrainCustom> custom_terrain;
    //EDK3::CreateCube(&cube_geo,1.0f, true, true);
    //custom_terrain.alloc();
    //custom_terrain->init(256, 256, // cols , rows
    //  2.0f, // height multiplier
    //  1.0f, // quad size
    //  0.05f, // smothness
    //  40.0f, // heightmap multiplier
    //  "./textures/island_heightmap.png",   // heightmap path
    //  true); // use heightmap


  //Loading texture:
    EDK3::ref_ptr<EDK3::Texture> texture;
    EDK3::Texture::Load("./test/cuesta.png", &texture);
    if (!texture) {
        printf("Can't load texture.png\n");
        exit(-2);
    }

    //Initializing the material and its settings:
    //mat_basic->init(error_log, "./shaders/basicVertex.vs", "./shaders/basicFragment.fs");
    manager->mat_basic->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    float color[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    manager->mat_basic_settings->set_color(color);

    manager->mat_light_settings.alloc();
    //for (int i = 0; i < 1; i++) {
    //    manager->mat_light_settings->light_confs_[i].enabled_ = true;
    //}
    manager->mat_light_settings->set_texture(texture.get());


    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(surface_custom.get());
    drawable->set_material(manager->mat_basic.get());
    drawable->set_material_settings(manager->mat_light_settings.get());
    //drawable->set_material_settings(mat_light_settings.get());
    drawable->set_position(0.0f, 0.0f, 0.0f);
    //drawable->set_HPR(360.0f * rand() / RAND_MAX, 360.0f * rand() / RAND_MAX, 360.0f * rand() / RAND_MAX);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    root->addChild(drawable.get());


    //Allocating and initializing the camera:
    manager->camera.alloc();
    float pos[] = { 0.0, 5.0f, 20.0f };
    //float pos[] = { 100.0, 20.0f, 10.0f };
    float view[] = { 0.0f, 0.0f, 0.0f };
    manager->camera->set_position(pos);
    manager->camera->initViewTarget(kWindowWidth, kWindowHeight);
    manager->camera->setSensitibity(1.0f);
    manager->camera->setSpeed(0.05f);
    manager->camera->setSpeedModifier(0.01f);
    manager->camera->set_position(pos);
    manager->camera->set_view_target(view);
    manager->camera->setupPerspective(70.0f, 8.0f / 6.0f, 1.0f, 1500.0f);


    EDK3::dev::GPUManager::CheckGLError("Prepare END");
}

void UpdateFn() {
    DemoManager* manager = DemoManager::getInstance();
    manager->camera->set_clear_color(0.94f, 1.0f, 0.94f, 1.0f);
    manager->camera->update(0.0, manager->camera->window_size().x,
        manager->camera->window_size().y);
    EDK3::Node* root = manager->root.get();
    EDK3::Node* drawable = root->child(0);
    drawable->set_rotation_y(ESAT::Time() * 0.05f);

}

void RenderFn() {
    DemoManager* manager = DemoManager::getInstance();
    //For every frame... determine what's visible:
    manager->camera->doCull(manager->root.get());

    //Rendering the scene:
    EDK3::dev::GPUManager::CheckGLError("begin Render-->");
    manager->camera->doRender();
    EDK3::dev::GPUManager::CheckGLError("end Render-->");
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




