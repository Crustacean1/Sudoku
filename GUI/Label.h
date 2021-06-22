#ifndef LABEL
#define LABEL

#include "Drawable.h"
#include "GameModes/Misc.h"

class Label : public Drawable
{
    static bool defaultFontLoaded;
    static sf::Font defaultFont;

    std::string _prevContent;
    Widget &_widget;
    unsigned int _size;

public:
    sf::Text _text;

    Label(Widget &widget);

    void render(sf::RenderWindow &window);
    void setPosition(const sf::Vector2f &pos);
    sf::Vector2f getPosition() const;
    sf::IntRect getBoundingBox() const;

    void setText(const std::string &text);
};

#endif /*LABEL*/