#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>

int main() {

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Tetris game");
	sf::RectangleShape squares;
	squares.setSize(sf::Vector2f(80, 80));
	squares.setFillColor(sf::Color::Cyan);
	sf::Clock time;

	int squareX = 0;
	int squareY = 0;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left) && (squareX > 0))
				squareX -= 80;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right) && (squareX < 1120))
				squareX += 80;
		}

		squares.setPosition(squareX, squareY);
	
		if(squareY < 720)
		squareY = 80 * int (time.getElapsedTime().asSeconds());
		
		//DRAW :


		window.clear();
		window.draw(squares);
		window.display();
	}

	return 0;
}