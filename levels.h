#ifndef LEVELS_H
#define LEVELS_H
#include "button.h"

class levels
{
public:
    levels(RenderWindow*,Font*);
    int choose_level(RenderWindow*);
    void draw_level(RenderWindow*);
    void level_won(int,string);

protected:
    vector <button> level;
private:

};

#endif // LEVELS_H
