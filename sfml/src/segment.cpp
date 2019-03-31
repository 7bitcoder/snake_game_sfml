/*
 * segment.cpp
 *
 *  Created on: 24 mar 2019
 *      Author: Sylwester
 */


#include "segment.h"
#include "SFML/Graphics.hpp"
static int base = 64;

segment::segment() :Sprite() {
	// TODO Auto-generated constructor stub

}
void segment::set(kind kind_)
{
	Kind = kind_;
	title = kind_;
	int i, j;
	switch (kind_) {
	case kind::HeadR:
		i = 4;
		j = 0;
		break;
	case kind::HeadL:
		i = 3;
		j = 1;
		break;
	case kind::HeadU:
		i = 3;
		j = 0;
		break;
	case kind::HeadD:
		i = 4;
		j = 1;
		break;
	case kind::TailR:
		i = 4;
		j = 2;
		break;
	case kind::TailL:
		i = 3;
		j = 3;
		break;
	case kind::TailU:
		i = 3;
		j = 2;
		break;
	case kind::TailD:
		i = 4;
		j = 3;
		break;
	case kind::StraightH:
		i = 1;
		j = 0;
		break;
	case kind::StraightV:
		i = 2;
		j = 1;
		break;
	case kind::RD:
		i = 2;
		j = 2;
		break;
	case kind::RU:
		i = 2;
		j = 0;
		break;
	case kind::LU:
		i = 0;
		j = 0;
		break;
	case kind::LD:
		i = 0;
		j = 1;
		break;
	case kind::food:
		i = 0;
		j = 3;
		break;
	default:
		break;

	}
	this->setTextureRect(sf::IntRect(base * i, base * j, base, base));
}
void segment::setposition(int x, int y)
{
positionx = x;
positiony = y;
this->setPosition(x*base,y*base);
}
void segment::setTex()
{
	texture.loadFromFile("snake.png");
	this->setTexture(texture);
}
void segment::updateposition(int x,int y)
{
	this->move(x,y);
}
segment::~segment() {
	// TODO Auto-generated destructor stub
}

