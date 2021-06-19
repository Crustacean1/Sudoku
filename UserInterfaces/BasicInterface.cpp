#include "BasicInterface.h"
#include "GameModes/Misc.h"

#include "Event/HintEvent.h"
#include "Event/MoveEvent.h"
#include "Event/StateEvent.h"
#include "Event/UndoEvent.h"

#include <iomanip>

char BasicInterface::_sudokuTiles[2][25] = {{'-', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'},
                                            {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}};
char BasicInterface::_metaMarkers[2][6][8] = {
    {"\33[30m", "\33[97m", "\33[90m", "\033[32m", "\33[34m", "\33[31m"},
    {"", "", "", "", "", ""}};

std::unordered_map<std::string, Event::EventType> BasicInterface::_events =
    {{"move", Event::EventType::MoveEvent},
     {"pause", Event::EventType::PauseEvent},
     {"resume", Event::EventType::ResumeEvent},
     {"hint", Event::EventType::HintEvent},
     {"undo", Event::EventType::UndoEvent},
     {"note", Event::EventType::NoteEvent},
     {"exit", Event::EventType::ExitEvent}};

BasicInterface::BasicInterface(LinkedList<std::unique_ptr<Event>> &eventQueue, LinkedList<std::string> &messageQueue) : UserInterface(eventQueue, messageQueue)
{
}

void BasicInterface::render(Sudoku &sudoku, Game::GameState state)
{
    std::cout << "   ";
    for (uint16_t i = 0; i < sudoku.getRootSize(); ++i)
    {
        for (uint16_t j = 0; j < sudoku.getRootSize(); ++j)
        {
            std::cout << i * sudoku.getRootSize() + j << "  ";
        }
        std::cout << " ";
    }
    std::cout << "\n";
    for (uint16_t i = 0; i < sudoku.getRootSize(); ++i)
    {
        for (uint16_t j = 0; j < sudoku.getRootSize(); ++j)
        {
            std::cout << i * sudoku.getRootSize() + j << ":";
            for (uint16_t k = 0; k < sudoku.getRootSize(); ++k)
            {
                for (uint16_t h = 0; h < sudoku.getRootSize(); ++h)
                {
                    auto cell = sudoku[k * sudoku.getRootSize() + h][i * sudoku.getRootSize() + j];
                    std::cout << _metaMarkers[state == Game::GameState::Pause][static_cast<unsigned char>(Sudoku::getMeta(cell))];
                    std::cout
                        << std::setw(2) << _sudokuTiles[state == Game::GameState::Pause][Sudoku::getNumber(cell)] << " \33[39m";
                }
                std::cout << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
void BasicInterface::render(Game &game)
{
    render(game.getTimer());
    render(game.getHint());
    render(game.getCounter());
    std::cout << "\n";
    render(game.getSudoku(), game.getState());
    std::cout << "\n";
    renderMessages();
}
void BasicInterface::render(const Timer &timer)
{
    if (timer._mode == Timer::Clock)
    {
        std::cout << "time: " << timer.asSeconds() / 60 << ":" << std::setw(2) << timer.asSeconds() % 60 << std::endl;
    }
    else if (timer._mode == Timer::Countdown)
    {
        std::cout << "time left: " << timer.asSeconds() / 60 << ":" << timer.asSeconds() % 60 << "/";
        std::cout << timer.limitAsSeconds() / 60 << ":" << timer.limitAsSeconds() % 60 << "\n";
    }
}
void BasicInterface::render(const Hint &hint)
{
    std::cout << "Available hints: " << (hint.getMaxHintCount() - hint.getHintCount()) << " / " << hint.getMaxHintCount() << "\t";
}
void BasicInterface::render(const MistakeCounter &counter)
{
    std::cout << "Mistakes: " << counter.getMistakes() << " / " << counter.getTolerance();
}
void BasicInterface::display()
{
    std::cout << std::flush;
}

void BasicInterface::initiate(Game & game)
{
}
void BasicInterface::clear()
{
#ifdef __linux__
    std::cout << "\033[2J\033[1;1H";
#elif __win32__

#endif
}

void BasicInterface::input()
{
    std::string userInput, req;
    std::getline(std::cin, userInput);
    std::stringstream ss(userInput);
    ss >> req;

    if (_events.find(req) == _events.end())
    {
        _messageQueue.push_back("Invalid command");
        return;
    }
    std::unique_ptr<Event> event(Event::createEvent(_events[req]));
    try
    {
        event->read(ss);
    }
    catch (const std::exception &e)
    {
        _messageQueue.push_back(e.what());
    }

    ss.clear();

    _eventQueue.push_back(std::move(event));
}
void BasicInterface::renderMessages()
{
    _messageQueue.iterate([](const std::string &message)
                          { std::cout << message << std::endl; });
    _messageQueue.clear();
}

BasicInterface::~BasicInterface()
{
}