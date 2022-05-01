#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

enum button_states {BTN_IDLE=0,BTN_ACTIVE};

class button
{
public:
    button(float, float,float,float,int,Font*,string,Color);
    virtual ~button() {};
    void render(RenderWindow*);
    void update( float,float);
    const bool ispressed() const;
    void change_pos(int,int);
    string get_text();
    RectangleShape shape;
    Text text;
protected:

private:
    short unsigned buttonState;



    void setpos();
};

#endif // BUTTON_H
