#ifdef _DEBUG 
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

#include <SFML/Graphics.hpp>
#include <cstdlib>

class Game
{
    std::uint32_t screenWidth = 1200;
    std::uint32_t screenHeight = 800;

public:
    void run()
    {
        sf::RenderWindow window(
            sf::VideoMode({ screenWidth, screenHeight }), "SFML Application");
        //window.setFrameRateLimit(25);

        sf::CircleShape shape(100.f);   // TODO: DIP violation still present
        shape.setFillColor(sf::Color::Green);

        while (window.isOpen())
        {
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }

            shape.setPosition({ static_cast<float>(std::rand() % screenWidth),
                static_cast<float>(std::rand() % screenHeight) });
            shape.setFillColor(
                sf::Color{ static_cast<std::uint8_t>(std::rand() % 256),
                          static_cast<std::uint8_t>(std::rand() % 256),
                          static_cast<std::uint8_t>(std::rand() % 256) });

            window.clear();
            window.draw(shape);
            window.display();
        }
    }
};

int main() {

	Game game;

	game.run();
	
    return 0;
}
