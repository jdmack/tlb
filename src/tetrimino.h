// Tetrimino like tetris and domino
#include <string>
#include "timer.h"

#ifndef TEITRUS_TETRIMINO_H_
#define TEITRUS_TETRIMINO_H_

const int kBlockWidth    = 50;
const int kBlockHeight   = 50;
const int kNumberOfTetroTypes = 7;
const int kTetroI = 0;
const int kTetroJ = 1;
const int kTetroL = 2;
const int kTetroO = 3;
const int kTetroS = 4;
const int kTetroT = 5;
const int kTetroZ = 6;
const int kTetroDescentRate = 1000;     // Number of millisecs per block descent
const int kBlocksPerDescent = 1;

class Tetrimino
{
    private:
        bool active_;
        int type_;
        float x_position_, y_position_;
        float rotation_;
        std::string art_asset_;
        SDL_Surface * surface_;
        Timer descent_delta_;

    public:

        Tetrimino();
        ~Tetrimino();
        void descend();
        void move(int);
        void show(SDL_Surface *);
        void rotate(int, int);

};

#endif
