#include "constants.h"
#include "game.h"
#include "util/logger.h"

int main(int argc, char* argv[])
{
    Logger::open(kLogFilename);
    Logger::write("Initializing game");

    int exitCode = 0;

    Game * game = Game::instance();

    game->processArguments(argc, argv);
    exitCode = game->run();

    delete game;
    game = nullptr;

    return exitCode;
}
