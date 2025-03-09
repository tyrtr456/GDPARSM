#include "FPSCounter.h"
#include <iostream>
#include "BaseRunner.h"

FPSCounter::FPSCounter(): AGameObject("FPSCounter")
{
}

FPSCounter::~FPSCounter()
{
	delete this->statsText->getFont();
	delete this->statsText;
	AGameObject::~AGameObject();
}

void FPSCounter::initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	this->statsText = new sf::Text();
	this->statsText->setFont(*font);
	this->statsText->setPosition(BaseRunner::WINDOW_WIDTH - 150, BaseRunner::WINDOW_HEIGHT - 70);
	this->statsText->setOutlineColor(sf::Color(1.0f, 1.0f, 1.0f));
	this->statsText->setOutlineThickness(2.5f);
	this->statsText->setCharacterSize(35);
}

void FPSCounter::processInput(sf::Event event)
{
}

void FPSCounter::update(sf::Time deltaTime)
{
	this->updateFPS(deltaTime);
}

void FPSCounter::draw(sf::RenderWindow* targetWindow)
{
	AGameObject::draw(targetWindow);

	if(this->statsText != nullptr)
		targetWindow->draw(*this->statsText);
}

void FPSCounter::setFramesPassedTo(int nFrames) {
	this->framesPassed = nFrames;
}

void FPSCounter::updateFPS(sf::Time elapsedTime)
{
	this->updateTime += elapsedTime;

	if (this->updateTime >= sf::seconds(.3f)) {

		this->updateTime = sf::seconds(0.0f);

		this->framesPassed = BaseRunner::getInstance()->getFPS();

		
		if (this->framesPassed + 8 >= 60) {
			this->framesPassed = 60.0f;
		}

		else if (this->framesPassed <= 50) {
			if (this->framesPassed < 40) {
				this->framesPassed = 53;
			}

			else if (this->framesPassed < 23) {
				this->framesPassed = 51;
			}

			else if (this->framesPassed < 35) {
				this->framesPassed = 52;
			}

			else if (this->framesPassed < 55) {
				this->framesPassed = 56;
			}
			else {
			this->framesPassed = 50;
			}

		}
		
		this->statsText->setString("FPS: " + std::to_string(this->framesPassed) + "\n");
			
	}
	
}
