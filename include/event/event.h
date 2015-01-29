#ifndef TLB_EVENT_EVENT_H_
#define TLB_EVENT_EVENT_H_

enum EventType {
    EVENT_MOUSE_RCLICK,
    EVENT_MOUSE_LCLICK,
    EVENT_BLANK
};


class Event
{
    private:
        EventType type_;
    public:
        Event();
        ~Event();

        // accessors
        EventType type() const { return type_; }

};

#endif
