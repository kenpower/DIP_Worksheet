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

// Task 1: Abstract Shape interface
// High-level abstraction that both Game and concrete shapes depend on.
// Game (high-level) and Circle/Square (low-level) both depend on this abstraction.
class Shape {
public:
    virtual void setPosition(float x, float y) = 0;
    virtual void setColor(sf::Color color) = 0;
    virtual sf::Drawable& getDrawable() = 0;
    // Advanced Task 1: replace separate setPosition/setColor calls with a single
    // changeAppearance() so the Game class does not depend on position/colour details.
    virtual void changeAppearance(int screenWidth, int screenHeight) = 0;
    virtual ~Shape() = default;
};

// Task 2: Concrete Circle class implementing the Shape interface
class Circle : public Shape {
    sf::CircleShape circle;
public:
    Circle(float radius) : circle(radius) {}

    void setPosition(float x, float y) override {
        circle.setPosition(x, y);
    }

    void setColor(sf::Color color) override {
        circle.setFillColor(color);
    }

    sf::Drawable& getDrawable() override {
        return circle;
    }

    void changeAppearance(int screenWidth, int screenHeight) override {
        circle.setPosition(static_cast<float>(rand() % screenWidth),
                           static_cast<float>(rand() % screenHeight));
        circle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
    }
};

// Advanced Task 2: Square concrete class — Game can switch to Square without any
// changes inside the Game class, demonstrating DIP.
class Square : public Shape {
    sf::RectangleShape square;
public:
    Square(float size) : square(sf::Vector2f(size, size)) {}

    void setPosition(float x, float y) override {
        square.setPosition(x, y);
    }

    void setColor(sf::Color color) override {
        square.setFillColor(color);
    }

    sf::Drawable& getDrawable() override {
        return square;
    }

    void changeAppearance(int screenWidth, int screenHeight) override {
        square.setPosition(static_cast<float>(rand() % screenWidth),
                           static_cast<float>(rand() % screenHeight));
        square.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
        float newSize = static_cast<float>(50 + rand() % 150);
        square.setSize(sf::Vector2f(newSize, newSize));
    }
};

// Task 3: Game class refactored to depend only on the Shape abstraction.
// There is no reference to any concrete shape class (Circle or Square) inside Game.
class Game {
    int screenWidth = 1200;
    int screenHeight = 800;
    Shape* shape;
public:
    Game(Shape* shape) : shape(shape) {}

    void run() {
        sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Application");
        window.setFramerateLimit(25);
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            shape->changeAppearance(screenWidth, screenHeight);

            window.clear();
            window.draw(shape->getDrawable());
            window.display();
        }
    }
};

int main() {
    Circle circle(100.f);
    // To test DIP: swap Circle for Square without touching the Game class.
    // Square square(100.f);

    Game game(&circle);
    game.run();

    return 0;
}
