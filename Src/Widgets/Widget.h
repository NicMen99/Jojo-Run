//
// Created by Niccolo on 10/03/2021.
//

#ifndef JOJO_RUN_WIDGET_H
#define JOJO_RUN_WIDGET_H

#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include "Observer.h"
#include "Subject.h"


struct WidgetTheme {
    std::string font_name;
    unsigned int font_size = 20;
    sf::Color font_color = sf::Color::White;
    float font_outline_thinckness = 0;
    sf::Color font_outline_color = sf::Color::Black;
};


class Widget : public Observer {
public:
    explicit Widget(std::string  name);
    ~Widget() override;

    void update(int32_t delta_time);
    void render(sf::RenderWindow & window, const sf::Vector2f & parent_position = {0,0});

    Widget* add(Widget* widget);
    Widget* findObjectByName(const std::string & name);
    void setPosition(const sf::Vector2f & position) { m_position = position; }
    void setPosition(float posx, float posy) { m_position = {posx, posy}; }
    sf::Vector2f getPosition() { return m_position; }
    void setVisible(bool visible) { m_visible = visible; }
    void startTimer(sf::Time time);
    bool isVisible(Widget* widget) { return m_visible; }
    virtual sf::Vector2f getSize() const { return {0,0}; };

    /* observer interface */

    void observe(Subject * observed, const std::string & item_name);

protected:
    virtual void _update(int32_t delta_time) {}
    virtual void _render(sf::RenderWindow & window, const sf::Vector2f & parent_position) {}
    void setParent(Widget *);
    Widget * getParent() const;

    sf::Clock m_clock;
    sf::Time m_time = sf::seconds(0);
    bool m_timer_started = false;

private:
    std::string m_name;
    bool m_visible=true;
    sf::Vector2f m_position = {0,0};
    Widget * m_parent = nullptr;
    std::list<Widget*> m_children;

    /* observer interface */

    void data_update(const std::string & item_name, const std::string & item_value) override {}
    void attach() override;
    void detach() override;
    Subject * m_observed = nullptr;
    std::string m_observed_value;
};


#endif //JOJO_RUN_WIDGET_H
