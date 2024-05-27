#include "scene.h"

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

void InitDemoGeometries(){

}


//void InitTerrain(){
//    DemoManager* manager = DemoManager::getInstance();
//
//    EDK3::ref_ptr<EDK3::TerrainCustom> terrain_custom;
//    terrain_custom.alloc();
//    terrain_custom->init(256, 256, // cols , rows
//      2.0f, // height multiplier
//      1.0f, // quad size
//      0.05f, // smothness
//      40.0f, // heightmap multiplier
//      //"./textures/australia.png",   // heightmap path
//      "./textures/island_heightmap.png",   // heightmap path
//      true); // use heightmap
//
//    manager->terrain_custom = terrain_custom;
//}

void SetupDrawable(EDK3::Geometry *geo, 
                   EDK3::MaterialCustom *mat, 
                   EDK3::MaterialSettings *mat_settings,
                   Vec3 pos, Vec3 scale, Vec3 rot) {
    DemoManager* manager = DemoManager::getInstance();
    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(geo); 
    drawable->set_material(mat);
    drawable->set_material_settings(mat_settings);
    drawable->set_rotation_xyz(rot.x, rot.y, rot.z);
    drawable->set_position(pos.x, pos.y, pos.z);
    drawable->set_scale(scale.x, scale.y, scale.z);
    manager->root->addChild(drawable.get());
}

void UpdateDrawable(EDK3::Drawable* drawable,
  EDK3::MaterialCustom* mat,
  EDK3::MaterialSettings* mat_settings,
  Vec3& pos) {
  DemoManager* manager = DemoManager::getInstance();
  drawable->set_material(mat);
  drawable->set_material_settings(mat_settings);
  drawable->set_position(pos.x, pos.y, pos.z);
}

