//
// Created by Niccolo on 14/03/2021.
//

#include "Game.h"
#include "ImageWidget.h"

ImageWidget::ImageWidget(const std::string & name):
        Widget(name) {
}

ImageWidget::~ImageWidget() {

}


void ImageWidget::init(const WidgetTheme &theme) {
}

void ImageWidget::_update(int32_t delta_time) {

}

void ImageWidget::_render(sf::RenderWindow &window, const sf::Vector2f &parent_position) {
    m_image.setPosition(parent_position);
    window.draw(m_image);
}

void ImageWidget::setTexture(const std::string & texture_name, const sf::Vector2u & texture_size) {
    auto t = RESOURCE->getTexture(texture_name);
    if(texture_size.x == 0 && texture_size.y ==0) {
        m_image.setTexture(*t, true);
    }
    else {
        m_image.setTexture(*t);
        m_image.setScale((float)texture_size.x / t->getSize().x, (float)texture_size.y / t->getSize().y);
    }
}

sf::Vector2f ImageWidget::getSize() const {
    sf::FloatRect size = m_image.getGlobalBounds();
    return sf::Vector2f{size.width, size.height};
}
