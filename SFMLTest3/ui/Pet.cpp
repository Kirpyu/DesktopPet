#include "Pet.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <windows.h>
#include <commdlg.h>
#include <Dwmapi.h>
#include <cstdlib>
#include <ctime>
#pragma comment (lib, "Dwmapi.lib")

namespace widget {

    //when initialized, spawn in the sprites too
    Pet::Pet(sf::RenderWindow &w) : window(w), timer(sf::seconds(.1)) {
        
    }

    Pet::~Pet() {
    }

    void Pet::initPet() {

        srand((unsigned int)time(NULL));
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

                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        closeWindow();
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
            renderPet();
            window.display();
        }
    }

    //brute forced
    void Pet::initSprite() {

        initTexture();
        int count = 0;
        for (std::string textureResource : spriteResource) {
            createSprite(textureVector[count], count);
            count += 1;
        }

        //initialize
        currentSprite = spriteVector[0];
    }

    //create the vector of textures to use
    void Pet::initTexture() {
        for (std::string textureImage : spriteResource) {
            sf::Texture texture;
            texture.loadFromFile(textureImage);
            textureVector.push_back(texture);
        }
    }

    //creates the vector of sprites to use
    void Pet::createSprite(sf::Texture textureResource, int frame) {
        sf::Sprite sprite;

        //textures must be able to be globally accessed, hence the vector
        sprite.setTexture(textureVector[frame]);
        sprite.setScale(3, 3);

        spriteVector.push_back(sprite);
    }

    void Pet::changeResource(std::vector<std::string> resourceVector)
    {
        spriteResource = resourceVector;
    }

    //Checks if pet is inside mouse, then returns a bool value, kidna useless
    bool Pet::checkIfPetInMouse() {
        sf::Vector2i mousePos = sf::Mouse::getPosition();

        if (mousePos.x > window.getPosition().x && mousePos.x < window.getPosition().x + window.getSize().x) {
            return (mousePos.y > window.getPosition().y && mousePos.y < window.getPosition().y + window.getSize().y);
        }

        return false;
    }

    //draws the updated pet into frame
    void Pet::renderPet() {
        window.draw(currentSprite);
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

        //makes the sprite move a certain amount so it doesnt just jitter, i can make this randomized in the future
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

        spritePointer += 1;
        int frame = spritePointer % std::size(spriteResource);

        /*createSprite(spriteResource[frame], frame);*/
        currentSprite = spriteVector[frame];

        switch (direction) {
        case RIGHT:
            currentSprite.setScale(-3, 3);
            //u get 72 by getting the sprite size (24,24) then multiplying it by the scale (3)
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

    void Pet::closeWindow() {
        window.close();
    }
}

