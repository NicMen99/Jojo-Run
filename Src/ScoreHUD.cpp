//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameConfig.h"
#include "GameStats.h"
#include "ScoreHUD.h"

void ScoreHUD::init() {
    attach();

    font.loadFromFile(GC.getAssetPath("arcadeclassic"));

    scoreTxt.setFont(font);
    scoreTxt.setString("Score");
    scoreTxt.setPosition(10, 3);
    scoreTxt.setCharacterSize(40);
    scoreTxt.setFillColor(sf::Color::White);

    numScore.setFont(font);
    numScore.setString(std::to_string(0));
    numScore.setPosition(135, 3);
    numScore.setCharacterSize(40);
    numScore.setFillColor(sf::Color::White);
    /*
    lifeTxt.setFont(font);
    lifeTxt.setString("HP");
    lifeTxt.setPosition(1440, 3);
    lifeTxt.setCharacterSize(40);
    lifeTxt.setFillColor(sf::Color::White);

    numLife.setFont(font);
    numLife.setString("100");
    numLife.setPosition(1500, 3);
    numLife.setCharacterSize(40);
    numLife.setFillColor(sf::Color::White);

    knivesTxt.setFont(font);
    knivesTxt.setString("Knives");
    knivesTxt.setPosition(1400, 38);
    knivesTxt.setCharacterSize(35);
    knivesTxt.setFillColor(sf::Color::White);

    numKnives.setFont(font);
    numKnives.setString("0");
    numKnives.setPosition(1535, 38);
    numKnives.setCharacterSize(35);
    numKnives.setFillColor(sf::Color::White);

    bestScoreTxt.setFont(font);
    bestScoreTxt.setString("High Score: ");
    bestScoreTxt.setPosition(450, 800);
    bestScoreTxt.setCharacterSize(75);
    bestScoreTxt.setFillColor(sf::Color::White);

    scoreB.setFont(font);
    scoreB.setString("0");
    scoreB.setCharacterSize(100);
    scoreB.setFillColor(sf::Color::White);

    bestScoreNum.setFont(font);
    bestScoreNum.setString(std::to_string(0));
    bestScoreNum.setPosition(1000, 850);
    bestScoreNum.setCharacterSize(100);
    bestScoreNum.setFillColor(sf::Color::White);

    bestScoreB.setFont(font);
    bestScoreB.setString("h");
    bestScoreB.setPosition(300, 600);
    bestScoreB.setCharacterSize(110);
    bestScoreB.setFillColor(sf::Color::Black);

    scoreTxt.setCharacterSize(80);
    numScore.setCharacterSize(80);
    scoreTxt.setPosition(600, 400);
    numScore.setPosition(900, 400);
    scoreB.setPosition(500, 390);
    */
}

void ScoreHUD::render(sf::RenderWindow &window) {
    window.draw(scoreTxt);
    window.draw(numScore);
    /*
    window.draw(scoreB);
    window.draw(bestScoreTxt);
    window.draw(bestScoreB);
    window.draw(bestScoreNum);
     */
}

void ScoreHUD::update() {

    numScore.setFont(font);
    numScore.setString(std::to_string(STATS.get()));
    numScore.setPosition(135, 3);
    numScore.setCharacterSize(40);
    numScore.setFillColor(sf::Color::White);
}

void ScoreHUD::attach() {
    STATS.subscribe(this);
}

void ScoreHUD::detach() {
    STATS.unsubscribe(this);
}
