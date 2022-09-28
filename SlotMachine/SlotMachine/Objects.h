#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

//in the object class are stored control buttons(start stop buttons)
class _objects
{
protected:
	//create image type variable
	sf::Image button_startI, button_stopI;
	//create texture type variables for buttons
	sf::Texture button_startT, button_stopT;
	//names of files with images of buttons and path to them
	string file_name_start = "images/start_image.jpg";
	string file_name_stop = "images/stop_image.jpg";
	//create a specific object, type (sprite)
	sf::Sprite button_startS, button_stopS;
public:
	_objects();
	sf::Sprite get_start_butt();
	sf::Sprite get_stop_butt();
	void draw_objects(sf::RenderWindow& tmp);
};

//start button getter
sf::Sprite _objects::get_start_butt()
{
	return button_startS;
}

//stop button getter
sf::Sprite _objects::get_stop_butt()
{
	return button_stopS;
}

//constructor for button initialization
_objects::_objects()
{
	//... loading an image from a file and assigning 
	//vvv it to a variable of type Image
	button_startI.loadFromFile(file_name_start);
	//... assigning an image to a texture variable 
	//vvv to create a texture(logical, right ? )
	button_startT.loadFromImage(button_startI);
	//... we pass our texture through the function 
	//vvv of a variable of type sprite to get an object
	button_startS.setTexture(button_startT);
	//... set the position of our object by x and y into the function 
	//vvv (the values ​​​​mean the number of pixels by x and y, respectively)
	button_startS.setPosition(1030, 250);

	//vvv with button stop exactly the same
	button_stopI.loadFromFile(file_name_stop);
	button_stopT.loadFromImage(button_stopI);
	button_stopS.setTexture(button_stopT);
	button_stopS.setPosition(1030, 450);
}

//function to display our startand stop buttons
void _objects::draw_objects(sf::RenderWindow& tmp)
{
	tmp.draw(button_startS);
	tmp.draw(button_stopS);

}
//^^^ you simply pass a ready - made object to the draw function, 
//... it itself displays it on the application window at your specified 
//... coordinates(default (0, 0) if you do not specify coordinates)