#include "gtest/gtest.h"
#include "finitestatemachine.h"

class FiniteStateMachineTest : public FiniteStateMachineImplementation {
    
    public:
    FiniteStateMachineTest() {};
};

TEST(FiniteStateMachine,FiniteStateMachineInitialization) {

    auto fsm = new FiniteStateMachineTest();
    ASSERT_EQ(fsm->getCurrentState(),"");  
}

TEST(FiniteStateMachine,FiniteStateMachineTrigger) {

    auto fsm = new FiniteStateMachineTest();
    fsm->AddState("idle");
    fsm->AddTransition("loaded",std::vector<std::string> {""},"idle");
    fsm->TriggerTransition("loaded");
    ASSERT_EQ(fsm->getCurrentState(),"idle");
    ASSERT_EQ(fsm->getPreviousState(),"");    
}
