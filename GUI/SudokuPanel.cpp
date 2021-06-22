#include "SudokuPanel.h"
#include "Event/MoveEvent.h"
#include "Button.h"

SudokuPanel::SudokuPanel(sf::RenderWindow &window, Sudoku &sudoku, LinkedList<std::unique_ptr<Event>> &eventQueue) : Layout<Vertical>(sf::IntRect(0, 0, 0, window.getSize().y * 0.75)), _size(50), _eventQueue(eventQueue)
{
    generateDigitTexture(sudoku.getRootSize());
    loadTextures();
    auto undoButton = std::unique_ptr<BaseButton>(new Button(sf::IntRect(0, 0, 50, 50), _undoTexture, this, &SudokuPanel::undo));
    auto pauseButton = std::unique_ptr<BaseButton>(new Button(sf::IntRect(0, 0, 50, 50), _pauseTexture, this, &SudokuPanel::pause));
    auto hintButton = std::unique_ptr<BaseButton>(new Button(sf::IntRect(0, 0, 50, 50), _hintTexture, this, &SudokuPanel::hint));

    auto sudokuBoard = std::unique_ptr<Drawable>(_sudokuBoard = new SudokuBoard(sudoku, _digitsTexture)); // Terrible, terrible idea, don't ever do this
    auto selector = std::unique_ptr<Drawable>(_selector = new Selector(sudoku, _digitsTexture));

    auto buttonStrip = std::unique_ptr<Drawable>(_buttonStrip = new Layout<Horizontal>(sf::IntRect(0, 0,
                                                                                                   sudokuBoard->getBoundingBox().width, 0),
                                                                                       undoButton, pauseButton, hintButton));

    addChild(buttonStrip);
    addChild(sudokuBoard);
    addChild(selector);
}

void SudokuPanel::generateDigitTexture(unsigned char root)
{
    _digitsTexture.create(_size * (root * root + 2), _size);
    _digitsTexture.clear(sf::Color(255, 255, 255, 0));
    sf::Font font;
    font.loadFromFile("font.ttf");
    sf::Text digit;
    digit.setFont(font);
    digit.setCharacterSize(_size / 2);
    digit.setFillColor(sf::Color::White);
    sf::FloatRect bounds;
    for (unsigned int i = 1; i <= root * root; ++i)
    {
        digit.setString(std::to_string(i));
        bounds = digit.getGlobalBounds();
        digit.setOrigin(sf::Vector2f(bounds.width / 2, bounds.height / 2));
        digit.setPosition(sf::Vector2f(_size * i + _size / 2, _size / 2));
        _digitsTexture.draw(digit);
    }

    sf::RectangleShape background(sf::Vector2f(_size, _size));
    background.setFillColor(sf::Color(35, 35, 35));
    background.setPosition(sf::Vector2f((root * root + 1) * _size, 0));
    _digitsTexture.draw(background);
    _digitsTexture.display();
}
bool SudokuPanel::action(const sf::Vector2i &position, const sf::Event &type)
{
    if (type.type != sf::Event::MouseButtonPressed)
    {
        return false;
    }
    _buttonStrip->action(position, type);
    auto selection = _selector->getNumber(position, _eType);
    sf::Vector2i coords = _sudokuBoard->selectField(position);
    if (coords.x != -1)
    {
        postEvent(coords, selection);
        return true;
    }
    return true;
}
void SudokuPanel::pause()
{
    _eType = Event::EventType::PauseEvent;
    postEvent();
}
void SudokuPanel::undo()
{
    _eType = Event::EventType::UndoEvent;
    postEvent();
}
void SudokuPanel::hint() { _eType = Event::EventType::HintEvent; }

void SudokuPanel::postEvent(sf::Vector2i pos, unsigned char number)
{
    auto event = std::unique_ptr<Event>(Event::createEvent(_eType));
    event->_data.move._coords = SudokuCoords(pos.y, pos.x);
    event->_data.move._number = number;
    _eventQueue.push_back(std::move(event));
}
void SudokuPanel::postEvent()
{
    auto event = std::unique_ptr<Event>(Event::createEvent(_eType));
    _eventQueue.push_back(std::move(event));
    _eType = Event::EventType::VoidEvent;
}
void SudokuPanel::loadTextures()
{
    _hintTexture.loadFromFile("hint.png");
    _undoTexture.loadFromFile("undo.png");
    _pauseTexture.loadFromFile("pause.png");
}