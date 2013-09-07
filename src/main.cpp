#include "constants.h"
#include "game.h"
#include "utils/logger.h"

int main(int argc, char* argv[])
{
    Logger::open(kLogFilename);
    Logger::write("Initializing game");

    int exit_code = 0;

    Game * game = new Game;

    game->process_arguments(argc, argv);
    exit_code = game->run();

    delete game;
    game = nullptr;

    return exit_code;
}
