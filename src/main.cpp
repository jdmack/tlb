#include "tlb_game.h"

int main(int argc, char* argv[])
{
  int exit_code = 0;

  // TODO(2013-08-23 JM): Create logger

  TlbGame * game = new TlbGame;

  game->process_arguments(argc, argv);

  exit_code = game->run();

  delete game;
  game = nullptr;

  return exit_code;
}
