#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "game.h"


TEST(Game,StartPlay) {
	Game game;
	game.Run();
	ASSERT_EQ(game.StartPlay(),false);
	game.AddMoney(10);
	ASSERT_EQ(game.fsm->getCurrentState(),"idle");
	ASSERT_EQ(game.StartPlay(),true);
	ASSERT_EQ(game.fsm->getCurrentState(),"draw");
}

TEST(Game,BetChange) {
	Game game;
	game.Run();
	ASSERT_EQ(game.getBet(),1);
	game.ChangeBet(false);
	ASSERT_EQ(game.getBet(),1);
	game.ChangeBet(true);
	ASSERT_EQ(game.getBet(),2);
	game.ChangeBet(false);
	ASSERT_EQ(game.getBet(),1);
}

TEST(Game,BetLinesChange) {
	Game game;
	game.Run();

	ASSERT_EQ(game.getBetLines(),1);
	game.ChangeBetLines(false);
	ASSERT_EQ(game.getBetLines(),1);
	game.ChangeBetLines(true);
	ASSERT_EQ(game.getBetLines(),2);
	game.ChangeBetLines(false);
	ASSERT_EQ(game.getBetLines(),1);
	
}
