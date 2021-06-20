#include "BasicGui.h"
#include "Event/Event.h"
#include "GUI/SudokuBoard.h"
#include "GUI/HorizontalLayout.h"
#include "GUI/VerticalLayout.h"
#include "GUI/Selector.h"
#include <iostream>

BasicGui::BasicGui(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue)
    : UserInterface(eventQueue, messageQueue)
{

    _window.create(sf::VideoMode(800, 600), "Sudoku Game");
}

void BasicGui::initiate(Game &game)
{
    SudokuBoard::init();
    std::cout << game.getSudoku() << std::endl;
    auto dimensions = _window.getSize();
    auto rect = std::unique_ptr<Rectangle>(new Rectangle(sf::Vector2f(0, 0), sf::Vector2f(100, 100)));
    _sudokuBoard = std::unique_ptr<SudokuBoard>(new SudokuBoard(game.getSudoku(), sf::Vector2f(0, 0)));
    auto selector = std::unique_ptr<Selector>(new Selector(sf::Vector2f(0,0), SudokuBoard::getDigits(), (unsigned char)game.getSudoku().getSize()));
    _guiRoot = std::unique_ptr<VerticalLayout>(new VerticalLayout(sf::IntRect(0, 0, dimensions.x, dimensions.y), _sudokuBoard, selector));
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
