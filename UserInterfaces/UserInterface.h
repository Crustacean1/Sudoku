#ifndef USERINTERFACE
#define USERINTERFACE

#include "GameModes/Game.h"

class Sudoku;
class EventQueue;

class Hint;
class Timer;
class MistakeCounter;
class Event;

/**
 * Base interface to be used by all derived classes implementing UserInterface, graphical or in console
 */
class UserInterface
{
protected:
    /**
     * Queue for passing messages between Game and UserInterface derived instances
    */
    LinkedList<std::string> &_messageQueue;
    
public:
    template <typename T>
    UserInterface(LinkedList<T> &eventQueue, LinkedList<std::string> &messageQueue) : _messageQueue(messageQueue) {}

    /**
     * Invoked before rendering of UI
     */
    virtual void initiate() = 0;

    /**
     * Clears screen before drawing
     */
    virtual void clear() = 0;

    /**
     * Renders, or in case of CLI displays, UI elements. Game rendered is specified to have select few base components, such as: SudokuBoard,
     * Timer or MistakeCounter and others that will be drawn by UI instance
     */
    virtual void render(Game & game) = 0;

    /**
     * Displays, or in case of CLI flushes, rendered elements. Meaningful mainly in GUI applications
     */
    virtual void display() = 0;

    /**
     * Gathers input from user and passes it to _eventQueue of appropriate type
     */
    virtual void input() = 0;

    virtual ~UserInterface() {}
};

#endif /*INTERFACE*/