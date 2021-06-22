#ifndef MESSAGE
#define MESSAGE

#include "Layout.h"

class Text : public Drawable
{
    sf::Text _text;

public:
    Text(const std::string &str);
    void setString(const std::string & str);
    std::string getString();

    void render(sf::RenderWindow &window);
    void setPosition(const sf::Vector2f &position);
    sf::Vector2f getPosition() const;
    sf::IntRect getBoundingBox() const;
};
class Message : public Layout<Vertical>
{
    LinkedList<std::string> &_messageQueue;
    sf::RectangleShape _background;

    sf::Texture _buttonTexture;
    void popQueue();
public:
    Message(LinkedList<std::string> &messageQueue, sf::IntRect size);
    void render(sf::RenderWindow & window);
};

#endif /*MESSAGE*/