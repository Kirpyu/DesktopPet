#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Pet.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(72, 72), "Desktop Cat",sf :: Style :: None);
    //creates a variable named pet and uses its constructor, similar to Pet pet = new Pet(window)
    widget::Pet pet(window);
    pet.initPet();
    return 0;
}