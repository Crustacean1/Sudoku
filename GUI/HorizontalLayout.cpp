#include "HorizontalLayout.h"
#include <iostream>
void HorizontalLayout::computeInnerBounds()
{
    sf::Vector2i max(0, 0);
    sf::Vector2i sum(0, 0);
    _children.iterate(BaseLayout::getBounds, max, sum);
    _innerBoundingBox.width = sum.x;
    _innerBoundingBox.height = max.y;
    _outerBoundingBox.width = std::max(_outerBoundingBox.width, _innerBoundingBox.width);
    _outerBoundingBox.height = std::max(_outerBoundingBox.height, _innerBoundingBox.height);

    _gap = sf::Vector2f(_outerBoundingBox.width, _outerBoundingBox.height) - sf::Vector2f(_innerBoundingBox.width, _innerBoundingBox.height);
    _gap.x /= (float)(_children.getRoot()->count() + 1);
    _gap.y/=2;
}
void HorizontalLayout::adjustPosition()
{
    auto begPos = sf::Vector2f(_outerBoundingBox.left, _outerBoundingBox.top + _outerBoundingBox.height / 2) + _gap;
    _children.iterate(BaseLayout::adjustSelfHorizontally, begPos, _gap);
}
void HorizontalLayout::setPosition(const sf::Vector2f &position)
{
    _outerBoundingBox.left = position.x - _outerBoundingBox.width / 2;
    _outerBoundingBox.top = position.y - _outerBoundingBox.height / 2;
    adjustPosition();
}
void HorizontalLayout::addChild(std::unique_ptr<Drawable> &child)
{
    _children.push_back(std::move(child));
    computeInnerBounds();
    adjustPosition();
}

void HorizontalLayout::addChild(std::unique_ptr<Drawable> &&child)
{
    _children.push_back(std::move(child));
    computeInnerBounds();
    adjustPosition();
}
