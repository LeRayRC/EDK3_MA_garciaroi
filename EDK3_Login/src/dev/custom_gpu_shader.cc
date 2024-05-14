#include "dev/custom_gpu_shader.h"
#include "EDK3/dev/opengl.h"

namespace EDK3{


  namespace dev {

    CustomGPUShader::CustomGPUShader() {
      is_compiled_ = false;
      type_ = EDK3::dev::Shader::Type::kType_Invalid;
      internal_id_ = 0;
    }



    bool CustomGPUShader::compile(
      EDK3::scoped_array<char>* output_log) {
        GLint params = 0;
        glCompileShader(internal_id_);
        glGetShaderiv(internal_id_, GL_COMPILE_STATUS, &params);
        if (GL_TRUE == params) {
          if (output_log) {
            output_log->alloc(1);
            output_log->get()[0] = '\0';
          }
          is_compiled_ = true;
        }
        else {
            GLenum error = glGetError();
            switch (error){
              case GL_INVALID_VALUE:
                printf("Compile error: GL_INVALID_VALUE\n");
                break;
              case GL_INVALID_OPERATION:
                printf("Compile error: GL_INVALID_OPERATION\n");
                break;
              default:
                printf("Compile error: Unknown error\n");
                break;
            }
            GLint info_length;
            glGetShaderiv(internal_id_, GL_INFO_LOG_LENGTH, &info_length);
            output_log->alloc(info_length + 1);
            glGetShaderInfoLog(internal_id_,info_length, NULL, output_log->get());
            output_log->get()[info_length] = '\0';
            is_compiled_ = false;
        }
        return is_compiled_;
    }

    void CustomGPUShader::loadSource(const Type shader_type,
      const char* source,
      const unsigned int source_size) {
        GLenum error;
        type_ = shader_type;
        if (internal_id_ != 0) return;
        switch (shader_type){
        case EDK3::dev::Shader::Type::kType_Fragment: {
            internal_id_ = glCreateShader(GL_FRAGMENT_SHADER);
            break;
          }
        case EDK3::dev::Shader::Type::kType_Vertex:{
            internal_id_ = glCreateShader(GL_VERTEX_SHADER);
            break;
          }
        case EDK3::dev::Shader::Type::kType_Geometry:{
            internal_id_ = glCreateShader(GL_GEOMETRY_SHADER);
            break;
          }
        }
        assert(0 != internal_id_, "Error creating shader");

        error = glGetError();
        if (error != GL_NO_ERROR) {
            switch (error) {
              case GL_INVALID_ENUM:
                printf("Create shader error: GL_INVALID_ENUM\n");
                break;
              default:
                printf("Create shader error: Unknown error\n");
                break;
            }
        }
        GLint size = source_size;
        glShaderSource(internal_id_, 1, &source, &size);

        error = glGetError();
        if (error != GL_NO_ERROR) {
            switch (error) {
            case GL_INVALID_VALUE:
                printf("Shader source error: GL_INVALID_VALUE\n");
                break;
            default:
                printf("Shader source error: Unknown error\n");
                break;
            }
        }
    }

    bool CustomGPUShader::is_compiled() const {
      return is_compiled_;
    }

    const EDK3::dev::Shader::Type CustomGPUShader::type() const {
      return type_;
    }
  

    unsigned int CustomGPUShader::internal_id() const {
      return internal_id_;
    }

    CustomGPUShader::CustomGPUShader(const CustomGPUShader& other) {
      is_compiled_ = other.is_compiled_;
      type_ = other.type_;
      internal_id_ = other.internal_id_;
    }

    CustomGPUShader& CustomGPUShader::operator=(const CustomGPUShader& other) {
      is_compiled_ = other.is_compiled_;
      type_ = other.type_;
      internal_id_ = other.internal_id_;
      return *this;
    }

    CustomGPUShader::~CustomGPUShader() {
        glDeleteShader(internal_id_);
        GLint params;
        glGetShaderiv(internal_id_, GL_DELETE_STATUS, &params);
        if (GL_TRUE != params) {
            GLenum error = glGetError();
            switch (error) {
            case GL_INVALID_VALUE:
                printf("Delete shader error: GL_INVALID_VALUE\n");
                break;
            default:
                printf("Delete shader error: Unknown error\n");
                break;
            }
        }

    }
  }
}