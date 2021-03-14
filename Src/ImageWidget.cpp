//
// Created by Niccolo on 14/03/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "ImageWidget.h"

ImageWidget::ImageWidget(const std::string & name):
        Widget(name) {
}

void ImageWidget::init(const WidgetTheme &theme) {
}

void ImageWidget::_update(int32_t delta_time) {

}

void ImageWidget::_render(sf::RenderWindow &window, const sf::Vector2f &parent_position) {
    m_image.setPosition(parent_position);
    window.draw(m_image);
}

void ImageWidget::setTexture(const std::string & texture_name) {
    auto t = RM.getTexture(texture_name);
    if(t != nullptr)
        m_image.setTexture(*t);
}

sf::Vector2f ImageWidget::getSize() {
    sf::FloatRect size = m_image.getLocalBounds();
    return sf::Vector2f{size.width, size.height};
}

