#ifndef BASICGUI
#define BASICGUI

#include "UserInterface.h"
#include "GUI/Rectangle.h"
#include <SFML/Graphics.hpp>
#include "GUI/Drawable.h"
#include <memory>

class BasicGui : public UserInterface
{
    sf::RenderWindow _window;
    std::unique_ptr<Drawable> _guiRoot;
    std::unique_ptr<Drawable> _sudokuBoard;
    //std::unique_ptr<GUI::GuiNode<GUI::GuiNode, GUI::GuiNode, GUI::GuiNode>> _node;

public:
    BasicGui(LinkedList<std::unique_ptr<Event>> &_eventQueue, LinkedList<std::string> &_messageQueue);

    void initiate(Game &game);
    void render(Game &game);
    void input();
    void display();
    void clear();
};

#endif /*BASICGUI*/