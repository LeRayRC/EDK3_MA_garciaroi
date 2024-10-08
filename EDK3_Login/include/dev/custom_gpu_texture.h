/**
 *
 * @brief Custom GPU texture header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 * Check the following OpenGL functions:
 *   glActiveTexture
 *   glBindTexture
 *   glGenerateMipmap
 *   glBindTexture
 *   glPixelStorei(GL_UNPACK_ALIGNMENT, GL_UNPACK_LSB_FIRST)
 *   glGenTextures
 *   glDeleteTextures
 *   glTexImage(1D, 2D, 3D)
 *   glTexParameteri(GL_TEXTURE_MIN_FILTER, GL_TEXTURE_MAG_FILTER, 
 *                   GL_TEXTURE_WRAP_S, GL_TEXTURE_WRAP_R, 
 *                   GL_TEXTURE_WRAP_S)
 *
 */

#ifndef __CUSTOM_GPU_TEXTURE_H__
#define __CUSTOM_GPU_TEXTURE_H__ 1

#include "EDK3/ref_ptr.h"
#include "EDK3/texture.h"

typedef unsigned int GLuint;
typedef unsigned int GLenum;
typedef int GLint;

namespace EDK3 {

class CustomGPUTexture : public EDK3::Texture {
 public:
  CustomGPUTexture();

  void init(Type t, Format internal_format, unsigned int width,
            unsigned int height, unsigned int depth);

  virtual void set_data(const Format f, 
                        const EDK3::Type t, 
                        const void* data, 
                        unsigned int mipmap_LOD = 0) override;

  virtual void bind(unsigned int textUnit) const override;
  virtual unsigned int internal_id() const override;

  virtual void set_min_filter(Filter f) override;
  virtual void set_mag_filter(Filter f) override;
  virtual void set_wrap_s(Wrap c) override;
  virtual void set_wrap_t(Wrap c) override;
  virtual void set_wrap_r(Wrap c) override;
  virtual void generateMipmaps() const override;

  GLenum getTextureTarget() const;
  GLenum getOpenGLWrappingType(Wrap c);
  GLenum getOpenGLDataPixelType(EDK3::Type t);
  GLint getOpenGLFormat(Format f);
 protected:
  virtual ~CustomGPUTexture();

  GLuint internal_id_;

 private:
  CustomGPUTexture(const CustomGPUTexture&);
  CustomGPUTexture& operator=(const CustomGPUTexture&);

}; //CustomGPUTexture

} //EDK3

#endif //__CUSTOM_GPU_TEXTURE_H__
