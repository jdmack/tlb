#ifndef TLB_EVENT_EVENT_DISPATCHER_H_
#define TLB_EVENT_EVENT_DISPATCHER_H_

class EventHandler;

class EventDispatcher
{

    private:
        EventDispatcher(void) : device_list_(0) {;}
        ~EventDispatcher(void) {;}

        static EventDispatcher * instance_;

        EventHandler * device_list_;

    public:
        static EventDispatcher * instance();

        void register_handler(EventHandler * device);

        void send_event(int event_tyep, int arg1 = 0, int arg2 = 0);

};

#endif
