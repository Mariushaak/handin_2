#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>

int main() {

	sf::RenderWindow window(sf::VideoMode(600, 400), "Tetris game");
	sf::RectangleShape squares;
	squares.setSize(sf::Vector2f(40, 40));
	squares.setFillColor(sf::Color::Cyan);
	

	int squareX = 280;
	int squareY = 180;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left) && (squareX > 0))
				squareX -= 10;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right) && (squareX < 560))
				squareX += 10;
		}

		squares.setPosition(squareX, squareY);
		
		
		//DRAW :


		window.clear();
		window.draw(squares);
		window.display();
	}

	return 0;
}