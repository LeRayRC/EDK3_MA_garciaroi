#ifndef _DEMO_MANAGER_H_
#define _DEMO_MANAGER_H_ 1

#include <stdlib.h>


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

const int kWindowWidth = 1280;
const int kWindowHeight = 768;
const int kNTorusPoints = 10;
const int kNTreePoints = 16;

/**
 * @brief Class the represents the singleton that manages the game
 * 
 */
class DemoManager{
  //Attributes
  private:
    static DemoManager* instance;
  public:

    EDK3::ref_ptr<EDK3::CameraCustom> camera;
    EDK3::ref_ptr<EDK3::Node> root;
    EDK3::ref_ptr<EDK3::MaterialCustom> mat_basic;
    EDK3::ref_ptr<EDK3::MaterialCustom> mat_normals;
    EDK3::ref_ptr<EDK3::MaterialCustom::LightSettings> mat_light_settings;

    EDK3::ref_ptr<EDK3::MaterialCustom> mat_selected;

    EDK3::ref_ptr<EDK3::QuadCustom> custom_quad;
    EDK3::ref_ptr<EDK3::SphereCustom> custom_sphere;
    EDK3::ref_ptr<EDK3::CubeCustom> custom_cube;
    EDK3::ref_ptr<EDK3::SurfaceCustom> custom_tree;
    EDK3::ref_ptr<EDK3::SurfaceCustom> custom_torus;
    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> house_geometry;
    EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> boat_geometry;


    EDK3::ref_ptr<EDK3::TerrainCustom> terrain_custom;
    EDK3::ref_ptr<EDK3::RenderTarget> render_target;
    EDK3::ref_ptr<EDK3::PostprocessBasic> mat_postprocess;
    EDK3::ref_ptr<EDK3::PostprocessBasic::PostprocessBasicSettings> mat_postprocess_settings;

    Entity entity_boat_;
    AnimationConfig anim_config_boat_;

    float dt;
    bool enable_postprocess;

    bool show_normals;

    ImGuiWindow settings_window;
    ImGuiWindow lights_window;
    ImGuiWindow performance_window;
    ImGuiWindow camera_window;
    ImGuiWindow hierachy_window;
    ImGuiWindow control_window;

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