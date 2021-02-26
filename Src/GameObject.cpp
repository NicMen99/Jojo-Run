//
// Created by Niccolo on 25/02/2021.
//

#include "GameConfig.h"
#include "GameObject.h"


void GameObject::update(int32_t delta_time) {
}

void GameObject::render(sf::RenderWindow &window) {
}

const sf::Vector2f &GameObject::getMPosition() const {
    return m_position;
}

void GameObject::setMPosition(const sf::Vector2f &mPosition) {
    m_position = mPosition;
}

/*
const sf::Vector2f &GameObject::getMSize() const {
    return m_size;
}

void GameObject::setMSize(const sf::Vector2f &mSize) {
    m_size = mSize;
}
*/

const std::string &GameObject::getMName() const {
    return m_name;
}

void GameObject::setMName(const std::string &mName) {
    m_name = mName;
}

bool GameObject::isMStarted() const {
    return m_started;
}

void GameObject::setMStarted(bool mStarted) {
    m_started = mStarted;
}

bool GameObject::isMEnable() const {
    return m_enable;
}

void GameObject::setMEnable(bool mEnable) {
    m_enable = mEnable;
}

bool GameObject::isMVisible() const {
    return m_visible;
}

void GameObject::setMVisible(bool mVisible) {
    m_visible = mVisible;
}

/*
GameObject *GameObject::getMParent() const {
    return m_parent;
}

void GameObject::setMParent(GameObject *mParent) {
    m_parent = mParent;
}

const std::list<GameObject *> &GameObject::getMChildren() const {
    return m_children;
}

void GameObject::setMChildren(const std::list<GameObject *> &mChildren) {
    m_children = mChildren;
}
*/

const sf::Vector2f &GameObject::getMSpeed() const {
    return m_speed;
}

void GameObject::setMSpeed(const sf::Vector2f &mSpeed) {
    m_speed = mSpeed-GC->getSceneSpeed();
}

void GameObject::move(const sf::Vector2f &offset) {
    m_position += offset;
}

