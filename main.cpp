#include "GameModes/BasicGame.h"
//#include "UserInterfaces/BasicInterface.h"
#include "UserInterfaces/BasicGui.h"
#include "Event/Event.h"
#include "SudokuGenerator/SudokuGenerator.h"

int main(int argc, char **argv)
{
    
    /*int a = (argc > 1 && argv[1][0] > '0' && argv[1][0] < '9') ? (argv[1][0] - '0') : 3;
    SudokuGenerator generator(a);
    try
    {
        auto sudoku = generator.generate();
        std::cout << std::get<0>(sudoku) << std::endl;
        std::cout << std::get<1>(sudoku) << std::endl;
    }
    catch (const std::string &e)
    {
        std::cerr << e << '\n';
    }*/
    LinkedList<std::unique_ptr<Event>> eventQueue;
    LinkedList<std::string> messageQueue;
    //BasicInterface bInterface(eventQueue,messageQueue);
    BasicGui gInterface(eventQueue,messageQueue);
    UserInterface &interface(gInterface);
    BasicGame game(interface, eventQueue,messageQueue);
    game.init();
    game.gameLoop();
    //game.summary()
}