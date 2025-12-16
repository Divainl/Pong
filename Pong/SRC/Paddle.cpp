#include "Paddle.h"


Paddle::Paddle(float startX, float startY)
{
	m_position.x = startX;
	m_position.y = startY;

	if (startX < 1280 / 2) {
		m_shape.setSize(sf::Vector2f(5.0, 50));
		m_shape.setFillColor(sf::Color::Red);
		m_shape.setOutlineColor(sf::Color::White);
		m_shape.setOutlineThickness(3);
	}
	if (startX > 1280 / 2) {
		m_shape.setSize(sf::Vector2f(5.0, 50));
		m_shape.setFillColor(sf::Color::Blue);
		m_shape.setOutlineColor(sf::Color::White);
		m_shape.setOutlineThickness(3);
	}

	m_shape.setPosition(m_position);
}

sf::FloatRect Paddle::getPosition()
{
	return m_shape.getGlobalBounds();
}

sf::RectangleShape Paddle::getShape()
{
	return m_shape;
}

void Paddle::moveUp()
{
	m_isMovingUp = true;
}

void Paddle::moveDown()
{
	m_isMovingDown = true;
}

void Paddle::stopUp()
{
	m_isMovingUp = false;
}

void Paddle::stopDown()
{
	m_isMovingDown = false;
}

void Paddle::update(sf::Time dt)
{
	if (m_isMovingUp && m_position.y > 0) {
		m_position.y -= m_speed * dt.asSeconds();
	}
	if (m_isMovingDown && m_position.y + m_shape.getSize().y < 720) {
		m_position.y += m_speed * dt.asSeconds();
	}
	m_shape.setPosition(m_position);
}