#include "game_state.h"

GameState::GameState()
{
    type_ = GS_BLANK;
}

GameState::~GameState()
{

}

int GameState::init()
{
    return 0;
}

bool GameState::update(int delta_ticks)
{
    return true;
}

void GameState::render()
{

}

void GameState::end()
{

}
