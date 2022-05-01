#pragma once
#include <iostream>
#include <string>
#include <stack>
using namespace std;
class Console
{
public :
    string Map;
    short int char_position{} ;
    short int Caisse_sur_une_zone{} ;
    short int Caisse{} ;
    short int x{} ;
    stack<string> pile;
    void movechar(short int,char) ;
    void foundcharacter();
    void createmap(short int) ;
    void undo();
    bool Close() ;
    Console() {};
};
