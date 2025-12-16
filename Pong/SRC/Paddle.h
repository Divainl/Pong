#pragma once
#include <SFML/Graphics.hpp>

class Paddle
{
private:
	sf::RectangleShape m_shape;
	sf::Vector2f m_position;
	float m_speed = 1100.0f;

	bool m_isMovingUp = false;
	bool m_isMovingDown = false;

public:
	Paddle(float startX, float startY);
	
	sf::RectangleShape getShape();
	sf::FloatRect getPosition();

	void moveUp();
	void moveDown();
	void stopUp();
	void stopDown();

	void update(sf::Time dt);

};

