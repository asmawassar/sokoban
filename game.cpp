#include "Game.h"

void Game::printmap(Time time)
{
    Ggame.window->clear();

    int l;
    l=Cgame.Map.length();

    Ggame.window->draw(Ggame.s_background);
    temps(time);
    Ggame.undo_b->render(Ggame.window);
    Ggame.restart_b->render(Ggame.window);
    Ggame.exit_b->render(Ggame.window);
    int g=(800/32-Cgame.x)/2;
    int y=(750/32-(l/Cgame.x)+1)/2;
    for(int i=0; i<l; i++)
    {
        if(Cgame.Map[i]=='#')
        {
            Ggame.s_mapp.setTextureRect(IntRect(0,0,32,32));
            Ggame.s_mapp.setPosition(g*32,y*32);
            Ggame.window->draw(Ggame.s_mapp);
        }

        if(Cgame.Map[i]=='.')
        {
            Ggame.s_mapp.setTextureRect(IntRect(96,0,32,32));
            Ggame.s_mapp.setPosition(g*32,y*32);
            Ggame.window->draw(Ggame.s_mapp);
        }
        if(Cgame.Map[i]=='@')
        {
            Ggame.s_player.setPosition(g,y);
            if(Ggame.anim.x*32>= Ggame.player.getSize().x)
                Ggame.anim.x=0;
            Ggame.s_player.setTextureRect(IntRect(Ggame.anim.x*32,Ggame.anim.y*32,32,32));
            Ggame.s_player.setPosition(g*32,y*32);
            Ggame.window->draw(Ggame.s_player);
        }
        if(Cgame.Map[i]=='$')
        {
            Ggame.s_mapp.setTextureRect(IntRect(32,0,32,32));
            Ggame.s_mapp.setPosition(g*32,y*32);
            Ggame.window->draw(Ggame.s_mapp);
        }
        if(Cgame.Map[i]=='*')
        {
            Ggame.s_mapp.setTextureRect(IntRect(64,0,32,32));
            Ggame.s_mapp.setPosition(g*32,y*32);
            Ggame.window->draw(Ggame.s_mapp);
        }
        if(Cgame.Map[i]=='+')
        {
            Ggame.s_mapp.setTextureRect(IntRect(96,0,32,32));
            Ggame.s_mapp.setPosition(g*32,y*32);
            Ggame.window->draw(Ggame.s_mapp);
            Ggame.s_player.setPosition(g,y);
            if(Ggame.anim.x*32>= Ggame.player.getSize().x)
                Ggame.anim.x=0;
            Ggame.s_player.setTextureRect(IntRect(Ggame.anim.x*32,Ggame.anim.y*32,32,32));
            Ggame.s_player.setPosition(g*32,y*32);
            Ggame.window->draw(Ggame.s_player);
        }
        g++;
        if (Cgame.Map[i]=='\n')
        {
            y++;
            g=(800/32-Cgame.x)/2;
        }
    }
    Ggame.window->display();
}
void Game::move_char(Event event,string ch1, Time time)
{
    short int nb{};
    char c;
    switch (event.key.code)
    {
    case Keyboard::Up:
        Ggame.anim.y= Ggame.Up;
        Ggame.anim.x++;
        c='z';
        nb=Cgame.x+1;
        break;
    case Keyboard::Down:
        Ggame.anim.y=Ggame.Down;
        Ggame.anim.x++;
        c='s';
        nb=-(Cgame.x+1);
        break;
    case Keyboard::Left:
        Ggame.anim.y = Ggame.Left;
        Ggame.anim.x++;
        c='q';
        nb=1;
        break;
    case Keyboard::Right:
        Ggame.anim.y=Ggame.Right;
        Ggame.anim.x++;
        c='d';
        nb=(-1);
        break;
    case Keyboard::Space:
        Cgame.undo();
        break;
    case Keyboard::R:
        restart_f(ch1, time);
        break;
    default:
        break;
    }
    if(nb!=0)
        Cgame.movechar(nb,c);
    printmap(time);
}
void Game::restart_f(string ch, Time time)
{
    Cgame.Map=ch;
    Cgame.foundcharacter();
    while(!Cgame.pile.empty())
        Cgame.pile.pop();
    printmap(time);
}
void Game::level_menu()
{
    Ggame.window->clear();
    Ggame.window->draw(Ggame.s_background);
    Ggame.lvl->draw_level(Ggame.window);
    Ggame.return_b->render(Ggame.window);
    Ggame.window->display();
    while (Ggame.window->isOpen())
    {
        Event event;
        while (Ggame.window->pollEvent(event))
        {
            float x1,y1;
            x1=Mouse::getPosition(*Ggame.window).x;
            y1=Mouse::getPosition(*Ggame.window).y;
            int n;
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                n=Ggame.lvl->choose_level(Ggame.window);
                if(n>0)
                {
                    Ggame.sound.pause();
                    play(n);
                }
            }
            Ggame.return_b->update(x1,y1);
            if(Ggame.return_b->ispressed())
                Game_start();
        }
        Ggame.input(event,Ggame.window);
    }
}
void Game::win_f(int n,string txt)
{
    Ggame.window->clear();
    Texture win;
    Ggame.lvl->level_won(n,txt);
    Sprite sprite_win;
    if(!win.loadFromFile("res/win.jpeg"))
        cout<<"prob"<<endl;
    win.setSmooth(true);
    sprite_win.setTexture(win);
    Ggame.window->draw(sprite_win);
    if(n<15)
        Ggame.next->render(Ggame.window);
    Ggame.exit_b->render(Ggame.window);
    Ggame.window->display();
    while (Ggame.window->isOpen())
    {
        Event event;
        while (Ggame.window->pollEvent(event))
        {
            float tx,ty;
            tx=Mouse::getPosition(*Ggame.window).x;
            ty=Mouse::getPosition(*Ggame.window).y;
            Ggame.exit_b->update(tx,ty);
            Ggame.next->update(tx,ty);
            Cgame.Map.erase(0,Cgame.Map.length());
            while(!Cgame.pile.empty())
                Cgame.pile.pop();
            if(Ggame.exit_b->ispressed())
            {
                Ggame.music.stop();
                Ggame.sound.play();
                level_menu();
            }
            if (Ggame.next->ispressed())
            {
                play(n+1);
            }
        }
        Ggame.input(event,Ggame.window);
    }
}
bool Game::lose()
{
    if(Cgame.Close())
    {
        RenderWindow window1;
        window1.create(VideoMode(800,350),"lost");
        Texture texture;
        Sprite lose_;
        if(!texture.loadFromFile("res/lose.png"))
            cout<<"prob"<<endl;
        texture.setSmooth(true);
        lose_.setTexture(texture);
        window1.draw(lose_);
        Ggame.undo_b->change_pos(610,250);
        Ggame.restart_b->change_pos(340,250);
        Ggame.exit_b->change_pos(70,250);
        Ggame.undo_b->render(&window1);
        Ggame.restart_b->render(&window1);
        Ggame.exit_b->render(&window1);
        window1.display();
        while (window1.isOpen())
        {
            Event event;
            while (window1.pollEvent(event))
            {
                float tx,ty;
                tx=Mouse::getPosition(window1).x;
                ty=Mouse::getPosition(window1).y;
                Ggame.undo_b->update(tx,ty);
                Ggame.restart_b->update(tx,ty);
                Ggame.exit_b->update(tx,ty);
                if(Ggame.undo_b->ispressed() || Ggame.restart_b->ispressed() || Ggame.exit_b->ispressed())
                {
                    window1.close();
                }
            }
        }
        return true;
    }
    return false;
}
string Game::temps(Time time)
{
    Text text;
    string ch="";
    text.setCharacterSize(25);
    text.setColor(Color::Black);
    text.setFont(Ggame.font);
    text.setPosition(150,100);
    int s=(time.asSeconds());
    int h=0;
    int m=0;
    if(s>=60)
    {
        m=s/60;
        s=s%60;
    }
    if(m>=60)
    {
        h=m/60;
        m=m%60;
    }
    ch+=to_string(h)+":"+to_string(m)+":"+to_string(s);
    text.setString(ch);
    Ggame.window->draw(text);
    text.setPosition(50,100);
    text.setString("time ");
    Ggame.window->draw(text);
    return ch;
}
void Game::play(short int n)
{
    Cgame.createmap(n);
    Ggame.music.play();
    Ggame.music.setLoop(true);
    Cgame.foundcharacter();
    string map1=Cgame.Map;
    Ggame.s_player.setTextureRect(IntRect(32,0,32,32));
    Clock clock;
    Time time = clock.getElapsedTime();
    printmap(time);

    while (Ggame.window->isOpen())
    {
        Event event;
        Ggame.input(event, Ggame.window);
        time = clock.getElapsedTime();
        printmap(time);
        while (Ggame.window->pollEvent(event))
        {
            if(event.type==Event::KeyPressed)
            {
                move_char(event,map1,time);
                if(lose())
                {
                    Ggame.undo_b->change_pos(600,760);
                    Ggame.restart_b->change_pos(335,760);
                    Ggame.exit_b->change_pos(70,760);
                    if(Ggame.restart_b->ispressed())
                    {
                        time= clock.restart();
                        restart_f(map1,time);
                    }

                    if (Ggame.undo_b->ispressed())
                    {
                        Cgame.undo();
                        printmap(time);
                    }

                    if (Ggame.exit_b->ispressed())
                    {
                        Ggame.music.stop();
                        Cgame.Map.erase(0,Cgame.Map.length());
                        while(!Cgame.pile.empty())
                            Cgame.pile.pop();
                        Ggame.sound.play();
                        level_menu();
                    }

                }
            }
            if(event.type==Event::MouseButtonPressed)
            {
                switch(Ggame.buttonInput())
                {
                case 1:
                    time= clock.restart();
                    restart_f(map1,time);
                    break;
                case 2:
                    Cgame.undo();
                    printmap(time);
                    break;
                case 3:
                    Ggame.music.stop();
                    Cgame.Map.erase(0,Cgame.Map.length());
                    while(!Cgame.pile.empty())
                        Cgame.pile.pop();
                    Ggame.sound.play();
                    level_menu();
                    break;
                default:
                    break;
                }
            }
            if (Cgame.Caisse==Cgame.Caisse_sur_une_zone)
            {
                string text=temps(time);
                win_f(n,text);
            }
        }
        Ggame.window->clear();
    }
}
void Game::Game_start()
{
    if(Ggame.start())
        level_menu();
}
