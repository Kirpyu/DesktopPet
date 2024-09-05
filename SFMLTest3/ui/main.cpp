#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Pet.h"

#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")

int main() {
    sf::RenderWindow window(sf::VideoMode(72, 72), "Desktop Cat",sf :: Style :: None);

    MARGINS margins;
    margins.cxLeftWidth = -1;

    SetWindowLong(window.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
    DwmExtendFrameIntoClientArea(window.getSystemHandle(), &margins);

    //creates a variable named pet and uses its constructor, similar to Pet pet = new Pet(window)
    widget::Pet pet(window);
    pet.initPet();
    return 0;
}