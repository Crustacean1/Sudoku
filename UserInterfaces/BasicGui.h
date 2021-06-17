#ifndef BASICGUI
#define BASICGUI

#include "UserInterface.h"

class BasicGui : public UserInterface
{
public:
    BasicGui(LinkedList<std::shared_ptr<Event>> &_eventQueue, LinkedList<std::string> &_messageQueue);
    
    void render();
    void input();
    void display();
    void clear();
};

#endif /*BASICGUI*/