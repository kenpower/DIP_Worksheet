﻿#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
//#pragma comment(lib,"thor-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
//#pragma comment(lib,"thor.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
//#pragma comment(lib,"libyaml-cppmdd") 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

class Game {
    int screenWidth = 1200;
    int screenHeight = 800;
public:
    void run() {
		{
			sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Application");
			window.setFramerateLimit(25);
			sf::CircleShape shape(100.f);
			shape.setFillColor(sf::Color::Green);
			while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}
				
				shape.setPosition(rand() % screenWidth, rand() % screenHeight);
				shape.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
				
				window.draw(shape);
				window.display();
				window.draw(shape); //paint on second buffer also to avoiud flicker
			}
		}
    }
};

int main() {

	Game game;

	game.run();
	
    return 0;
}
