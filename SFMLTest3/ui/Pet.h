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
		void updateTexture();

		widget::Timer timer;
		//create an array that contains all the images, then go through the images lol,4
		//if deducting x, then use flipped 

		int desktop_width = sf::VideoMode::getDesktopMode().width;
		int desktop_height = sf::VideoMode::getDesktopMode().height;
		sf::Texture texture1;
		sf::Texture texture2;
		sf::Sprite sprite;
		
	};
}