void InitIslandPoints(Vec2 *island_points) {
    int index = 0;
    //island_points[0] = Vec2(0.01f, 0.00f);
    //island_points[1] = Vec2(0.03f, 0.01f);
    //island_points[2] = Vec2(0.07f, 0.00f);
    //island_points[3] = Vec2(0.10f, 0.01f);
    //island_points[4] = Vec2(0.12f, 0.04f);
    //island_points[5] = Vec2(0.13f, 0.07f);
    //island_points[6] = Vec2(0.16f, 0.11f);
    //island_points[7] = Vec2(0.17f, 0.15f);
    //island_points[8] = Vec2(0.16f, 0.19f);
    //island_points[9] = Vec2(0.18f, 0.23f);
    //island_points[10] = Vec2(0.20f, 0.26f);
    //island_points[11] = Vec2(0.21f, 0.29f);
    //island_points[12] = Vec2(0.22f, 0.33f);
    //island_points[13] = Vec2(0.22f, 0.36f);
    //island_points[14] = Vec2(0.25f, 0.40f);
    //island_points[15] = Vec2(0.25f, 0.43f);
    //island_points[16] = Vec2(0.27f, 0.46f);
    //island_points[17] = Vec2(0.27f, 0.50f);
    //island_points[18] = Vec2(0.27f, 0.52f);
    //island_points[19] = Vec2(0.29f, 0.54f);
    //island_points[20] = Vec2(0.30f, 0.57f);
    //island_points[21] = Vec2(0.35f, 0.58f);
    //island_points[22] = Vec2(0.39f, 0.59f);
    //island_points[23] = Vec2(0.43f, 0.59f);
    //island_points[24] = Vec2(0.45f, 0.60f);
    //island_points[25] = Vec2(0.47f, 0.62f);
    //island_points[26] = Vec2(0.49f, 0.64f);
    //island_points[27] = Vec2(0.49f, 0.66f);
    //island_points[28] = Vec2(0.51f, 0.68f);
    //island_points[29] = Vec2(0.56f, 0.71f);
    //island_points[30] = Vec2(0.60f, 0.72f);
    //island_points[31] = Vec2(0.64f, 0.73f);
    //island_points[32] = Vec2(0.69f, 0.75f);
    //island_points[33] = Vec2(0.72f, 0.76f);
    //island_points[34] = Vec2(0.79f, 0.78f);
    //island_points[35] = Vec2(0.84f, 0.78f);
    //island_points[36] = Vec2(0.87f, 0.80f);
    //island_points[37] = Vec2(0.89f, 0.82f);
    //island_points[38] = Vec2(0.89f, 0.85f);
    //island_points[39] = Vec2(0.91f, 0.88f);
    //island_points[40] = Vec2(0.94f, 0.90f);
    //island_points[41] = Vec2(0.96f, 0.93f);
    //island_points[42] = Vec2(1.00f, 0.95f);
    //island_points[43] = Vec2(0.97f, 0.98f);
    //island_points[44] = Vec2(0.92f, 0.99f);
    //island_points[45] = Vec2(0.89f, 0.98f);
    //island_points[46] = Vec2(0.82f, 0.99f);
    //island_points[47] = Vec2(0.76f, 0.99f);
    //island_points[48] = Vec2(0.71f, 0.99f);
    //island_points[49] = Vec2(0.68f, 0.99f);
    //island_points[50] = Vec2(0.62f, 0.99f);
    //island_points[51] = Vec2(0.56f, 0.99f);
    //island_points[52] = Vec2(0.55f, 0.98f);
    //island_points[53] = Vec2(0.50f, 0.99f);
    //island_points[54] = Vec2(0.45f, 1.00f);
    //island_points[55] = Vec2(0.42f, 0.99f);
    //island_points[56] = Vec2(0.37f, 0.99f);
    //island_points[57] = Vec2(0.32f, 0.99f);
    //island_points[58] = Vec2(0.29f, 1.00f);
    //island_points[59] = Vec2(0.23f, 0.99f);
    //island_points[60] = Vec2(0.18f, 0.99f);
    //island_points[61] = Vec2(0.13f, 0.99f);
    //island_points[62] = Vec2(0.08f, 0.98f);
    //island_points[63] = Vec2(0.03f, 0.98f);
    //island_points[64] = Vec2(0.00f, 0.98f);
    //island_points[65] = Vec2(0.00f, 1.00f);


    island_points[index++] = Vec2(0.00f, 0.00f) ;
    island_points[index++] = Vec2(0.09f, 0.00f);
    island_points[index++] = Vec2(0.11f, 0.09f);
    island_points[index++] = Vec2(0.18f, 0.06f);
    island_points[index++] = Vec2(0.28f, 0.05f);
    island_points[index++] = Vec2(0.36f, 0.09f);
    island_points[index++] = Vec2(0.41f, 0.20f);
    island_points[index++] = Vec2(0.45f, 0.14f);
    island_points[index++] = Vec2(0.55f, 0.16f);
    island_points[index++] = Vec2(0.55f, 0.25f);
    island_points[index++] = Vec2(0.64f, 0.23f);
    island_points[index++] = Vec2(0.73f, 0.28f);
    island_points[index++] = Vec2(0.78f, 0.35f);
    island_points[index++] = Vec2(0.82f, 0.43f);
    island_points[index++] = Vec2(0.86f, 0.50f);
    island_points[index++] = Vec2(0.91f, 0.57f);
    island_points[index++] = Vec2(0.94f, 0.66f);
    island_points[index++] = Vec2(1.00f, 0.76f);
    island_points[index++] = Vec2(0.99f, 0.82f);
    island_points[index++] = Vec2(0.92f, 0.85f);
    island_points[index++] = Vec2(0.82f, 0.89f);
    island_points[index++] = Vec2(0.73f, 0.94f);
    island_points[index++] = Vec2(0.63f, 0.95f);
    island_points[index++] = Vec2(0.56f, 0.96f);
    island_points[index++] = Vec2(0.49f, 0.96f);
    island_points[index++] = Vec2(0.45f, 0.94f);
    island_points[index++] = Vec2(0.39f, 0.89f);
    island_points[index++] = Vec2(0.34f, 0.88f);
    island_points[index++] = Vec2(0.26f, 0.90f);
    island_points[index++] = Vec2(0.20f, 0.97f);
    island_points[index++] = Vec2(0.10f, 1.00f);
    island_points[index++] = Vec2(0.03f, 0.95f);
    island_points[index++] = Vec2(0.00f, 0.87f);
    island_points[index++] = Vec2(0.00f, 1.00f);
}                                       

