#ifndef Dynami_Timer_h
#define Dynami_Timer_h

class Dynami_Timer
{
public:
    Dynami_Timer(const unsigned int frecuency)
    {
        this->timeout_frecuency_ = frecuency;
        next_update_ = millis() + frecuency;
    }

    bool TimeoutCheck()
    {
        if (millis() > next_update_)
        {
            next_update_ = millis() + timeout_frecuency_;
            return true;
        }
        return false;
    }
private:
    unsigned int timeout_frecuency_;
    unsigned long next_update_;
};

#endif