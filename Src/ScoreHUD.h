//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_SCOREHUD_H
#define JOJO_RUN_SCOREHUD_H

#include <string>
#include <map>
#include <list>
#include <SFML/Graphics.hpp>

class Widget;

class ScoreHUD: public GameObject {
public:
    ScoreHUD ();
    ~ScoreHUD() override;

    void init();
    void update(int32_t delta_time) override {}
    void render(sf::RenderWindow & window) override;

private:
    Widget * m_score{};
    Widget * m_hero_status{};
};


#endif //JOJO_RUN_SCOREHUD_H
