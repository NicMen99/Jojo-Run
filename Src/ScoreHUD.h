//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_SCOREHUD_H
#define JOJO_RUN_SCOREHUD_H

#include <string>
#include <map>
#include <list>
#include <SFML/Graphics.hpp>
#include "Observer.h"

class Widget;

class ScoreHUD: public GameObject, Observer {
public:
    ScoreHUD ();
    ~ScoreHUD() override;

    void init();
    void update(int32_t delta_time) override {}
    void render(sf::RenderWindow & window) override;

private:
    sf::Sprite m_sprite;

    Widget * m_score;

    sf::Text lifeTxt;
    sf::Text numLife;
    sf::Text knivesTxt;
    sf::Text numKnives;
    sf::Text scoreB;
    sf::Text bestScoreTxt;
    sf::Text bestScoreB;
    sf::Text bestScoreNum;

    /*
     * Observer
     */
private:
    void event() override;
    void attach() override;
    void detach() override;

};


#endif //JOJO_RUN_SCOREHUD_H
