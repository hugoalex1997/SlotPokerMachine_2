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

TEST(Game,LinesChange) {
	Game game;
	game.Run();

	ASSERT_EQ(game.getLines(),1);
	game.ChangeLines(false);
	ASSERT_EQ(game.getLines(),1);
	game.ChangeLines(true);
	ASSERT_EQ(game.getLines(),2);
	game.ChangeLines(false);
	ASSERT_EQ(game.getLines(),1);
	
}
