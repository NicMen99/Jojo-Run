//
// Created by Niccolo on 10/03/2021.
//

#include "Game.h"
#include "GameStats.h"
#include "GameResourceManager.h"
#include "TextWidget.h"

TextWidget::TextWidget(const std::string & name):
    Widget(name) {
}

TextWidget::~TextWidget() {
}

void TextWidget::init(const WidgetTheme & theme) {
    setFont(theme.font_name);
    setCharacterSize(theme.font_size);
    setFillColor(theme.font_color);
    setOutlineThickness(theme.font_outline_thinckness);
}

void TextWidget::_update(int32_t delta_time) {

}

void TextWidget::_render(sf::RenderWindow & window, const sf::Vector2f & parent_position) {
    m_text.setPosition(parent_position);
    window.draw(m_text);
}

void TextWidget::setFont(const std::string & font_name) {
    m_text.setFont(*RM.getFont(font_name));
}

sf::Vector2f TextWidget::getSize() {
    sf::FloatRect size = m_text.getGlobalBounds();
    return sf::Vector2f{size.width, size.height};
}
