#include "dev/custom_gpu_manager.h"
#include "dev/custom_gpu_shader.h"
#include "dev/custom_gpu_program.h"
#include "dev/custom_gpu_buffer.h"
#include "dev/custom_gpu_texture.h"
#include "EDK3/dev/glew.h"

namespace EDK3{


  namespace dev {

    void CustomGPUManager::newShader(EDK3::ref_ptr<EDK3::dev::Shader>* output) {
      output->allocT<CustomGPUShader>();
    }

    void CustomGPUManager::newProgram(EDK3::ref_ptr<EDK3::dev::Program>* output) {
      output->allocT<CustomGPUProgram>();
    }
    void CustomGPUManager::newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output) {
      output->allocT<CustomGPUBuffer>();
    }
    void CustomGPUManager::newTexture1D(const Texture::Format internal_format,
      const unsigned int size,
      EDK3::ref_ptr<Texture>* output){
      output->allocT<CustomGPUTexture>()->init(
        EDK3::Texture::Type::T_1D,
        internal_format,
        size, 1, 1
      );
      
    }
    void CustomGPUManager::newTexture2D(const Texture::Format internal_format,
      const unsigned int width, const unsigned int height,
      EDK3::ref_ptr<Texture>* output){
    
      output->allocT<CustomGPUTexture>()->init(
        EDK3::Texture::Type::T_2D,
        internal_format,
        width, height, 1
      );
    }
    void CustomGPUManager::newTexture3D(const Texture::Format internal_format,
      const unsigned int width, const unsigned int height,
      const unsigned int depth,
      EDK3::ref_ptr<Texture>* output){
    
      output->allocT<CustomGPUTexture>()->init(
        EDK3::Texture::Type::T_3D,
        internal_format,
        width, height, depth
      );
    }
    
    void CustomGPUManager::enableDepthTest(const CompareFunc f) {
        glEnable(GL_DEPTH_TEST);
        switch (f) {
        case kCompareFunc_Never:
            glDepthFunc(GL_NEVER);
            break;
        case kCompareFunc_Less:
            glDepthFunc(GL_LESS);
            break;
        case kCompareFunc_LessOrEqual:
            glDepthFunc(GL_LEQUAL);
            break;
        case kCompareFunc_Equal:
            glDepthFunc(GL_EQUAL);
            break;
        case kCompareFunc_NotEqual:
            glDepthFunc(GL_NOTEQUAL);
            break;
        case kCompareFunc_GreaterOrEqual:
            glDepthFunc(GL_GEQUAL);
            break;
        case kCompareFunc_Greater:
            glDepthFunc(GL_GREATER);
            break;
        case kCompareFunc_Always:
            glDepthFunc(GL_ALWAYS);
            break;
        }

    }
    void CustomGPUManager::disableDepthTest() {
        glDisable(GL_DEPTH_TEST);
    }

    void CustomGPUManager::clearFrameBuffer(const float rgba[4],
        const unsigned int FrameBufferOrMask) {
        glClearColor(rgba[0], rgba[1], rgba[2], rgba[3]);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClear(FrameBufferOrMask);
    }

    void CustomGPUManager::enableCullFaces(const FaceType f) {
        glEnable(GL_CULL_FACE);
        switch (f)
        {
        case FaceType::kFace_Back:
            glCullFace(GL_BACK);
            break;
        case FaceType::kFace_Front:
            glCullFace(GL_FRONT);
            break;
        case FaceType::kFace_FrontAndBack:
            glCullFace(GL_FRONT_AND_BACK);
            break;
        }
        assert(glGetError() == GL_NO_ERROR);
    }
    void CustomGPUManager::disableCullFaces() {
        glDisable(GL_CULL_FACE);
        assert(glGetError() == GL_NO_ERROR);
    }

