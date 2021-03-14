//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameConfig.h"
#include "GameResourceManager.h"
#include "GameStats.h"
#include "GameObject.h"
#include "Widget.h"
#include "TextWidget.h"
#include "ScoreHUD.h"


const char * font_name = "arcadeclassic";
const unsigned int font_size = 40;


ScoreHUD::ScoreHUD() :
    GameObject(GameObjectGroup::Scene, GameObjectType::Hud, "HUD", m_sprite)
{
    attach();
}

ScoreHUD::~ScoreHUD()
{
    detach();
}

void ScoreHUD::init() {

    m_score = new Widget("score");
    m_score->setPosition({100,100});
    {
        auto w = new TextWidget("label");
        w->setPosition({10, 10});
        w->setFont(font_name);
        w->setCharacterSize(font_size);
        w->setFillColor(sf::Color::White);
        w->setString("SCORE");
        m_score->add(w);
    }
    {
        auto w = new TextWidget("value");
        w->setPosition({10, 100});
        w->setFont(font_name);
        w->setCharacterSize(font_size);
        w->setFillColor(sf::Color::White);
        w->setString("33");
        m_score->add(w);
    }

    /*
     * m_score->setPosition({10, 3});
       m_score->setSize({100, 100});
       m_score->setBackgroundColor(sf::Color::Transparent);

       TextWidget * m_score_label = new TextWidget("label");
       m_score_label->setPosition({0, 0});
       m_score_label->setFont("arcadeclassic");
       m_score_label->setFontSize(40);
       m_score_label->setFontColor(sf::Color::White);
       m_score_label->setBackgroundColor(sf::Color::Transparent);
       m_score_label->setText("SCORE");
       m_score->addWidget(m_score_label);

       TextWidget * m_score_value = new TextWidget();
       m_score_label->setName("value");
       m_score_label->setPosition(0, 0);
       m_score_label->setFont("arcadeclassic");
       m_score_label->setFontSize(40);
       m_score_label->setFontColor(sf::Color::White);
       m_score_label->setBackgroundColor(sf::Color::Transparent);
       m_score_label->setText("0");
       m_score->add(m_score_label);

       /*
       lifeTxt.setFont(m_font);
       lifeTxt.setString("HP");
       lifeTxt.setPosition(1440, 3);
       lifeTxt.setCharacterSize(40);
       lifeTxt.setFillColor(sf::Color::White);

       numLife.setFont(m_font);
       numLife.setString("100");
       numLife.setPosition(1500, 3);
       numLife.setCharacterSize(40);
       numLife.setFillColor(sf::Color::White);

       knivesTxt.setFont(m_font);
       knivesTxt.setString("Knives");
       knivesTxt.setPosition(1400, 38);
       knivesTxt.setCharacterSize(35);
       knivesTxt.setFillColor(sf::Color::White);

       numKnives.setFont(m_font);
       numKnives.setString("0");
       numKnives.setPosition(1535, 38);
       numKnives.setCharacterSize(35);
       numKnives.setFillColor(sf::Color::White);

       bestScoreTxt.setFont(m_font);
       bestScoreTxt.setString("High Score: ");
       bestScoreTxt.setPosition(450, 800);
       bestScoreTxt.setCharacterSize(75);
       bestScoreTxt.setFillColor(sf::Color::White);

       scoreB.setFont(m_font);
       scoreB.setString("0");
       scoreB.setCharacterSize(100);
       scoreB.setFillColor(sf::Color::White);

       bestScoreNum.setFont(m_font);
       bestScoreNum.setString(std::to_string(0));
       bestScoreNum.setPosition(1000, 850);
       bestScoreNum.setCharacterSize(100);
       bestScoreNum.setFillColor(sf::Color::White);

       bestScoreB.setFont(m_font);
       bestScoreB.setString("h");
       bestScoreB.setPosition(300, 600);
       bestScoreB.setCharacterSize(110);
       bestScoreB.setFillColor(sf::Color::Black);

       m_scoreLabel.setCharacterSize(80);
       m_scoreValue.setCharacterSize(80);
       m_scoreLabel.setPosition(600, 400);
       m_scoreValue.setPosition(900, 400);
       scoreB.setPosition(500, 390);
       */
}

void ScoreHUD::render(sf::RenderWindow &window) {
    m_score->render(window);
}

void ScoreHUD::event() {
    /*
    m_score.setText("score::label::value", std::to_string(STATS.get()));
     */
}

void ScoreHUD::attach() {
    STATS.subscribe(this);
}

void ScoreHUD::detach() {
    STATS.unsubscribe(this);
}

