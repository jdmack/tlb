#ifndef TLB_GLOBAL_TIMER_H_
#define TLB_GLOBAL_TIMER_H_

class GlobalTimer
{
    private:
        int start_ticks_;
        int paused_ticks_;
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
        void toggle_pause();
        int get_ticks();

        // accessors
        bool started() const { return started_; }
        bool paused() const { return paused_; }
};

#endif
