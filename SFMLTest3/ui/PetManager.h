#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <windows.h>
#include <commdlg.h>
#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")

namespace manager {
	class PetManager
	{
	public:
		PetManager(sf::RenderWindow& w);
		void initManager();
		~PetManager();

	private:
		sf::RenderWindow &window;
		void createPet();
	};
}

