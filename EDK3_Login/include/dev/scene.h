#ifndef _SCENE_H_
#define _SCENE_H_

#include "EDK3/geometry.h"
#include "material_custom.h"
#include "EDK3/materialsettings.h"
#include "EDK3/node.h"
#include "EDK3/drawable.h"

void InitDemoGeometries();

void InitTerrain();

void SetupDrawable(EDK3::Geometry* geo,
                   EDK3::MaterialCustom *mat, 
                   EDK3::MaterialSettings *mat_settings,
                   Vec3& pos);

void UpdateDrawable(EDK3::Drawable* geo,
  EDK3::MaterialCustom* mat,
  EDK3::MaterialSettings* mat_settings,
  Vec3& pos);
#endif