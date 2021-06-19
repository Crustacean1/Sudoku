#include "BasicGui.h"
#include "Event/Event.h"

BasicGui::BasicGui(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue)
    : UserInterface(eventQueue, messageQueue),
      _node(sf::Vector2f(100, 50), GUI::LayoutMode::Horizontalgt,
            GUI::Rectangle(sf::Vector2f(0, 0), sf::Vector2f(50, 100)),
            GUI::Rectangle(sf::Vector2f(0, 0), sf::Vector2f(100, 50)),
            GUI::Rectangle(sf::Vector2f(0, 0), sf::Vector2f(50, 50)))
{
}

void BasicGui::initiate(Game &game)
{
    _window.create(sf::VideoMode(800, 600), "Sudoku Game");
}
void BasicGui::render(Game &game)
{
    _node.render(_window);
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
