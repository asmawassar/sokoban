#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Menu.h"
#include "button.h"
#include "levels.h"
using namespace std;
using namespace sf;
class Graphique
{
public:
    Graphique();
    virtual ~Graphique();
    bool start();
    int buttonInput();
    void input(Event, RenderWindow * );
    Image icon;
    Texture player,character;
    Sprite s_player,boy,girl,boy_2,girl_2;
    Texture mapp,background,Manual;
    Sprite s_mapp,s_background,s_Manual;
    button *exit_b,*next,*restart_b,*undo_b,*return_b;
    Music music, sound;
    menu *Menu;
    levels *lvl;
    Font font;
    RenderWindow *window;
    enum Dir {Down,Left,Right,Up};
    Vector2i anim;
    bool choose_char();
    bool Manual_f();
    bool about_us();
};
