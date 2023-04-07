#pragma once

class Mediator;

/**
 * The Base Component provides the basic functionality of storing a mediator's
 * instance inside component objects.
 */
class BaseComponent {
protected:
    Mediator* dynamiMediator;

public:
    BaseComponent(Mediator* mediator = nullptr) : dynamiMediator(mediator) {
    }
    void set_mediator(Mediator* mediator) {
        this->dynamiMediator = mediator;
    }
};