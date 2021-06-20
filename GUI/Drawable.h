#ifndef DRAWABLE
#define DRAWABLE

#include <SFML/Graphics.hpp>

class Drawable
{
private:
public:
    virtual void render(sf::RenderWindow & window) = 0;
    virtual sf::IntRect getBoundingBox() const = 0;
    virtual sf::Vector2f getPosition() const = 0;
    virtual void setPosition(const sf::Vector2f & position) = 0;
};


#endif /*DRAWABLE*/