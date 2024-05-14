/**
 *
 * @brief Custom quad source file.
 * @author Ivan Sancho, ESAT 2022-23
 * @subject Graphic Programming
 *
 */

#include "geometry_custom_obj.h"
#include "ESAT/math.h"
#include "dev/custom_gpu_manager.h"

namespace EDK3 {

    //IMPORTANT!!!
    //TODO constructors, destructor and =operator here!!!
    ObjCustom::ObjCustom() {}
    ObjCustom::~ObjCustom() {}

    void ObjCustom::render() const {
        //TODO
        EDK3::dev::GPUManager::Instance()->drawElements
        (EDK3::dev::CustomGPUManager::DrawMode::kDrawMode_Triangles, 
            0 , nullptr, EDK3::Type::T_UINT, 0);
    }

} //EDK3