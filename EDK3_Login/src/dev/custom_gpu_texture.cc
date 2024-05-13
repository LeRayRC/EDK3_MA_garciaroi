#include "dev/custom_gpu_texture.h"
#include "EDK3/dev/opengl.h"
#include <stdio.h>

namespace EDK3 {

  CustomGPUTexture::CustomGPUTexture() {}

  void CustomGPUTexture::init(Type t, Format internal_format, unsigned int width,
    unsigned int height, unsigned int depth) {
    //Llamar a la textura base para que la informacion se vaya guardando
    Texture::init(t, internal_format, width, height, depth);
      internal_id_ = 0;
  }

  GLenum CustomGPUTexture::getOpenGLDataPixelType(EDK3::Type t) {
    GLenum datatype = GL_UNSIGNED_BYTE;
    switch (t) {
    case EDK3::Type::T_UBYTE:
      datatype = GL_UNSIGNED_BYTE;
      break;
    case EDK3::Type::T_BYTE:
      datatype = GL_BYTE;
      break;
    case EDK3::Type::T_USHORT:
      datatype = GL_UNSIGNED_SHORT;
      break;
    case EDK3::Type::T_SHORT:
      datatype = GL_SHORT;
      break;
    case EDK3::Type::T_UINT:
      datatype = GL_UNSIGNED_INT;
      break;
    case EDK3::Type::T_INT:
      datatype = GL_INT;
      break;
    case EDK3::Type::T_FLOAT:
      datatype = GL_FLOAT;
      break;
    default:
      printf("Data type not found");
      break;
    }
    return datatype;
  }

  GLint CustomGPUTexture::getOpenGLFormat(Format f) {
    GLint format = GL_RED;
    switch (f) {
    case EDK3::Texture::Format::F_RG:
      format = GL_RG;
        break;
      case EDK3::Texture::Format::F_RGB:
        format = GL_RGB;
        break;
      case EDK3::Texture::Format::F_BGR:
        format = GL_BGR;
        break;
      case EDK3::Texture::Format::F_BGRA:
        format = GL_BGRA;
        break;
      case EDK3::Texture::Format::F_RGBA:
        format = GL_RGBA;
        break;
      case EDK3::Texture::Format::F_DEPTH32:
        format = GL_DEPTH_COMPONENT32;
        break;
      case EDK3::Texture::Format::F_DEPTH:
        format = GL_DEPTH_COMPONENT;
        break;
    }
    return format;
  }

  void CustomGPUTexture::set_data(const Format f,
    const EDK3::Type t,
    const void* data,
    unsigned int mipmap_LOD) {
    GLenum error;
    glGenTextures(1, &internal_id_);

    GLenum target = getTextureTarget();
    GLenum pixel_type = getOpenGLDataPixelType(t);
    GLint  internal_format = getOpenGLFormat(format());
    GLenum external_format = getOpenGLFormat(f);

    glBindTexture(target, internal_id_);

    switch (type())
    {
    case EDK3::Texture::Type::T_1D:
      glTexImage1D(target, mipmap_LOD, internal_format, width(), 0, external_format, pixel_type, data);
      break;
    case EDK3::Texture::Type::T_2D:
      glTexImage2D(target, mipmap_LOD, internal_format, width(), height(), 0, external_format, pixel_type, data);
      break;
    case EDK3::Texture::Type::T_3D:
      glTexImage3D(target, mipmap_LOD, internal_format, width(), height(), depth(), 0, external_format, pixel_type, data);
      break;
    default:
      printf("Invalid type");
      break;
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_UNPACK_LSB_FIRST, 1);
    generateMipmaps();
    set_wrap(EDK3::Texture::Wrap::W_REPEAT);
    set_min_filter(EDK3::Texture::Filter::F_LINEAR);
    set_mag_filter(EDK3::Texture::Filter::F_LINEAR);
    assert(glGetError() == GL_NO_ERROR);
  }

  void CustomGPUTexture::bind(unsigned int textUnit) const {
    GLenum target = getTextureTarget();
    glActiveTexture(GL_TEXTURE0 + textUnit);
    glBindTexture(target, internal_id_);
    assert(glGetError() == GL_NO_ERROR);
  }

  unsigned int CustomGPUTexture::internal_id() const {
    return internal_id_;
  }

