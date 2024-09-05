#include "Pet.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")

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

        sf::Vector2i grabbedOffset;
        bool grabbedWindow = false;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        grabbedOffset = window.getPosition() - sf::Mouse::getPosition();
                        grabbedWindow = true;
                    }
                }
                else if (event.type == sf::Event::MouseButtonReleased)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                        grabbedWindow = false;
                }
                else if (event.type == sf::Event::MouseMoved)
                {
                    if (grabbedWindow)
                        window.setPosition(sf::Mouse::getPosition() + grabbedOffset);
                }
            }

            // and if stopped == false
            if (timer.timerElapsed()) {
                updatePet();
            }

            window.clear(sf::Color::Transparent);
            
 /*           renderPet();*/

            //sf::Sprite spriteArray[] = { sprite1, sprite2 , sprite3, sprite4, sprite5, sprite6, sprite7, sprite8};
            //
            //
            //int frame = texturePointer % std::size(spriteArray);

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

        currentSprite = sprite1;
    }

    //Checks if pet is inside mouse, then returns a bool value, kidna useless
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

    //updates the pets texture and position
    void Pet::updatePet() {
        if ((rand() % 2) == 0) {
            //while the window's x coordinate is less than the window's size, then move pet towards the right, else move it left because theres no space on the right
            if (window.getPosition().x < desktopWidth - window.getSize().x) {
                if (currentMoveAmount == 0) {
                    direction = RIGHT;
                }
            }
            else {
                direction = LEFT;
            }
        }

        else {
            if (window.getPosition().x > window.getSize().x) {
                if (currentMoveAmount == 0) {
                    direction = LEFT;
                }
            }
            else {
                direction = RIGHT;
            }
        }

        currentMoveAmount += 1;
        movePet();
        updateTexture();
        if (currentMoveAmount >= maxMoveAmount) {
            currentMoveAmount = 0;
        }
    }

    //moves the window the pet is in
    void Pet::movePet() {
        
        switch (direction) {
        case LEFT:
            window.setPosition(sf::Vector2i(window.getPosition().x - moveDistance, window.getPosition().y));
            break;
        case RIGHT:
            window.setPosition(sf::Vector2i(window.getPosition().x + moveDistance, window.getPosition().y));
            break;  
        }


    }

    //updates the pets texture
    void Pet::updateTexture() {
        texturePointer += 1;
        sf::Sprite spriteArray[] = { sprite1, sprite2 , sprite3, sprite4, sprite5, sprite6, sprite7, sprite8 };

        int frame = texturePointer % std::size(spriteArray);
        currentSprite = spriteArray[frame];

        switch (direction) {
        case RIGHT:
            currentSprite.setScale(-3, 3);
            //u get 72 by getting the sprite size (24,24) then multiplying it by the sclae (3)
            currentSprite.move(sf::Vector2f(72, 0));
            break;
        case LEFT:
            currentSprite.setScale(3, 3);
            break;
        }
    }

    void Pet::setWindowPos() {
        window.setPosition(sf::Vector2i(desktopWidth - window.getSize().x, desktopHeight - window.getSize().y - 100));

    }
}

