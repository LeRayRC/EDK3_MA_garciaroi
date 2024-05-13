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
                   Vec3& pos, Vec3& scale, Vec3& rot) {
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

void InitSceneGeometries() {
    DemoManager* manager = DemoManager::getInstance();

    Vec2 tree_points[kNTreePoints + 1];
    Vec2 points[kNTorusPoints + 1];

    //Init Tree points
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

    //Init Torus points
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


    manager->custom_quad.alloc();
    manager->custom_quad->init(20.0f);

    manager->custom_sphere.alloc();
    manager->custom_sphere->init(8.0f);

    manager->custom_cube.alloc();
    manager->custom_cube->init24v(8.0f);

    manager->custom_tree.alloc();
    manager->custom_torus.alloc();
    manager->custom_torus->init(points, kNTorusPoints, 40, 2.0f, 2.0f);
    manager->custom_tree->init(tree_points, kNTreePoints, 40, 6.0f, 4.0f);

    manager->terrain_custom.alloc();
    manager->terrain_custom->init(256, 256, // cols , rows
        2.0f, // height multiplier
        1.0f, // quad size
        0.05f, // smothness
        40.0f, // heightmap multiplier
        //"./textures/australia.png",   // heightmap path
        "./textures/island_heightmap.png",   // heightmap path
        true); // use heightmap

    manager->water_terrain.alloc();
    manager->water_terrain->init(256, 256, // cols , rows
      2.0f, // height multiplier
      1.0f, // quad size
      0.05f, // smothness
      40.0f, // heightmap multiplier
      //"./textures/australia.png",   // heightmap path
      "./textures/island_heightmap.png",   // heightmap path
      false); // use heightmap
}

void InitSceneMaterials() {
    EDK3::scoped_array<char> error_log;
    DemoManager* manager = DemoManager::getInstance();

    //Initializing the material and its settings:
    manager->mat_basic->init(error_log, "./shaders/basicVertex.vs", "./shaders/light_shader.fs");
    manager->mat_normals->init(error_log, "./shaders/basicVertex.vs", "./shaders/normalFragment.fs");
    manager->mat_wireframe->init(error_log, "./shaders/basicVertex.vs", "./shaders/wireframeFragment.fs");
    //manager->mat_light_settings.alloc();
    //manager->mat_light_water_settings.alloc();

    manager->render_target.alloc()->init((float)kWindowWidth,
        (float)kWindowHeight, 1);
    manager->mat_postprocess.alloc();
    manager->mat_postprocess_settings.alloc();

    manager->mat_postprocess->init("./shaders/postprocessVertex.vs", "./shaders/postprocessFragment.fs");
    float green[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    manager->mat_postprocess->set_use_texture(true);
    //Aqui le asociamos la textura del render target y se la asociamos al material de postproceso
    manager->mat_postprocess_settings->set_texture(manager->render_target->color_texture(0));
    manager->mat_postprocess_settings->set_color(green);


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


    manager->mat_light_water_settings->set_texture(manager->texture_water.get());
    
    if (manager->show_normals) {
        manager->mat_selected = manager->mat_normals;
    }
    else {
        manager->mat_selected = manager->mat_basic;
    }
}

void InitSceneEntities() {
    DemoManager* manager = DemoManager::getInstance();
    Entity* obj_entity;
    obj_entity = new Entity(true, "Terrain");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 0.0f, -100.0f, 0.0f });
        obj_entity->attachDrawable(DrawableAttached_Terrain);
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Tree");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 0.97f, -90.0f, -5.0f });
        obj_entity->attachDrawable(DrawableAttached_Tree);
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Sphere");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ -12.0f, -42.0f, 100.0f });
        obj_entity->attachDrawable(DrawableAttached_Sphere);
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Cube");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ -95.0f, -40.0f, -88.0f });
        obj_entity->attachDrawable(DrawableAttached_Cube);
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;


    obj_entity = new Entity(true, "Donut");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 26.0f, -30.0f, -28.0f });
        obj_entity->attachDrawable(DrawableAttached_Donut);
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Quad");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 80.0f, -15.0f, 0.0f });
        obj_entity->attachDrawable(DrawableAttached_Quad);
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "House");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 18.0f, -85.0f, -9.0f });
        obj_entity->set_scale({ 0.5f, 0.5f, 0.5f });
        obj_entity->attachDrawable(DrawableAttached_House);
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

    obj_entity = new Entity(true, "Boat");
    if (obj_entity != nullptr) {
        obj_entity->init();
        obj_entity->set_position({ 40.0f, -98.0f, 100.0f });
        obj_entity->set_scale({ 4.5f, 4.5f, 4.5f });
        obj_entity->attachDrawable(DrawableAttached_Boat);
        manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;


    obj_entity = new Entity(true, "Water");
    if (obj_entity != nullptr) {
      obj_entity->init();
      obj_entity->set_position({ 0.0f, -98.0f, 0.0f });
      obj_entity->attachDrawable(DrawableAttached_Water);
      obj_entity->drawable_->set_material_settings(manager->mat_light_water_settings.get());

      manager->entities_.push_back(obj_entity);
    }
    obj_entity = nullptr;

}

void InitSceneTextures() {
    DemoManager* manager = DemoManager::getInstance();

    EDK3::Texture::Load("./textures/sand_texture.png", &manager->texture_sand);
    if (!manager->texture_sand) {
        printf("Error loading sand texture\n");
        exit(-2);
    }

    EDK3::Texture::Load("./textures/clear_water.png", &manager->texture_water);
    if (!manager->texture_water) {
      printf("Error loading water texture\n");
      exit(-2);
    }
}
