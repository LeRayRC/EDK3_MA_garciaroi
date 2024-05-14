/**
 *
 * @brief Custom cube header file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */


#ifndef __GEOMETRY_CUSTOM_OBJ_H__
#define __GEOMETRY_CUSTOM_OBJ_H__ 1

#include "EDK3/geometry.h"
#include "EDK3/dev/buffer.h"

namespace EDK3 {

class ObjCustom : public EDK3::Geometry {
 public:
  ObjCustom();

  virtual void render() const override;

 protected:
  virtual ~ObjCustom();

 private:
  ObjCustom(const ObjCustom&);
  ObjCustom& operator=(const ObjCustom&);
};

} //EDK3

#endif //__GEOMETRY_CUSTOM_CUBE_H__
