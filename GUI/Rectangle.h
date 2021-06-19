#ifndef RECTANGLE
#define RECTANGLE

#include <SFML/Graphics.hpp>
#include <random>
namespace GUI
{
    class Rectangle
    {
        sf::RectangleShape _shape;

        sf::Vector2f _localPosition;
        sf::Vector2f _globalPosition;
        static std::default_random_engine __engine;

    public:
        Rectangle(sf::Vector2f position, sf::Vector2f size);
        void render(sf::RenderWindow &window) const;
        void setLocalPosition(sf::Vector2f position);
        void setGlobalPosition(sf::Vector2f position);
        sf::IntRect getBoundingBox();
    };
};

#endif /*RECTANGLE*/