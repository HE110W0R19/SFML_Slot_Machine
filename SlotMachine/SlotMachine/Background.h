#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//...This is the class for which contains the 
//vvv background element of the application
class _back_picture
{
protected:
	sf::Image backround; //image type variable
	sf::Texture backtexture; //variable texture
	sf::Sprite backsprite; //end object (sprite)
	std::string file_name_back = "images/back.png"; //image path name
public:
	_back_picture();
	void print_back_picture(sf::RenderWindow& tmp);
};

//... in the constructor, first our background is loaded into a variable of the image type
//... then this picture is transferred to a texture type variable, and a full - fledged texture 
//vvv is created from our image, at the end our texture is moved to a sprite type variable, and an object is created
_back_picture::_back_picture()
{
	backround.loadFromFile(file_name_back); //file to image
	backtexture.loadFromImage(backround); //image to texture
	backsprite.setTexture(backtexture); //texture to object (sprite)
	backsprite.setPosition(0, 0); //set the position of our image in our window
}

//vvv function to display the back image
void _back_picture::print_back_picture(sf::RenderWindow& tmp)
{
	tmp.draw(backsprite); //draw - is a sfml window function that draws the passed object to the screen.
}