/*
 * segment.h
 *
 *  Created on: 24 mar 2019
 *      Author: Sylwester
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_
#include "SFML/Graphics.hpp"
#include<iostream>
	enum kind  { StraightV, StraightH, RU, RD, LD, LU, HeadR, HeadL, HeadU, HeadD, TailU, TailD, TailR, TailL, food};
class segment: public sf::Sprite{
private:
	int positionx;
	int positiony;
	kind title;
	sf::Texture texture;
	kind Kind;
public:
	segment();
	kind getKind(){return Kind;};
	void setTex(sf::Texture &);
	void set(kind);
	void setposition(int x,int y);
	void updateposition(int x,int y);
	int getpositionx(){return positionx;};
	int getpositiony(){return positiony;};
	void setTex();
	virtual ~segment();

};
#endif /* SEGMENT_H_ */
