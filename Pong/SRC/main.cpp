#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ball.h"
#include "Paddle.h"
#include <sstream>

int main() {
    sf::VideoMode VM({ 1280, 720 }, 24);
    sf::RenderWindow window(VM, "Pong Game");
	sf::Clock clock;
    ball myball(1280/2,720/2);
	Paddle leftPaddle(50, 720 / 2 - 50 / 2);
	Paddle rightPaddle(1280 - 50 - 5, 720 / 2 - 50 / 2);

    sf::SoundBuffer hitBuffer("SRC/Sounds/hit.wav");
    sf::SoundBuffer wallBuffer("SRC/Sounds/wall.wav");
    sf::SoundBuffer scoreBuffer("SRC/Sounds/score.wav");


    sf::Sound hitSound(hitBuffer);
    sf::Sound wallSound(wallBuffer);
    sf::Sound scoreSound(scoreBuffer);

    sf::Font font;
    if (!font.openFromFile("SRC/Fonts/Pixel Emulator.otf")) {
        std::cerr << "Failed to load font: SRC/Fonts/Pixel Emulator.otf" << std::endl;
        return 1;
    }
    sf::Text fontScore1(font);
    fontScore1.setPosition({ 5, 0 });
    fontScore1.setCharacterSize(24);
    fontScore1.setFillColor(sf::Color::White);

	int score1 = 0;
    std::stringstream ss1;
    ss1 << "Score: " << score1;

    fontScore1.setString(ss1.str());

	sf::Text fontScore2(font);
	fontScore2.setPosition({ 1280 - 150, 0 });
	fontScore2.setCharacterSize(24);
	fontScore2.setFillColor(sf::Color::White);

	int score2 = 0;
	std::stringstream ss2;
	ss2 << "Score: " << score2;

	fontScore2.setString(ss2.str());

	sf::Text fontStartMenu(font);
	fontStartMenu.setPosition({ 400, 300 });
	fontStartMenu.setCharacterSize(24);
	fontStartMenu.setFillColor(sf::Color::White);

    std::stringstream ssStartMenu;
	ssStartMenu << "Press Enter to Start\nPress W/S to move left paddle\nPress Up/Down to move right paddle\nPress Escape to quit";
	bool gameStarted = false;

	fontStartMenu.setString(ssStartMenu.str());

    sf::Time dt;

    float bounceTimer = 0.1f;

    const auto onClose = [&window](const sf::Event::Closed&) {
        window.close();
        };
    const auto onKeyPressed = [&window](const sf::Event::KeyPressed& keyPressed) {
        if (keyPressed.scancode == sf::Keyboard::Scancode::Escape) {
            window.close();
        }
    };

    while (window.isOpen()) {

        window.handleEvents(onClose, onKeyPressed);

        dt = clock.restart();
        bounceTimer -= dt.asSeconds();

        if ((myball.getPosition().findIntersection(leftPaddle.getPosition())) || myball.getPosition().findIntersection(rightPaddle.getPosition())) {
            if (bounceTimer < 0) {
				hitSound.play();
                myball.hitBall();
                bounceTimer = 0.1f;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
            gameStarted = true;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            leftPaddle.moveUp();
        }
        else {
            leftPaddle.stopUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            leftPaddle.moveDown();
        }
        else {
            leftPaddle.stopDown();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            rightPaddle.moveUp();
        }
        else {
            rightPaddle.stopUp();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            rightPaddle.moveDown();
        }
        else {
            rightPaddle.stopDown();
        }

        if (myball.getPosition().position.x < 0) {
            score2++;
            ss2.str("");
            ss2 << "Score: " << score2;
            fontScore2.setString(ss2.str());
            myball.missSides();
            scoreSound.play();
        }
        if (myball.getPosition().position.x + myball.getPosition().size.x > 1280) {
            score1++;
            ss1.str("");
            ss1 << "Score: " << score1;
            fontScore1.setString(ss1.str());
            myball.missSides();
			scoreSound.play();
        }
        if (myball.getPosition().position.y < 0 && bounceTimer < 0) {
            myball.reboundTop();
            bounceTimer = 0.1f;
			wallSound.play();
        }
        if (myball.getPosition().position.y + myball.getPosition().size.y > 720 && bounceTimer < 0) {
            myball.reboundBottom();
            bounceTimer = 0.1f;
			wallSound.play();
        }

        window.clear();

        if (gameStarted == true) {
            myball.update(dt);
            window.draw(myball.getShape());
        }
		leftPaddle.update(dt);
		rightPaddle.update(dt);

        if (gameStarted == false) {
            window.draw(fontStartMenu);
        }

		window.draw(leftPaddle.getShape());
		window.draw(rightPaddle.getShape());
		window.draw(fontScore1);
		window.draw(fontScore2);

        window.display();

    }
    return 0;
}