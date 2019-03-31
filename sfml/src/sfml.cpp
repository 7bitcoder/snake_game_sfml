//============================================================================
// Name        : sfml.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
#include "snake.h"
#include "segment.h"
#include<string>

using namespace std;

int main() {

	int xcoord = 64*30;
	int ycoord = 64*15;
	int resizedx = 64*30;
	int resizedy = 64*15;
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile("music.wav"))
	        return -1;
	sf::RenderWindow window(sf::VideoMode(xcoord,ycoord),"Wunsz");
	sf::Font font;
	if (!font.loadFromFile("SUNA_Arial_Bold.ttf"))
	{
	    std::cout<<"fail";
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(60);
	text.setPosition(64*25/2,64*12/2);
	//text.setStyle(sf::Text::Bold);
	//text.setFillColor(sf::Color::Cyan);
	//text.setString("WUNSZv0.69\n\n      Start");
	// Load a sprite to display
	sf::Texture menu;
	menu.loadFromFile("menu.png");//458x384
	sf::Sprite Menu;
	Menu.setTexture(menu);
	Menu.setOrigin(458/2,384/2);
	Menu.setPosition(xcoord/2,ycoord/2);
	sf::Texture back;
	back.loadFromFile("background.jpg");//458x384
	sf::Sprite background;
	background.setTexture(back);
	snake boa;
	    sf::Clock clock;
	    sf::Time framerate = sf::seconds(0.15);
	    clock.restart();
	    direction actual = direction::right;
	    enum stan{Start, Gra, Gameover, Pause};
	    stan State = Start;
	    bool start = false;
	    bool pause = false;
		while (window.isOpen())
			{
				sf::Event event;
				while (window.pollEvent(event))
				{
					// check the type of the event...
					switch (event.type)
					{
						// window closed
						case sf::Event::Closed:
							window.close();
							break;

						// key pressed
						case sf::Event::KeyPressed:
							switch(event.key.code)
							{
							case sf::Keyboard::Right:
								actual = direction::right;
								break;
							case sf::Keyboard::Left:
								actual = direction::left;
								break;
							case sf::Keyboard::Up:
								actual = direction::up;
								break;
							case sf::Keyboard::Down:
								actual = direction::down;
								break;
							case sf::Keyboard::Escape:
							case sf::Keyboard::P:
								pause = true;
								break;
							default:
								break;
							}
							break;
							case sf::Event::MouseButtonPressed:
							    if (event.mouseButton.button == sf::Mouse::Left)
							    {
							    	//std::cout<<"x:"<<event.mouseButton.x<<std::endl<<"y :"<<event.mouseButton.y<<std::endl;
							        if(event.mouseButton.x < 1073.f*(float(resizedx)/float(xcoord)) && event.mouseButton.x > 855.f*(float(resizedx)/float(xcoord)) && event.mouseButton.y > 326.f*(float(resizedy)/float(ycoord)) && event.mouseButton.y < 371.f*(float(resizedy)/float(ycoord)))
							        	start = true;
							        if(State != stan::Start && State != stan::Gameover)
							        if(event.mouseButton.x < 1073.f*(float(resizedx)/float(xcoord)) && event.mouseButton.x > 855.f*(float(resizedx)/float(xcoord)) && event.mouseButton.y > 408.f*(float(resizedy)/float(ycoord)) && event.mouseButton.y < 459.f*(float(resizedy)/float(ycoord)))
							        	pause = false;
							        if(event.mouseButton.x < 1073.f*(float(resizedx)/float(xcoord)) && event.mouseButton.x > 855.f*(float(resizedx)/float(xcoord)) && event.mouseButton.y > 575.f*(float(resizedy)/float(ycoord)) && event.mouseButton.y < 624.f*(float(resizedy)/float(ycoord)))
							        	window.close();
							    }
							    break;
							case  sf::Event::Resized:
							   resizedx =  event.size.width;
							   resizedy = event.size.height;
							   std::cout<<1041.f*float(float(resizedx)/float(xcoord));
							break;

						// we don't process other types of events
						default:
							break;
					}
				}
				// Clear screen
				window.clear(sf::Color::Blue);
			    switch(State)
			    {
			    case stan::Start:
			    	if(start == true)
			    	{
			    		State = stan::Gra;
			    		text.setCharacterSize(40);
			    		text.setPosition(0,0);
			    		start = false;
			    	}
			    	window.clear(sf::Color::Blue);
			    	window.draw(background);
			    	window.draw(Menu);
			    	window.display();

			    	break;
			    case stan::Gra:
					// Draw the sprite
					// Update the window
			    	if(pause == true)
			    	{
			    		State = stan::Pause;
			    		break;
			    	}
					text.setString("Punkty :"+std::to_string(boa.points));
					window.clear(sf::Color::Blue);
					window.draw(background);
					boa.draw(window);
					if(clock.getElapsedTime()>framerate)
										{
											if(!boa.movehead(actual))
											{
												State = stan::Gameover;
												text.setCharacterSize(40);
												text.setPosition(853,200);
												text.setString("Punkty :"+std::to_string(boa.points));
												boa.reset();
												actual = direction::right;
												break;
											}
											 clock.restart();
											 boa.dropFood();
										}
					window.draw(text);
					window.display();
					break;
			    case stan::Pause:
			    	if(pause == false)
			    	  	{
			    	  		State = stan::Gra;
			    	   		break;
			    	   	}
			    	if(start == true)
			    	{
						boa.reset();
						actual = direction::right;
						State = stan::Gra;
						start = false;
						pause = false;
			    	}
			    	   	window.clear(sf::Color::Blue);
						window.draw(background);
						boa.draw(window);
						window.draw(text);
						window.draw(Menu);
			    	   	window.display();
			    	   	break;
			    case stan::Gameover:
			    	if(start == true)
			    	{
			    		State = stan::Gra;
			    		text.setCharacterSize(40);
			    		text.setPosition(0,0);
			    		start = false;
			    	}
			    	window.clear(sf::Color::Blue);
			    	window.draw(background);
			    	window.draw(text);
			    	window.draw(Menu);
			    	window.display();
			    	break;
				}

			}
	    return EXIT_SUCCESS;
}
