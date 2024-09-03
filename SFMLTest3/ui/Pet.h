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
		void renderPet();
		bool checkIfPetInMouse();
		void setWindowPos();
		void initSprite();
		void updateTexture(bool flipped);
		
		widget::Timer timer;
		//create an array that contains all the images, then go through the images lol,4
		//if deducting x, then use flipped 

		int desktop_width = sf::VideoMode::getDesktopMode().width;
		int desktop_height = sf::VideoMode::getDesktopMode().height;
		int move_amount = 8;
		sf::Texture texture1;
		sf::Texture texture2;
		sf::Texture texture3;
		sf::Texture texture4;
		sf::Texture texture5;
		sf::Texture texture6;
		sf::Texture texture7;
		sf::Texture texture8;

		int texture_pointer = 0;
		sf::Sprite sprite1;
		sf::Sprite sprite2;
		sf::Sprite sprite3;
		sf::Sprite sprite4;
		sf::Sprite sprite5;
		sf::Sprite sprite6;
		sf::Sprite sprite7;
		sf::Sprite sprite8;

		sf::Sprite currentSprite;
	};
}


