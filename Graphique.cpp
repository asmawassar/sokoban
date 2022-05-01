#include "Graphique.h"

Graphique::Graphique()
{
    window = new RenderWindow(VideoMode(800, 870), "Sokoban");
    icon.loadFromFile("res/icon.jpeg");
    window->setIcon(50,50, icon.getPixelsPtr());
    window->setFramerateLimit(60);
    font.loadFromFile("res/nasalization.otf");
    Menu = new menu(window,&this->font);

    music.openFromFile("res/music.org.ogg");
    sound.openFromFile("res/menu.ogg");
    sound.play();

    lvl= new levels(window,&font);
    undo_b = new button ( 600,760,130,60,30,&font,"Undo",Color(216,138,214));
    restart_b = new button ( 335,760,130,60,30,&font,"Restart",Color(216,138,214));
    exit_b = new button ( 70,760,130,60,30,&font,"Exit",Color(216,138,214));
    next= new button (600,760,170,60,30,&font,"Next Level",Color(216,138,214));
    return_b = new button ( 335,760,130,60,30,&font,"Return",Color(230,183,203));

    player.loadFromFile("res/boy.png");
    player.setSmooth(true);
    s_player.setTexture(player);

    mapp.loadFromFile("res/map.png");
    s_mapp.setTexture(mapp);

    background.loadFromFile("res/background.jpg");
    s_background.setTexture(background);

    Manual.loadFromFile("res/manual.png");
    s_Manual.setTexture(Manual);

    character.loadFromFile("res/textures.png");
    character.setSmooth(true);
    boy.setTexture(character);
    girl.setTexture(character);
    boy_2.setTexture(character);
    girl_2.setTexture(character);

    boy.setScale(1.25,1.25);
}
Graphique::~Graphique()
{
    delete window;
    delete Menu;
    delete lvl;
    delete undo_b;
    delete restart_b;
    delete exit_b;
    delete next;
    delete return_b;
}

void Graphique::input(Event event, RenderWindow *window)
{
    if (event.type==Event::Closed)
        window->close();

    if ( event.key.code==Keyboard::Escape)
        window->close();
}
int Graphique::buttonInput()
{
    float tx,ty;
    tx=Mouse::getPosition(*window).x;
    ty=Mouse::getPosition(*window).y;

    restart_b->update(tx,ty);
    if(restart_b->ispressed())
        return 1;

    undo_b->update(tx,ty);
    if (undo_b->ispressed())
        return 2;

    exit_b->update(tx,ty);
    if (exit_b->ispressed())
        return 3;
    return 0;
}

bool Graphique::about_us()
{
    window->clear();
    Text text;
    text.setCharacterSize(25);
    text.setPosition(50,50);
    text.setColor(Color::Black);
    text.setFont(font);
    text.setString(" This game was developed by first year engineering\n students at National School for Computer  Science\n Tunisia (ENSI) as part of a programming project:\n\n \t\t\t Wassar Asma \n \t\t\t Oueslati Mohamed Amine \n \t\t\t Ben Mbarek Akrem \n \t\t\t Wanis Nour \n ");
    window->draw(s_background);
    window->draw(text);
    return_b->render(window);
    window->display();
    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            float x1,y1;
            x1=Mouse::getPosition(*window).x;
            y1=Mouse::getPosition(*window).y;
            return_b->update(x1,y1);
            if(return_b->ispressed())
                return start();
        }
        input(event,window);
    }
}
bool Graphique::Manual_f()
{
    window->clear();
    window->draw(s_Manual);
    return_b->render(window);
    window->display();
    while (window->isOpen())
    {
        Event event;
        input(event,window);
        while (window->pollEvent(event))
        {
            float x1,y1;
            x1=Mouse::getPosition(*window).x;
            y1=Mouse::getPosition(*window).y;
            return_b->update(x1,y1);
            if(return_b->ispressed())
                return start();
        }
    }
}
bool Graphique::choose_char()
{
    SoundBuffer buffer;
    buffer.loadFromFile("res/click.ogg");
    Sound click;
    click.setBuffer(buffer);
    click.setPitch(3.f);

    boy.setTextureRect(IntRect(160,0,78,80));
    girl.setTextureRect(IntRect(80,0,78,80));
    boy_2.setTextureRect(IntRect(240,0,80,80));
    girl_2.setTextureRect(IntRect(0,0,80,80));
    boy.setPosition(105,405);
    boy_2.setPosition(275,405);
    girl.setPosition(445,405);
    girl_2.setPosition(615,405);
    window->clear();
    window->draw(s_background);
    window->draw(boy);
    window->draw(girl);
    window->draw(boy_2);
    window->draw(girl_2);
    return_b->render(window);
    window->display();
    Event event;
    while (window->isOpen())
    {
        Event event;
        input(event, window);
        while (window->pollEvent(event))
        {
            float x1,y1;
            x1=Mouse::getPosition(*window).x;
            y1=Mouse::getPosition(*window).y;
            return_b->update(x1,y1);
            if(return_b->ispressed())
            {
                return start();
            }
            if(Mouse::isButtonPressed(Mouse::Left))
            {
                if(boy.getGlobalBounds().contains(x1,y1))
                {
                    click.play();
                    player.loadFromFile("res/boy.png");
                    boy.setScale(1.25,1.25);
                    girl.setScale(1,1);
                    boy_2.setScale(1,1);
                    girl_2.setScale(1,1);
                }
                else if(girl.getGlobalBounds().contains(x1,y1))
                {
                    click.play();
                    player.loadFromFile("res/girl2.png");
                    boy.setScale(1,1);
                    girl.setScale(1.25,1.25);
                    boy_2.setScale(1,1);
                    girl_2.setScale(1,1);
                }
                else if(boy_2.getGlobalBounds().contains(x1,y1))
                {
                    click.play();
                    player.loadFromFile("res/boy2.png");
                    boy.setScale(1,1);
                    girl.setScale(1,1);
                    boy_2.setScale(1.25,1.25);
                    girl_2.setScale(1,1);
                }
                else if(girl_2.getGlobalBounds().contains(x1,y1))
                {
                    click.play();
                    player.loadFromFile("res/girl.png");
                    boy.setScale(1,1);
                    girl.setScale(1,1);
                    boy_2.setScale(1,1);
                    girl_2.setScale(1.25,1.25);
                }
                player.setSmooth(true);
                s_player.setTexture(player);
                window->clear();
                window->draw(s_background);
                window->draw(boy);
                window->draw(girl);
                window->draw(boy_2);
                window->draw(girl_2);
                return_b->render(window);
                window->display();
            }
        }
    }
}
bool Graphique::start()
{
    window->draw(s_background);
    Menu->draw_menu(window);

    window->display();
    sound.setLoop(true);
    Event event;;
    while (window->isOpen())
    {
        Event event;
        while (window->pollEvent(event))
        {
            float tx,ty;
            tx=Mouse::getPosition(*window).x;
            ty=Mouse::getPosition(*window).y;
            Menu->update_menu(tx,ty);
            if (Menu->play->ispressed())
            {
                return true;
            }
            if(Menu->choose_char->ispressed())
            {
                return choose_char();
            }
            if(Menu->manual->ispressed())
            {
                return Manual_f();
            }
            if(Menu->about->ispressed())
            {
                return about_us();
            }
        }
        input(event, window);
    }
}
