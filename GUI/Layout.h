#ifndef BASELAYOUT
#define BASELAYOUT

#include <SFML/Graphics.hpp>
#include <memory>
#include "LinkedList/LinkedList.h"
#include "GUI/Drawable.h"

class BaseLayout : public Drawable
{
public:

protected:
    sf::IntRect _innerBoundingBox;
    sf::IntRect _outerBoundingBox;
    sf::Vector2f _gap;
    LinkedList<std::unique_ptr<Drawable>> _children;

    static void renderSelf(const std::unique_ptr<Drawable> &drawable, sf::RenderWindow &window);
    static void getBounds(const std::unique_ptr<Drawable> &drawable, sf::Vector2i &max, sf::Vector2i &sum);
    static void adjustSelfHorizontally(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap);
    static void adjustSelfVertically(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap);

public:
    template <typename... Args>
    BaseLayout(sf::IntRect boundingBox, std::unique_ptr<Args>&... args) :_outerBoundingBox(boundingBox)
    {
        ((void)_children.push_back(std::move(args)), ...);
        //computeInnerBounds();
        //adjustPositions();
    }

    void render(sf::RenderWindow &window);
    sf::IntRect getBoundingBox() const;
    sf::Vector2f getPosition() const;
    //void setPosition(const sf::Vector2f &position);
    
    //void addChild(std::unique_ptr<Drawable> & ptr);
};

#endif /*BASELAYOUT*/