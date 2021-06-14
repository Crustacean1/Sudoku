#include "BasicInterface.h"
#include "GameModes/Misc.h"
#include <iomanip>

BasicInterface::BasicInterface(LinkedList<std::unique_ptr<Event>> &eventQueue,LinkedList<std::string> & messageQueue) : UserInterface(eventQueue,messageQueue),_eventQueue(eventQueue){}

void BasicInterface::render(Sudoku &sudoku)
{
    for (uint16_t i = 0; i < sudoku.getRootSize(); ++i)
    {
        for (uint16_t j = 0; j < sudoku.getRootSize(); ++j)
        {
            for (uint16_t k = 0; k < sudoku.getRootSize(); ++k)
            {
                for (uint16_t h = 0; h < sudoku.getRootSize(); ++h)
                {
                    std::cout << std::setw(2) << (int)sudoku[i * sudoku.getRootSize() + j][k * sudoku.getRootSize() + h]<<" ";
                }
                std::cout << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
}
void BasicInterface::render(Game & game)
{
    render(game.getTimer());
    render(game.getCountdownTimer());
    render(game.getHint());
    render(game.getCounter());
    std::cout<<"\n";
    render(game.getSudoku());
}
void BasicInterface::render(const Timer &timer)
{
    std::cout << "time: " << timer.asSeconds() / 60 << ":" << timer.asSeconds() % 60 << std::endl;
}
void BasicInterface::render(const Hint &hint)
{
    std::cout << "Available hints: " << (hint.getMaxHintCount() - hint.getHintCount()) << " / " << hint.getMaxHintCount() << "\t";
}
void BasicInterface::render(const MistakeCounter &counter)
{
    std::cout << "Mistakes: " << counter.getMistakes() << " / " << counter.getTolerance() << std::endl;
}
void BasicInterface::render(const CountdownTimer &countdown)
{
    std::cout << "Time left: " << countdown.asSeconds() / 60 << ":" << countdown.asSeconds() % 60
              << " / " << countdown.limitAsSeconds() / 60 << ":" << countdown.limitAsSeconds() % 60 << "\t";
}
void BasicInterface::display()
{
    std::cout << std::flush;
}

void BasicInterface::initiate()
{
}
void BasicInterface::clear()
{
    
}

void BasicInterface::input()
{
    std::string req;
    std::cin>>req;
    if(req=="move")
    {

    }
    else if(req=="undo")
    {

    }
    else if(req=="pause")
    {

    }
    else if(req=="quit")
    {

    }
    else
    {
        
    }
}
void BasicInterface::message(const std::string &msg)
{
}

BasicInterface::~BasicInterface() {}