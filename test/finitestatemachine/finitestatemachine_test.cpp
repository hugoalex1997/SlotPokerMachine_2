#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "fsm/finitestatemachine.h"

struct MockFiniteStateMachine : public FiniteStateMachineImplementation {
    MockFiniteStateMachine() {};
};

TEST(FiniteStateMachine,FiniteStateMachineInitialization) {

    auto fsm = new MockFiniteStateMachine();
    ASSERT_EQ(fsm->getCurrentState(),"");  
}

TEST(FiniteStateMachine,FiniteStateMachineTrigger) {

    auto fsm = new MockFiniteStateMachine();
    fsm->AddState("idle");
    fsm->AddTransition("loaded",std::vector<std::string> {""},"idle");
    fsm->TriggerTransition("loaded");
    ASSERT_EQ(fsm->getCurrentState(),"idle");
    ASSERT_EQ(fsm->getPreviousState(),"");    
}
