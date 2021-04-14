//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_SCOREHUD_H
#define JOJO_RUN_SCOREHUD_H

#include <string>
#include <map>
#include <list>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Observer.h"

class Widget;

class ScoreHUD: public Entity, Observer {
public:
    ScoreHUD ();
    ~ScoreHUD() override;

    void init();
    void update(int32_t delta_time) override;
    void render(sf::RenderWindow & window) override;

    void observe(Subject * observed, const std::string & item_name);

private:
    Widget * m_score{};
    Widget * m_achievements{};
    Widget * m_hero_status{};

    SoundManager m_soundManager;

    void data_update(const std::string & item_name, const std::string & item_value) override;
    void attach() override;
    void detach() override;
    Subject * m_observed = nullptr;
    std::string m_observed_value;
};


#endif //JOJO_RUN_SCOREHUD_H
