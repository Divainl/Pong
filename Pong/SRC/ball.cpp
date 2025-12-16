#include "ball.h"


ball::ball(float startx, float starty)
{
	m_position.x = startx;
	m_position.y = starty;
	m_BallShape.setSize(sf::Vector2f(10,10));
	//m_BallShape.setFillColor(sf::Color::White);
	m_BallShape.setPosition(m_position);
}

sf::FloatRect ball::getPosition()
{
	return m_BallShape.getGlobalBounds();
}

sf::RectangleShape ball::getShape()
{
	return m_BallShape;
}

float ball::getXVelocity()
{
	return m_directionX;
}

void ball::missSides()
{
	m_position.x = 1280 / 2;
	m_position.y = 720/2;
}

void ball::reboundTop()
{
	m_directionY = -m_directionY;
}

void ball::reboundBottom()
{
	m_directionY = -m_directionY;
}

void ball::hitBall()
{
	m_directionX = -m_directionX;
}

void ball::update(sf::Time dt)
{
	m_position.x += m_directionX * m_speed * dt.asSeconds();
	m_position.y += m_directionY * m_speed * dt.asSeconds();
	m_BallShape.setPosition(m_position);
}