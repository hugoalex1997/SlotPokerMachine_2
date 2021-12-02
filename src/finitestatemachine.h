#pragma once
#ifndef _FiniteStateMachine_H
#define _FiniteStateMachine_H

#include <iostream>
#include <vector>
#include <unordered_map>



class Transition {
    std::string trigger;
	std::vector<std::string> from;
	std::string to;

    public:

    /**
	 * @brief Construct a new transition object
	 *
	 */
	Transition() = default;

    /**
	 * @brief Construct a new transition object
	 *
	 * @param trigger - Transition trigger to be created
	 * @param from - Transition origin state to be created
	 * @param to - Transition destiny state to be created
	 */
    Transition(std::string trigger, std::vector<std::string> from, std::string to) :
        trigger(std::move(trigger)),
        from(std::move(from)),
        to(std::move(to)) {}

    std::string getTrigger() const { return trigger; }

    std::vector<std::string> getFrom() const { return from; }

    std::string getTo() const { return to; }


    
};

class State {
    std::string id;
    public:

    /**
	 * @brief Construct a new state object
	 *
	 */
	State() = default;

    /**
	 * @brief Construct a new state object
	 *
	 * @param id - State id to be created
	 */
    State(std::string id) : id(std::move(id)) {}

    std::string getId() const { return id; }
};

class FiniteStateMachine {

    std::vector<Transition> transitions;
    std::vector<State> states;
    std::unordered_map<std::string, Transition> trigger_map;
    
    State currentState {nullptr};
    State previousState {nullptr};

    
    public:
    
    static FiniteStateMachine* Instance();

    void AddTransition(Transition transition);
    void AddTransition(std::string trigger, std::vector<std::string> from, std::string to);

    void AddState(State state);
    void AddState(std::string id);

    /**
	 * @brief Receives a transition trigger, and validates if the transition can happen
	 *
	 * @param trigger - transition trigger
	 * @return true - if the transition happened
	 * @return false - if the transition failed
	 */
    bool TriggerTransition(std::string trigger);

    
};


#endif //_FiniteStateMachine_H