#include "game.h"
#include <iostream>

void Game::Run() {
  std::cout << " Start Game Loading" << std::endl;

  /*
  TODO:
          - Restore, Pause and Unpause, Admin
          - Possibility to be triggered from AnyState functionality
  */
  CreateFSM({State("loading"), State("idle"), State("draw"),
             State("prizeAnimation"), State("endPlay"), State("pause"),
             State("admin")},
            {
                Transition("loaded", std::vector<std::string>{""}, "idle"),
                Transition("startDraw",
                           std::vector<std::string>{"idle", "endPlay"}, "draw"),
                Transition("prizeAnimate", std::vector<std::string>{"draw"},
                           "prizeAnimation"),
                Transition("finishPrizeAnimation",
                           std::vector<std::string>{"draw"}, "prizeAnimation"),
                Transition("finishDraw",
                           std::vector<std::string>{"draw", "prizeAnimation"},
                           "endPlay"),
            });

  fsm->TriggerTransition("loaded");
  std::cout << "Finished Loading" << std::endl;

  view = this->CreateGameView();
  // TODO: Lock FPS here
  while (running && view->isOpen()) {
    this->Update();
  }
  view->Close();
  std::cout << "Closing Game" << std::endl;
}

void Game::Update() { view->Update(); }

GameView *Game::CreateGameView() {
  std::cout << "Creating Game View" << std::endl;
  auto *_gameView = new GameView();
  return _gameView;
}

void Game::CreateFSM(std::vector<State> states,
                     std::vector<Transition> transitions) {
  for (auto &state : states) {
    fsm->AddState(state);
  }
  for (auto &transition : transitions) {
    fsm->AddTransition(transition);
  }
}

bool Game::StartPlay() {
  if (accounting->StartPlay(this->getBet())) {
    return fsm->TriggerTransition("startDraw");
  } else {
    std::cout << "Not Enough Credits to Start a Play" << std::endl;
    return false;
  }
}

void Game::PauseGame() {
  // TODO: Add Pause trigger
}

void Game::AddMoney(int amount) { accounting->AddMoney(amount); }

void Game::ChangeBet(bool increment) {
  // TODO: Implement MaxBet and MinBet
  if (increment) {
    if (this->getBet() == this->getMaxBet()) {
      return;
    }
    this->setBet(this->getBet() + 1);
  } else {
    if (this->getBet() == 1) {
      return;
    }
    this->setBet(this->getBet() - 1);
  }
}

void Game::ChangeLines(bool increment) {
  // TODO: Implement MaxLines and MinLines
  if (increment) {
    if (this->getLines() == this->getMaxLines()) {
      return;
    }
    this->setLines(this->getLines() + 1);
  } else {
    if (this->getLines() == 1) {
      return;
    }
    this->setLines(this->getLines() - 1);
  }
}
