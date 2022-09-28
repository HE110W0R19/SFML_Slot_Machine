#pragma once
#include <SFML/Graphics.hpp>
//... this class stores two rectangular windows that cover the viewport of the 
//vvv reels so that the player only sees a specific side of the reel
class _interface
{
protected:
	//vvv the size of the rectangle in x and y, 
	//vvv both are the same size, the size is calculated by pixels
	float _window_y_size = 100.f;
	float _window_x_size = 700.f;
	//vvv position relative to y
	float _window1_y_pos = 175.f;
	float _window2_y_pos = 425.f;
	//vvv position relative to x (both are the same)
	float _window_x_pos = 300;
	//vvv create a rectangle according to the data above
	sf::RectangleShape _interface_window1, _interface_window2;
public:
	_interface();
	void draw_interface(sf::RenderWindow& tmp);
};

_interface::_interface()
{
	//set the spawn point for our object
	this->_interface_window1.setPosition(_window_x_pos, _window1_y_pos);
	//set dimensions (using a float vector)
	this->_interface_window1.setSize(sf::Vector2f(_window_x_size, _window_y_size));
	//set the background color of an object
	this->_interface_window1.setFillColor(sf::Color::Black);
	//set the color of the line in a circle ()
	//^v sfml has built-in colors, so there will be no difficulties
	this->_interface_window1.setOutlineColor(sf::Color::Yellow);
	//set the thickness of the line in a circle
	this->_interface_window1.setOutlineThickness(3.f);

	//here everything is similar to the first
	this->_interface_window2.setPosition(_window_x_pos, _window2_y_pos);
	this->_interface_window2.setSize(sf::Vector2f(_window_x_size, _window_y_size));
	this->_interface_window2.setFillColor(sf::Color::Black); 
	
	this->_interface_window2.setOutlineColor(sf::Color::Yellow);
	this->_interface_window2.setOutlineThickness(3.f);
}

//output previously created windows (or curtain type xD ))) )
void _interface::draw_interface(sf::RenderWindow& tmp)
{
	tmp.draw(_interface_window1);
	tmp.draw(_interface_window2);
}