#include "menu.h"

menu::menu(RenderWindow *window, Font *font)
{
    this->play= new button ( 225,150,350,100,40,font,"Levels",Color(106,90,205));
    this->about= new button ( 225,300,350,100,40,font,"About Creators",Color(172,101,139));
    this->choose_char= new button ( 225,450,350,100,40,font,"Choose Player",Color(221,160,221));
    this->manual= new button ( 225,600,350,100,40,font,"Manual",Color(218,112,214));

}

void menu::update_menu(float x, float y)
{
    play->update(x,y);
    about->update(x,y);
    choose_char->update(x,y);
    manual->update(x,y);

}

void menu::draw_menu(RenderWindow* window)
{
    play->render(window);
    about->render(window);
    choose_char->render(window);
    manual->render(window);
}

menu::~menu()
{
    delete play;
    delete about;
    delete choose_char;
    delete manual;
}
