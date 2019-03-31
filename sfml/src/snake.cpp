/*
 * snake.cpp
 *
 *  Created on: 24 mar 2019
 *      Author: Sylwester
 */

#include "snake.h"

snake::snake(): boundx(30),boundy(15)
{
	points = 0;
	// TODO Auto-generated constructor stub
	std::srand(std::time(nullptr));
	head.setTex();
	head.set(kind::HeadR);
	food.setTex();
	food.set(kind::food);
	tail.setTex();
	tail.set(kind::TailR);
	tail.setposition(0,0);
	food.setposition(-1,-1);
	positionx = 3;
	positiony = 0;
	lastx = 3;
	lasty = 0;
	dir = direction::right;
	lastdir = direction::right;
	base = 64;

	//hitbox = new bool[boundx][boundy];
	hitbox = new bool*[boundx];
	for(int i = 0; i < boundx; ++i)
	    hitbox[i] = new bool[boundy];
	for(int i = 0; i < boundx; ++i)
		for(int j = 0; j < boundy; ++j)
				hitbox[i][j] = false;
	hitbox[3][0] = true;
	hitbox[2][0] = true;
	hitbox[1][0] = true;
	hitbox[0][0] = true;
	head.setposition(positionx,positiony);
	add(2,0,kind::StraightH);
	add(1,0,kind::StraightH);
	add(0,0,kind::StraightH);
}
void snake::reset()
{
	bus.clear();
	points = 0;
	// TODO Auto-generated constructor stub
	head.setTex();
	head.set(kind::HeadR);
	food.setTex();
	food.set(kind::food);
	tail.setTex();
	tail.set(kind::TailR);
	tail.setposition(0,0);
	food.setposition(-1,-1);
	positionx = 3;
	positiony = 0;
	lastx = 3;
	lasty = 0;
	dir = direction::right;
	lastdir = direction::right;
	base = 64;

	//hitbox = new bool[boundx][boundy];
	for(int i = 0; i < boundx; ++i)
		for(int j = 0; j < boundy; ++j)
				hitbox[i][j] = false;
	hitbox[3][0] = true;
	hitbox[2][0] = true;
	hitbox[1][0] = true;
	hitbox[0][0] = true;
	head.setposition(positionx,positiony);
	add(2,0,kind::StraightH);
	add(1,0,kind::StraightH);
	add(0,0,kind::StraightH);
}

snake::~snake()
{
	for(int i = 0; i < boundx; ++i)
		    delete(hitbox[i]);
	delete(hitbox);
}
	// TODO Auto-generated destructor stub
