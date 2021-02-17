//
// Created by angiolo99 on 23/01/20.
//

#ifndef JOJO_RUN_MAP_H
#define JOJO_RUN_MAP_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Config.hpp>

class Map {
public:
    Map();
    Map(const std::string &Title, const sf::Vector2u &Size);
    ~Map() { map.close(); }

    void update();
    void clear();
    void draw(sf::Drawable &Drawable);
    void display();

    sf::RenderWindow *getRenderMap();
    bool isClosed() const { return closed; }
    const sf::Vector2u getMapSize() const;

    sf::Event event;
private:
    sf::RenderWindow map;
    sf::Vector2u mapSize;
    std::string mapTitle;
    bool closed = false;
};

#endif //JOJO_RUN_MAP_H
