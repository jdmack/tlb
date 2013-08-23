#ifndef TEITRUS_SCORE_H_
#define TEITRUS_SCORE_H_

// Constants
const float kScoreXPosition = 540;
const float kScoreYPosition = 192;

class Score
{
    private:
        int value;

    public:
        float x_position_, y_position_;
        Score();
        void increment(int);
        void show();
};

#endif
