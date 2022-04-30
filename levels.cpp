#include "levels.h"

levels::levels(RenderWindow *window, Font *font)
{
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<5;j++)
        {
            string ch=to_string(i*5+j+1);
            level.push_back( button( 100+j*132.5,150+i*132.5,80,80,42,font,ch,Color(255,160,i*25+j*20+122)));
        }
    }
}

void levels::draw_level(RenderWindow* window)
{
    for (auto a = level.begin(); a != level.end(); ++a)
        a->render(window);
}

int levels::choose_level(RenderWindow *window)
{

    int n=1;
    float x1=Mouse::getPosition(*window).x;
    float y1=Mouse::getPosition(*window).y;
    for(int i=0;i<3;i++)
    {
        int y_min= 150+i*132.5;
        int y_max= y_min+70;
        for(int j=0;j<5;j++)
        {
            int x_min= 100+j*132.5;
            int x_max= x_min+70;
            if (x1>x_min && x1<x_max && y1>y_min && y1<y_max)
                return n;
            n++;
        }
    }
    return 0;
}
void levels::level_won(int n,string txt)
{
    auto a = level.begin();
    if(n>1)
        for (int i=1; i<n ; i++)
            a++;
    a->text.setCharacterSize(17);
    if(a->get_text()>txt)
        a->text.setString(txt);
    a->shape.setFillColor(Color(80, 208, 123));
}
