#ifndef _DEMO_MANAGER_H_
#define _DEMO_MANAGER_H_ 1

#include <stdlib.h>
#include <vector>

#include "interface.h"
#include "EDK3/geometry.h"
#include "EDK3/camera.h"
#include "EDK3/drawable.h"
#include "EDK3/matdiffusetexture.h"
#include "EDK3/rendertarget.h"
#include "EDK3/texture.h"
#include "EDK3/dev/gpumanager.h"

#include "ESAT_extra/imgui.h"
#include "EDK3/dev/opengl.h"

#include "camera_custom.h"
#include "material_custom.h"
#include "geometry_custom_terrain.h"
#include "postprocess_basic.h"
#include "anim_library/animationinstance.h"
#include "anim_library/entity.h"

#include "geometry_custom_sphere.h"
#include "geometry_custom_cube.h"
#include "geometry_custom_quad.h"
#include "geometry_custom_surface.h"
#include "geometry_custom_obj.h"
#include "dev/custom_gpu_camera.h"
#include "dev/custom_gpu_manager.h"

const unsigned int kWindowWidth = 1280;
const unsigned int kWindowHeight = 768;
const int kNTorusPoints = 10;
const int kNTreePoints = 16;
const int kNIslandPoints = 33;

/**
 * @brief Class the represents the singleton that manages the game
 * 
 */
class DemoManager{
  //Attributes
  private:
    static DemoManager* instance;
  public:

    //EDK3::ref_ptr<EDK3::CameraCustom> camera;
    EDK3::dev::CustomGPUManager GPU;
    float clear_rgba[4] = { 1.0f,1.0f,1.0f,1.0f };

    EDK3::dev::GPUManager::BlendParam blend_src = EDK3::dev::GPUManager::BlendParam::kBlendParam_SourceAlpha;
    EDK3::dev::GPUManager::BlendParam blend_dst = EDK3::dev::GPUManager::BlendParam::kBlendParam_OneMinusSourceAlpha;
    EDK3::dev::GPUManager::BlendOp blend_op = EDK3::dev::GPUManager::BlendOp::kBlendOp_Add;
    float blend_white[4] = { 1.0f,1.0f,1.0f,1.0f };
    float blend_black[4] = { 0.0f,0.0f,0.0f,0.0f };
    

    EDK3::ref_ptr<EDK3::dev::CustomGPUCamera> camera;
    //EDK3::ref_ptr<EDK3::CameraCustom> camera;
    EDK3::ref_ptr<EDK3::Node> root;
    EDK3::ref_ptr<EDK3::Node> skybox_root;
    EDK3::ref_ptr<EDK3::MaterialCustom> mat_basic;
    EDK3::ref_ptr<EDK3::MaterialCustom> mat_normals;
    EDK3::ref_ptr<EDK3::MaterialCustom> mat_wireframe;
    EDK3::ref_ptr<EDK3::MaterialCustom> mat_panoramic;
    EDK3::ref_ptr<EDK3::MaterialCustom> mat_water;
    EDK3::ref_ptr<EDK3::MaterialCustom> mat_heightlayer;
    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> mat_light_settings_general;
    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> mat_light_settings;
    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> mat_light_water_settings;
    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> mat_panoramic_settings;
    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> mat_heightlayer_settings;
    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> mat_house_settings;
    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> mat_dolphin_settings;

    EDK3::scoped_array<EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings>> light_materials_settings;

    EDK3::ref_ptr<EDK3::MaterialCustom> mat_selected;

    EDK3::ref_ptr<EDK3::QuadCustom> custom_quad;
    EDK3::ref_ptr<EDK3::SphereCustom> custom_sphere;
    EDK3::ref_ptr<EDK3::CubeCustom> custom_cube;
    EDK3::ref_ptr<EDK3::CubeCustom> custom_cube_8v;
    EDK3::ref_ptr<EDK3::SurfaceCustom> custom_tree;
    EDK3::ref_ptr<EDK3::SurfaceCustom> custom_island_small;
    EDK3::ref_ptr<EDK3::SurfaceCustom> custom_island_medium;
    EDK3::ref_ptr<EDK3::SurfaceCustom> custom_island_big;
    EDK3::ref_ptr<EDK3::SurfaceCustom> custom_torus;
    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> house_geometry;
    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> boat_geometry;
    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> dolphin_geometry;

    Entity* skybox_entity_;
    Entity* water_entity_;
    std::vector<Entity*> dolphin_entities_;
    std::vector<Entity*> entities_;
    std::vector<AnimationConfig> animation_configs_;
    AnimationConfig dolphin_animation_config_;
    EDK3::scoped_array<char> animation_configs_names_;
    
    EDK3::ref_ptr<EDK3::TerrainCustom> terrain_custom;
    EDK3::ref_ptr<EDK3::TerrainCustom> water_terrain;
    EDK3::ref_ptr<EDK3::TerrainCustom> terrain_cliff;

    EDK3::ref_ptr<EDK3::RenderTarget> render_target;
    EDK3::ref_ptr<EDK3::PostprocessBasic> mat_postprocess;
    EDK3::ref_ptr<EDK3::PostprocessBasic::PostprocessBasicSettings> mat_postprocess_settings;

    EDK3::ref_ptr<EDK3::Texture> texture_water;
    EDK3::ref_ptr<EDK3::Texture> texture_skybox;
    EDK3::ref_ptr<EDK3::Texture> texture_sand;
    EDK3::ref_ptr<EDK3::Texture> texture_grass;
    EDK3::ref_ptr<EDK3::Texture> texture_forest;
    EDK3::ref_ptr<EDK3::Texture> texture_rocks;
    EDK3::ref_ptr<EDK3::Texture> texture_house;
    EDK3::ref_ptr<EDK3::Texture> texture_dolphin;

    double dt;
    float time_;
    bool enable_postprocess;
    bool enable_wireframe;

    bool show_normals;

    ImGuiWindow settings_window;
    ImGuiWindow lights_window;
    ImGuiWindow performance_window;
    ImGuiWindow camera_window;
    ImGuiWindow control_window;
    ImGuiWindow entities_window;
    ImGuiWindow animationconfigs_window;

    float kMaxAnimationDuration = 60.0f;
    int animation_configs_counter = 0;

    Vec2 tree_points[kNTreePoints + 1];
    Vec2 points[kNTorusPoints + 1];
    Vec2 island_points[kNIslandPoints + 1];
  //Methods
  private:
    // Constructor
    DemoManager();
    // Copy constructor
    DemoManager(DemoManager& other);


  public:

    static DemoManager* getInstance();


    void init();
};

#endif