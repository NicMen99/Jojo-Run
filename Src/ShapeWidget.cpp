//
// Created by Niccolo on 23/03/2021.
//

#include "ShapeWidget.h"

ShapeWidget::ShapeWidget(const std::string & name):
        Widget(name) {
}

void ShapeWidget::init(const WidgetTheme &theme) {
}

void ShapeWidget::_update(int32_t delta_time) {

}

void ShapeWidget::_render(sf::RenderWindow &window, const sf::Vector2f &parent_position) {
    m_shape.setPosition(parent_position);
    window.draw(m_shape);
}

void ShapeWidget::setFillColor(const sf::Color & color) {
    m_shape.setFillColor(color);
}

void ShapeWidget::setSize(sf::Vector2f size) {
    m_shape.setSize(size);
}

sf::Vector2f ShapeWidget::getSize() const {
    sf::FloatRect size = m_shape.getGlobalBounds();
    return sf::Vector2f{size.width, size.height};
}

