#ifndef TLB_HEADER_H_
#define TLB_HEADER_H_

class CLASS
{
    private:
        TYPE NAME_;

    public:
        // constructors
        CLASS();

        // accessors
        TYPE NAME() const { return NAME_; }

        // mutators
        void NAME(TYPE NAME) { NAME_ = NAME; }

};
#endif

