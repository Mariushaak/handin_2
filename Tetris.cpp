#include <SFML/Graphics.hpp>
#include <vector>
#include <time.h>

const int windowHeight = 1440;
const int windowWidth = 1200;
const int menuWidth = 400;
int main() {
	sf::Font font;
	font.loadFromFile("joystix monospace.ttf");
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Tetris game");
	sf::RectangleShape squares;
	sf::RectangleShape playField;
	sf::ConvexShape figure1;
	playField.setSize(sf::Vector2f(800, windowHeight));
	playField.setFillColor(sf::Color::Black);
	playField.setOutlineThickness(windowWidth / 100);
	playField.setOutlineColor(sf::Color::White);
	squares.setSize(sf::Vector2f((windowWidth - menuWidth) / 10, (windowWidth - menuWidth) / 10));
	squares.setFillColor(sf::Color::Cyan);
	sf::Clock time;
	figure1.setPointCount(8);

	int squareX = 0;
	int squareY = 0;
	bool downPressed = 0;
	while (window.isOpen()) {
		sf::Event event;
		sf::Text score;
		
		score.setFont(font);
		score.setFillColor(sf::Color::White);
		score.setString("Score: ");
		score.setCharacterSize(50);
		score.setPosition(850, 200);
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left) && (squareX > 0))
				squareX -= 80;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right) && (squareX < 720))
				squareX += 80;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down)) {
				squareY = windowHeight - ((windowWidth - menuWidth) / 10);
				downPressed = true;
			}
		}

		squares.setPosition(squareX, squareY);
		playField.setPosition(0, 0);
		if((squareY < windowHeight - ((windowWidth - menuWidth) / 10)) && !downPressed)
		squareY = (windowWidth - menuWidth) / 10 * int (time.getElapsedTime().asSeconds());
		
		//DRAW :


		window.clear();
		window.draw(playField);
		window.draw(squares);
		window.draw(score);
		window.display();
	}

	return 0;
}