    void CustomGPUManager::enableScissor(int x, int y,
        unsigned int width,
        unsigned int height) {
        glEnable(GL_SCISSOR_TEST);
        glScissor(x, y, width, height);


    }
    void CustomGPUManager::disableScissor() {
        glDisable(GL_SCISSOR_TEST);
    }
    
    
    void CustomGPUManager::enableVertexAttribute(const EDK3::dev::Buffer* buffer,
      const unsigned int attribute_index,
      const EDK3::Type type,
      const bool normalized,
      const unsigned int offset,
      const unsigned int stride) {
        buffer->bind(EDK3::dev::Buffer::Target::kTarget_Vertex_Data);

        GLenum t = GL_BYTE;
        GLint size = 1;
        switch (type)
        {
            case EDK3::Type::T_BYTE_2:
                t = GL_BYTE;
                size = 2;
                break;
            case EDK3::Type::T_BYTE_3:
                t = GL_BYTE;
                size = 3;
                break;
            case EDK3::Type::T_BYTE_4:
                t = GL_BYTE;
                size = 4;
                break;
            case EDK3::Type::T_UBYTE:
                t = GL_UNSIGNED_BYTE;
                size = 1;
                break;
            case EDK3::Type::T_UBYTE_2:
                t = GL_UNSIGNED_BYTE;
                size = 2;
                break;
            case EDK3::Type::T_UBYTE_3:
                t = GL_UNSIGNED_BYTE;
                size = 3;
                break;
            case EDK3::Type::T_UBYTE_4:
                t = GL_UNSIGNED_BYTE;
                size = 4;
                break;
            case EDK3::Type::T_SHORT:
                t = GL_SHORT;
                size = 2;
                break;
            case EDK3::Type::T_SHORT_2:
                t = GL_SHORT;
                size = 3;
                break;
            case EDK3::Type::T_SHORT_3:
                t = GL_SHORT;
                size = 4;
                break;
            case EDK3::Type::T_SHORT_4:
                t = GL_SHORT;
                size = 1;
                break;
            case EDK3::Type::T_USHORT:
                t = GL_UNSIGNED_SHORT;
                size = 1;
                break;
            case EDK3::Type::T_USHORT_2:
                t = GL_UNSIGNED_SHORT;
                size = 2;
                break;
            case EDK3::Type::T_USHORT_3:
                t = GL_UNSIGNED_SHORT;
                size = 3;
                break;
            case EDK3::Type::T_USHORT_4:
                t = GL_UNSIGNED_SHORT;
                size = 4;
                break;
            case EDK3::Type::T_INT:
                t = GL_INT;
                size = 1;
                break;
            case EDK3::Type::T_INT_2:
                t = GL_INT;
                size = 2;
                break;
            case EDK3::Type::T_INT_3:
                t = GL_INT;
                size = 3;
                break;
            case EDK3::Type::T_INT_4:
                t = GL_INT;
                size = 4;
                break;
            case EDK3::Type::T_UINT:
                t = GL_UNSIGNED_INT;
                size = 1;
                break;
            case EDK3::Type::T_UINT_2:
                t = GL_UNSIGNED_INT;
                size = 2;
                break;
            case EDK3::Type::T_UINT_3:
                t = GL_UNSIGNED_INT;
                size = 3;
                break;
            case EDK3::Type::T_UINT_4:
                t = GL_UNSIGNED_INT;
                size = 4;
                break;
            case EDK3::Type::T_FLOAT:
                t = GL_FLOAT;
                size = 1;
                break;
            case EDK3::Type::T_FLOAT_2:
                t = GL_FLOAT;
                size = 2;
                break;
            case EDK3::Type::T_FLOAT_3:
                t = GL_FLOAT;
                size = 3;
                break;
            case EDK3::Type::T_FLOAT_4:
                t = GL_FLOAT;
                size = 4;
                break;
        }

        glVertexAttribPointer(attribute_index, size, t, normalized, stride, (GLvoid*)offset);
        glEnableVertexAttribArray(attribute_index);
    }

    void CustomGPUManager::disableVertexAttribute(const unsigned int attrib_index) {
        glDisableVertexAttribArray(attrib_index);
    }
    

    void CustomGPUManager::drawElements(const DrawMode mode,
      unsigned int count,
      const EDK3::dev::Buffer* buffer,
      const EDK3::Type element_type,
      const unsigned int offset) const {

      GLenum m = GL_TRIANGLES;
      switch (draw_mode_){
        case DrawMode::kDrawMode_TriangleStrip:
          m = GL_TRIANGLE_STRIP;
          break;
        case DrawMode::kDrawMode_Points:
          m = GL_POINTS;
          break;
        case DrawMode::kDrawMode_LineStrip:
          m = GL_LINE_STRIP;
          break;
        case DrawMode::kDrawMode_Lines:
          m = GL_LINES;
          break;
        case DrawMode::kDrawMode_LineLoop:
          m = GL_LINE_LOOP;
          break;
      }
      GLenum t = GL_UNSIGNED_BYTE;
      switch (element_type){
        case EDK3::Type::T_USHORT:
          t = GL_UNSIGNED_SHORT;
          break;
        case EDK3::Type::T_UINT:
          t = GL_UNSIGNED_INT;
          break;
      }
      buffer->bind(EDK3::dev::Buffer::Target::kTarget_Elements);
      glDrawElements(m, count, t, (GLvoid*)offset);
    }

  }
}