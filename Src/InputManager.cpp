//
// Created by Niccolo on 07/03/2021.
//
#include "InputManager.h"

void InputManager::init() {
    m_current_status.clear();
    m_previous_status.clear();
}

void InputManager::update() {
    std::swap(m_current_status, m_previous_status);
    for(auto& key : m_current_status)
        key.second = sf::Keyboard::isKeyPressed(key.first);
}

void InputManager::registerKey(const sf::Keyboard::Key &key) {
    m_current_status.insert(std::make_pair(key, false));
    m_previous_status.insert(std::make_pair(key, false));
}

void InputManager::unregisterKey(const sf::Keyboard::Key &key) {
    m_current_status.erase(key);
    m_previous_status.erase(key);
}

bool InputManager::isKeyPressed(const sf::Keyboard::Key &key) {
    if(m_current_status.count(key))
        return m_current_status[key];
    return false;
}

bool InputManager::isKeyJustPressed(const sf::Keyboard::Key &key) {
    if(m_current_status.count(key))
        if (!m_previous_status[key] && m_current_status[key])
        return true;
    return false;
}


bool InputManager::isKeyJustReleased(const sf::Keyboard::Key &key) {
    if(m_current_status.count(key))
        if (m_previous_status[key] && !m_current_status[key])
            return true;
    return false;

}

void InputManager::registerAll() {
    for(int k = sf::Keyboard::A; k < sf::Keyboard::KeyCount; k++) {
        registerKey((sf::Keyboard::Key)k);
    }
}

void InputManager::unregisterAll() {
    for(int k = sf::Keyboard::A; k < sf::Keyboard::KeyCount; k++) {
        unregisterKey((sf::Keyboard::Key)k);
    }
}

sf::Keyboard::Key InputManager::getKeyJustPressed() {
    for(int k = sf::Keyboard::A; k < sf::Keyboard::KeyCount; k++) {
        if(isKeyJustPressed((sf::Keyboard::Key)k)) {
            return (sf::Keyboard::Key)k;
        }
    }
    return sf::Keyboard::Unknown;
}



