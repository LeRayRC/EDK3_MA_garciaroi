#include "dev/custom_gpu_buffer.h"
#include "dev/custom_gpu_manager.h"
#include "dev/custom_gpu_shader.h"
#include "dev/custom_gpu_program.h"
#include "EDK3/dev/opengl.h"

namespace EDK3 {


  namespace dev {


    CustomGPUBuffer::CustomGPUBuffer() {
      internal_id_ = 0;
      size_ = 0;
      target_ = kTarget_Vertex_Data;
    }

    CustomGPUBuffer::~CustomGPUBuffer(){}

    void CustomGPUBuffer::init(unsigned int size) {
      GLenum error;
      glGenBuffers(1, &internal_id_);
      error = glGetError();
      if (error != GL_NO_ERROR) {
        switch (error) {
        case GL_INVALID_VALUE:
          printf("Gen buffer uniform error: GL_INVALID_VALUE\n");
          break;
        default:
          printf("Gen buffer uniform value error: Unknown error\n");
          break;
        }
      }
      glBindBuffer(GL_ARRAY_BUFFER, internal_id_);
      glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
      size_ = size;
    }


    void CustomGPUBuffer::bind(const Target t) const {
      CustomGPUBuffer* p = const_cast<CustomGPUBuffer*>(this);
      p->target_ = t;
      GLenum error;
      switch (t)
      {
        case EDK3::dev::Buffer::Target::kTarget_Elements: {
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, internal_id_);
        }
        case EDK3::dev::Buffer::Target::kTarget_Vertex_Data: {
          glBindBuffer(GL_ARRAY_BUFFER, internal_id_);
        }
      }
      error = glGetError();
      if (error != GL_NO_ERROR) {
        switch (error) {
          case GL_INVALID_VALUE:
            printf("Gen bind buffer error: GL_INVALID_VALUE\n");
            break;
          case GL_INVALID_ENUM:
            printf("Gen bind buffer error: GL_INVALID_ENUM\n");
            break;
          default:
            printf("Gen bind buffer error: Unknown error\n");
            break;
        }
      }
    }

    unsigned int CustomGPUBuffer::size() const {
      return size_;
    }

    void CustomGPUBuffer::uploadData(const void* data, unsigned int size,
      unsigned int offset){
      switch (target_){
        case kTarget_Vertex_Data:
          glBindBuffer(GL_ARRAY_BUFFER, internal_id_);
          glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
          break;
        
        case kTarget_Elements:
          glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, internal_id_);
          glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
          break;
       }
    }

    CustomGPUBuffer::CustomGPUBuffer(const CustomGPUBuffer& other) {
      internal_id_ = other.internal_id_;
      size_ = other.size_;
      target_ = other.target_;
    }

    CustomGPUBuffer& CustomGPUBuffer::operator=(const CustomGPUBuffer& other) {
      internal_id_ = other.internal_id_;
      size_ = other.size_;
      target_ = other.target_;
      return *this;
    }

    void CustomGPUBuffer::release() {
      GLenum error;
      glDeleteBuffers(1, &internal_id_);
      error = glGetError();
      if (error != GL_NO_ERROR) {
        switch (error) {
        case GL_INVALID_VALUE:
          printf("Delete buffer uniform error: GL_INVALID_VALUE\n");
          break;
        default:
          printf("Delete buffer uniform value error: Unknown error\n");
          break;
        }
      }
    }
  }
}