#include "Pet.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <windows.h>
#include <commdlg.h>
#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")

namespace widget {

    //when initialized, spawn in the sprites too
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

                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        OPENFILENAME ofn;       // common dialog box structure
                        wchar_t szFile[260];       // buffer for file name

                        // Initialize OPENFILENAME
                        ZeroMemory(&ofn, sizeof(ofn));
                        ofn.lStructSize = sizeof(ofn);
                        ofn.lpstrFile = szFile;
                        ofn.lpstrFile[0] = '\0';
                        ofn.nMaxFile = sizeof(szFile);
                        ofn.lpstrFilter = L"Iamges\0*.png\0";
                        ofn.nFilterIndex = 1;
                        ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_ALLOWMULTISELECT | OFN_EXPLORER;

                        // Display the Open dialog box. 

                        if (GetOpenFileName(&ofn) == TRUE) {
                            wchar_t * str = ofn.lpstrFile;
                            std::wstring directory = str;
                            // goes to the file name, prints out the entire file name if pointer lands on it, starting from where it lands, +1 because there is a buffer of /0 which is null
                            str += (directory.length() + 1);
                            while (*str) {

                                //gets the current file name we are on
                                std::wstring filename = str;
                                
                                //since pointer does not move yet, print the current one
                                std::wcout << directory + L"\\" + str << std::endl;

                                //go to the next 
                                str += (filename.length() + 1);
                            }
                        }
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

            window.draw(currentSprite);
            window.display();
        }
    }

    //brute forced
    void Pet::initSprite() {
        //for (std::string textureResource : spriteResource) {
        //    createSprite(textureResource, count);
        //}
        initTexture();
        createSprite(spriteResource[0], 0);
    }

    void Pet::initTexture() {
        for (std::string textureImage : spriteResource) {
            sf::Texture texture;
            texture.loadFromFile(textureImage);
            textureVector.push_back(texture);
        }
    }

    //creates the sprite
    void Pet::createSprite(std::string textureResource, int frame) {
        sf::Sprite sprite;

        //textures must be able to be globally accessed, hence the vector
        sprite.setTexture(textureVector[frame]);
        sprite.setScale(3, 3);

        currentSprite = sprite;
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

        spritePointer += 1;
        int frame = spritePointer % std::size(spriteResource);

        createSprite(spriteResource[frame], frame);

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
}

