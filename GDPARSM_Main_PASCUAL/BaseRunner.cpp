#include "BaseRunner.h"
#include "GameObjectManager.h"
#include "BGObject.h"
#include "TextureManager.h"
#include "TextureDisplay.h"
#include "FPSCounter.h"

/// <summary>
/// This demonstrates a running parallax background where after X seconds, a batch of assets will be streamed and loaded.
/// </summary>
const float FRAME_RATE = 60.0f;
const sf::Time BaseRunner::TIME_PER_FRAME = sf::seconds(1.f / FRAME_RATE);
const int BaseRunner::MAX_OBJECTS = 479;
const float BaseRunner::SPACING = 0.3f;
const float BaseRunner::ROW_SPACING = 1.0f;

BaseRunner* BaseRunner::sharedInstance = NULL;

BaseRunner::BaseRunner() :
	window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "HO: A Barrage of Threads - PASCUAL", sf::Style::Close) {

	sharedInstance = this;
	this->window.setFramerateLimit(FRAME_RATE);

	//load initial textures
	TextureManager::getInstance()->loadFromAssetList();

	//load objects
	BGObject* bgObject = new BGObject("BGObject");
	GameObjectManager::getInstance()->addObject(bgObject);

	TextureDisplay* display = new TextureDisplay();
	GameObjectManager::getInstance()->addObject(display);

	FPSCounter* fpsCounter = new FPSCounter();
	GameObjectManager::getInstance()->addObject(fpsCounter);
}

void BaseRunner::run() {

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	while (this->window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			this->fps = floor(1.0f / timeSinceLastUpdate.asSeconds());
			//FPSCounter* fpsCounter = (FPSCounter*)GameObjectManager::getInstance()->findObjectByName("FPSCounter");
			//fpsCounter->setFramesPassedTo(this->fps);

			timeSinceLastUpdate -= TIME_PER_FRAME;

			currentTime = clock.getElapsedTime();

			processEvents();
			update(elapsedTime);

		}


		render();
	}
}
	/*
	sf::Clock clock;
	sf::Time previousTime = clock.getElapsedTime();
	sf::Time currentTime;
	while (this->window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		float deltaTime = currentTime.asSeconds() - previousTime.asSeconds();
		this->fps = floor(1.0f / deltaTime);

		processEvents();
		update(sf::seconds(1.0f / this->fps));
		render();

		previousTime = currentTime;

	} */


void BaseRunner::processEvents()
{
	sf::Event event;
	if (this->window.pollEvent(event)) {
		switch (event.type) {
		
		default: GameObjectManager::getInstance()->processInput(event); break;
		case sf::Event::Closed:
			this->window.close();
			break;

		}
	}
}

void BaseRunner::update(sf::Time elapsedTime) {

	GameObjectManager::getInstance()->update(elapsedTime);

	/*
	 Old method (no longer necessary nor compatible with threading)
	if (nObjects < MAX_OBJECTS) {
			
			IconObject* iconObject = new IconObject("Icon", this->nObjects);
			GameObjectManager::getInstance()->addObject(iconObject);
			//nextSpaceX += iconObject->getSize().x + SPACING;


			iconObject->setPosition(nextSpaceX, nextSpaceY);

			nextSpaceX += iconObject->getSize().x + SPACING;
			if (nextSpaceX + iconObject->getSize().x > WINDOW_WIDTH) {
				nextSpaceX = 0.0f;
				nextSpaceY += iconObject->getSize().y + ROW_SPACING;
			}
			nObjects++;
	}*/
	
}

void BaseRunner::render() {
	this->window.clear();
	GameObjectManager::getInstance()->draw(&this->window);
	this->window.display();
}


BaseRunner* BaseRunner::getInstance()
{
	return sharedInstance;
}


float BaseRunner::getFPS() const
{
	return this->fps;
}