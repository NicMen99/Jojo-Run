//
// Created by Niccolo on 10/03/2021.
//

#include "Game.h"
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
    setOutlineColor(theme.font_outline_color);
}

void TextWidget::_update(int32_t delta_time) {
    if(m_timer_started){
        if (m_clock.getElapsedTime() > m_time){
            setString("");
            setVisible(false);
            m_timer_started = false;
        }
    }
}

void TextWidget::_render(sf::RenderWindow & window, const sf::Vector2f & parent_position) {
    m_text.setPosition(parent_position);
    window.draw(m_text);
}

void TextWidget::setFont(const std::string & font_name) {
    m_text.setFont(*RESOURCE->getFont(font_name));
}

sf::Vector2f TextWidget::getSize() const {
    sf::FloatRect size = m_text.getGlobalBounds();
    return sf::Vector2f{size.width, size.height};
}

void TextWidget::data_update(const std::string & item_name, const std::string & item_value) {
    m_text.setString(item_value);
}