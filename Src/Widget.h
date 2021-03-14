//
// Created by Niccolo on 10/03/2021.
//

#ifndef JOJO_RUN_WIDGET_H
#define JOJO_RUN_WIDGET_H

#include <string>
#include <list>
#include "Observer.h"

#include "SFML/Graphics.hpp"


struct WidgetTheme {
    std::string font_name;
    unsigned int font_size;
    sf::Color font_color;
};


class Widget : public Observer {
public:
    explicit Widget(std::string  name);
    ~Widget() override;

    void update(int32_t delta_time);
    void render(sf::RenderWindow & window, const sf::Vector2f & parent_position = {0,0});

    Widget* add(Widget* widget);
    Widget* findObjectByName(const std::string & name);
    void setPosition(const sf::Vector2f & position);

protected:
    virtual void _update(int32_t delta_time) {}
    virtual void _render(sf::RenderWindow & window, const sf::Vector2f & parent_position) {}
    void setParent(Widget *);
    Widget * getParent() const;
    sf::Vector2f getPosition() { return m_position; }

private:
    void event(const std::string & value) override {}
    void attach(const std::string & value) override {};
    void detach(const std::string & value) override {};

private:
    std::string m_name;
    sf::Vector2f m_position = {0,0};
    Widget * m_parent = nullptr;
    std::list<Widget*> m_children;
};


#endif //JOJO_RUN_WIDGET_H
