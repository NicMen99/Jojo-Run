//
// Created by Niccolo on 14/03/2021.
//

#ifndef JOJO_RUN_IMAGEWIDGET_H
#define JOJO_RUN_IMAGEWIDGET_H

#include "Widgets/Widget.h"

class ImageWidget : public Widget {
public:
    explicit ImageWidget(const std::string & name);
    ~ImageWidget() override;
    void init(const WidgetTheme & theme);

    void setTexture(const std::string & texture_name, const sf::Vector2u & texture_size = {0, 0});
    sf::Vector2f getSize() const override;

protected:
    void _update(int32_t delta_time) override;
    void _render(sf::RenderWindow & window, const sf::Vector2f & parent_position) override;

private:
    sf::Sprite m_image;
};


#endif //JOJO_RUN_IMAGEWIDGET_H
