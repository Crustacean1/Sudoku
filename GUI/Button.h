#ifndef BUTTON
#define BUTTON

#include "Drawable.h"
#include <iostream>

class BaseButton : public Drawable
{
protected:
    virtual void execute() = 0;
    sf::RectangleShape _shape;

public:
    BaseButton(sf::IntRect size, sf::Texture &tex);

    void render(sf::RenderWindow &window);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition() const;
    sf::IntRect getBoundingBox() const;
    bool action(const sf::Vector2i &position, const sf::Event &type);

    void setTexture(sf::Texture &tex);
    ~BaseButton();
};

template <typename T>
class Button : public BaseButton
{
protected:
    typedef void (T::*Ptr)();
    Ptr _f;
    T *_t;
    void execute()
    {
        ((_t)->*(_f))();
    }

public:
    Button(sf::IntRect size, sf::Texture &tex, T *t, Ptr f) : BaseButton(size, tex), _f(f), _t(t) {}
};

template <typename T>
class ToggleButton : public Button<T>
{
    sf::Texture _texs[2];
    unsigned char _state;
    void execute()
    {
        Button<T>::setTexture(_texs[_state = (_state + 1) % 2]);
        ((Button<T>::_t)->*(Button<T>::_f))();
    }

public:
    ToggleButton(sf::IntRect size, sf::Texture &tex1, sf::Texture &tex2, T *t, Button<T>::Ptr f) : Button<T>(size, tex1, t, f), _texs{tex1, tex2}, _state(0) {}
};

#endif /*BUTTON*/