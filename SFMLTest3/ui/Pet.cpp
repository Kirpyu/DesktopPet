#include "Pet.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace widget {

    Pet::Pet(sf::RenderWindow &w) : window(w), timer(sf::seconds(.1)) {

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
            
 /*           renderPet();*/

            //sf::Sprite sprite_array[] = { sprite1, sprite2 , sprite3, sprite4, sprite5, sprite6, sprite7, sprite8};
            //
            //
            //int frame = texture_pointer % std::size(sprite_array);

            window.draw(currentSprite);
            window.display();
        }
    }

    //brute forced
    void Pet::initSprite() {
        texture1.loadFromFile("resource/walking-Sheet-2 Copy1.png");
        texture2.loadFromFile("resource/walking-Sheet-2 Copy2.png");
        texture3.loadFromFile("resource/walking-Sheet-2 Copy3.png");
        texture4.loadFromFile("resource/walking-Sheet-2 Copy4.png");
        texture5.loadFromFile("resource/walking-Sheet-2 Copy5.png");
        texture6.loadFromFile("resource/walking-Sheet-2 Copy6.png");
        texture7.loadFromFile("resource/walking-Sheet-2 Copy7.png");
        texture8.loadFromFile("resource/walking-Sheet-2 Copy8.png");
        
        sprite1.setTexture(texture1);
        sprite2.setTexture(texture2);
        sprite3.setTexture(texture3);
        sprite4.setTexture(texture4);
        sprite5.setTexture(texture5);
        sprite6.setTexture(texture6);
        sprite7.setTexture(texture7);
        sprite8.setTexture(texture8);

        sprite1.setScale(3, 3);
        /*sprite1.setPosition(sf::Vector2f(75, 75));*/
        currentSprite = sprite1;
        //sprite1.setScale(3, 3);
        //sprite2.setScale(3, 3);
        //sprite3.setScale(3, 3);
        //sprite4.setScale(3, 3);
        //sprite5.setScale(3, 3);
        //sprite6.setScale(3, 3);
        //sprite7.setScale(3, 3);
        //sprite8.setScale(3, 3);
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
        bool flipped = false;

        if ((rand() % 2) == 0) {
            if (window.getPosition().x < desktop_width - window.getSize().x) {
                window.setPosition(sf::Vector2i(window.getPosition().x + move_amount, window.getPosition().y));
            }
            else {
                window.setPosition(sf::Vector2i(window.getPosition().x - move_amount, window.getPosition().y));
                flipped = true;
            }
        }
        else {
            if (window.getPosition().x > 0) {
                window.setPosition(sf::Vector2i(window.getPosition().x - move_amount, window.getPosition().y));
                flipped = true;
            }
            else {
                window.setPosition(sf::Vector2i(window.getPosition().x + move_amount, window.getPosition().y));
            }
        }
        updateTexture(flipped);
    }

    void Pet::updateTexture(bool flipped) {
        texture_pointer += 1;
        sf::Sprite sprite_array[] = { sprite1, sprite2 , sprite3, sprite4, sprite5, sprite6, sprite7, sprite8 };

        int frame = texture_pointer % std::size(sprite_array);
        currentSprite = sprite_array[frame];
        if (flipped == true) {
            currentSprite.setScale(3, 3);
            
        } else {
            currentSprite.setScale(-3, 3);
            //u get 72 by getting the sprite size (24,24) then multiplying it by the sclae (3)
            currentSprite.move(sf::Vector2f(72, 0));

            
        }
        std::cout << currentSprite.getPosition().y << std::endl;
    }

    void Pet::setWindowPos() {
        window.setPosition(sf::Vector2i(desktop_width - window.getSize().x, desktop_height - window.getSize().y - 100));

    }
}

