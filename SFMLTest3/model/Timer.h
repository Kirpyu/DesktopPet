#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

namespace widget {
	class Timer
	{
	public:
		Timer(sf::Time t);
		~Timer();
		bool timerElapsed();
	private:
		sf::Time waitTime;
		sf::Time elapsedTime;
		sf::Clock clock;
	};
}


