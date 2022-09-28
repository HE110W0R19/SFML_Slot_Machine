#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
//... The slots themselves are stored in this class, the
//... slot itself actually consists of 5 elements,
//vvv they are simply glued together in a vector
class _slot
{
	float posX = 0.0, posY_tmp = 200.f; //default spawn coordinates(by x and y)
	//vvv variables of the image type for storing a picture of the drum elements
	sf::Image slot_appleI, slot_barI, slot_grapeI, slot_redberryI, slot_sevenI;
	sf::Texture slot_appleT, slot_barT, slot_grapeT, slot_redberryT, slot_sevenT;
	sf::Sprite slot_appleS, slot_barS, slot_grapeS, slot_redberryS, slot_sevenS;
	std::vector<sf::Sprite> drum{}; //<- the final result, a vector of elements - a full-fledged drum
	std::string drum_names; //<- variable for storing the first letters of the name of the elements 
	std::vector<float> posY; //<- variable for storing positions of drum elements
public:
	_slot();
	bool check_slot_pos(std::string& drum_simbol_name);
	void initPos(float tmp_posX);
	void draw_slots(sf::RenderWindow& tmp);
	void move_drum(sf::RenderWindow& tmp, int tmp_speed, int& spawn_counter);
};


_slot::_slot()
{
	//1-load the image into a variable of type image
	//2-load our image into a texture type variable
	//3-from the texture create an object (sprite)
	slot_appleI.loadFromFile("images/SlotTextures/apple.png");
	slot_appleT.loadFromImage(slot_appleI);
	slot_appleS.setTexture(slot_appleT);
	drum.push_back(slot_appleS);//<-add the resulting object to the vector
	//vvv and so with everyone
	slot_barI.loadFromFile("images/SlotTextures/bar.png");
	slot_barT.loadFromImage(slot_barI);
	slot_barS.setTexture(slot_barT);
	drum.push_back(slot_barS);

	slot_grapeI.loadFromFile("images/SlotTextures/grape.png");
	slot_grapeT.loadFromImage(slot_grapeI);
	slot_grapeS.setTexture(slot_grapeT);
	drum.push_back(slot_grapeS);

	slot_sevenI.loadFromFile("images/SlotTextures/seven.png");
	slot_sevenT.loadFromImage(slot_sevenI);
	slot_sevenS.setTexture(slot_sevenT);
	drum.push_back(slot_sevenS);

	drum_names += "BGSA";//<-set the variable to the first letters of the slots

	for (int i = 0; i < 4; ++i, posY_tmp += 100.f)
	{
		posY.push_back(posY_tmp);
	}
	//^^^ set the position of our elements with a step of 100 pixels by y
	//... since each element has an image size of 100x100
}

//... a function to check that our slot is 
//... at position 200 in y, to stop the slots evenly
//... the function also assigns the letter of the name of a correctly standing 
//vvv slot to the measure(which is passed to the argument)
bool _slot::check_slot_pos(std::string& drum_simbol_name)
{
	for (int i = 0; i < 4; ++i)
	{
		if (drum[i].getPosition().y == 200)
		{
			drum_simbol_name += drum_names[i];
			return 1; // true - position is greate
		}
	}
	return 0; // false - position is bad
}

//... function to initialize the elements,
//vvv here the elements are placed in their positions
void _slot::initPos(float tmp_posX)
{
	
	this->posX = tmp_posX; //<-x position is set, for the possibility 
							//of placing several reels in a row
	for (int i = 0; i < 4; ++i)
	{
		drum[i].setPosition(posX, posY[i]);
	}
}
//vvv output function of each drums
void _slot::draw_slots(sf::RenderWindow& tmp)
{
	for (int i = 0; i < 4; ++i) //4-number of drums amount
	{
		tmp.draw(drum[i]);
	}
}

//... function for moving drum elements, arguments - 
//vvv 1) output window 2) move step(in pixels) 3) number of moves(cycles)
void _slot::move_drum(sf::RenderWindow& tmp, int tmp_speed, int& spawn_counter)
{
	for (int i = 0; i < 4; ++i) //4-number of drums amount
	{
		//checking for the location of the element, if the condition is met, it appears
		//vvv behind the "dark curtain" to pass the circle on a new
		if (drum[i].getPosition().y >= 500.f + (float)tmp_speed)
		{
			posY[i] = 100.f + (float)tmp_speed; //new position
			drum[i].setPosition(posX, posY[i]); //move object to new position
			++spawn_counter;
		}
		tmp.draw(drum[i]);
		drum[i].move(0, tmp_speed); 
		//^^^ movement of elements through the step specified in the arguments
	}
}