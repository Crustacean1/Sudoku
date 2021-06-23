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

    auto sudokuPanel = std::unique_ptr<SudokuPanel>(new SudokuPanel(_window, game.getSudoku(), game.getState(), _eventQueue, _messageQueue));

    auto hints = std::unique_ptr<Label>(new Label(game.getHint()));
    auto timer = std::unique_ptr<Label>(new Label(game.getTimer()));
    auto mistakes = std::unique_ptr<Label>(new Label(game.getCounter()));

    sf::Event event;
    ((Drawable *)sudokuPanel.get())->action(sf::Vector2i(0, 0), event);

    auto widgetPanel = std::unique_ptr<Layout<Horizontal>>(new Layout<Horizontal>(sf::IntRect(0, 0, dimensions.x, 0), hints, timer, mistakes));
    _guiRoot = std::unique_ptr<Layout<Vertical>>(new Layout<Vertical>(sf::IntRect(0, 0, dimensions.x, dimensions.y), widgetPanel, sudokuPanel));
}
void BasicGui::renderMessage()
{
    if (_messageRoot.get() == nullptr)
    {
        if (_messageQueue.getRoot() == nullptr)
        {
            return;
        }
        _messageRoot = std::unique_ptr<Message>(new Message(_messageQueue.getRoot()->_value, _window));
        _messageQueue.pop_front();
    }
    _messageRoot->render(_window);

    if (_messageRoot->isAccepted())
    {
        _messageRoot = std::unique_ptr<Message>(nullptr);
    }
}

void BasicGui::render(Game &game)
{
    _guiRoot->render(_window);
    renderMessage();
}
void BasicGui::input()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        // Handle events here ...
        switch (event.type)
        {
        case sf::Event::Closed:

            _eventQueue.push_back(std::unique_ptr<Event>(Event::createEvent(Event::EventType::ExitEvent)));
            _window.close();
            break;
        case sf::Event::Resized:
            resizeHandler(sf::Vector2i(event.size.width, event.size.height));
            break;
        default:
            break;
        }
        if (_messageRoot != nullptr)
        {
            _messageRoot->action(sf::Mouse::getPosition(_window), event);
            continue;
        }
        _guiRoot->action(sf::Mouse::getPosition(_window), event);
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
void BasicGui::resizeHandler(sf::Vector2i size)
{
    sf::FloatRect rect(sf::Vector2f(0, 0), (sf::Vector2f)size);
    _window.setView(sf::View(rect));
    _guiRoot->setOuterBox(sf::IntRect(sf::Vector2i(0, 0), size));
}