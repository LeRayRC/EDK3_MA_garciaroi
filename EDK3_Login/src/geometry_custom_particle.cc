/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_particle.h"
#include "ESAT/math.h"
#include "dev/custom_gpu_manager.h"
#include "dev/custom_gpu_buffer.h"


namespace EDK3 {

//IMPORTANT!!!
//TODO constructors, destructor and =operator here!!!
    ParticleSystem::ParticleSystem(){}
    ParticleSystem::~ParticleSystem(){}

void ParticleSystem::init() {
  //TODO demand graphic resources to the GPUManager.
  EDK3::dev::GPUManager& GPU = *EDK3::dev::GPUManager::Instance();
  GPU.newBuffer(&elements_buffer);
  GPU.newBuffer(&order_buffer);

  mesh_elements_.alloc(kNumParticles * 4);
  mesh_order_.alloc(kNumParticles * 6);


  elements_buffer->init(mesh_elements_.sizeInBytes());
  order_buffer->init(mesh_order_.sizeInBytes());
  
  internal_timer_ = 0.0f;
  particles_alive_ = 0;
  

  for (int i = 0; i < kNumParticles; i++) {
      particles_[i].alive = false;
  }

  assert(glGetError() == GL_NO_ERROR);
}

bool ParticleSystem::bindAttribute(const Attribute a,
                               unsigned int where_to_bind_attribute) const {
  //TODO
  //EDK3::dev::GPUManager::Instance()->enableVertexAttribute
  switch (a){
    case Attribute::A_POSITION:
        EDK3::dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(),
            0, EDK3::T_FLOAT_3, false, 0, 8 * sizeof(float));
        break;
    case Attribute::A_NORMAL:
        EDK3::dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(),
            1, EDK3::T_FLOAT_3, false, 3 * sizeof(float), 8 * sizeof(float));
        break;
    case Attribute::A_UV:
        EDK3::dev::GPUManager::Instance()->enableVertexAttribute(elements_buffer.get(),
            2, EDK3::T_FLOAT_2, false, 6 * sizeof(float), 8 * sizeof(float));
        break;
    default:
        break;
  }
  return true;
}

