/*
 * snake.h
 *
 *  Created on: 24 mar 2019
 *      Auhor: Sylwester
 */

#ifndef SNAKE_H_
#define SNAKE_H_
#include"segment.h"
#include<deque>
#include<iostream>
#include<ctime>
#include<vector>

enum direction{up, down, left, right};

class snake {
private:
 std::deque<segment> bus;
int	base;
const int boundx;
const int boundy;
int positionx;
int positiony;
int lastx;
int lasty;
direction dir;
direction lastdir;
sf::Texture texture;
segment head;
segment tail;
segment food;
bool ** hitbox;
void movesnake();
kind checkKurve();
bool bounds();
void add(int x, int y, kind kind_);
bool eat();
void updateTail();
public:
	int points;
	snake();
	segment & get() {return head; };
	bool movehead(direction dir);
	void draw(sf::RenderWindow & window);
	void dropFood();
	void reset();
	~snake();

};

#endif /* SNAKE_H_ */
