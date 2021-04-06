//
// Created by angiolo99 on 29/01/20.
//

#ifndef JOJO_RUN_ENEMY_H
#define JOJO_RUN_ENEMY_H


#include "Entity.h"

class Bullet;

class Enemy: public Entity {
protected:
    enum State {Init, Idle, Attack, Jump, Dead};

public:
    Enemy(EntityType mtype, const std::string & name);
    ~Enemy() override;
    void init(const std::string & texture_name, sf::Vector2f scale, sf::Vector2f speed, int damage);

    void setDamage(int damage) { m_damage = damage; }
    int getDamage() const { return m_damage; };
    void setLifeBonus(int damage) { m_lifebonus = damage; }
    int getLifeBonus() const { return m_lifebonus; };

protected:
    void update(int32_t delta_time) override;
    void event(GameEvent event, Entity *collider) override;
    void updatePhysics(int32_t delta_time);
    void speedCap();
    virtual void changeState(State){}

    State m_state = State::Init;
    int m_damage = 0;
    int m_lifebonus = 0;

    sf::Clock m_dyingTimer;

};


#endif //JOJO_RUN_ENEMY_H
