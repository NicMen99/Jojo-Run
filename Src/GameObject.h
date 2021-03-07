//
// Created by Niccolo on 25/02/2021.
//

#ifndef JOJO_RUN_GAMEOBJECT_H
#define JOJO_RUN_GAMEOBJECT_H

#include <string>
#include <list>
#include <SFML/Graphics.hpp>
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
    Knife,
    Platform,
    Hero,
    Background
};

//@TODO
enum class GameObjectStatus {
    Created,
    Started,
    Destroyed
};

class GameObject : public Observer {
public:
    GameObject(GameObjectGroup mgroup, GameObjectType mtype, std::string mName, sf::Sprite &mSprite);
    ~GameObject() override = default;

public:
    virtual void update(int32_t delta_time);
    virtual void render(sf::RenderWindow & window);
protected:
    virtual void move(const sf::Vector2f & offset);

    void event() override {};
    void attach() override {};
    void detach() override {};

    //Getter & setter
public:
    GameObjectGroup getGroup() { return m_group; }
    GameObjectType getType() { return m_type; }
    const std::string & getName() const { return m_name; };
    const sf::Vector2f & getSpeed() const { return m_speed; };
    const sf::Vector2f & getPosition() const { return m_active_sprite.getPosition(); };
    virtual sf::FloatRect getBounds() const { return m_active_sprite.getGlobalBounds(); }
    bool isStarted() const { return m_started; };
    bool isEnable() const { return m_enabled; };
    bool isVisible() const { return m_visible; };
    bool isDestroyed() const { return m_destroyed; };

    void setStarted(bool mStarted) { m_started = mStarted; };
    void setEnable(bool mEnabled) { m_enabled = mEnabled; };
    void setVisible(bool mVisible) { m_visible = mVisible; };
    void setDestroyed(bool mInvalid) { m_destroyed = mInvalid; };
    void setPosition(sf::Vector2f position) { m_active_sprite.setPosition(position);}

    /*
    GameObject *getMParent() const;
    void setMParent(GameObject *mParent);
    const std::list<GameObject *> &getMChildren() const;
    void setMChildren(const std::list<GameObject *> &mChildren);
    */

protected:
    GameObjectGroup m_group;
    GameObjectType m_type;
    std::string m_name;
    sf::Sprite & m_active_sprite;
    sf::Vector2f m_speed = {0, 0};
    bool m_started = false;
    bool m_enabled = false;
    bool m_visible = false;
    bool m_destroyed = false;
    /*
    GameObject* m_parent;
    std::list<GameObject*> m_children;
    */
};


#endif //JOJO_RUN_GAMEOBJECT_H
