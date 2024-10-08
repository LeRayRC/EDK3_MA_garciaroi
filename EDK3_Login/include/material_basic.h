/**
 *
 * @brief Basic material header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __MATERIAL_BASIC_H__
#define __MATERIAL_BASIC_H__ 1

#include "ESAT/math.h"
#include "EDK3/ref_ptr.h"
#include "EDK3/material.h"
#include "EDK3/materialsettings.h"
#include "EDK3/dev/program.h"
#include "EDK3/dev/shader.h"
#include "EDK3/texture.h"


namespace EDK3 {

class MaterialBasic : public EDK3::Material {
 public:
  MaterialBasic();
  void init(EDK3::scoped_array<char>& error_log);

  //Indica el uso del material, se llamara frame a frame cada que queramos pintar algo
  virtual bool enable(const EDK3::MaterialSettings *mat) const override;
  virtual void setupCamera(const float projection[16], const float view[16]) const override;
  virtual void setupModel(const float model[16]) const override;

  virtual unsigned int num_attributes_required() const; //Devolver un 3 de momento
  virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const; 
  virtual EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const;


  class MaterialBasicSettings : public EDK3::MaterialSettings {
   public:
    MaterialBasicSettings() {
      memset(color_, 0, sizeof(color_));
    }
    void set_color(const float v[4]) { memcpy(color_, v, sizeof(color_)); }
    const float* color() const { return color_; }
   protected:
    virtual ~MaterialBasicSettings() {}
   private:
    MaterialBasicSettings(const MaterialBasicSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
    }
    MaterialBasicSettings(MaterialBasicSettings&& other) {
      memcpy(color_, other.color_, sizeof(color_));
      memset(other.color_, 0, sizeof(color_));
    }
    MaterialBasicSettings& operator=(const MaterialBasicSettings& other) {
      memcpy(color_, other.color_, sizeof(color_));
      return *this;
    }
    float color_[4];
  }; //MaterialBasicSettings

  class MaterialBasicTextureSettings : public EDK3::MaterialSettings {
  public:
      MaterialBasicTextureSettings() {
          memset(color_, 0, sizeof(color_));
      }
      void set_color(const float v[4]) { memcpy(color_, v, sizeof(color_)); }
      const float* color() const { return color_; }
      void set_texture(EDK3::ref_ptr<EDK3::Texture> t, const int i) { texture_[i] = t; }
      EDK3::ref_ptr<EDK3::Texture> texture(const int i) const { return texture_[i]; }
  protected:
      virtual ~MaterialBasicTextureSettings() {}
  private:
      MaterialBasicTextureSettings(const MaterialBasicTextureSettings& other) {
          memcpy(color_, other.color_, sizeof(color_));
          texture_[0] = other.texture_[0];
          texture_[1] = other.texture_[1];
      }
      MaterialBasicTextureSettings(MaterialBasicTextureSettings&& other) {
          memcpy(color_, other.color_, sizeof(color_));
          memset(other.color_, 0, sizeof(color_));
          texture_[0] = other.texture_[0];
          texture_[1] = other.texture_[1];
          other.texture_[0].release();
          other.texture_[1].release();
      }
      MaterialBasicTextureSettings& operator=(const MaterialBasicTextureSettings& other) {
          memcpy(color_, other.color_, sizeof(color_));
          texture_[0] = other.texture_[0];
          texture_[1] = other.texture_[1];
          return *this;
      }
      float color_[4];
      EDK3::ref_ptr<EDK3::Texture> texture_[2];
  }; //MaterialBasicTextureSettings


 protected:
  virtual ~MaterialBasic();

 private:
  EDK3::ref_ptr<EDK3::dev::Program> program_;
  
  MaterialBasic(const MaterialBasic&);
  //MaterialBasic(MaterialBasic&&);
  MaterialBasic& operator=(const MaterialBasic&);
};

} //EDK3

#endif //__MATERIAL_BASIC_H__
