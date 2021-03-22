//
// Created by Niccolo on 10/03/2021.
//

#include "Game.h"
#include "GameStats.h"
#include "Widget.h"

Widget::Widget(std::string  name) :
    m_name(std::move(name)) {

}

Widget::~Widget() {
    for (auto& widget : m_children)
        delete widget;
    m_children.clear();

    if(m_observed)
        detach(m_observed_value);
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

void Widget::observe(Subject * observed, const std::string & item_name) {
    if(nullptr != m_observed) {
        detach(m_observed_value);
    }
    m_observed = observed;
    m_observed_value = item_name;
    attach(m_observed_value);
}

void Widget::attach(const std::string & item_name) {
    m_observed->subscribe(this, item_name);
}

void Widget::detach(const std::string & item_name) {
    m_observed->unsubscribe(this, item_name);
}