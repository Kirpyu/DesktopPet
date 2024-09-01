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
		sf::Time wait_time;
		sf::Time elapsed_time;
		sf::Clock clock;
	};
}


