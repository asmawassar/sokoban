#include "Button.h"

button::button(float x, float y,float width,float height,int siz,Font *fnt,string txt,
               Color idlecolor)
{
    buttonState=BTN_IDLE;

    shape.setPosition(Vector2f(x,y));
    shape.setSize(Vector2f(width,height));

    text.setFont(*fnt);
    text.setString(txt);
    text.setFillColor(Color::Black);
    text.setCharacterSize(siz);

    shape.setFillColor(idlecolor);
    shape.setOutlineColor(Color(188,143,143));
    shape.setOutlineThickness(1);
}

void button::setpos() //text fl west
{
    float x,y;
    x=shape.getPosition().x;
    y=shape.getPosition().y;
    float width=shape.getGlobalBounds().width;
    float height=shape.getGlobalBounds().height;
    float a=(x+width/2)-(text.getLocalBounds().width/2);
    float b=(y+height/2)-(text.getLocalBounds().height/2)-10;
    text.setPosition(a,b);

}

void button::render(RenderWindow* target) //draw bouton
{
    target->draw(shape);
    setpos();
    target->draw(text);
}

void button::update(float x, float y)
{
    buttonState=BTN_IDLE;

    if(shape.getGlobalBounds().contains(x,y))
    {
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            buttonState=BTN_ACTIVE;
        }
    }
}
const bool button::ispressed() const
{
    if(buttonState==BTN_ACTIVE)
    {
        return true;
    }
    return false;
}
void button::change_pos(int x, int y)
{
    shape.setPosition(x,y);
    setpos();
}
string button::get_text()
{
    return text.getString();
}
