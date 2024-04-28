#define _ESAT_BACKEND 1

#include "interface.h"

#include "game.h"
#include "math_lib/vector_2.h"

void ImageFromTexture(Handle handle){

    ImGui::ImageFromSpriteHandle(handle,
                                ImVec2((float)esat::SpriteWidth(handle),(float)esat::SpriteHeight(handle)));
}

