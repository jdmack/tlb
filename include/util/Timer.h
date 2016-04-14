#ifndef TLB_TIMER_H_
#define TLB_TIMER_H_

class Timer
{
    private:
        int startTicks_;
        int pausedTicks_;
        bool paused_;
        bool started_;

    public:
        Timer();

        void start();
        void stop();
        void pause();
        void unpause();
        int getTicks();

        // accessors
        bool started() const { return started_; }
        bool paused() const { return paused_; }
};

#endif
