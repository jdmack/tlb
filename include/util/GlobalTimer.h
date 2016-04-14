#ifndef TLB_GLOBAL_TIMER_H_
#define TLB_GLOBAL_TIMER_H_

class GlobalTimer
{
    private:
        int startTicks_;
        int pausedTicks_;
        bool paused_;
        bool started_;
        static GlobalTimer * instance_;

        GlobalTimer();
        ~GlobalTimer();


    public:
        GlobalTimer(const GlobalTimer &) = delete;
        GlobalTimer& operator=(const GlobalTimer &) = delete;
        static GlobalTimer * instance();

        void start();
        void stop();
        void pause();
        void unpause();
        void togglePause();
        int getTicks();

        // accessors
        bool started() const { return started_; }
        bool paused() const { return paused_; }
};

#endif