bool snake::movehead(direction dir_)
{
	lastdir = dir;
	dir = dir_;
	kind tmp;
	lastx = positionx;
	lasty = positiony;
	if((lastdir == direction::right && dir == direction::left)||(lastdir == direction::left&&dir == direction::right))
		dir = lastdir;
	if((lastdir == direction::up&&dir == direction::down)||(lastdir == direction::down&&dir == direction::up))
		dir = lastdir;
	switch(dir)
	{
	case direction::up:
		positiony-=1;
		tmp = kind::HeadU;
		break;
	case direction::down:
		positiony+=1;
		tmp = kind::HeadD;
		break;
	case direction::right:
		positionx+=1;
		tmp = kind::HeadR;
		break;
	case direction::left:
		positionx-=1;
		tmp = kind::HeadL;
		break;
	default:
		break;
	}

	if(!bounds()){
		return false;
		std::cout<<"xd";
	}
	head.setposition(positionx,positiony);
	hitbox[positionx][positiony] = true;
	//chech for snackif true addend
	head.set(tmp);
	movesnake();
	return true;
}
void snake::movesnake()
{
	kind tmp = checkKurve();
	segment X;
	bus.push_front(X);
	bus.front().setTex();
	bus.front().set(tmp);
	bus.front().setposition(lastx,lasty);
	if(!eat())
	{
		updateTail();
		//hitbox[bus.back().getpositionx()][bus.back().getpositiony()] = false;
		bus.pop_back();
	}
//S	bus.pop_back();
}
void snake::updateTail()
{
	hitbox[tail.getpositionx()][tail.getpositiony()] = false;
	kind tmp = bus.back().getKind();
	int ax = bus.back().getpositionx();
	int ay = bus.back().getpositiony();
	int x = bus[bus.size()-2].getpositionx();
	int y = bus[bus.size()-2].getpositiony();
	if(tmp == kind::StraightH)
	{
		if(ax > x)
			tail.set(kind::TailL);
		else
			tail.set(kind::TailR);
	}
	if(tmp == kind::StraightV)
		{
			if(ay > y)
				tail.set(kind::TailU);
			else
				tail.set(kind::TailD);
		}
	if(tmp == kind::RU)
			{
				if(ax > x)
					tail.set(kind::TailL);
				else
					tail.set(kind::TailD);
			}
	if(tmp == kind::LU)
				{
					if(ax < x)
						tail.set(kind::TailR);
					else
						tail.set(kind::TailD);
				}
	if(tmp == kind::RD)
				{
					if(ax > x)
						tail.set(kind::TailL);
					else
						tail.set(kind::TailU);
				}
	if(tmp == kind::LD)
				{
					if(ax < x)
						tail.set(kind::TailR);
					else
						tail.set(kind::TailU);
				}
	tail.setposition(ax,ay);
}
kind snake::checkKurve()
{
	kind tmp;
	if(lastdir == direction::right)
	{
		if(dir == direction::right)
			tmp = kind::StraightH;
		if(dir == direction::down)
			tmp = kind::RU;
		if(dir == direction::up)
			tmp = kind::RD;
	}
	if(lastdir == direction::left)
	{
		if(dir == direction::left)
			tmp = kind::StraightH;
		if(dir == direction::down)
			tmp = kind::LU;
		if(dir == direction::up)
			tmp = kind::LD;
	}
	if(lastdir == direction::up)
	{
		if(dir == direction::up)
			tmp = kind::StraightV;
		if(dir == direction::left)
			tmp = kind::RU;
		if(dir == direction::right)
			tmp = kind::LU;
	}
	if(lastdir == direction::down)
	{
		if(dir == direction::down)
			tmp = kind::StraightV;
		if(dir == direction::left)
			tmp = kind::RD;
		if(dir == direction::right)
			tmp = kind::LD;
	}
	return tmp;
}

void snake::draw(sf::RenderWindow & window)
{
	window.draw(head);
	for(int i = 0;i<bus.size();i++)
	{
		window.draw(bus[i]);
	}
	window.draw(food);
	window.draw(tail);
}
bool snake::bounds()
{
	if(positiony<0||positiony>boundy)
	{
		//std::cout<<"reszta";
		return false;
	}
	if(positionx<0||positionx>boundx)
		{
			//std::cout<<"reszta";
			return false;
		}
	if(hitbox[positionx][positiony] == true)
	{
		//std::cout<<"na siebie";
		return false;
	}
	return true;
}
void snake::add(int x, int y, kind kind_)
{
	segment tmp;
	bus.push_back(tmp);
	bus.back().setTex();
	bus.back().set(kind_);
	bus.back().setposition(x,y);
	//std::cout <<bus.size();

}
bool snake::eat()
{
 if(positionx == food.getpositionx() && positiony == food.getpositiony())
	 {
	 points++;
	 food.setposition(-1,-1);
	 return true;
	 }
 else
	 return false;
}
void snake::dropFood()
{

	if(food.getpositionx()==-1)
	{
		struct coord
			{
				int x;
				int y;
			};
			coord g;
			std::vector<coord> tmp;
			for(int i = 0;i<boundx;i++)
			{
				for(int j = 0;j<boundy;j++)
				{
					if(hitbox[i][j] == false)
					{
						g.x = i;
						g.y = j;
						tmp.push_back(g);
					}
				}
			}
			int index = std::rand()%tmp.size();
		/*int a;
		int b;
		do{
			 a = std::rand()%boundx;
			 b = std::rand()%boundy;
	}
		while(hitbox[a][b]==true);*/
		food.setposition(tmp[index].x,tmp[index].y);
	}
}