void InitSceneGeometries() {
    DemoManager* manager = DemoManager::getInstance();

    

    //Init Tree points
    manager->tree_points[0] = Vec2(0.00f, 0.01f);
    manager->tree_points[1] = Vec2(0.30f, 0.00f);
    manager->tree_points[2] = Vec2(0.22f, 0.41f);
    manager->tree_points[3] = Vec2(0.38f, 0.44f);
    manager->tree_points[4] = Vec2(0.67f, 0.47f);
    manager->tree_points[5] = Vec2(0.81f, 0.51f);
    manager->tree_points[6] = Vec2(0.81f, 0.57f);
    manager->tree_points[7] = Vec2(1.00f, 0.63f);
    manager->tree_points[8] = Vec2(1.00f, 0.72f);
    manager->tree_points[9] = Vec2(0.84f, 0.79f);
    manager->tree_points[10] = Vec2(0.72f, 0.80f);
    manager->tree_points[11] = Vec2(0.78f, 0.86f);
    manager->tree_points[12] = Vec2(0.75f, 0.90f);
    manager->tree_points[13] = Vec2(0.62f, 0.92f);
    manager->tree_points[14] = Vec2(0.47f, 0.91f);
    manager->tree_points[15] = Vec2(0.31f, 0.95f);
    manager->tree_points[16] = Vec2(0.001f, 1.0f);

    InitIslandPoints(manager->island_points);
    

    //Init Torus points
    float alpha = 6.28f / kNTorusPoints;
    float offset = 3.0f;
    for (int i = 0; i <= kNTorusPoints; i++) {
        if (i == kNTorusPoints) {
            manager->points[i] = manager->points[0];
        }
        else {
            manager->points[i] = Vec2(cosf(alpha * i - 1.57f) + offset,
                sinf(alpha * i - 1.57f));
        }
    }

    EDK3::LoadObj(
        "./obj/house.obj",
        &manager->house_geometry,
        nullptr
    );

    //load geometry
    EDK3::LoadObj(
        "./obj/paper_boat.obj",
        &manager->boat_geometry,
        nullptr
    );

    EDK3::LoadObj(
        "./obj/dolphin.obj",
        &manager->dolphin_geometry,
        nullptr
    );


    manager->custom_quad.alloc();
    manager->custom_quad->init(20.0f);

    manager->custom_sphere.alloc();
    manager->custom_sphere->init(8.0f);

    manager->custom_cube.alloc();
    manager->custom_cube->init24v(8.0f);

    manager->custom_cube_8v.alloc();
    manager->custom_cube_8v->init8v(8.0f);

    manager->custom_tree.alloc();
    manager->custom_torus.alloc();
    manager->custom_island_small.alloc();
    manager->custom_island_medium.alloc();
    manager->custom_island_big.alloc();

    manager->custom_torus->init(manager->points, kNTorusPoints, 40, 2.0f, 2.0f);
    manager->custom_tree->init(manager->tree_points, kNTreePoints, 40, 6.0f, 4.0f);

    manager->custom_island_small->init(manager->island_points, kNIslandPoints, 40, 8.0f, 0.5f, true, 0.01f, {5.0f,5.0f});
    manager->custom_island_medium->init(manager->island_points, kNIslandPoints, 40, 20.0f, 0.8f, true, 0.03f, {8.0f,8.0f});
    manager->custom_island_big->init(manager->island_points, kNIslandPoints, 40, 30.0f, 1.2f, true, 0.02f, {10.f,10.0f});

    manager->terrain_custom.alloc();
    manager->terrain_custom->init(256, 256, // cols , rows
        2.0f, // height multiplier
        1.0f, // quad size
        0.05f, // smothness
        { 40.0f,1.0f,1.0f}, // heightmap multiplier
        //"./textures/australia.png",   // heightmap path
        "./textures/island_heightmap.png",   // heightmap path
        true, true, {16.0f,16.0f}); // use heightmap

    manager->water_terrain.alloc();
    manager->water_terrain->init(64, 64, // cols , rows
      20.0f, // height multiplier
      24.0f, // quad size
      0.25f, // smothness
        { 40.0f, 1.0f,1.0f }, // heightmap multiplier
      //"./textures/australia.png",   // heightmap path
      "./textures/island_heightmap.png",   // heightmap path
        false, true, { 64.0f, 64.0f }); // use heightmap

    manager->terrain_cliff.alloc();
    manager->terrain_cliff->init(128, 128, // cols , rows
        2.0f, // height multiplier
        12.0f, // quad size
        0.05f, // smothness
        {10.0f,2.0f,5.0f}, // heightmap multiplier
        //"./textures/australia.png",   // heightmap path
        "./textures/101_dday.jpg",   // heightmap path
        true, true, { 64.0f, 64.0f }); // use heightmap
}

