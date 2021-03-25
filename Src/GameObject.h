//
// Created by Niccolo on 25/02/2021.
//

#ifndef JOJO_RUN_GAMEOBJECT_H
#define JOJO_RUN_GAMEOBJECT_H

#include <memory>
#include <string>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animator.h"
#include "Observer.h"


enum class GameObjectGroup {
    Scene,
    Map,
    Bullet,
    Enemy,
    Powerup,
    Hero
};

enum class GameObjectType {
    Block, Wall,
    FireEnemy, HamonEnemy, EmeraldEnemy,
    Weapon, Shield,
    Knife, FireBullet, EmeraldBullet,
    Platform, SPlatform, MPlatform, XPlatform,
    Hero,
    Hud,
    Background, Sky, City, SkyScrapers, Bridge
};


class GameObject {
public:
    GameObject(GameObjectGroup mgroup, GameObjectType mtype, std::string  mName);
    virtual ~GameObject() = default;

public:
    virtual void update(int32_t delta_time);
    virtual void render(sf::RenderWindow & window);
    virtual void collision(GameObject * collider) {}

protected:
    virtual void move(const sf::Vector2f & offset);
    virtual void applyImpulse(const sf::Vector2f & acceleration, int32_t delta_time);

    //Getter & setter
public:
    GameObjectGroup getGroup() { return m_group; }
    GameObjectType getType() { return m_type; }
    const std::string & getName() const { return m_name; };

public:
    const sf::Vector2f & getPosition() const { return m_position; };
    virtual sf::FloatRect getBounds() const; // { return m_animator.getCurrentFrame()->getGlobalBounds(); }
    bool isStarted() const { return m_started; };
    bool isEnabled() const { return m_enabled; };
    bool isVisible() const { return m_visible; };
    bool isDestroyed() const { return m_destroyed; };

public:
    void setStarted(bool mStarted) { m_started = mStarted; };
    void setEnabled(bool mEnabled) { m_enabled = mEnabled; };
    void setVisible(bool mVisible) { m_visible = mVisible; };
    void setDestroyed() { m_destroyed = true; };
    void setPosition(sf::Vector2f position) { m_position = position;}
    void setSpeed(sf::Vector2f speed) { m_speed = speed; }

public:
    void addSound(const std::string & sound_name, const std::string & sound_resource);

protected:
    void playSound(const std::string & sound_name, float volume = 100.f);

protected:
    GameObjectGroup m_group;
    GameObjectType m_type;
    std::string m_name;
    sf::Vector2f m_position = {0, 0};
    sf::Vector2f m_speed = {0, 0};
    bool m_started = false;
    bool m_enabled = true;
    bool m_visible = true;
    bool m_destroyed = false;

    Animator m_animator;

    sf::Sound m_sound;
    std::string m_active_sound;
    std::map<std::string, std::string> m_sound_map;
};


#endif //JOJO_RUN_GAMEOBJECT_H
