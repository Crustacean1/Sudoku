#ifndef BASICGUI
#define BASICGUI

#include "UserInterface.h"
#include "GUI/Rectangle.h"
#include "GUI/GUINode.h"
#include <SFML/Graphics.hpp>

class BasicGui : public UserInterface
{
    sf::RenderWindow _window;
    GUI::LayoutMode mode;
    GUI::GuiNode<GUI::Rectangle,GUI::Rectangle,GUI::Rectangle> _node;

public:
    BasicGui(LinkedList<std::unique_ptr<Event>> &_eventQueue, LinkedList<std::string> &_messageQueue);

    void initiate(Game & game);
    void render(Game & game);
    void input();
    void display();
    void clear();
};

#endif /*BASICGUI*/