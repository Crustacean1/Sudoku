#include "BasicGui.h"
#include "Event/Event.h"

using namespace GUI;

BasicGui::BasicGui(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue)
    : UserInterface(eventQueue, messageQueue)
{
    std::unique_ptr<Rectangle> hRect1(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(50, 50)));
    std::unique_ptr<Rectangle> hRect2(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(50, 50)));
    std::unique_ptr<Rectangle> hRect3(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(50, 50)));

    std::unique_ptr<Rectangle> sRect1(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    std::unique_ptr<Rectangle> sRect2(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    std::unique_ptr<Rectangle> sRect3(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    std::unique_ptr<Rectangle> sRect4(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(100, 100)));


    std::unique_ptr<Rectangle> fRect1(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(50, 50)));
    std::unique_ptr<Rectangle> fRect2(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(50, 50)));
    std::unique_ptr<Rectangle> fRect3(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(50, 50)));

    _window.create(sf::VideoMode(800, 600), "Sudoku Game");
    auto dimensions = _window.getSize();

    //_node = std::unique_ptr<GuiNode<Rectangle, Rectangle, Rectangle>>(new GuiNode<Rectangle, Rectangle, Rectangle>(sf::IntRect(0, 0, _window.getSize().x, 100), LayoutMode::Horizontal, (rect1), (rect2), (rect3)));
    auto header = std::unique_ptr<GuiNode<Rectangle, Rectangle, Rectangle>>(new GuiNode(sf::IntRect(0, 0, dimensions.x, dimensions.y / 4), LayoutMode::Horizontal, hRect1, hRect2, hRect3));
    auto body = std::unique_ptr<GuiNode<Rectangle, Rectangle, Rectangle,Rectangle>>(new GuiNode(sf::IntRect(0, 0, dimensions.x, dimensions.y / 2), LayoutMode::Vertical, sRect1, sRect2, sRect3,sRect4));
    auto footer = std::unique_ptr<GuiNode<Rectangle, Rectangle, Rectangle>>(new GuiNode(sf::IntRect(0, 0, dimensions.x, dimensions.y / 4), LayoutMode::Horizontal, fRect1, fRect2, fRect3));
    
    //_node.setGlobalPosition(sf::Vector2f(150,50));
}

void BasicGui::initiate(Game &game)
{
    //_window.create(sf::VideoMode(800, 600), "Sudoku Game");
}
void BasicGui::render(Game &game)
{
    //_node->render(_window);
}
void BasicGui::input()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        // Handle events here ...
        if (event.type == sf::Event::Closed)
        {
            _eventQueue.push_back(std::unique_ptr<Event>(Event::createEvent(Event::EventType::ExitEvent)));
            _window.close();
        }
    }
}
void BasicGui::display()
{
    _window.display();
}
void BasicGui::clear()
{
    _window.clear(sf::Color(0, 0, 0));
}
