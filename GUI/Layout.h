#ifndef BASELAYOUT
#define BASELAYOUT

#include <SFML/Graphics.hpp>
#include <memory>
#include "LinkedList/LinkedList.h"
#include "GUI/Drawable.h"

class Horizontal
{
public:
    static sf::Vector2f getGap(const sf::IntRect &outer, const sf::IntRect &inner, unsigned char root);
    static sf::Vector2f getBegPos(const sf::IntRect &outer, const sf::Vector2f &gap);
    static void adjustSelf(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap);
    static sf::IntRect getInnerBounds(const sf::Vector2i &max, const sf::Vector2i &sum);
};
class Vertical
{
public:
    static sf::Vector2f getGap(const sf::IntRect &outer, const sf::IntRect &inner, unsigned char root);
    static sf::Vector2f getBegPos(const sf::IntRect &outer, const sf::Vector2f &gap);
    static void adjustSelf(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap);
    static sf::IntRect getInnerBounds(const sf::Vector2i &max, const sf::Vector2i &sum);
};

template <typename T>
class Layout : public Drawable
{
public:
protected:
    sf::IntRect _innerBoundingBox;
    sf::IntRect _outerBoundingBox;
    sf::Vector2f _gap;
    LinkedList<std::unique_ptr<Drawable>> _children;

    static void renderSelf(const std::unique_ptr<Drawable> &drawable, sf::RenderWindow &window);
    static void getBounds(const std::unique_ptr<Drawable> &drawable, sf::Vector2i &max, sf::Vector2i &sum);
    static void passAction(const std::unique_ptr<Drawable> &drawable, const sf::Vector2i &position, const sf::Event &type, bool &active);
    // static void adjustSelfHorizontally(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap);
    // static void adjustSelfVertically(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap);

public:
    template <typename... Args>
    Layout(sf::IntRect boundingBox, std::unique_ptr<Args> &...args) : _outerBoundingBox(boundingBox)
    {
        ((void)_children.push_back(std::move(args)), ...);
        _outerBoundingBox.left = _outerBoundingBox.top = 0;
        computeInnerBounds();
        adjustPosition();
    }

    void render(sf::RenderWindow &window);
    sf::IntRect getBoundingBox() const;
    sf::Vector2f getPosition() const;

    void computeInnerBounds();
    void adjustPosition();
    void setPosition(const sf::Vector2f &position);
    void addChild(std::unique_ptr<Drawable> &child);
    void addChild(std::unique_ptr<Drawable> &&child);

    bool action(const sf::Vector2i &position, const sf::Event &type);
};

template <typename T>
void Layout<T>::renderSelf(const std::unique_ptr<Drawable> &drawable, sf::RenderWindow &window)
{
    drawable->render(window);
}
template <typename T>
void Layout<T>::getBounds(const std::unique_ptr<Drawable> &drawable, sf::Vector2i &max, sf::Vector2i &sum)
{
    auto bbox = drawable->getBoundingBox();
    sum.x += bbox.width;
    sum.y += bbox.height;
    max.x = std::max(max.x, bbox.width);
    max.y = std::max(max.y, bbox.height);
}

template <typename T>
void Layout<T>::render(sf::RenderWindow &window)
{
    _children.iterate(Layout::renderSelf, window);
}
template <typename T>
sf::IntRect Layout<T>::getBoundingBox() const
{
    return _outerBoundingBox;
}
template <typename T>
sf::Vector2f Layout<T>::getPosition() const
{
    return sf::Vector2f(_outerBoundingBox.left + _outerBoundingBox.width / 2, _outerBoundingBox.top + _outerBoundingBox.height / 2);
}

template <typename T>
void Layout<T>::computeInnerBounds()
{
    sf::Vector2i max(0, 0);
    sf::Vector2i sum(0, 0);
    _children.iterate(getBounds, max, sum);
    _innerBoundingBox = T::getInnerBounds(max, sum);
    _outerBoundingBox.width = std::max(_outerBoundingBox.width, _innerBoundingBox.width);
    _outerBoundingBox.height = std::max(_outerBoundingBox.height, _innerBoundingBox.height);

    _gap = T::getGap(_outerBoundingBox, _innerBoundingBox, _children.count());
}
template <typename T>
void Layout<T>::adjustPosition()
{
    auto begPos = T::getBegPos(_outerBoundingBox, _gap);
    _children.iterate(T::adjustSelf, begPos, _gap);
}
template <typename T>
void Layout<T>::setPosition(const sf::Vector2f &position)
{
    _outerBoundingBox.left = position.x - _outerBoundingBox.width / 2;
    _outerBoundingBox.top = position.y - _outerBoundingBox.height / 2;
    adjustPosition();
}
template <typename T>
void Layout<T>::addChild(std::unique_ptr<Drawable> &child)
{
    _children.push_back(std::move(child));
    computeInnerBounds();
    adjustPosition();
}

template <typename T>
void Layout<T>::addChild(std::unique_ptr<Drawable> &&child)
{
    _children.push_back(std::move(child));
    computeInnerBounds();
    adjustPosition();
}
template <typename T>
void Layout<T>::passAction(const std::unique_ptr<Drawable> &drawable, const sf::Vector2i &position, const sf::Event &type, bool &active)
{
    if (!drawable->getBoundingBox().contains(position))
    {
        return;
    }
    drawable->action(position, type);
}
template <typename T>
bool Layout<T>::action(const sf::Vector2i &position, const sf::Event &type)
{
    bool active = false;
    _children.iterate(passAction, position, type, active);
    return active;
}
#endif /*BASELAYOUT*/