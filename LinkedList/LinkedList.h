#ifndef LINKEDLIST
#define LINKEDLIST

#include "../LinkedNode/LinkedNode.h"

template <typename T>
class LinkedList
{
private:
    LinkedNode<T> *_root;
    void push_back() {}
    void push_front() {}

public:
    template <typename... V>
    LinkedList(const V &...v);
    ~LinkedList();

    template <typename... V>
    void push_back(const T &value, const V &...v);

    template <typename... V>
    void push_front(const T &value, const V &...v);
    T &getElement(unsigned int i);

    void pop_front();
    void pop_back();

    LinkedNode<T> *getRoot() { return _root; }
    template <typename... V, typename F>
    void iterate(const F &function, V &...v);

    template <typename... V, typename F>
    void reverseIterate(const F &function, V &...v);

    uint32_t count();
};
template <typename T>
template <typename... V>
LinkedList<T>::LinkedList(const V &...v) : _root(nullptr)
{
    push_back(v...);
}
template <typename T>
LinkedList<T>::~LinkedList()
{
    delete _root;
}
template <typename T>
template <typename... V>
void LinkedList<T>::push_back(const T &value, const V &...v)
{
    if (_root == nullptr)
    {
        _root = new LinkedNode<T>(value);
        push_back(v...);
        return;
    }
    _root->insertBefore(new LinkedNode<T>(value));
    push_back(v...);
}
template <typename T>
template <typename... V>
void LinkedList<T>::push_front(const T &value, const V &...v)
{
    if (_root == nullptr)
    {
        _root = new LinkedNode<T>(value);
        push_front(v...);
        return;
    }
    _root->insertBefore(new LinkedNode<T>(value));
    _root = _root->prev();
    push_front(v...);
}
template <typename T>
template <typename... V, typename F>
void LinkedList<T>::iterate(const F &f, V &...v)
{
    if (_root == nullptr)
    {
        return;
    }
    auto ptr = _root;
    do
    {
        f(ptr->getValue(), v...);
        ptr = ptr->next();
    } while (ptr != _root);
}

template <typename T>
template <typename... V, typename F>
void LinkedList<T>::reverseIterate(const F &f, V &...v)
{
    if (_root == nullptr)
    {
        return;
    }
    auto ptr = _root->prev();
    do
    {
        f(ptr->getValue(), v...);
        ptr = ptr->prev();
    } while (ptr != _root->prev());
}

template <typename T>
void LinkedList<T>::pop_front()
{
    if (_root->next() == _root)
    {
        //delete _root;
        _root = nullptr;
        return;
    }
    _root->erase();
    auto newRoot = _root->next();
    delete _root;
    _root = newRoot;
}
template <typename T>
void LinkedList<T>::pop_back()
{
    if (_root->next() == _root)
    {
        //delete _root;
        _root = nullptr;
        return;
    }
    auto prevEl = _root->prev();
    _root->prev()->erase();
    delete prevEl;
}
template <typename T>
uint32_t LinkedList<T>::count()
{
    if (_root == nullptr)
    {
        return 0;
    }
    uint32_t count = 1;
    for (auto ptr = _root->next(); ptr != _root; ptr = ptr->next(), ++count)
    {
    }
    return count;
}
#endif /*LINKEDLIST*/