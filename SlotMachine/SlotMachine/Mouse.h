#pragma once
#include <SFML/Graphics.hpp>
#include "Objects.h"

//vvv this class will store information about the location of the mouse
class _mouse
{
	sf::Vector2i mouse_pos_window;//an int vector that stores our mouse x and y coordinates
public:
	void update_poz(sf::RenderWindow& tmp);
	int check_button_press(_objects& tmp_butt);
};

//vvv in this function, information about the location of the mouse is written to the vector
void _mouse::update_poz(sf::RenderWindow& tmp)
{
	this->mouse_pos_window = sf::Mouse::getPosition(tmp);
}
//^^^ method for getting the mouse coordinate, a window is passed to the argument, 
//... for orientation in our window, that is, 
//... the x and y coordinates start from the upper left corner of our window (which is always 0.0 for x, y)

//vvv function for checking mouse click, you can click both left and right mouse button
int _mouse::check_button_press(_objects& tmp_butt)
{
	//mouse click condition vvv
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
		|| sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
	{
		//vvv checking if the mouse cursor is in the area of ​​the "start" or "stop" button
		if (tmp_butt.get_start_butt().getGlobalBounds().contains(mouse_pos_window.x, mouse_pos_window.y))
		{
			/*cout << "Button start was pressed!" << endl;*/
			return 1;
		}
		else if (tmp_butt.get_stop_butt().getGlobalBounds().contains(mouse_pos_window.x, mouse_pos_window.y))
		{
			/*cout << "Button stop was pressed!" << endl;*/
			return 0;
		}
	}
	return 2;
}