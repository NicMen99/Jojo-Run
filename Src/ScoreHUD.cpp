//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "GameObject.h"
#include "Widget.h"
#include "TextWidget.h"
#include "ImageWidget.h"
#include "ScoreHUD.h"


const char * font_name = "arcadeclassic";
const unsigned int font_size = 40;


ScoreHUD::ScoreHUD() :
    GameObject(GameObjectGroup::Scene, GameObjectType::Hud, "HUD", m_sprite)
{
}

ScoreHUD::~ScoreHUD()
{
}

void ScoreHUD::init() {

    WidgetTheme theme;
    theme.font_name = "arcadeclassic";
    theme.font_size = 40;
    theme.font_color = sf::Color::White;

    m_score = new Widget("score");
    m_score->setPosition({30,30});

    auto score_icon = new ImageWidget("icon");
    score_icon->setPosition({0, 0});
    score_icon->setTexture("blockTexture");
    m_score->add(score_icon);

    auto score_label = new TextWidget("label");
    score_label->init(theme);
    score_label->setPosition(sf::Vector2f{score_icon->getSize().x, 0});
    score_label->setString("SCORE  ");
    score_icon->add(score_label);

    auto score_value = new TextWidget("value");
    score_value->init(theme);
    score_value->setPosition(sf::Vector2f{score_label->getSize().x, 0});
    score_value->setString("");
    score_value->observe("SCORE");
    score_label->add(score_value);

    m_hero_status = new Widget("hero_stat");
    m_hero_status->setPosition({1350,30});

    auto healthPoints_label = new TextWidget("HealthPoints_label");
    healthPoints_label->init(theme);
    healthPoints_label->setPosition({0,0});
    healthPoints_label->setString("HP  ");
    m_hero_status->add(healthPoints_label);

    auto healthPoints_value = new TextWidget("HealthPoints_value");
    healthPoints_value->init(theme);
    healthPoints_value->setPosition(sf::Vector2f{healthPoints_label->getSize().x, 0});
    healthPoints_value->setString("");
    healthPoints_value->observe("HEALTH");
    healthPoints_label->add(healthPoints_value);

    auto knives_label = new TextWidget("Knives_label");
    knives_label->init(theme);
    knives_label->setPosition({0,40});
    knives_label->setString("KNIVES  ");
    m_hero_status->add(knives_label);

    auto knives_value = new TextWidget("Knives_value");
    knives_value->init(theme);
    knives_value->setPosition(sf::Vector2f{knives_label->getSize().x, 0});
    knives_value->setString("");
    knives_value->observe("KNIVES");
    knives_label->add(knives_value);


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
    m_hero_status->render(window);
}


