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

Vec3 EDK3::MaterialCustom::LightSettings::ambient_color_ = Vec3(0.0f, 0.0f, 0.0f);

const int kWindowWidth = 1280;
const int kWindowHeight = 768;
const int kNTorusPoints = 10;
const int kNTreePoints = 16;

void InitScene() {
    DemoManager* manager = DemoManager::getInstance();
    EDK3::scoped_array<char> error_log;
    //Allocating root node:
    EDK3::Node* root = manager->root.get();

    Vec2 tree_points[kNTreePoints + 1];

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

    //Init Geometries

    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> geos;
    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> geos_boat;

    //load geometry
    EDK3::LoadObj(
        "./obj/house.obj",
        &geos,
        nullptr
    );
    
    //load geometry
    EDK3::LoadObj(
        "./obj/paper_boat.obj",
        &geos_boat,
        nullptr
    );

    //EDK3::ref_ptr<EDK3::Drawable> obj_drawable;
    //obj_drawable.alloc();

    //EDK3::ref_ptr<EDK3::Drawable> trex_drawable;
    //trex_drawable.alloc();

    
    EDK3::ref_ptr<EDK3::QuadCustom> custom_quad;
    custom_quad.alloc();
    custom_quad->init(20.0f);

    EDK3::ref_ptr<EDK3::SphereCustom> custom_sphere;
    custom_sphere.alloc();
    custom_sphere->init(8.0f);

    EDK3::ref_ptr<EDK3::CubeCustom> custom_cube;
    custom_cube.alloc();
    custom_cube->init24v(8.0f);

    EDK3::ref_ptr<EDK3::SurfaceCustom> surface_custom;
    surface_custom.alloc();

    EDK3::ref_ptr<EDK3::SurfaceCustom> surface_custom_torus;
    surface_custom_torus.alloc();
    surface_custom_torus->init(points, kNTorusPoints, 40, 2.0f,2.0f);
    surface_custom->init(tree_points, kNTreePoints, 40, 6.0f, 4.0f);

    InitTerrain();

  //Loading texture:
    EDK3::ref_ptr<EDK3::Texture> texture;
    EDK3::Texture::Load("./test/cuesta.png", &texture);
    if (!texture) {
        printf("Can't load texture.png\n");
        exit(-2);
    }

    //Initializing the material and its settings:
    manager->mat_basic->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    manager->mat_normals->init(error_log, "./shaders/basicVertex.vs", "./shaders/basicFragment.fs");

    manager->mat_light_settings.alloc();

    manager->render_target.alloc()->init((float)kWindowWidth,
                                         (float)kWindowHeight, 1);
    manager->mat_postprocess.alloc();
    manager->mat_postprocess_settings.alloc();

    manager->mat_postprocess->init();
    float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    manager->mat_postprocess->set_use_texture(true);
    //Aqui le asociamos la textura del render target y se la asociamos al material de postproceso
    manager->mat_postprocess_settings->set_texture(manager->render_target->color_texture(0));
    manager->mat_postprocess_settings->set_color(green);



    
    
    for (int i = 0; i < 3; i++) {
        manager->mat_light_settings->light_confs_[i].enabled_ = true;
    }

    manager->mat_light_settings->light_confs_[0].type_ = 0;
    manager->mat_light_settings->light_confs_[0].dir_ = Vec3(0.0f, 0.6f, 0.9f);
    manager->mat_light_settings->light_confs_[0].diff_color_ = Vec3(0.24f, 0.37f, 0.32f);

    manager->mat_light_settings->light_confs_[1].type_ = 1;
    manager->mat_light_settings->light_confs_[1].pos_ = Vec3(17.0f, -63.0f, -24.0f);
    manager->mat_light_settings->light_confs_[1].dir_ = Vec3(0.0f, 0.0f, 0.0f);
    manager->mat_light_settings->light_confs_[1].diff_color_ = Vec3(1.0f, 1.0f, 0.0f);
    manager->mat_light_settings->light_confs_[1].linear_att_ = 0.0027f;
    manager->mat_light_settings->light_confs_[1].quadratic_att_ = 0.0028f;
    manager->mat_light_settings->light_confs_[1].shininess_ = 45.0f;

    manager->mat_light_settings->light_confs_[2].type_ = 2;
    manager->mat_light_settings->light_confs_[2].pos_ = Vec3(33.0f, -55.0f, -23.0f);
    manager->mat_light_settings->light_confs_[2].spot_dir_ = Vec3(-0.57f, -1.0f, 0.53f);
    manager->mat_light_settings->light_confs_[2].diff_color_ = Vec3(1.0f, 0.0f, 0.0f);
    manager->mat_light_settings->light_confs_[2].linear_att_ = 0.014f;
    manager->mat_light_settings->light_confs_[2].quadratic_att_ = 0.0007f;
    manager->mat_light_settings->light_confs_[2].shininess_ = 90.0f;
    manager->mat_light_settings->light_confs_[2].cutoff_ = 0.960f;
    manager->mat_light_settings->light_confs_[2].cutoff_ = 0.946f;


    manager->mat_light_settings->set_texture(texture.get());

    EDK3::ref_ptr<EDK3::MaterialCustom> mat_selected;
    if (manager->show_normals) {
      mat_selected = manager->mat_normals;
    }else {
      mat_selected = manager->mat_basic;
    }

    SetupDrawable(manager->terrain_custom.get(),
                  mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(0.0f, -100.0f, 0.0f));


    SetupDrawable(surface_custom.get(),
                  mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(0.97f, -90.0f, -5.0f));

    SetupDrawable(custom_sphere.get(),
                  mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(-12.0f, -42.0f, 100.0f));

    SetupDrawable(custom_cube.get(),
                  mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(-95.0f, -40.0f, -88.0f));

    SetupDrawable(surface_custom_torus.get(),
                  mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(26.0f, -30.0f, -28.0f));

    SetupDrawable(custom_quad.get(),
                  mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(80.0f, -15.0f, 0.0f));

    SetupDrawable(geos[4].get(),
                  mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(18.0f, -85.0f, -9.0f),
                  Vec3(0.5f, 0.5f,0.5f));

    SetupDrawable(geos_boat[0].get(),
                  mat_selected.get(),
                  manager->mat_light_settings.get(),
                  Vec3(40.0f, -98.0f, 100.0f),
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




