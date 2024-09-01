#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Pet.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Desktop Cat",sf :: Style :: Titlebar | sf::Style::Close | sf::Style::None);
    //creates a variable named pet and uses its constructor, similar to Pet pet = new Pet(window)
    widget::Pet pet(window);
    pet.initPet();
    return 0;
}