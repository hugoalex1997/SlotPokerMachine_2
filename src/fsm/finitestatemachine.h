#pragma once
#ifndef _FINITESTATEMACHINE_H
#define _FINITESTATEMACHINE_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <functional>



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

		State(std::string id,std::function<void()> onEnter) : id(std::move(id)), onEnter(onEnter) {}

        std::string getId() const { return id; }
		std::function<void()> onEnter = []() {};
};

class FiniteStateMachineImplementation {

        std::vector<Transition> transitions;
        std::vector<State> states;
        std::unordered_map<std::string, Transition> trigger_map;

        State currentState;
        State previousState;

        void setCurrentState(const State &currentState_) { currentState = currentState_; }
        void setPreviousState(const State &previousState_) { previousState = previousState_; }

    
    public:

        void AddTransition(Transition transition);
        void AddTransition(std::string trigger, std::vector<std::string> from, std::string to);

        void AddState(State state);
        void AddState(std::string id);

        bool TriggerTransition(std::string trigger);

        std::string getCurrentState() const { return currentState.getId(); }
        std::string getPreviousState() const { return previousState.getId(); }

};  

class FiniteStateMachine {

        FiniteStateMachineImplementation impl;

    public:
	
        static FiniteStateMachine* Instance();

		// API to FiniteStateMachine Implementation
		
        void AddTransition(Transition transition) {impl.AddTransition(transition);};
        void AddTransition(std::string trigger, std::vector<std::string> from, std::string to) {impl.AddTransition(trigger,from,to);};

        void AddState(State state) {impl.AddState(state);};
        void AddState(std::string id) {impl.AddState(id);};

        /**
	     * @method TriggerTransition
         * 
	     * @return true - Successful transition
	     * @return false - Failed transition
	     */
        bool TriggerTransition(std::string trigger) {return impl.TriggerTransition(trigger);};

        std::string getCurrentState() const { return impl.getCurrentState();};
        std::string getPreviousState() const { return impl.getPreviousState();};

};  


#endif //_FINITESTATEMACHINE_H