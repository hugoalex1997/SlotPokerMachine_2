#pragma once
#ifndef _GAME_H
#define _GAME_H


class Game {
    public:

    static Game* Instance();

    void Run();

    private:
    Game();
    ~Game();
};

#endif //_GAME_H