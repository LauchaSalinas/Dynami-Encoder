#pragma once
#include <string>
/**
 * The Mediator interface declares a method used by components to notify the
 * mediator about various events. The Mediator may react to these events and
 * pass the execution to other components.
 */
class BaseComponent;
class Mediator {
public:
    virtual void Notify(BaseComponent* sender, std::string event){};
};