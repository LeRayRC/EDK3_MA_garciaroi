#ifndef _SCENE_H_
#define _SCENE_H_

#include "EDK3/geometry.h"
#include "material_custom.h"
#include "EDK3/materialsettings.h"
#include "EDK3/node.h"
#include "EDK3/drawable.h"

void InitDemoGeometries();

//void InitTerrain();

void SetupDrawable(EDK3::Geometry* geo,
                   EDK3::MaterialCustom *mat, 
                   EDK3::MaterialSettings *mat_settings,
                   Vec3 pos, 
                   Vec3 scale = Vec3(1.0f,1.0f,1.0f),
                   Vec3 rot = Vec3(0.0f, 0.0f, 0.0f));

void UpdateDrawable(EDK3::Drawable* geo,
  EDK3::MaterialCustom* mat,
  EDK3::MaterialSettings* mat_settings,
  Vec3& pos);

void InitSceneGeometries();
void InitSceneMaterials();
void InitSceneEntities();
void InitSceneTextures();
void InitIslandPoints(Vec2* island_points);
void InitSceneAnimationConfigs();

#endif