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
    GameObject(GameObjectGroup::Scene, GameObjectType::Hud, "HUD")
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

}

void ScoreHUD::render(sf::RenderWindow &window) {
    m_score->render(window);
    m_hero_status->render(window);
}


