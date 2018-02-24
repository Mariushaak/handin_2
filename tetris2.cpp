
#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>
#include "polyminos.h"

using namespace std;

//
// Tetris
//



class Shape
{
public:
	sf::Color tiles[6][6];
	sf::Vector2i pos;

	// times since last downward movement
	float time;

	Shape();

	// reinitialise the shape: move to top and change shape
	void init();

	// move downwards once per second
	void update(float dt);

	// render the shape
	void draw(sf::RenderWindow& w);

	// rotate the shape
	void rotateLeft();
	void rotateRight();
};

void Shape::rotateLeft()
{
	sf::Color tmp[6][6];
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			tmp[i][j] = tiles[j][5 - i];
		}
	}
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			tiles[i][j] = tmp[i][j];
		}
	}
}

void Shape::rotateRight()
{
	rotateLeft();
	rotateLeft();
	rotateLeft();
}

Shape::Shape()
{
	init();
}

void Shape::init()
{
	// move to top and reset timer
	pos.y = 0;
	pos.x = 4;
	time = 0.0f;

	// fill with black tiles
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			tiles[i][j] = sf::Color::Black;
		}
	}

	int shapenr = 0;						// rand() % 7;

	for (int i = shapenr; i < 6; i++) {
		tiles[polyminos(shapenr, i, 1)][polyminos(shapenr, i, 2)] = sf::Color::White;
	}



}

void Shape::update(float dt)
{
	time += dt;
	if (time > 1) {
		time = 0;
		pos.y += 1;
	}
}

void Shape::draw(sf::RenderWindow& w)
{
	sf::CircleShape s;
	s.setRadius(8);
	s.setOrigin(8, 8);
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (tiles[i][j] != sf::Color::Black) {
				s.setFillColor(tiles[i][j]);
				s.setPosition(sf::Vector2f(pos.x * 16 + 16 * i + 100, pos.y * 16 + 16 * j + 100));
				w.draw(s);
			}
		}
	}
}

class Board
{
public:
	sf::Color tiles[12][20];

	Board();

	// add a shape to the board
	void add(Shape& shape);

	// check if a shape intersects with the board
	bool intersect(Shape& shape);

	// remove full lines - should be implemented by you
	void reduce();

	// render board
	void draw(sf::RenderWindow& w);
};

void Board::reduce()
{

}

bool Board::intersect(Shape& shape)
{
	bool intersect = false;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (tiles[i + shape.pos.x][j + shape.pos.y] != sf::Color::Black &&
				shape.tiles[i][j] != sf::Color::Black)
				intersect = true;
		}
	}
	return intersect;
}

void Board::draw(sf::RenderWindow& w)
{
	sf::CircleShape s;
	s.setRadius(8);
	s.setOrigin(8, 8);
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 20; j++) {
			s.setFillColor(tiles[i][j]);
			s.setPosition(sf::Vector2f(16 * i + 100, 16 * j + 100));
			w.draw(s);
		}
	}
}

void Board::add(Shape& shape)
{
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {

			if (shape.tiles[i][j] != sf::Color::Black) {
				tiles[i + shape.pos.x][j + shape.pos.y] = shape.tiles[i][j];

			}

		}

	}


}





Board::Board()
{
	// fill with black
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 12; j++) {
			tiles[j][i] = sf::Color::Black;
		}
	}

	// boundary
	for (int i = 0; i < 12; i++) {
		tiles[i][19] = sf::Color::Red;
	}
	for (int i = 0; i < 19; i++) {
		tiles[0][i] = sf::Color::Red;
		tiles[11][i] = sf::Color::Red;
	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(512, 512), "Tetris");
	sf::Font font; font.loadFromFile("joystix monospace.ttf");
	sf::Text score; score.setString("Score: ");
	score.setCharacterSize(30);
	score.setFont(font);
	score.setPosition(300, 200);
	sf::Clock clock;
	clock.restart();
	int score1 = 0;
	sf::Text score2;
	score2.setFont(font);
	score2.setCharacterSize(50);
	score2.setPosition(320, 250);
	
	Shape shape;

	Board board;

	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;

		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();


			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Left) {
					shape.pos.x -= 1;
					if (board.intersect(shape)) {
						shape.pos.x += 1;
						cout << "intersect left" << endl;
					}
				}
				if (event.key.code == sf::Keyboard::Right) {
					shape.pos.x += 1;
					if (board.intersect(shape)) {
						shape.pos.x -= 1;
						cout << "intersect right" << endl;
					}
				}
				if (event.key.code == sf::Keyboard::Down) {
					shape.pos.y += 1;
					if (board.intersect(shape)) {
						shape.pos.y -= 1;
						cout << "intersect down" << endl;
					}
				}
				if (event.key.code == sf::Keyboard::Up) {
					shape.rotateLeft();
					if (board.intersect(shape)) {
						shape.rotateRight();
						cout << "intersect rotate" << endl;
					}
				}
				if (event.key.code == sf::Keyboard::Space) {
					while (!board.intersect(shape)) {
						shape.pos.y += 1;
						cout << "fast down" << endl;
					}
				}
			}
		}

		float dt = clock.restart().asSeconds();

		shape.update(dt);

		int k = 20 - 1;
		for (int i = 20; i > 0; i--) {
			int count = 0;
			for (int j = 1; j < 12; j++) {
				if (board.tiles[j][i] != sf::Color::Black && board.tiles[j][i] != sf::Color::Red)
					count++;
				board.tiles[k][j] = board.tiles[i][j];
			}
			if (count == 10) {
				for (int d = 1; d < 11; d++)
					board.tiles[d][i] = sf::Color::Black;
				for (int f = i; f > 0; f--)
					for (int w = 1; w < 11; w++)
						board.tiles[w][f] = board.tiles[w][f-1];
				score1 += 10;
			}

		}
		score2.setString(to_string(score1));
		

		if (board.intersect(shape)) {
			shape.pos.y -= 1;
			board.add(shape);
			board.reduce();
			shape.init();
			if (board.intersect(shape)) {
				cout << "GAME OVER" << endl;
			}
		}

		window.clear(sf::Color::Black);
		
		board.draw(window);
		shape.draw(window);
		window.draw(score);
		window.draw(score2);
		window.display();
	}

	return 0;
}


