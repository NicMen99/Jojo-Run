//
// Created by Niccolo on 10/03/2021.
//

#include "Game.h"
#include "Widget.h"

Widget::Widget(std::string  name) :
    m_name(std::move(name)) {

}

Widget::~Widget() {
    for (auto& widget : m_children)
        delete widget;
    m_children.clear();

    if(m_observed)
        detach();
}

Widget * Widget::getParent() const {
    return m_parent;
}

void Widget::setParent(Widget * widget) {
    m_parent = widget;
}

Widget * Widget::add(Widget *widget) {
    m_children.push_back(widget);
    widget->setParent(this);
    return widget;
}

Widget * Widget::findObjectByName(const std::string & name) {
    if(name == m_name)
        return this;
    for (auto& widget : m_children)
        if(widget->findObjectByName(name) != nullptr)
            return widget;
    return nullptr;
}

void Widget::render(sf::RenderWindow & window, const sf::Vector2f & parent_position) {
    if(!m_visible) return;
    sf::Vector2f offset = parent_position + getPosition();
    _render(window, offset);
    for (auto& widget : m_children)
        widget->render(window, offset);
}

void Widget::update(int32_t delta_time) {
    _update(delta_time);
    for (auto& widget : m_children)
        widget->update(delta_time);
}

void Widget::setPosition(const sf::Vector2f & position) {
    m_position = position;
}

void Widget::startTimer(sf::Time time) {
    if(time > sf::seconds(0)) {
        setVisible(true);
        m_clock.restart();
        m_time = time;
        m_timer_started = true;
    }
}

/**/

void Widget::observe(Subject * observed, const std::string & item_name) {
    if(nullptr != m_observed) {
        detach();
    }
    m_observed = observed;
    m_observed_value = item_name;
    attach();
}

void Widget::attach() {
    m_observed->subscribe(this, m_observed_value);
}

void Widget::detach() {
    m_observed->unsubscribe(this, m_observed_value);
}