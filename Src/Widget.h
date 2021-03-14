//
// Created by Niccolo on 10/03/2021.
//

#ifndef JOJO_RUN_WIDGET_H
#define JOJO_RUN_WIDGET_H

#include <string>
#include <list>
#include "SFML/Graphics.hpp"

class Widget {
/*
protected:
    struct Theme {
        const char * font_name;
        unsigned int font_size;
        sf::Color font_color;
    };
*/
public:
    explicit Widget(std::string  name);
    virtual ~Widget();

    void update(int32_t delta_time);
    void render(sf::RenderWindow & window);
    Widget* add(Widget* widget);
    Widget* findObjectByName(const std::string & name);
    void setPosition(const sf::Vector2f & position) { m_position = position; }
    sf::Vector2f getPosition() { return m_position; }

protected:
    virtual void _update(int32_t delta_time) {}
    virtual void _render(sf::RenderWindow & window, const sf::Vector2f & position) {}
    void setParent(Widget *);
    Widget * getParent() const;

private:
    std::string m_name;
    sf::Vector2f m_position = {0,0};
    Widget * m_parent = nullptr;
    std::list<Widget*> m_children;
};


#endif //JOJO_RUN_WIDGET_H
