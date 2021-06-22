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
};

template <typename T>
class Button : public BaseButton
{
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

#endif /*BUTTON*/