#define _ESAT_BACKEND 1

#include "game.h"

#include <stdlib.h>

#include "path.h"
#include "gsprite.h"
#include "gwindow.h"
#include "interface.h"

void Game::mainCicle(){
  Game *game = Game::getInstance();
  game->window.windowInit({1280,720});

  while (game->window.isOpen() && !esat::IsSpecialKeyDown(esat::kSpecialKey_Escape)){

    game->dt =  ((float)game->last_time - (float)game->current_time) / 1000.0f;
    game->current_time = esat::Time();

    game->update();

    game->window.windowDrawBegin();

        
    game->draw();

    game->window.windowDrawEnd();

    WindowsController();
    ImGui::Render();

    game->window.windowRenderFrame();
    last_time = esat::Time();
  }
}

