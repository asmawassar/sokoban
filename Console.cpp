#include "Console.h"
#include <fstream>
void Console::foundcharacter()
{
    int l;
    l=Map.length();
    Caisse=0;
    Caisse_sur_une_zone=0;
    for(int i{x+1}; i<l-x-1; i++)
    {
        if (Map[i]=='@'|| Map[i]=='+')
            char_position = i;
        else if (Map[i]=='$')
            Caisse++;
        else if (Map[i]=='*')
        {
            Caisse++;
            Caisse_sur_une_zone++;
        }
    }
}
void Console::createmap(short int n)
{
    string Map1{"Map"},Map2{"Map"} ;
    Map1+=to_string(n);
    Map2+=to_string(++n);
    string line;
    ifstream myfile ("Sokoban_map") ;
    if(myfile.is_open())
    {
        getline(myfile,line);
        for(; line!=Map1; getline(myfile,line));
        getline(myfile,line);
        x=stoi(line);
        getline(myfile,line);
        for(; line!=Map2; getline(myfile,line))
        {
            Map+=line;
            Map+="\n";
        }
    }
    else
        cout<<"unable to open file"<<endl;
    myfile.close();
}
void Console::movechar(short int nb,char c)
{
    string ch{c};
    if(Map[char_position-nb]==' ' || Map[char_position-nb]=='.')
    {
        if(Map[char_position-nb]==' ')
            Map[char_position-nb]='@';
        else
            Map[char_position-nb]='+';
        if(Map[char_position]=='@')
            Map[char_position]=' ' ;
        else
            Map[char_position]='.' ;
        char_position-=nb;
        pile.push(ch+='F');
    }
    else if ((Map[char_position-nb]=='$' || Map[char_position-nb]=='*')
             && (Map[char_position-2*nb]==' ' || Map[char_position-2*nb]=='.' ))
    {
        if(Map[char_position-nb]=='$')
            Map[char_position-nb]='@';
        else
        {
            Map[char_position-nb]='+';
            Caisse_sur_une_zone--;
        }
        if(Map[char_position]=='@')
            Map[char_position]=' ';
        else
            Map[char_position]='.';
        if(Map[char_position-2*nb]==' ')
            Map[char_position-2*nb]='$';
        else
        {
            Map[char_position-2*nb]='*';
            Caisse_sur_une_zone++;
        }
        char_position-=nb;
        pile.push(ch+='T');
    }
}
void Console::undo()
{
    if(!pile.empty())
    {
        string c{pile.top()};
        pile.pop();
        short int nb;
        switch (c[0])
        {
        case 'z':
            nb=-x-1;
            break;
        case 's':
            nb=x+1;
            break;
        case 'd':
            nb=1;
            break;
        case 'q':
            nb=-1;
            break;

        default:
            break;
        }
        if(Map[char_position-nb]==' ')
            Map[char_position-nb]='@';
        else
            Map[char_position-nb]='+';
        if((Map[char_position+nb]=='$' || Map[char_position+nb]=='*') && c[1]=='T')
        {
            if(Map[char_position+nb]=='$')
                Map[char_position+nb]=' ';
            else
            {
                Caisse_sur_une_zone--;
                Map[char_position+nb]='.';
            }
            if(Map[char_position]=='@')
                Map[char_position]='$';
            else
            {
                Map[char_position]='*';
                Caisse_sur_une_zone++;
            }

        }
        else
        {
            if(Map[char_position]=='@')
                Map[char_position]=' ';
            else
                Map[char_position]='.';
        }
        char_position-=nb;
    }
    else
        cout<<"unable to undo"<<endl;
}
bool Console::Close()
{
    if(!pile.empty())
    {
        if(pile.top()[1]=='T')
        {
            short int nb;
            switch (pile.top()[0])
            {
            case 'z':
                nb=char_position-x-1;
                break;
            case 's':
                nb=char_position+x+1;
                break;
            case 'd':
                nb=char_position+1;
                break;
            case 'q':
                nb=char_position-1;
                break;
            default:
                break;
            }
            if(Map[nb]=='$')
            {
                if (((Map[nb+x+1]=='#'|| Map[nb-x-1]=='#' ) && (Map[nb+1]=='#' || Map[nb-1]=='#'))
                        || ((Map[nb+x+1]=='#'|| Map[nb-x-1]=='#')&&(Map[nb+1]=='$'&&(Map[nb+x+2]=='#'|| Map[nb-x]=='#')))
                        || ((Map[nb+x+1]=='#'|| Map[nb-x-1]=='#')&&(Map[nb-1]=='$'&&(Map[nb+x]=='#'|| Map[nb-x-2]=='#')))
                        || ((Map[nb-1]=='#'|| Map[nb+1]=='#')&&(Map[nb-x-1]=='$'&&(Map[nb-x]=='#'|| Map[nb-x-2]=='#')))
                        || ((Map[nb-1]=='#'|| Map[nb+1]=='#')&&(Map[nb+x+1]=='$'&&(Map[nb+x]=='#'|| Map[nb+x+2]=='#')))
                        || (((Map[nb-x]=='$')||(Map[nb-x]=='#'))&&((Map[nb-x-1]=='$')||(Map[nb-x-1]=='#'))&&((Map[nb+1]=='$')||(Map[nb+1]=='#')))
                        || (((Map[nb+x+2]=='$')||(Map[nb+x+2]=='#'))&&((Map[nb+x+1]=='$')||(Map[nb+x+1]=='#'))&&((Map[nb+1]=='$')||(Map[nb+1]=='#')))
                        || (((Map[nb+x]=='$')||(Map[nb+x]=='#'))&&((Map[nb+x+1]=='$')||(Map[nb+x+1]=='#'))&&((Map[nb-1]=='$')||(Map[nb-1]=='#')))
                        || (((Map[nb-x-2]=='$')||(Map[nb-x-2]=='#'))&&((Map[nb-x-1]=='$')||(Map[nb-x-1]=='#'))&&((Map[nb-1]=='$')||(Map[nb-1]=='#'))))
                {
                    return true;
                }
            }
        }
    }
    return false;
}
