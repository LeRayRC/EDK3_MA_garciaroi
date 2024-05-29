/**
 *
 * @brief Custom quad header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __GEOMETRY_CUSTOM_PARTICLE_H__
#define __GEOMETRY_CUSTOM_PARTICLE_H__ 1

#include "EDK3/geometry.h"
#include "EDK3/dev/buffer.h"
#include "math_library/vector_2.h";
#include "math_library/vector_3.h";
#include "math_library/matrix_4.h"

namespace EDK3 {

class ParticleSystem : public EDK3::Geometry {
public:
    static const int kNumParticles = 300;

    struct Particle {
        bool alive;
        Vec3 pos;
        Vec3 speed;
        float size;
        float lifetime;
    };

    struct MeshVtx {
        Vec3 pos;
        Vec3 normal;
        Vec2 uv;
    };
public:
    struct ParticleSystemConfig {
        Vec3 spawn_position_;
        int spawn_radius_;
        int spawn_rate_;
        float spawn_ratio_;
        float init_lifetime_;
        float init_size_;
    };

 public:
     ParticleSystem();

     void set_config(ParticleSystemConfig *config);
     //void set_spawn_position(Vec3& pos);
  void init();
  void update(float dt, const float* camera_pos, const float* view_matrix);
  void spawnParticle(int rate);
  void killParticle(Particle* particle);

  virtual bool bindAttribute(const Attribute a,
                             unsigned int where_to_bind_attribute) const override;
  virtual void render() const override;

 protected:
  virtual ~ParticleSystem();

 private:
     ParticleSystem(const ParticleSystem&);
  //QuadCustom(QuadCustom&&);
     ParticleSystem& operator=(const ParticleSystem&);

  EDK3::ref_ptr<EDK3::dev::Buffer> elements_buffer;
  EDK3::ref_ptr<EDK3::dev::Buffer> order_buffer;

  bool is_initialized_;

  
public:
  ParticleSystemConfig *config_;
  float internal_timer_;
  int particles_alive_;
  Particle particles_[kNumParticles];
  EDK3::scoped_array<MeshVtx> mesh_elements_;
  EDK3::scoped_array<unsigned int> mesh_order_;
};

} //EDK3

#endif //__GEOMETRY_CUSTOM_QUAD_H__
