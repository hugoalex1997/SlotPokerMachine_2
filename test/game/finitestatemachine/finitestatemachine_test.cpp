#include "fsm/finitestatemachine.h"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

struct MockFiniteStateMachine : public FiniteStateMachineImplementation {
	MockFiniteStateMachine() {};
};

TEST(FiniteStateMachine, FiniteStateMachineInitialization) {
	auto fsm = new MockFiniteStateMachine();
	// std::cout << &fsm << std::endl;
	ASSERT_EQ(fsm->getCurrentState(), "");
}

TEST(FiniteStateMachine, FiniteStateMachineTrigger) {
	auto fsm = new MockFiniteStateMachine();
	// std::cout << &fsm << std::endl;
	fsm->AddState("idle");
	fsm->AddTransition("loaded", std::vector<std::string>{""}, "idle");
	fsm->TriggerTransition("loaded");
	ASSERT_EQ(fsm->getCurrentState(), "idle");
	ASSERT_EQ(fsm->getPreviousState(), "");
}
