#ifndef BASICGUI
#define BASICGUI

#include "UserInterface.h"
#include <SFML/Graphics.hpp>
#include "GUI/Drawable.h"
#include "GUI/Message.h"
#include <memory>

class BasicGui : public UserInterface
{
    sf::RenderWindow _window;
    std::unique_ptr<Layout<Vertical>> _guiRoot;
    std::unique_ptr<Message> _messageRoot;
    //std::unique_ptr<GUI::GuiNode<GUI::GuiNode, GUI::GuiNode, GUI::GuiNode>> _node;
    void processMouse(sf::Event & event);
    void renderMessage();
    void resizeHandler(sf::Vector2i size);

public:
    BasicGui(LinkedList<std::unique_ptr<Event>> &_eventQueue, LinkedList<std::string> &_messageQueue);

    void initiate(Game &game);
    void render(Game &game);
    void input();
    void display();
    void clear();
    ~BasicGui();
};

#endif /*BASICGUI*/