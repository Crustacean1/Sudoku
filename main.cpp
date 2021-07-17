#include "GameModes/BasicGame.h"
#include "UserInterfaces/BasicInterface.h"
#include "UserInterfaces/BasicGui.h"
#include "Event/Event.h"
#include "SudokuGenerator/SudokuGenerator.h"

int main(int argc, char **argv)
{
    LinkedList<std::unique_ptr<Event>> eventQueue;
    LinkedList<std::string> messageQueue;
    UserInterface *interface = new BasicInterface(eventQueue, messageQueue);
    Game *game = new BasicGame(*interface, eventQueue, messageQueue);

    game->init();
    game->gameLoop();
    delete interface;
    delete game;
    std::cout<<(int)eventQueue.count()<<std::endl;
    std::cout<<messageQueue.count()<<std::endl;
}