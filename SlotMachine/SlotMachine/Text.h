#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

//class for storing text displayed to the user
class _text
{
protected:
	sf::Font font; //<-the variable stores the font of the text
	sf::Text text; //<-umm, well, as if the text itself :)
	std::string file_name = "images/Fonts/Test_Font.ttf";
	//^^^ font path
public:
	_text();
	void edit_text(std::string enter_text);
	void print_text(sf::RenderWindow& tmp, float text_pos_x, float text_pos_y);
};

//vvv text initialization
_text::_text()
{
	this->font.loadFromFile(file_name);
	text.setFont(this->font); //font transfer
	text.setCharacterSize(25); //passing text size
	text.setFillColor(sf::Color::Yellow); //color rendering
	text.setStyle(sf::Text::Regular); //text style (in this example just normal)
}

//... text editing function
//vvv (transferring the text that is assigned to the main variable), like a getter
void _text::edit_text(std::string enter_text)
{
	text.setString(enter_text);
}

//... this function for text output, the window for outputand 
//vvv the coordinates of our text in xand y are passed to the arguments
void _text::print_text(sf::RenderWindow& tmp, float text_pos_x, float text_pos_y)
{
	text.setPosition(text_pos_x, text_pos_y); //<- move text to desired position
	tmp.draw(text); //<- displaying text on the application window
}