void InitSceneMaterials() {
    EDK3::scoped_array<char> error_log;
    DemoManager* manager = DemoManager::getInstance();

    //Initializing the material and its settings:
    manager->mat_basic->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    manager->mat_normals->init(error_log, "./shaders/basicVertex.vs", "./shaders/normalFragment.fs");
    manager->mat_wireframe->init(error_log, "./shaders/basicVertex.vs", "./shaders/wireframeFragment.fs");
    manager->mat_panoramic->init(error_log, "./shaders/panoramicVertex.vs", "./shaders/panoramicFragment.fs");
    manager->mat_water->init(error_log, "./shaders/waterVertex.vs", "./shaders/water_light_shader.fs");
    manager->mat_heightlayer->init(error_log, "./shaders/heightLayerVertex.vs", "./shaders/heightLayerFragment.fs",4);


    manager->mat_postprocess->init("./shaders/postprocessVertex.vs", "./shaders/postprocessFragment.fs");
    float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    manager->mat_postprocess->set_use_texture(true);
    //Aqui le asociamos la textura del render target y se la asociamos al material de postproceso
    manager->mat_postprocess_settings->set_texture(manager->render_target->color_texture(0));
    manager->mat_postprocess_settings->set_color(green);


    manager->mat_light_settings_general->use_texture_ = true;
    manager->mat_light_settings_general->show_normal_ = false;
    for (int i = 0; i < 3; i++) {
        manager->mat_light_settings_general->light_confs_[i].enabled_ = true;
    }

    manager->mat_light_settings_general->light_confs_[0].type_ = 0;
    manager->mat_light_settings_general->light_confs_[0].dir_ = Vec3(0.0f, 1.0f, 0.0f);
    manager->mat_light_settings_general->light_confs_[0].diff_color_ = Vec3(0.5f, 0.8f, 0.8f);

    manager->mat_light_settings_general->light_confs_[1].type_ = 1;
    manager->mat_light_settings_general->light_confs_[1].pos_ = Vec3(17.0f, -63.0f, -24.0f);
    manager->mat_light_settings_general->light_confs_[1].dir_ = Vec3(0.0f, 0.0f, 0.0f);
    manager->mat_light_settings_general->light_confs_[1].diff_color_ = Vec3(1.0f, 1.0f, 0.0f);
    manager->mat_light_settings_general->light_confs_[1].linear_att_ = 0.0027f;
    manager->mat_light_settings_general->light_confs_[1].quadratic_att_ = 0.0028f;
    manager->mat_light_settings_general->light_confs_[1].shininess_ = 45.0f;

    manager->mat_light_settings_general->light_confs_[2].type_ = 2;
    manager->mat_light_settings_general->light_confs_[2].pos_ = Vec3(33.0f, -55.0f, -23.0f);
    manager->mat_light_settings_general->light_confs_[2].spot_dir_ = Vec3(-0.57f, -1.0f, 0.53f);
    manager->mat_light_settings_general->light_confs_[2].diff_color_ = Vec3(1.0f, 0.0f, 0.0f);
    manager->mat_light_settings_general->light_confs_[2].linear_att_ = 0.014f;
    manager->mat_light_settings_general->light_confs_[2].quadratic_att_ = 0.0007f;
    manager->mat_light_settings_general->light_confs_[2].shininess_ = 90.0f;
    manager->mat_light_settings_general->light_confs_[2].cutoff_ = 0.960f;
    manager->mat_light_settings_general->light_confs_[2].cutoff_ = 0.946f;

    manager->mat_light_settings->set_texture(manager->texture_sand.get());
    manager->mat_heightlayer_settings->set_texture(manager->texture_sand.get());
    manager->mat_heightlayer_settings->set_texture(manager->texture_rocks.get(),1);
    manager->mat_heightlayer_settings->set_texture(manager->texture_grass.get(),2);
    manager->mat_light_water_settings->set_texture(manager->texture_water.get());
    manager->mat_panoramic_settings->set_texture(manager->texture_skybox.get());
    manager->mat_house_settings->set_texture(manager->texture_house.get());
    manager->mat_dolphin_settings->set_texture(manager->texture_dolphin.get());
    
    if (manager->show_normals) {
        manager->mat_selected = manager->mat_normals;
    }
    else {
        manager->mat_selected = manager->mat_basic;
    }
}

