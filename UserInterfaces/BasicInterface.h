#ifndef BASICINTERFACE
#define BASICINTERFACE

#include "UserInterface.h"

class BasicInterface
{
private:
    
public:
    BasicInterface(EventQueue & eventQueue);
    
    void initiate();

    void render(Sudoku &sudoku);
    void render(Timer &timer);
    void render(Hint &hint);
    void render(MistakeCounter &mistakeCounter);
    void render(CountdownTimer &countdownTimer);

    void message(const std::string &msg);

    void display();

    void input();

    ~BasicInterface();
};



#endif /*BASICINTERFACE*/