#include "BasicGui.h"
#include "Event/Event.h"
#include "GUI/SudokuPanel.h"
#include "GUI/Label.h"
#include <iostream>

BasicGui::BasicGui(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue)
    : UserInterface(eventQueue, messageQueue)
{

}

void BasicGui::initiate(Game &game)
{
    _window.create(sf::VideoMode(800, 600), "Sudoku Game");
    std::cout << game.getSudoku() << std::endl;
    auto dimensions = _window.getSize();
    
    auto sudokuPanel = std::unique_ptr<SudokuPanel>(new SudokuPanel(_window, game.getSudoku(), _eventQueue));
    
    auto hints = std::unique_ptr<Label>(new Label(game.getHint()));
    auto timer = std::unique_ptr<Label>(new Label(game.getTimer()));
    auto mistakes = std::unique_ptr<Label>(new Label(game.getCounter()));

    sf::Event event;
    ((Drawable *)sudokuPanel.get())->action(sf::Vector2i(0, 0), event);

    auto widgetPanel = std::unique_ptr<Layout<Horizontal>>(new Layout<Horizontal>(sf::IntRect(0, 0, dimensions.x, 0), hints, timer, mistakes));
    _guiRoot = std::unique_ptr<Layout<Vertical>>(new Layout<Vertical>(sf::IntRect(0, 0, dimensions.x, dimensions.y), widgetPanel, sudokuPanel));
}
void BasicGui::render(Game &game)
{
    _guiRoot->render(_window);
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
    processMouse(event);
}
void BasicGui::display()
{
    _window.display();
    sf::sleep(sf::Time(sf::milliseconds(10)));
}
void BasicGui::clear()
{
    _window.clear(sf::Color(0, 0, 0));
}
void BasicGui::processMouse(sf::Event &event)
{
    _guiRoot->action(sf::Mouse::getPosition(_window), event);
}