/**
 *
 * @brief Custom terrain header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 * 
 * Use of Simplex Noise algorithm:
 * https://github.com/SRombauts/SimplexNoise
 *
 */



#ifndef __GEOMETRY_CUSTOM_TERRAIN_H__
#define __GEOMETRY_CUSTOM_TERRAIN_H__ 1

#include "EDK3/geometry.h"
#include "EDK3/dev/buffer.h"
#include "EDK3/dev/gpumanager.h"
#include "math_library/vector_2.h"
#include "tools.h"




namespace EDK3 {

class TerrainCustom : public EDK3::Geometry {
 public:
  TerrainCustom();

  void init(const int num_cols = 4, const int num_rows = 4, 
            const float height_mult = 1.0f, const float size = 1.0f, const float smoothness = 0.1f,
            const HeightmapConf conf = {0.0f,0.0f,0.0f}, const char* heightmap_path = NULL, const bool use_heightmap = false,
            const bool is_centered = true, const Vec2 tilling = { 1.0f,1.0f });
  virtual bool bindAttribute(const Attribute a, 
                             unsigned int where_to_bind_attribute) const override;
  virtual void render() const override;


 protected:
  virtual ~TerrainCustom();

 private:
  TerrainCustom(const TerrainCustom&);
  TerrainCustom(TerrainCustom&&);
  TerrainCustom& operator=(const TerrainCustom&);



  EDK3::ref_ptr<EDK3::dev::Buffer> elements_buffer;
  EDK3::ref_ptr<EDK3::dev::Buffer> order_buffer;
  bool is_initialized_;
  int num_rows_;
  int num_cols_;
};

} //EDK3

#endif //__GEOMETRY_CUSTOM_TERRAIN_H__