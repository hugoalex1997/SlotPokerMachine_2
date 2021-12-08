#include "finitestatemachine.h"



FiniteStateMachine* FiniteStateMachine::Instance() {
    static FiniteStateMachine instance;
    return &instance;
}

void FiniteStateMachineImplementation::AddTransition(Transition transition) {
    transitions.emplace_back(transition);
    trigger_map[transition.getTrigger()] = transition;
}

void FiniteStateMachineImplementation::AddTransition(std::string trigger, std::vector<std::string> from, std::string to) {
    this->AddTransition(Transition(trigger,from,to));
}

void FiniteStateMachineImplementation::AddState(State state) {
    states.emplace_back(state);
}

void FiniteStateMachineImplementation::AddState(std::string id) {
    this->AddState(State(id));
}


bool FiniteStateMachineImplementation::TriggerTransition(std::string trigger) {
    auto _elem = trigger_map.find(trigger);

    if(_elem == trigger_map.end()) {
        std::cout<< "Warning: Unknown transition" << std::endl;
        return false;
    }

    auto _transition = _elem->second;
    auto _from = _transition.getFrom();
    for(int i=0; i<_from.size();i++) {
        if(_from[i] == currentState.getId()) {
            setPreviousState(currentState.getId());
            setCurrentState(_transition.getTo());
            std::cout << "Trigger '" << _transition.getTrigger() << "' from '" 
                        << previousState.getId() << "' to '" 
                        << _transition.getTo() << "'" << std::endl;
            return true;
        }
    }
    return false;
} 




