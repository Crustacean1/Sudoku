#ifndef LINKEDNODE
#define LINKEDNODE

#define __ERROR                                        \
    std::cerr << "error on line: " << __LINE__ << " "; \
    std::cin.get();

#include <iostream>

template <typename T>
class LinkedNode
{
private:
    LinkedNode<T> *_next;
    LinkedNode<T> *_prev;

    LinkedNode(const LinkedNode<T> &node) {}
    LinkedNode<T> &operator=(const LinkedNode<T> &node) {}

public:
    LinkedNode(T value);
    ~LinkedNode();

    operator T &() { return _value; }
    void setValue(T value) { _value = value; }

    T _value;

    void insertBefore(LinkedNode<T> *node);
    void insertBefore(T value) { insertBefore(new LinkedNode<T>(value)); }
    void insertAfter(LinkedNode<T> *node);
    void insertAfter(T value) { insertAfter(new LinkedNode<T>(value)); }

    void popIn();
    void popOut();

    LinkedNode<T> *erase();

    bool insideChain() { return (_next->_prev == _prev->_next) && (_prev->_next == this); }
    bool selfReference() { return (_next == this) || (_prev == this); }

    LinkedNode<T> *next(unsigned int distance);
    LinkedNode<T> *prev(unsigned int distance);

    LinkedNode<T> *next() { return _next; }
    LinkedNode<T> *prev() { return _prev; }

    static void advance(LinkedNode<T> *&ptr, uint32_t dist);
    static void advance(LinkedNode<T> *&ptr);
    static void recede(LinkedNode<T> *&ptr, uint32_t dist);
    static void recede(LinkedNode<T> *&ptr);

    template <typename F>
    LinkedNode<T> *select(const F &f);

    template <typename F, typename... V>
    void iterateForward(const F &f, V &...v);

    template <typename F, typename... V>
    void iterateBackward(const F &f, V &...v);

    uint32_t count();
};
template <typename T>
LinkedNode<T>::LinkedNode(T value) : _next(this), _prev(this), _value(std::move(value))
{
}

template <typename T>
LinkedNode<T>::~LinkedNode()
{
    _next->_prev = _prev;
    _prev->_next = _next;
    if (_next != this)
    {
        delete _next;
    }
}

template <typename T>
void LinkedNode<T>::insertBefore(LinkedNode<T> *node)
{
    if (node == nullptr)
    {
        return;
    }
    node->_prev = _prev;
    node->_next = this;

    _prev->_next = node;
    _prev = node;
}
template <typename T>
void LinkedNode<T>::insertAfter(LinkedNode<T> *node)
{
    if (node == nullptr)
    {
        return;
    }
    node->_prev = this;
    node->_next = _next;

    _next->_prev = node;
    _next = node;
}
template <typename T>
inline void LinkedNode<T>::popOut()
{
    _next->_prev = _prev;
    _prev->_next = _next;
}
template <typename T>
inline void LinkedNode<T>::popIn()
{
    _next->_prev = this;
    _prev->_next = this;
}
template <typename T>
LinkedNode<T> *LinkedNode<T>::erase()
{
    _next->_prev = _prev;
    _prev->_next = _next;
    _prev = _next = this;
    return this;
}
template <typename T>
LinkedNode<T> *LinkedNode<T>::next(unsigned int distance)
{
    auto ptr = this;
    while (distance--)
    {
        ptr = ptr->_next;
    }
    return ptr;
}
template <typename T>
LinkedNode<T> *LinkedNode<T>::prev(unsigned int distance)
{
    auto ptr = this;
    while (distance--)
    {
        ptr = ptr->_prev;
    }
    return ptr;
}
template <typename T>
uint32_t LinkedNode<T>::count()
{
    uint32_t cnt = 1;
    for (auto ptr = _next; this != ptr; ptr = ptr->next(), ++cnt)
    {
    }
    return cnt;
}
template <typename T>
void LinkedNode<T>::advance(LinkedNode<T> *&ptr, uint32_t dist)
{
    while (dist--)
    {
        ptr = ptr->_next;
    }
}
template <typename T>
void LinkedNode<T>::advance(LinkedNode<T> *&ptr)
{
    ptr = ptr->_next;
}
template <typename T>
void LinkedNode<T>::recede(LinkedNode<T> *&ptr, uint32_t dist)
{
    while (dist--)
    {
        ptr = ptr->_prev;
    }
}
template <typename T>
void LinkedNode<T>::recede(LinkedNode<T> *&ptr)
{
    ptr = ptr->_prev;
}
template <typename T>
template <typename F>
LinkedNode<T> *LinkedNode<T>::select(const F &f)
{
    LinkedNode<T> * it = _next;
    LinkedNode<T> * selection = this;
    auto score = f(_value);
    auto newScore = score;
    while (it != this)
    {
        newScore = f(it->_value);
        if (score < newScore)
        {
            score = newScore;
            selection = it;
        }
        it = it->_next;
    }
    return selection;
}
template <typename T>
template <typename F, typename... V>
void LinkedNode<T>::iterateForward(const F &f, V &...v)
{
    auto it = this;
    do
    {
        f((const T &)it->_value, v...);
        it = it->_next;
    } while (it != this);
}

template <typename T>
template <typename F, typename... V>
void LinkedNode<T>::iterateBackward(const F &f, V &...v)
{
    auto it = this->_prev;
    do
    {
        f((const T &)it->_value, v...);
        it = it->_prev;
    } while (it != this->_prev);
}
#endif /*LINKEDNODE*/