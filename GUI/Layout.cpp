#include "Layout.h"

void BaseLayout::renderSelf(const std::unique_ptr<Drawable> &drawable, sf::RenderWindow &window)
{
    drawable->render(window);
}
void BaseLayout::getBounds(const std::unique_ptr<Drawable> &drawable, sf::Vector2i &max, sf::Vector2i &sum)
{
    auto bbox = drawable->getBoundingBox();
    sum.x += bbox.width;
    sum.y += bbox.height;
    max.x = std::max(max.x, bbox.width);
    max.y = std::max(max.y, bbox.height);
}
void BaseLayout::adjustSelfHorizontally(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap)
{
    auto bbox = drawable->getBoundingBox();
    drawable->setPosition(pos + sf::Vector2f(bbox.width / 2, 0));
    pos += sf::Vector2f(bbox.width + gap.x, 0);
}
void BaseLayout::adjustSelfVertically(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap)
{
    auto bbox = drawable->getBoundingBox();
    drawable->setPosition(pos + sf::Vector2f(0, bbox.height / 2));
    pos += sf::Vector2f(0, bbox.height + gap.y);
}

void BaseLayout::render(sf::RenderWindow &window)
{
    _children.iterate(BaseLayout::renderSelf, window);
}
sf::IntRect BaseLayout::getBoundingBox() const
{
    return _outerBoundingBox;
}
sf::Vector2f BaseLayout::getPosition() const
{
    return sf::Vector2f(_outerBoundingBox.left + _outerBoundingBox.width / 2, _outerBoundingBox.top + _outerBoundingBox.height / 2);
}