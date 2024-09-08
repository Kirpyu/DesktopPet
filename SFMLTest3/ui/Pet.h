#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "../model/Timer.h"

namespace widget {
	class Pet
	{
	public:
		Pet(sf::RenderWindow& w);
		void initPet();
		~Pet();
	

	private:
		sf::RenderWindow &window;
		void updatePet();
		void movePet();
		void renderPet();
		bool checkIfPetInMouse();
		void setWindowPos();
		void initSprite();
		void initTexture();
		void updateTexture();
		void createSprite(sf::Texture textureResource, int frame);
		
		widget::Timer timer;
		//create an array that contains all the images, then go through the images lol,4
		//if deducting x, then use flipped 

		const int desktopWidth = sf::VideoMode::getDesktopMode().width;
		const int desktopHeight = sf::VideoMode::getDesktopMode().height;
		int moveDistance = 8;

		int maxMoveAmount = 20;
		int currentMoveAmount = 0;

		enum Direction {LEFT, RIGHT};
		Direction direction;

		sf::Sprite currentSprite;

		int spritePointer = 0;
		std::vector<sf::Sprite> spriteVector;
		const std::vector<std::string> spriteResource = { "resource/walking-Sheet-2 Copy1.png", "resource/walking-Sheet-2 Copy2.png" , "resource/walking-Sheet-2 Copy3.png" , "resource/walking-Sheet-2 Copy4.png" , "resource/walking-Sheet-2 Copy5.png", "resource/walking-Sheet-2 Copy6.png", "resource/walking-Sheet-2 Copy7.png", "resource/walking-Sheet-2 Copy8.png" };

		std::vector<sf::Texture> textureVector;
	};
}