void InitSceneAnimationConfigs() {
    DemoManager* manager = DemoManager::getInstance();

    snprintf(manager->dolphin_animation_config_.name, 16, "DolphinAnim");

    //Animation 1
    manager->dolphin_animation_config_.is_moving = true;
    manager->dolphin_animation_config_.move_from = Vec3(-500.0f, -112.0f, -500.0f);
    manager->dolphin_animation_config_.move_to = Vec3(-500.0f, -112.0f, 500.0f);
    manager->dolphin_animation_config_.move_duration = 12.0f;

    manager->dolphin_animation_config_.is_rotating = true;
    manager->dolphin_animation_config_.rotate_from = Vec3(-60.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_to = Vec3(3000.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_duration = 12.0f;

    manager->dolphin_animation_config_.total_delay = 0.2f * (float)(rand()%20);

    manager->animation_configs_.push_back(manager->dolphin_animation_config_);

    //Animation 2
    manager->dolphin_animation_config_.is_moving = true;
    manager->dolphin_animation_config_.move_from = Vec3(-450.0f, -112.0f, -500.0f);
    manager->dolphin_animation_config_.move_to = Vec3(-450.0f, -112.0f, 500.0f);
    manager->dolphin_animation_config_.move_duration = 12.0f;

    manager->dolphin_animation_config_.is_rotating = true;
    manager->dolphin_animation_config_.rotate_from = Vec3(-60.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_to = Vec3(3000.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_duration = 12.0f;

    manager->dolphin_animation_config_.total_delay = 0.2f* (float)(rand() % 20);

    manager->animation_configs_.push_back(manager->dolphin_animation_config_);

    //Animation 3
    manager->dolphin_animation_config_.is_moving = true;
    manager->dolphin_animation_config_.move_from = Vec3(-400.0f, -112.0f, -500.0f);
    manager->dolphin_animation_config_.move_to = Vec3(-400.0f, -112.0f, 500.0f);
    manager->dolphin_animation_config_.move_duration = 12.0f;

    manager->dolphin_animation_config_.is_rotating = true;
    manager->dolphin_animation_config_.rotate_from = Vec3(-60.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_to = Vec3(3000.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_duration = 12.0f;

    manager->dolphin_animation_config_.total_delay = 0.2f * (float)(rand() % 20);

    manager->animation_configs_.push_back(manager->dolphin_animation_config_);

    //Animation 4
    manager->dolphin_animation_config_.is_moving = true;
    manager->dolphin_animation_config_.move_from = Vec3(-380.0f, -112.0f, -600.0f);
    manager->dolphin_animation_config_.move_to = Vec3(-380.0f, -112.0f, 600.0f);
    manager->dolphin_animation_config_.move_duration = 12.0f;

    manager->dolphin_animation_config_.is_rotating = true;
    manager->dolphin_animation_config_.rotate_from = Vec3(-60.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_to = Vec3(3000.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_duration = 12.0f;

    manager->dolphin_animation_config_.total_delay = 0.2f * (float)(rand() % 20);

    manager->animation_configs_.push_back(manager->dolphin_animation_config_);

    //Animation 5
    manager->dolphin_animation_config_.is_moving = true;
    manager->dolphin_animation_config_.move_from = Vec3(-530.0f, -112.0f, -600.0f);
    manager->dolphin_animation_config_.move_to = Vec3(-530.0f, -112.0f, 600.0f);
    manager->dolphin_animation_config_.move_duration = 12.0f;

    manager->dolphin_animation_config_.is_rotating = true;
    manager->dolphin_animation_config_.rotate_from = Vec3(-60.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_to = Vec3(3000.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_duration = 12.0f;

    manager->dolphin_animation_config_.total_delay = 0.2f * (float)(rand() % 20);

    manager->animation_configs_.push_back(manager->dolphin_animation_config_);

    //Animation 6
    manager->dolphin_animation_config_.is_moving = true;
    manager->dolphin_animation_config_.move_from = Vec3(-560.0f, -112.0f, -550.0f);
    manager->dolphin_animation_config_.move_to = Vec3(-400.0f, -112.0f, 550.0f);
    manager->dolphin_animation_config_.move_duration = 12.0f;

    manager->dolphin_animation_config_.is_rotating = true;
    manager->dolphin_animation_config_.rotate_from = Vec3(-60.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_to = Vec3(3000.0f, 0.0f, 0.0f);
    manager->dolphin_animation_config_.rotate_duration = 12.0f;

    manager->dolphin_animation_config_.total_delay = 0.2f * (float)(rand() % 20);

    manager->animation_configs_.push_back(manager->dolphin_animation_config_);

    UpdateAnimationConfigsString();
}

void InitSceneEntities() {
    DemoManager* manager = DemoManager::getInstance();
    Entity* obj_entity;
    obj_entity = new Entity(true, "Terrain");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 0.0f, -100.0f, 0.0f });
        obj_entity->attachDrawable(DrawableAttached_Terrain, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Cliff");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 610.0f, -120.0f, 0.0f });
        obj_entity->drawable_->set_geometry(manager->terrain_cliff.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->root->addChild(obj_entity->drawable_.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Tree");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 0.97f, -90.0f, -5.0f });
        obj_entity->attachDrawable(DrawableAttached_Tree, manager->root.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Sphere");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ -12.0f, -42.0f, 100.0f });
        obj_entity->attachDrawable(DrawableAttached_Sphere, manager->root.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Cube");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ -95.0f, -40.0f, -88.0f });
        obj_entity->attachDrawable(DrawableAttached_Cube, manager->root.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;


    obj_entity = new Entity(true, "Donut");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 26.0f, -30.0f, -28.0f });
        obj_entity->attachDrawable(DrawableAttached_Donut, manager->root.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "IslandSmall");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 94.0f, 19.0f, -28.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandSmall, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "IslandMedium");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ -71.0f, 18.0f, -24.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandMedium, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "IslandBig");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 6.0f, 46.0f, 58.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandBig, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    ///////////////////////////////////////////
    //Island Tower 
    obj_entity = new Entity(true, "IslandTower1");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 321.0f, -27.0f, 76.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandMedium, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "IslandTower2");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 321.0f, 0.0f, 127.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandMedium, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "IslandTower3");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 363.0f, -36.0f, 54.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandSmall, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;


    obj_entity = new Entity(true, "IslandTower4");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 361.0f, 24.0f, 161.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandBig, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "IslandTower5");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 416.0f, -74.0f, 102.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandSmall, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "IslandTower6");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 400.0f, 46.0f, 92.0f });
        obj_entity->attachDrawable(DrawableAttached_IslandBig, manager->root.get());
        obj_entity->drawable_->set_material(manager->mat_heightlayer.get());
        obj_entity->drawable_->set_material_settings(manager->mat_heightlayer_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    ////////////////////////////////////////////////////////


    obj_entity = new Entity(true, "Quad");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 80.0f, -15.0f, 0.0f });
        obj_entity->attachDrawable(DrawableAttached_Quad, manager->root.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "House");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 18.0f, -85.0f, -9.0f });
        obj_entity->set_scale({ 0.5f, 0.5f, 0.5f });
        obj_entity->attachDrawable(DrawableAttached_House, manager->root.get());
        obj_entity->drawable_->set_material_settings(manager->mat_house_settings.get());
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    for (int i = 0; i < 6; i++) {
    obj_entity = new Entity(true, "Dolphin");
        if (obj_entity != nullptr) {
            obj_entity->init();
            obj_entity->set_position({ 40.0f, -200.0f, 100.0f });
            obj_entity->set_scale({ 0.2f+rand()%3*0.05f, 0.2f + rand()%3 * 0.05f, 0.2f + rand()%3 * 0.05f });
            obj_entity->animation_config_selected = i;
            obj_entity->attachDrawable(DrawableAttached_Dolphin, manager->root.get());
            obj_entity->drawable_->set_material_settings(manager->mat_dolphin_settings.get());
            manager->entities_.push_back(obj_entity);
            manager->dolphin_entities_.push_back(obj_entity);
        }
        obj_entity = nullptr;
    }

    /*
    */
    obj_entity = new Entity(true, "Skybox");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 0.0f, 0.0f, 0.0f });
        obj_entity->attachDrawable(DrawableAttached_Cube, manager->skybox_root.get());
        obj_entity->drawable_->set_material(manager->mat_panoramic.get());
        obj_entity->drawable_->set_material_settings(manager->mat_panoramic_settings.get());
        manager->skybox_entity_ = obj_entity;
    }
    obj_entity = nullptr;


    obj_entity = new Entity(true, "Water");
    if (obj_entity != nullptr) {
      obj_entity->init();
      obj_entity->set_position({ 0.0f, -98.0f, 0.0f });
      obj_entity->attachDrawable(DrawableAttached_Water, manager->root.get());
      obj_entity->drawable_->set_material_settings(manager->mat_light_water_settings.get());
      obj_entity->drawable_->set_material(manager->mat_water.get());
      manager->entities_.push_back(obj_entity);
      manager->water_entity_ = obj_entity;
    }
    obj_entity = nullptr;

}

