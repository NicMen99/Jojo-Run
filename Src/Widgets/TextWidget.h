//
// Created by Niccolo on 10/03/2021.
//

#ifndef JOJO_RUN_TEXTWIDGET_H
#define JOJO_RUN_TEXTWIDGET_H

#include "Widgets/Widget.h"

class TextWidget : public Widget {
public:
    explicit TextWidget(const std::string & name);
    ~TextWidget() override;
    void init(const WidgetTheme & theme);

    void setFont(const std::string & font_name);
    void setCharacterSize(const unsigned int fontsize) { m_text.setCharacterSize(fontsize); }
    void setFillColor(const sf::Color & color) { m_text.setFillColor(color); }
    void setOutlineThickness(float thickness) { m_text.setOutlineThickness(thickness); }
    void setOutlineColor(const sf::Color & color) { m_text.setOutlineColor(color); }
    void setString(const std::string & text) { m_text.setString(text); }
    std::string getString() const { return m_text.getString(); }
    sf::Vector2f getSize();

protected:
    void _update(int32_t delta_time) override;
    void _render(sf::RenderWindow & window, const sf::Vector2f & parent_position) override;

private:
    void data_update(const std::string & item_name, const std::string & item_value) override;

    sf::Text m_text;
};


#endif //JOJO_RUN_TEXTWIDGET_H
