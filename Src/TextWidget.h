//
// Created by Niccolo on 10/03/2021.
//

#ifndef JOJO_RUN_TEXTWIDGET_H
#define JOJO_RUN_TEXTWIDGET_H

#include "Widget.h"

class TextWidget : public Widget {
public:
    explicit TextWidget(const std::string & name);
    ~TextWidget() override = default;

    void setFont(const std::string & font_name);
    void setCharacterSize(const unsigned int fontsize) { m_text.setCharacterSize(fontsize); }
    void setFillColor(const sf::Color & color) { m_text.setFillColor(color); }
    void setString(const std::string & text) { m_text.setString(text); }

protected:
    void _update(int32_t delta_time) override;
    void _render(sf::RenderWindow & window, const sf::Vector2f & position) override;

private:
    sf::Text m_text;
};


#endif //JOJO_RUN_TEXTWIDGET_H
