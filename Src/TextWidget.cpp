//
// Created by Niccolo on 10/03/2021.
//

#include "Game.h"
#include "GameResourceManager.h"
#include "TextWidget.h"

TextWidget::TextWidget(const std::string & name):
    Widget(name) {
}

void TextWidget::_update(int32_t delta_time) {

}

void TextWidget::_render(sf::RenderWindow & window, const sf::Vector2f & position) {
    m_text.setPosition(position + getPosition());
    window.draw(m_text);
}

void TextWidget::setFont(const std::string & font_name) {
    auto f = RM.getFont(font_name);
    if(f != nullptr)
        m_text.setFont(*f);
}

