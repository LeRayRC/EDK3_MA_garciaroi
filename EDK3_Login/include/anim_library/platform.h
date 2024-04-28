/**
 * @file path.h
 * @author Carlos García
 * @brief Header file that general platform includes
 */
#ifndef _PLATFORM_H_
#define _PLATFORM_H_

// #define _ESAT_BACKEND 1
// #define _SFML_BACKEND 1

#ifdef _ESAT_BACKEND

#include "esat/window.h"
#include "esat/draw.h"
#include "esat/sprite.h"
#include "esat/input.h"
#include "esat/time.h"
#include "esat_extra/imgui.h"
#include "esat/helpers.h"

typedef esat::SpriteHandle Handle;
typedef void* WindowRenderer;

#else 

#include "SFML/Graphics.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

typedef sf::Texture* Handle;
typedef sf::RenderWindow* WindowRenderer;

#endif

#endif