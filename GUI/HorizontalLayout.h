#ifndef HORIZONTALLAYOUT
#define HORIZONTALLAYOUT

#include "Layout.h"

class HorizontalLayout : public BaseLayout
{
public:
    HorizontalLayout(sf::IntRect boundingBox = sf::IntRect(0,0,0,0)) : BaseLayout(boundingBox) {}
    
    template <typename... Args>
    HorizontalLayout(sf::IntRect boundingBox, Args&... args) : BaseLayout(boundingBox, args...) {computeInnerBounds();adjustPosition();}
    void computeInnerBounds();
    void adjustPosition();
    void setPosition(const sf::Vector2f & position);
    void addChild(std::unique_ptr<Drawable> & child);
    void addChild(std::unique_ptr<Drawable> && child);
};

#endif /*HORIZONTALLAYOUT*/