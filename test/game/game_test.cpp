#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "game.h"

struct GameMock : public Game {
	MOCK_METHOD0(CreateGameView, GameView*());
	GameMock() { running = false; };
};

TEST(Game, StartPlay) {
	GameMock game;
	EXPECT_CALL(game, CreateGameView());
	game.Run();
	ASSERT_EQ(game.StartPlay(), false);
	game.AddMoney(10);
	ASSERT_EQ(game.fsm->getCurrentState(), "idle");
	ASSERT_EQ(game.StartPlay(), true);
	ASSERT_EQ(game.fsm->getCurrentState(), "draw");
}

TEST(Game, BetChange) {
	GameMock game;

	ASSERT_EQ(game.getBet(), 1);
	game.ChangeBet(false);
	ASSERT_EQ(game.getBet(), 1);
	game.ChangeBet(true);
	ASSERT_EQ(game.getBet(), 2);
	game.ChangeBet(false);
	ASSERT_EQ(game.getBet(), 1);
}

TEST(Game, LinesChange) {
	GameMock game;

	ASSERT_EQ(game.getLines(), 1);
	game.ChangeLines(false);
	ASSERT_EQ(game.getLines(), 1);
	game.ChangeLines(true);
	ASSERT_EQ(game.getLines(), 2);
	game.ChangeLines(false);
	ASSERT_EQ(game.getLines(), 1);
}
