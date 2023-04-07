#ifndef optionMenu_h
#define optionMenu_h

#include "../Dynami_Mediator.h"

struct optionMenu {
public:
    String optionName;
    void (Dynami_Mediator::* func_ptr)();
};

#endif //optionMenu_h