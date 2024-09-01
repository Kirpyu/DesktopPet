#include "Pet.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace widget {

    Pet::Pet(sf::RenderWindow &w) : window(w), timer(sf::seconds(1)) {

    }

    Pet::~Pet() {

    }

    void Pet::initPet() {
        initSprite();
        sf::CircleShape shape(100.f);
        shape.setFillColor(sf::Color::Green);
        setWindowPos();

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                    if (checkIfPetInMouse()) {
                        
                    }
            }

            // and if stopped == false
            if (timer.timerElapsed()) {
                updatePet();
            }

            window.clear(sf::Color::Transparent);
            
            renderPet();

            window.draw(sprite);
            window.display();
        }
    }

    void Pet::initSprite() {
        
        if (!texture1.loadFromFile("resource/cheese.png")) {
        }
        if (!texture2.loadFromFile("resource/catPaw.png")) {
        }
        
        sprite.setTexture(texture1);
        
    }
    bool Pet::checkIfPetInMouse() {
        sf::Vector2i mousePos = sf::Mouse::getPosition();

        if (mousePos.x > window.getPosition().x && mousePos.x < window.getPosition().x + window.getSize().x) {
            return (mousePos.y > window.getPosition().y && mousePos.y < window.getPosition().y + window.getSize().y);
        }

        return false;
    }

    void Pet::renderPet() {
        // draw it onto the frame
    }

    void Pet::updatePet() {
        if ((rand() % 2) == 0) {
            if (window.getPosition().x < desktop_width - window.getSize().x) {
                window.setPosition(sf::Vector2i(window.getPosition().x + 30, window.getPosition().y));
            }
            else {
                window.setPosition(sf::Vector2i(window.getPosition().x - 30, window.getPosition().y));
            }
        }
        else {
            if (window.getPosition().x > 0) {
                window.setPosition(sf::Vector2i(window.getPosition().x - 30, window.getPosition().y));
            }
            else {
                window.setPosition(sf::Vector2i(window.getPosition().x + 30, window.getPosition().y));
            }
            
        }
    }

    void Pet::updateTexture() {

    }

    void Pet::setWindowPos() {
        window.setPosition(sf::Vector2i(desktop_width - window.getSize().x, desktop_height - window.getSize().y - 100));

    }
}

