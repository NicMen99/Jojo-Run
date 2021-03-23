//
// Created by Niccolo on 23/03/2021.
//

#ifndef JOJO_RUN_SHAPEWIDGET_H
#define JOJO_RUN_SHAPEWIDGET_H


#include "Widget.h"

class ShapeWidget : public Widget {
public:
    explicit ShapeWidget(const std::string & name);
    ~ShapeWidget() override = default;
    void init(const WidgetTheme & theme);

    void setFillColor(const sf::Color & color);
    void setSize(sf::Vector2f size);

    sf::Vector2f getSize() const;

protected:
    void _update(int32_t delta_time) override;
    void _render(sf::RenderWindow & window, const sf::Vector2f & parent_position) override;

private:
    sf::RectangleShape m_shape;
};


#endif //JOJO_RUN_SHAPEWIDGET_H
