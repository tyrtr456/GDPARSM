#include "IconObject.h"
#include <iostream>
#include "BaseRunner.h"
#include "TextureManager.h"

IconObject::IconObject(String name, int textureIndex): AGameObject(name)
{
	this->textureIndex = textureIndex;
}

void IconObject::initialize()
{
	//assign texture
	this->sprite = new sf::Sprite();
	sf::Texture* texture = TextureManager::getInstance()->getStreamTextureFromList(this->textureIndex);
	this->sprite->setTexture(*texture);
	this->textureSize = this->sprite->getTexture()->getSize();



}

void IconObject::processInput(sf::Event event)
{


}

void IconObject::update(sf::Time deltaTime)
{
}

sf::Vector2u IconObject::getSize()
{
	return this->textureSize;
}
