//
// Created by Niccolo on 10/03/2021.
//

#include "Widget.h"

Widget::Widget(std::string  name) :
    m_name(std::move(name)) {

}

Widget::~Widget() {
    for (auto& widget : m_children)
        delete widget;
    m_children.clear();
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
    return nullptr;
}

void Widget::render(sf::RenderWindow & window) {
    _render(window, (getParent() != nullptr) ? getParent()->getPosition() : sf::Vector2f{0, 0} );
    for (auto& widget : m_children)
        widget->render(window);
}

void Widget::update(int32_t delta_time) {
    _update(delta_time);
    for (auto& widget : m_children)
        widget->update(delta_time);
}

