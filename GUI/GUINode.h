#ifndef DRAWABLE
#define DRAWABLE

#include <SFML/Graphics.hpp>
#include <tuple>
#include <iostream>
namespace GUI
{
    template <unsigned int N>
    struct TupleIterator
    {
    public:
        template <typename T, typename... tArgs, typename... Args>
        static void iterate(void (*f)(T &, tArgs &...), T &t, std::tuple<tArgs...> &tuple, Args &...args)
        {
            TupleIterator<N - 1>::iterate(f, t, tuple, std::get<N - 1>(tuple), args...);
        }
    };

    template <>
    struct TupleIterator<0>
    {
    public:
        template <typename T, typename... tArgs, typename... Args>
        static void iterate(void (*f)(T &, tArgs &...), T &t, std::tuple<tArgs...> tuple, Args &...args)
        {
            f(t, args...);
        }
    };

    enum class LayoutMode : uint8_t
    {
        Horizontal,
        Vertical
    };
    template <typename... Q>
    sf::IntRect computeBoundingBox(LayoutMode mode, Q... q);
    template <typename... Q>
    sf::IntRect computeVerticalBoundingBox(Q... q);
    template <typename... Q>
    sf::IntRect computeHorizontalBoundingBox(Q... q);

    template <typename T>
    T max(T t)
    {
        return t;
    }

    template <typename T, typename... Q>
    T max(T t, Q... q)
    {
        return std::max(t, max(q...));
    }

    template <typename... V>
    class GuiNode
    {
        std::tuple<V...> _children;
        sf::IntRect _boundingBox;
        sf::Vector2f _globalPosition;
        LayoutMode _layout;

        template <typename... Q>
        static void renderDrawables(sf::RenderWindow &window, Q &...q)
        {
            ((void)q.render(window), ...);
        }

        template <typename T, typename... Q>
        static void computePositionsVertically(sf::Vector2f &lastPos, T &t, Q &...q)
        {
            auto bbox = t.getBoundingBox();
            t.setGlobalPosition(lastPos + sf::Vector2f(0, bbox.height / 2));
            lastPos += sf::Vector2f(0, bbox.height);
            computePositionsVertically(lastPos, q...); // tail recursion perhaps...
        }
        template <typename T>
        static void computePositionsVertically(sf::Vector2f &lastPos, T &t)
        {
            auto bbox = t.getBoundingBox();
            t.setGlobalPosition(lastPos + sf::Vector2f(0, bbox.height / 2));
        }

        template <typename T, typename... Q>
        static void computePositionsHorizontally(sf::Vector2f &lastPos, T &t, Q &...q)
        {
            auto bbox = t.getBoundingBox();
            t.setGlobalPosition(lastPos + sf::Vector2f(bbox.width / 2, 0));
            lastPos += sf::Vector2f(bbox.width, 0);
            computePositionsHorizontally(lastPos, q...); // tail recursion perhaps...
        }
        template <typename T>
        static void computePositionsHorizontally(sf::Vector2f &lastPos, T &t)
        {
            auto bbox = t.getBoundingBox();
            t.setGlobalPosition(lastPos + sf::Vector2f(bbox.width / 2, 0));
        }

        void recalculateChildPositions()
        {
            _boundingBox.top = _globalPosition.y - _boundingBox.height / 2;
            _boundingBox.left = _globalPosition.x - _boundingBox.width / 2;
            std::cout << _boundingBox.top << " " << _boundingBox.left << std::endl;
            std::cout << _boundingBox.width << " " << _boundingBox.height << std::endl;

            sf::Vector2f posIt;
            sf::IntRect rect;
            if (_layout == LayoutMode::Horizontal)
            {
                posIt = sf::Vector2f(_boundingBox.left, _globalPosition.y);
                TupleIterator<sizeof...(V)>::iterate(&computePositionsHorizontally, posIt, _children);
            }
            else
            {
                posIt = sf::Vector2f(_globalPosition.x, _boundingBox.top);
                TupleIterator<sizeof...(V)>::iterate(&computePositionsVertically, posIt, _children);
            }
        }

    public:
        GuiNode(sf::Vector2f pos, LayoutMode mode, V... v) : _children(v...), _boundingBox(computeBoundingBox(mode, v...)), _globalPosition(pos), _layout(mode)
        {
            recalculateChildPositions();
        }
        void render(sf::RenderWindow &window)
        {
            TupleIterator<sizeof...(V)>::iterate(renderDrawables, window, _children);
        }
        sf::IntRect getBoundingBox() { return _boundingBox; }
        void setGlobalPosition(sf::Vector2f position)
        {
            _globalPosition = position;
            recalculateChildPositions();
        }
    };

    template <typename... Q>
    sf::IntRect computeBoundingBox(LayoutMode mode, Q... q)
    {
        switch (mode)
        {
        case LayoutMode::Horizontal:
            return computeHorizontalBoundingBox(q...);
            break;
        case LayoutMode::Vertical:
            return computeVerticalBoundingBox(q...);
            break;
        default:
            return sf::IntRect();
        }
    }
    template <typename... Q>
    sf::IntRect computeVerticalBoundingBox(Q... q)
    {
        sf::IntRect bbox;
        bbox.width = max((q.getBoundingBox().width)...);
        bbox.height = ((q.getBoundingBox().height) + ...);
        return bbox;
    }
    template <typename... Q>
    sf::IntRect computeHorizontalBoundingBox(Q... q)
    {
        sf::IntRect bbox;
        bbox.height = max((q.getBoundingBox().height)...);
        bbox.width = ((q.getBoundingBox().width) + ...);
        return bbox;
    }

};

#endif /*DRAWABLE*/