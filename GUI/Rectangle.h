#ifndef RECTANGLE
#define RECTANGLE

#include "Drawable.h"
#include <random>

    class Rectangle : public Drawable
    {
        sf::RectangleShape _shape;

        static std::default_random_engine __engine;

    public:
        Rectangle(sf::Vector2f position, sf::Vector2f size);
        Rectangle(const sf::RectangleShape &shape);
        void render(sf::RenderWindow &window);
        void setPosition(const sf::Vector2f &position);
        sf::Vector2f getPosition() const;
        sf::IntRect getBoundingBox() const;
    };

#endif /*RECTANGLE*/