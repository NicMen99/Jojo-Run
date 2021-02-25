//
// Created by Niccolo on 25/02/2021.
//

#ifndef JOJO_RUN_GAMEOBJECT_H
#define JOJO_RUN_GAMEOBJECT_H

#include <string>
#include <list>
#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject() = default;
    virtual ~GameObject() = default;


    //Getter & setter
public:
    const sf::Vector2f &getMPosition() const;
    void setMPosition(const sf::Vector2f &mPosition);
    /*
    const sf::Vector2f &getMSize() const;
    void setMSize(const sf::Vector2f &mSize);
    */
    const sf::Vector2f &getMSpeed() const;
    void setMSpeed(const sf::Vector2f &mSpeed);
    const std::string &getMName() const;
    void setMName(const std::string &mName);
    bool isMStarted() const;
    void setMStarted(bool mStarted);
    bool isMEnable() const;
    void setMEnable(bool mEnable);
    bool isMVisible() const;
    void setMVisible(bool mVisible);
    /*
    GameObject *getMParent() const;
    void setMParent(GameObject *mParent);
    const std::list<GameObject *> &getMChildren() const;
    void setMChildren(const std::list<GameObject *> &mChildren);
    */
    virtual sf::FloatRect getMBounds() const {return {0,0,0,0};}

public:
    virtual void update(int32_t delta_time);
    virtual void render(sf::RenderWindow& window);
    virtual void move(const sf::Vector2f &offset);

private:
    sf::Vector2f m_position;
    sf::Vector2f m_speed;
    std::string m_name;
    bool m_started;
    bool m_enable;
    bool m_visible;
    /*
    GameObject* m_parent;
    std::list<GameObject*> m_children;
    */
};


#endif //JOJO_RUN_GAMEOBJECT_H
