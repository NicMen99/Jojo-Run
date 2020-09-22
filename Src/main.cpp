#include <iostream>
#include <chrono>
#include <SFML/Graphics.hpp>


/** Qui è ancora tutto da rivedere per bene a conti fatti, è diverso da quello che abbiamo visto
 *
 *
 *
 *
 *
 *
 *
 * */
int main() {

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "JoJo Run");

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }
        window.clear();
        //Qui va la roba da disegnare a schermo
        window.display();
    }
    return 0;
}