void ParticleSystem::update(float dt, const float* camera_pos,const float* view_matrix) {
    //Fill mesh points
    MeshVtx* mesh_pointer = mesh_elements_.get();
    Vec3 v_camera_pos = { camera_pos[0],camera_pos[1],camera_pos[2] };
    Vec3 camera_right = { view_matrix[0], view_matrix[1], view_matrix[2] };
    Vec3 camera_up = { view_matrix[4], view_matrix[5], view_matrix[6] };
    /*printf("%f %f %f %f\n", view_matrix[0], view_matrix[1], view_matrix[2], view_matrix[3]);
    printf("%f %f %f %f\n", view_matrix[4], view_matrix[5], view_matrix[6], view_matrix[7]);
    printf("%f %f %f %f\n", view_matrix[8], view_matrix[9], view_matrix[10], view_matrix[11]);
    printf("%f %f %f %f\n", view_matrix[12], view_matrix[13], view_matrix[14], view_matrix[15]);*/

    Vec3 view_direction = v_camera_pos - config_->spawn_position_;
    Vec3 view_direction_normalized = view_direction.Normalized();
    Vec3 view_direction_projection = Vec3(view_direction.x, 0.0f, view_direction.z).Normalized();
    Vec3 look_at_vector = Vec3(0.0f, 0.0f, 1.0f);

    float cos_angle = Vec3::DotProduct(look_at_vector, view_direction_projection);
    Vec3 cross_product = Vec3::CrossProduct(look_at_vector, view_direction_projection);
    float angle = acosf(cos_angle);

    float cos_angle_2 = Vec3::DotProduct(view_direction_projection, view_direction_normalized);
    float angle_2 = acosf(cos_angle_2);
    Vec3 cross_product_2 = Vec3::CrossProduct(view_direction_projection, view_direction_normalized);

    if (cross_product.y < 0) {
        angle = -angle;
    }

    if (v_camera_pos.y < config_->spawn_position_.y) {
        angle_2 = -angle_2;
    }


    internal_timer_ += dt;
    if (internal_timer_ >= config_->spawn_ratio_) {
        spawnParticle(config_->spawn_rate_);
        internal_timer_ = 0.0f;
    }

    for (int i = 0, counter = 0; i < kNumParticles; i++) {

        if (particles_[i].alive) {
            particles_[i].lifetime -= dt;
            if (particles_[i].lifetime <= 0.0f) {
                killParticle(&particles_[i]);
                break;
            }else {
           /*     mesh_pointer[counter * 4].pos     = {-particles_[i].size*0.5f + particles_[i].pos.x, -particles_[i].size*0.5f + particles_[i].pos.y, 0.0f};
                mesh_pointer[counter * 4 + 1].pos = { particles_[i].size*0.5f + particles_[i].pos.x, -particles_[i].size*0.5f + particles_[i].pos.y, 0.0f};
                mesh_pointer[counter * 4 + 2].pos = { particles_[i].size*0.5f + particles_[i].pos.x,  particles_[i].size*0.5f + particles_[i].pos.y, 0.0f};
                mesh_pointer[counter * 4 + 3].pos = {-particles_[i].size*0.5f + particles_[i].pos.x,  particles_[i].size*0.5f + particles_[i].pos.y, 0.0f};*/


                mesh_pointer[counter * 4].pos     = { -particles_[i].size * 0.5f, -particles_[i].size * 0.5f, 0.0f };
                mesh_pointer[counter * 4 + 1].pos = { particles_[i].size * 0.5f , -particles_[i].size * 0.5f, 0.0f };
                mesh_pointer[counter * 4 + 2].pos = { particles_[i].size * 0.5f ,  particles_[i].size * 0.5f, 0.0f };
                mesh_pointer[counter * 4 + 3].pos = { -particles_[i].size * 0.5f,  particles_[i].size * 0.5f, 0.0f };
                //Billboarding
                //apply rotation to every point
                /*ESAT::Mat4 m = ESAT::Mat4Identity();
                m = ESAT::Mat4Multiply(ESAT::Mat4RotateY(angle),m);
                m = ESAT::Mat4Multiply(ESAT::Mat4RotateX(angle_2), m);*/

                Mat4 rotate_matrix = Mat4::Identity();
                //printf("%f , %f, Cross:{%f , %f , %f}\n", angle_2, cos_angle_2, cross_product_2.x , cross_product_2.y , cross_product_2.z);
                rotate_matrix = Mat4::RotateX(angle_2).Multiply(rotate_matrix);
                rotate_matrix = Mat4::RotateY(angle).Multiply(rotate_matrix);
                
                mesh_pointer[counter * 4].pos = rotate_matrix.TransformVec3(mesh_pointer[counter * 4].pos);
                mesh_pointer[counter * 4+1].pos = rotate_matrix.TransformVec3(mesh_pointer[counter * 4+1].pos);
                mesh_pointer[counter * 4+2].pos = rotate_matrix.TransformVec3(mesh_pointer[counter * 4+2].pos);
                mesh_pointer[counter * 4+3].pos = rotate_matrix.TransformVec3(mesh_pointer[counter * 4+3].pos);

                
                mesh_pointer[counter * 4].pos += { mesh_pointer[counter * 4].pos.x + particles_[i].pos.x,0.0f , mesh_pointer[counter * 4].pos.z + particles_[i].pos.z };
                mesh_pointer[counter * 4 + 1].pos += { mesh_pointer[counter * 4 + 1].pos.x + particles_[i].pos.x,0.0f , mesh_pointer[counter * 4 + 1].pos.z + particles_[i].pos.z };
                mesh_pointer[counter * 4 + 2].pos += { mesh_pointer[counter * 4 + 2].pos.x + particles_[i].pos.x,0.0f , mesh_pointer[counter * 4 + 2].pos.z + particles_[i].pos.z };
                mesh_pointer[counter * 4 + 3].pos += { mesh_pointer[counter * 4 + 3].pos.x + particles_[i].pos.x,0.0f , mesh_pointer[counter * 4 + 3].pos.z + particles_[i].pos.z };

                
                
                mesh_pointer[counter * 4].pos +=     {0.0f, particles_[i].pos.y + particles_[i].speed.y * (config_->init_lifetime_- particles_[i].lifetime), 0.0f };
                mesh_pointer[counter * 4 + 1].pos += {0.0f, particles_[i].pos.y + particles_[i].speed.y * (config_->init_lifetime_- particles_[i].lifetime), 0.0f };
                mesh_pointer[counter * 4 + 2].pos += {0.0f, particles_[i].pos.y + particles_[i].speed.y * (config_->init_lifetime_- particles_[i].lifetime), 0.0f };
                mesh_pointer[counter * 4 + 3].pos += {0.0f, particles_[i].pos.y + particles_[i].speed.y * (config_->init_lifetime_- particles_[i].lifetime), 0.0f };


                //ESAT::Vec3 vec_1 = ESAT::Mat4TransformVec3(m, mesh_pointer[counter * 4].pos.x)

                

                /*mesh_pointer[counter * 4].pos = (camera_right * mesh_pointer[counter * 4].pos.x) + (camera_up * mesh_pointer[counter * 4].pos.y);
                mesh_pointer[counter * 4 + 1].pos = (camera_right * mesh_pointer[counter * 4 + 1].pos.x) + (camera_up * mesh_pointer[counter * 4 + 1].pos.y);
                mesh_pointer[counter * 4 + 2].pos = (camera_right * mesh_pointer[counter * 4 + 2].pos.x) + (camera_up * mesh_pointer[counter * 4 + 2].pos.y);
                mesh_pointer[counter * 4 + 3].pos = (camera_right * mesh_pointer[counter * 4 + 3].pos.x) + (camera_up * mesh_pointer[counter * 4 + 3].pos.y);*/


                mesh_pointer[counter * 4].normal     = view_direction_normalized;
                mesh_pointer[counter * 4 + 1].normal = view_direction_normalized;
                mesh_pointer[counter * 4 + 2].normal = view_direction_normalized;
                mesh_pointer[counter * 4 + 3].normal = view_direction_normalized;

               /* mesh_pointer[counter * 4].normal = { 0.0f, 0.0f, 1.0f };
                mesh_pointer[counter * 4 + 1].normal = { 0.0f, 0.0f, 1.0f };
                mesh_pointer[counter * 4 + 2].normal = { 0.0f, 0.0f, 1.0f };
                mesh_pointer[counter * 4 + 3].normal = { 0.0f, 0.0f, 1.0f };*/

                mesh_pointer[counter * 4].uv     = { 0.0f, 0.0f};
                mesh_pointer[counter * 4 + 1].uv = { 1.0f, 0.0f};
                mesh_pointer[counter * 4 + 2].uv = { 1.0f, 1.0f};
                mesh_pointer[counter * 4 + 3].uv = { 0.0f, 1.0f};

                counter++;
            }
        }

        if (counter >= particles_alive_) break;
    }

    unsigned int* order_pointer = mesh_order_.get();
    for (int i = 0; i < particles_alive_; i++) {
        order_pointer[i * 6]     = (i * 4);
        order_pointer[i * 6 + 1] = (i * 4) + 1;
        order_pointer[i * 6 + 2] = (i * 4) + 3;
        order_pointer[i * 6 + 3] = (i * 4) + 1;
        order_pointer[i * 6 + 4] = (i * 4) + 2;
        order_pointer[i * 6 + 5] = (i * 4) + 3;
    }                                 

    order_buffer->uploadData(mesh_order_.get(), particles_alive_*6*4, 0);
    assert(glGetError() == GL_NO_ERROR);


    elements_buffer->uploadData(mesh_elements_.get(), particles_alive_ * 128, 0);
    assert(glGetError() == GL_NO_ERROR);


}

