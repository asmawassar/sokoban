#ifndef GAME_H
#define GAME_H
#include "Graphique.h"
#include "Console.h"

class Game
{
public:
    Game() {};
    void Game_start();

private:
    Console Cgame;
    Graphique Ggame;
    void printmap(Time);
    string temps(Time);
    void move_char(Event,string,Time);
    void restart_f(string,Time);
    void level_menu(); //mechekel
    void win_f(int, string);
    void play(short int);
    bool lose();
};

#endif // GAME_H
