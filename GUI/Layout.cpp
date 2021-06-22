#include "Layout.h"

sf::Vector2f Vertical::getGap(const sf::IntRect &outer, const sf::IntRect &inner, unsigned char root)
{
    return sf::Vector2f((outer.width - inner.width) / 2, (outer.height - inner.height) / (root + 1));
}
sf::Vector2f Vertical::getBegPos(const sf::IntRect &outer, const sf::Vector2f &gap)
{
    return sf::Vector2f(outer.left + outer.width / 2, outer.top + gap.y);
}

void Vertical::adjustSelf(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap)
{
    auto bbox = drawable->getBoundingBox();
    drawable->setPosition(pos + sf::Vector2f(0, bbox.height / 2));
    pos += sf::Vector2f(0, bbox.height + gap.y);
}
sf::IntRect Vertical::getInnerBounds(const sf::Vector2i &max, const sf::Vector2i &sum)
{
    return sf::IntRect(0, 0, max.x, sum.y);
}
sf::Vector2f Horizontal::getGap(const sf::IntRect &outer, const sf::IntRect &inner, unsigned char root)
{
    return sf::Vector2f((outer.width - inner.width) / (root + 1), (outer.height - inner.height) / 2);
}

sf::Vector2f Horizontal::getBegPos(const sf::IntRect &outer, const sf::Vector2f &gap)
{
    return sf::Vector2f(outer.left + gap.x, outer.top + outer.height / 2);
}
void Horizontal::adjustSelf(const std::unique_ptr<Drawable> &drawable, sf::Vector2f &pos, sf::Vector2f &gap)
{
    auto bbox = drawable->getBoundingBox();
    drawable->setPosition(pos + sf::Vector2f(bbox.width / 2, 0));
    pos += sf::Vector2f(bbox.width + gap.x, 0);
}
sf::IntRect Horizontal::getInnerBounds(const sf::Vector2i &max, const sf::Vector2i &sum)
{
    return sf::IntRect(0, 0, sum.x, max.y);
}