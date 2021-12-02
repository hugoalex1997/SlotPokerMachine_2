#include "finitestatemachine.h"



FiniteStateMachine* FiniteStateMachine::Instance() {
    static FiniteStateMachine instance;
    return &instance;
}

void FiniteStateMachine::AddTransition(Transition transition) {
    transitions.emplace_back(transition);
    trigger_map[transition.getTrigger()] = transition;
}

void FiniteStateMachine::AddTransition(std::string trigger, std::vector<std::string> from, std::string to) {
    this->AddTransition(Transition(trigger,from,to));
}

void FiniteStateMachine::AddState(State state) {
    states.emplace_back(state);
}

void FiniteStateMachine::AddState(std::string id) {
    this->AddState(State(id));
}


bool FiniteStateMachine::TriggerTransition(std::string trigger) {
    auto _elem = trigger_map.find(trigger);

    if(_elem == trigger_map.end()) {
        std::cout<< "Unknown transition" << std::endl;
    }

    auto _transition = _elem->second;
    auto _from = _transition.getFrom();
    for(int i=0; i<_from.size();i++) {
        if(_from[i] == currentState.getId()) {
            //TODO: Add transition logic
            //TODO: Add debug logic
            std::cout<< "TriggerTransition Available" << std::endl;
            return true;
        }
    }
    return false;
} 




