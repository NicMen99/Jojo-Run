//
// Created by angiolo99 on 23/01/20.
//

#include "Game.h"
#include "Widgets/Widget.h"
#include "Widgets/TextWidget.h"
#include "Widgets/ImageWidget.h"
#include "ScoreHUD.h"


const char * font_name = "arcadeclassic";
const unsigned int font_size = 40;


ScoreHUD::ScoreHUD() :
        Entity(EntityGroup::Scene, EntityType::Hud, "HUD")
{
    if(m_observed)
        detach();
}

ScoreHUD::~ScoreHUD() {
    delete m_score;
    delete m_hero_status;
}

void ScoreHUD::init() {

    WidgetTheme theme;
    theme.font_name = "gameover";
    theme.font_size = 100;
    theme.font_color = sf::Color::White;

    /* score */
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
    score_label->add(score_value);
    score_value->observe(STATS, Stats::Score);

    /* hero */
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
    healthPoints_label->add(healthPoints_value);
    healthPoints_value->observe(STATS,Stats::Health);

    auto knives_label = new TextWidget("Knives_label");
    knives_label->init(theme);
    knives_label->setPosition({0,40});
    knives_label->setString("KNIVES  ");
    m_hero_status->add(knives_label);

    auto knives_value = new TextWidget("Knives_value");
    knives_value->init(theme);
    knives_value->setPosition(sf::Vector2f{knives_label->getSize().x, 0});
    knives_value->setString("");
    knives_label->add(knives_value);
    knives_value->observe(STATS,Stats::Knives);

    /* achievement */
    m_achievements = new Widget("achiemements");
    m_achievements->setPosition({400, 30});

    auto achievement_label = new TextWidget("achievement_message");
    achievement_label->init(theme);
    achievement_label->setPosition({0,0});
    m_achievements->add(achievement_label);
    observe(STATS,Achievements::Distance);
    observe(STATS, Achievements::Killed);
    observe(STATS, Achievements::ConsecutiveKilled);
}

void ScoreHUD::update(int32_t delta_time) {
    m_score->update(delta_time);
    m_achievements->update(delta_time);
    m_hero_status->update(delta_time);
}

void ScoreHUD::render(sf::RenderWindow &window) {
    m_score->render(window);
    m_achievements->render(window);
    m_hero_status->render(window);
}

/**/

void ScoreHUD::data_update(const std::string & item_name, const std::string & item_value){
    TextWidget* widget = dynamic_cast<TextWidget*>(m_achievements->findObjectByName("achievement_message"));

    if(item_name == Achievements::Distance) {
        widget->setString("MILE RUNNER:  " + item_value + " METERS RUN");
    }
    if(item_name == Achievements::Killed) {
        widget->setString("KILLING SPREE:  KILLED " + item_value + " ENEMIES");
    }
    if(item_name == Achievements::ConsecutiveKilled) {
        widget->setString("COMBO:  KILLED " + item_value + " CONSECUTIVE KILLS");
    }

    widget->startTimer(sf::seconds(3));
}

void ScoreHUD::observe(Subject * observed, const std::string & item_name) {
    m_observed = observed;
    m_observed_value = item_name;
    attach();
}

void ScoreHUD::attach() {
    m_observed->subscribe(this, m_observed_value);
}

void ScoreHUD::detach() {
    m_observed->unsubscribe(this, m_observed_value);
}