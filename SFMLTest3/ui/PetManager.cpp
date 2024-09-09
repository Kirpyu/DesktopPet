#include "PetManager.h"
#include "Pet.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include<thread>
#include <windows.h>
#include <commdlg.h>
#include <Dwmapi.h>
#pragma comment (lib, "Dwmapi.lib")


namespace manager {
	PetManager::PetManager(sf::RenderWindow &w) : window(w) {
		//initManager();
	}

	PetManager::~PetManager()
	{

	}

	void PetManager::initManager() {
		
	}

	void PetManager::createPet() {
		sf::RenderWindow petWindow
			
;
		petWindow.create(sf::VideoMode(72, 72), "Desktop Cat", sf::Style::None);
		
		MARGINS margins;
		margins.cxLeftWidth = -1;

		SetWindowLong(petWindow.getSystemHandle(), GWL_STYLE, WS_POPUP | WS_VISIBLE);
		DwmExtendFrameIntoClientArea(petWindow.getSystemHandle(), &margins);

		widget::Pet pet(petWindow);
		pet.initPet();
		

		std::cout << "Pressed" << std::endl;
	}
}
