#include "game.h"
#include "platform.h"

#ifdef _ESAT_BACKEND
int esat::main(int argc, char **argv) {
#else
int main() {
#endif

  Game *game = Game::getInstance();

  game->init();
  game->mainCicle();
  game->end();

  printf("Bye!\n");
  return 0;
}