void InitSceneTextures() {
    DemoManager* manager = DemoManager::getInstance();

    EDK3::Texture::Load("./textures/sand.png", &manager->texture_sand);
    if (!manager->texture_sand) {
        printf("Error loading sand texture\n");
        exit(-2);
    }

    EDK3::Texture::Load("./textures/grass.png", &manager->texture_grass);
    if (!manager->texture_grass) {
        printf("Error loading grass texture\n");
        exit(-2);
    }

    EDK3::Texture::Load("./textures/rocks.png", &manager->texture_rocks);
    if (!manager->texture_rocks) {
        printf("Error loading sand texture\n");
        exit(-2);
    }

    EDK3::Texture::Load("./textures/clear_water.png", &manager->texture_water);
    if (!manager->texture_water) {
      printf("Error loading water texture\n");
      exit(-2);
    }

    EDK3::Texture::Load("./textures/texture_skybox.png", &manager->texture_skybox);
    if (!manager->texture_skybox) {
        printf("Error loading skybox texture\n");
        exit(-2);
    }

    EDK3::Texture::Load("./textures/house_d.png", &manager->texture_house);
    if (!manager->texture_house) {
        printf("Error loading house texture\n");
        exit(-2);
    }

    EDK3::Texture::Load("./textures/dolphin.jpg", &manager->texture_dolphin);
    if (!manager->texture_dolphin) {
        printf("Error loading dolphin texture\n");
        exit(-2);
    }
}
