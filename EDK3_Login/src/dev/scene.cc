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


void InitTerrain(){
    DemoManager* manager = DemoManager::getInstance();

    EDK3::ref_ptr<EDK3::TerrainCustom> terrain_custom;
    terrain_custom.alloc();
    terrain_custom->init(256, 256, // cols , rows
      2.0f, // height multiplier
      1.0f, // quad size
      0.05f, // smothness
      40.0f, // heightmap multiplier
      "./textures/island_heightmap.png",   // heightmap path
      true); // use heightmap

    manager->terrain_custom = terrain_custom;
}

void SetupDrawable(EDK3::Geometry *geo, 
                   EDK3::MaterialCustom *mat, 
                   EDK3::MaterialSettings *mat_settings,
                   Vec3& pos){
    DemoManager* manager = DemoManager::getInstance();          
    EDK3::ref_ptr<EDK3::Drawable> drawable;
    drawable.alloc();
    drawable->set_geometry(geo);
    drawable->set_material(mat);
    drawable->set_material_settings(mat_settings);
    drawable->set_position(pos.x, pos.y, pos.z);
    drawable->set_HPR(0.0f, 0.0f, 0.0f);
    manager->root->addChild(drawable.get());
}
