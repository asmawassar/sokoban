#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <stack>
#include "button.h"

using namespace sf;

class menu
{
public:
    menu(RenderWindow *, Font *);
    virtual ~menu();
    void draw_menu(RenderWindow*);
    void update_menu(float,float);
    button *play;
    button *choose_char;
    button *manual;
    button *about;
protected:

private:

};

#endif // MENU_H
