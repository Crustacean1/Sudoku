#ifndef VARTICALLAYOUT
#define VARTICALLAYOUT

#include "Layout.h"

class VerticalLayout : public BaseLayout
{
    public:
    VerticalLayout(sf::IntRect boundingBox = sf::IntRect(0,0,0,0)) : BaseLayout(boundingBox){}

    template<typename... Args>
    VerticalLayout(sf::IntRect boundingBox,Args&... args) : BaseLayout(boundingBox,args...){computeInnerBounds();adjustPosition();}
    void computeInnerBounds();
    void adjustPosition();
    void setPosition(const sf::Vector2f & position);
    void addChild(std::unique_ptr<Drawable> & child);
    void addChild(std::unique_ptr<Drawable> && child);
};

#endif /*VARTICALLAYOUT*/