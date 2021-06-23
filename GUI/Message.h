#ifndef MESSAGE
#define MESSAGE

#include "Layout.h"

class Text : public Drawable
{
    sf::Text _text;
    static sf::Font __defaultFont;
    static sf::Font getFont(const std::string& fname);
public:
    Text(const std::string &str);
    void setString(const std::string &str);
    std::string getString();

    void render(sf::RenderWindow &window);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition() const;
    sf::IntRect getBoundingBox() const;
};
class Message : public Layout<Vertical>
{
    sf::RectangleShape _background;

    sf::Texture _buttonTexture;
    bool _accepted;
    void accept();

public:
    Message(const std::string &content,sf::RenderWindow & window);
    void render(sf::RenderWindow &window);
    bool isAccepted();
};

#endif /*MESSAGE*/