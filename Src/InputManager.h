//
// Created by Niccolo on 07/03/2021.
//

#ifndef JOJO_RUN_INPUTMANAGER_H
#define JOJO_RUN_INPUTMANAGER_H

#include <map>
#include <SFML/Window.hpp>

class InputManager {
public:
    void init();
    void update();

    bool isKeyPressed(const sf::Keyboard::Key& key);
    bool isKeyJustPressed(const sf::Keyboard::Key& key);
    bool isKeyJustReleased(const sf::Keyboard::Key& key);
    void registerKey(const sf::Keyboard::Key& key);
    void unregisterKey(const sf::Keyboard::Key& key);
    void registerAll();
    void unregisterAll();
    sf::Keyboard::Key getKeyJustPressed();
private:
    std::map<sf::Keyboard::Key, bool> m_current_status, m_previous_status;
};


#endif //JOJO_RUN_INPUTMANAGER_H