//void ParticleSystem::set_spawn_position(Vec3& pos) {
//    spawn_position_ = pos;
//}

void ParticleSystem::set_config(ParticleSystemConfig *config) {
    config_ = config;
}

void ParticleSystem::render() const {
  //TODO
    EDK3::dev::GPUManager::Instance()->drawElements
    (EDK3::dev::CustomGPUManager::DrawMode::kDrawMode_Triangles,
        6 * particles_alive_, order_buffer.get(), EDK3::Type::T_UINT, 0);
}

void ParticleSystem::spawnParticle(int rate) {
    for (int j = 0; j < rate; j++) {
        for (int i = 0; i < kNumParticles; i++) {
            if (!particles_[i].alive) {
                particles_[i].alive = true;
                float angle = 3.14f / 180.0f * (float)(rand() % 360);
                particles_[i].pos.x = config_->spawn_position_.x + (cosf(angle) * (config_->spawn_radius_));
                particles_[i].pos.y = config_->spawn_position_.y;
                particles_[i].pos.z = config_->spawn_position_.z + (sinf(angle) * (config_->spawn_radius_));
                particles_[i].speed = { 0.0f, -1.0f * (rand() % 100) , 0.0f};    
                particles_[i].size = config_->init_size_;
                particles_[i].lifetime = config_->init_lifetime_;
                particles_alive_++;
                break;
            }
        }
    }
}

void ParticleSystem::killParticle(Particle* particle) {
    particle->alive = false;
    particles_alive_--;
}

} //EDK3
