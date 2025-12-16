#pragma once
#include <SFML/Graphics.hpp>

class ball{
private:
	sf::Vector2f m_position;
	sf::RectangleShape m_BallShape;

	float m_speed = 500;
	float m_directionX = 1.0f;
	float m_directionY = 1.0f;

public:
	ball(float startx,float starty);
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();

	float getXVelocity();

	void missSides();

	void reboundTop();

	void reboundBottom();

	void hitBall();

	void update(sf::Time dt);

};

