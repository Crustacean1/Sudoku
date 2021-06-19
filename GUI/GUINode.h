#ifndef DRAWABLE
#define DRAWABLE

#include <SFML/Graphics.hpp>
#include <tuple>
#include <memory>
#include <iostream>
namespace GUI
{
    template <unsigned int N>
    struct TupleIterator
    {
    public:
        template <typename C, typename T, typename... tArgs, typename... Args>
        static void iterate(C &c, void (C::*f)(T &, tArgs *...), T &t, std::tuple<std::unique_ptr<tArgs>...> &tuple, Args... args)
        {
            auto ptr = (std::get<N - 1>(tuple)).get();
            TupleIterator<N - 1>::iterate(c, f, t, tuple, ptr, args...);
        }
    };

    template <>
    struct TupleIterator<0>
    {
    public:
        template <typename C, typename T, typename... tArgs, typename... Args>
        static void iterate(C &c, void (C::*f)(T &, tArgs *...), T &t, std::tuple<std::unique_ptr<tArgs>...> &tuple, Args... args)
        {
            (c.*f)(t, args...);
        }
    };

    enum class LayoutMode : uint8_t
    {
        Horizontal,
        Vertical
    };
    template <typename... Q>
    sf::IntRect computeBoundingBox(LayoutMode mode, const Q &...q);
    template <typename... Q>
    sf::IntRect computeVerticalBoundingBox(const Q &...q);
    template <typename... Q>
    sf::IntRect computeHorizontalBoundingBox(const Q &...q);

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
        std::tuple<std::unique_ptr<V>...> _children;
        sf::IntRect _innerBoundingBox;
        sf::IntRect _outerBoundingBox;
        sf::Vector2f _gap;
        LayoutMode _layout;

        template <typename... Q>
        void computeBoundingBox(LayoutMode &mode, Q...q)
        {
            switch (_layout)
            {
            case LayoutMode::Horizontal:
                computeHorizontalBoundingBox(q...);
                break;
            case LayoutMode::Vertical:
                computeVerticalBoundingBox(q...);
                break;
            default:
            return;
            }
        }
        template <typename... Q>
        void computeVerticalBoundingBox(const Q &...q)
        {
            _innerBoundingBox.width = max((q->getBoundingBox().width)...);
            _innerBoundingBox.height = ((q->getBoundingBox().height) + ...);
        }
        template <typename... Q>
        void computeHorizontalBoundingBox(const Q &...q)
        {
            _innerBoundingBox.height = max((q->getBoundingBox().height)...);
            _innerBoundingBox.width = ((q->getBoundingBox().width) + ...);
        }

        template <typename... Q>
        void renderDrawables(sf::RenderWindow &window, Q... q)
        {
            ((void)(q->render(window)), ...);
        }

        template <typename T, typename... Q>
        void computePositionsVertically(sf::Vector2f &lastPos, T t, Q... q)
        {
            auto bbox = t->getBoundingBox();
            t->setGlobalPosition(lastPos + sf::Vector2f(0, bbox.height / 2));
            lastPos += sf::Vector2f(0, bbox.height + _gap.y);
            computePositionsVertically(lastPos, q...); // tail recursion perhaps...
        }
        template <typename T>
        void computePositionsVertically(sf::Vector2f &lastPos, T t)
        {
            auto bbox = t->getBoundingBox();
            t->setGlobalPosition(lastPos + sf::Vector2f(0, bbox.height / 2));
        }

        template <typename T, typename... Q>
        void computePositionsHorizontally(sf::Vector2f &lastPos, T t, Q... q)
        {
            auto bbox = t->getBoundingBox();
            t->setGlobalPosition(lastPos + sf::Vector2f(bbox.width / 2, 0));
            lastPos += sf::Vector2f(bbox.width + _gap.x, 0);
            computePositionsHorizontally(lastPos, q...); // tail recursion perhaps...
        }
        template <typename T>
        void computePositionsHorizontally(sf::Vector2f &lastPos, T t)
        {
            auto bbox = t->getBoundingBox();
            t->setGlobalPosition(lastPos + sf::Vector2f(bbox.width / 2, 0));
        }

        void recalculateChildPositions()
        {

            sf::Vector2f posIt;
            sf::IntRect rect;
            if (_layout == LayoutMode::Horizontal)
            {
                posIt = sf::Vector2f(_outerBoundingBox.left + _gap.x, _outerBoundingBox.top + _outerBoundingBox.height / 2);
                TupleIterator<sizeof...(V)>::iterate(*this, &GuiNode<V...>::computePositionsHorizontally, posIt, _children);
            }
            else
            {
                posIt = sf::Vector2f(_outerBoundingBox.left + _outerBoundingBox.width / 2, _outerBoundingBox.top + _gap.y);
                TupleIterator<sizeof...(V)>::iterate(*this, &GuiNode<V...>::computePositionsVertically, posIt, _children);
            }
        }

    public:
        GuiNode(sf::IntRect boundingBox, LayoutMode mode, std::unique_ptr<V> &...v) : _children(std::move(v)...), _outerBoundingBox(boundingBox), _layout(mode)
        {
            TupleIterator<sizeof...(V)>::iterate(*this, &GuiNode<V...>::computeBoundingBox, _layout, _children);
            //_innerBoundingBox = computeBoundingBox(mode, v...);
            _gap = (sf::Vector2f(_outerBoundingBox.width, _outerBoundingBox.height) - sf::Vector2f(_innerBoundingBox.width, _innerBoundingBox.height)) / (float)(sizeof...(V) + 1);
            recalculateChildPositions();
        }
        void render(sf::RenderWindow &window)
        {
            TupleIterator<sizeof...(V)>::iterate(*this, &GuiNode<V...>::renderDrawables, window, _children);
        }
        sf::IntRect getBoundingBox() { return _outerBoundingBox; }
        void setGlobalPosition(sf::Vector2f position)
        {
            _outerBoundingBox.left = position.x - _outerBoundingBox.width / 2;
            _outerBoundingBox.top = position.y - _outerBoundingBox.height / 2;
            recalculateChildPositions();
        }
    };

}; // namespace GUI

#endif /*DRAWABLE*/