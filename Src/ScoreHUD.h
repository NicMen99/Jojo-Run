//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_SCOREHUD_H
#define JOJO_RUN_SCOREHUD_H

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Observer.h"

class ScoreHUD: public Observer {
public:
    ScoreHUD () = default;
    ~ScoreHUD() override {detach();}

    void init();
    void update();
    void render(sf::RenderWindow & window);

private:
    sf::Text scoreTxt;
    sf::Text numScore;
    sf::Text lifeTxt;
    sf::Text numLife;
    sf::Text knivesTxt;
    sf::Text numKnives;
    sf::Text scoreB;
    sf::Text bestScoreTxt;
    sf::Text bestScoreB;
    sf::Text bestScoreNum;
    sf::Font font;

private:
    void event() override;
    void attach() override;
    void detach() override;
};

#endif //JOJO_RUN_SCOREHUD_H