  void CustomGPUTexture::set_min_filter(Filter f) {
    Texture::set_min_filter(f);
    GLenum target = getTextureTarget();
    GLenum filter_type = GL_NEAREST;
    switch (f)
    {
    case EDK3::Texture::F_LINEAR:
      filter_type = GL_LINEAR;
      break;
    case EDK3::Texture::F_NEAREST_MIPMAP_NEAREST:
      filter_type = GL_NEAREST_MIPMAP_NEAREST;
      break;
    case EDK3::Texture::F_LINEAR_MIPMAP_NEAREST:
      filter_type = GL_LINEAR_MIPMAP_NEAREST;
      break;
    case EDK3::Texture::F_NEAREST_MIPMAP_LINEAR:
      filter_type = GL_NEAREST_MIPMAP_LINEAR;
      break;
    case EDK3::Texture::F_LINEAR_MIPMAP_LINEAR:
      filter_type = GL_LINEAR_MIPMAP_LINEAR;
      break;
    }
    glBindTexture(target, internal_id_);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter_type);
    assert(glGetError() == GL_NO_ERROR);
  }
  void CustomGPUTexture::set_mag_filter(Filter f) {
    Texture::set_mag_filter(f);
    GLenum target = getTextureTarget();
    GLenum filter_type = GL_NEAREST;
    switch (f) {
      case EDK3::Texture::F_LINEAR:
        filter_type = GL_LINEAR;
        break;
    }
    glBindTexture(target, internal_id_);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter_type);
    assert(glGetError() == GL_NO_ERROR);
  }
  void CustomGPUTexture::set_wrap_s(Wrap c) {
    Texture::set_wrap_s(c);
    GLenum target = getTextureTarget();
    GLenum wrap_type = getOpenGLWrappingType(c);

    glBindTexture(target, internal_id_);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap_type);
    assert(glGetError() == GL_NO_ERROR);
  }
  void CustomGPUTexture::set_wrap_t(Wrap c) {
    Texture::set_wrap_t(c);
    GLenum target = getTextureTarget();
    GLenum wrap_type = getOpenGLWrappingType(c);

    glBindTexture(target, internal_id_);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap_type);
    assert(glGetError() == GL_NO_ERROR);
  }
  void CustomGPUTexture::set_wrap_r(Wrap c) {
    Texture::set_wrap_r(c);
    GLenum target = getTextureTarget();
    GLenum wrap_type = getOpenGLWrappingType(c);

    glBindTexture(target, internal_id_);
    glTexParameteri(target, GL_TEXTURE_WRAP_R, wrap_type);
    assert(glGetError() == GL_NO_ERROR);
  }
  void CustomGPUTexture::generateMipmaps() const {
    GLenum target = getTextureTarget();
    glBindTexture(target, internal_id_);
    glGenerateMipmap(target);
    assert(glGetError() == GL_NO_ERROR);
  }

  CustomGPUTexture::~CustomGPUTexture() {
    //glDeleteTextures(1, &internal_id_);
    //glDeleteTextures
  }

  GLenum CustomGPUTexture::getTextureTarget() const {
    GLenum target = GL_TEXTURE_2D;
    switch (type())
    {
    case Type::T_1D:
      target = GL_TEXTURE_1D;
      break;
    case Type::T_3D:
      target = GL_TEXTURE_3D;
      break;
    case Type::T_CUBEMAP:
      target = GL_TEXTURE_CUBE_MAP;
      break;
    }
    return target;
  }

  GLenum CustomGPUTexture::getOpenGLWrappingType(Wrap c) {
    GLenum wrap_type = GL_REPEAT;
    switch (c)
    {
      case W_MIRRORED_REPEAT:
        wrap_type =  GL_MIRRORED_REPEAT;
        break;
      case W_CLAMP_TO_EDGE:
        wrap_type = GL_CLAMP_TO_EDGE;
        break;
    }
    return wrap_type;
  }




  CustomGPUTexture::CustomGPUTexture(const CustomGPUTexture& other) {
    internal_id_ = other.internal_id_;
  }
  CustomGPUTexture& CustomGPUTexture::operator=(const CustomGPUTexture& other) {
    internal_id_ = other.internal_id_;
    return *this;
  }
}