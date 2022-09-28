//!!! Before reading the code, I advise you to read the "ReadMe" file
//!!! Перед чтением кода, советую прочитать "ReadMe" файл
//+-+-+-+-+-+-+-+-+
//...here in the comments functionsand variables will be described 
//...in detail, if you did not find the definition of 
//...any function inside the function, then it is stored 
//...in the parent folder of the class
//+-+-+-+-+-+-+-+-+
#include <SFML/Graphics.hpp> //<- main sfml library for working with graphics
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <random>
//...connection of.h files with classes
#include "Background.h"
#include "Text.h"
#include "Interface.h"
#include "Objects.h"
#include "Slots.h"
#include "Mouse.h"

using namespace std;
random_device Rand; //rename random to "Rand"

//...This class describes the main functions and 
//...elements of the game itself.
class Game_logic
{
private:
	//creating variables based on generated classes
	_mouse user_mouse;
	_interface interface_texture;
	_back_picture back_texture; 
	_text text_spin_amount; _text text_score_amount;
	_objects button_texture;
	//each reel of the slot machine is created separately
	_slot slots_drum_1; _slot slots_drum_2; 
	_slot slots_drum_3; _slot slots_drum_4;
	//score is the player's total score 
	//spin count is the number of player spins possible vvv
	int score = 0; int spin_count = 7;
public:
	void get_score(int tmp_score, int tmp_spin_count);
	void draw_text(sf::RenderWindow& tmp);
	void check_drum_pos(bool& tmp, string& simbol_name);
	void initDrums(float& posX);
	void draw_elements(sf::RenderWindow& tmp);
	void check_press(sf::RenderWindow& tmp, bool& mouse);
	void draw_drums(sf::RenderWindow& tmp);
	void drum_animation(sf::RenderWindow& tmp, int& spawn_counter);
	void drum_stop_animation(sf::RenderWindow& tmp, string& simbol);
};

void Game_logic::drum_animation(sf::RenderWindow& tmp, int& spawn_counter)
{
	slots_drum_1.move_drum(tmp, 25, spawn_counter);
	slots_drum_2.move_drum(tmp, 5, spawn_counter);
	slots_drum_3.move_drum(tmp, 20, spawn_counter);
	slots_drum_4.move_drum(tmp, 10, spawn_counter);
}
//^^^this is the reel movement function, where tmp is the window in which 
//...the image should be displayed, and spawn_counter is the counter of the reel movement, 
//...in order to use it for automatic stop in the future

void Game_logic::drum_stop_animation(sf::RenderWindow& tmp, string& simbol)
{
	bool tmp_pos = 0; int tmp_counter = 0;
	check_drum_pos(tmp_pos, simbol);
	while (tmp_pos != 1)
	{
		draw_elements(tmp);
		drum_animation(tmp, tmp_counter);
		check_drum_pos(tmp_pos, simbol);
	}
}
//^^^drum stop animation - is a function to stop the reels, 
//...tmp is also an output window, simbol is passed to record the results of the rotation, 
//...the data is stored as the first letter of the name of the dropped item, 
//...in order to later calculate the number of points scored,

void Game_logic::draw_drums(sf::RenderWindow& tmp)
{
	slots_drum_1.draw_slots(tmp);
	slots_drum_2.draw_slots(tmp);
	slots_drum_3.draw_slots(tmp);
	slots_drum_4.draw_slots(tmp);
}
//^^^this is a function that simply displays the reels on the screen

void Game_logic::initDrums(float& posX)
{
	slots_drum_1.initPos(posX);
	slots_drum_2.initPos(posX+150);
	slots_drum_3.initPos(posX+300);
	slots_drum_4.initPos(posX+450);
}
//^^^this function sets the initial position of the slot machine reels,
//...the initial position of the first automaton is passed into the arguments

void Game_logic::get_score(int tmp_score, int tmp_spin_count)
{
	score = tmp_score;
	spin_count = tmp_spin_count;
}
//^^^this function is for assigning the results to a private variable 

void Game_logic::draw_text(sf::RenderWindow& tmp)
{
	text_score_amount.edit_text("Your score :" + to_string(score));
	text_spin_amount.edit_text("Spin amount: " + to_string(spin_count));
	text_score_amount.print_text(tmp, 640.f, 230.f);
	text_spin_amount.print_text(tmp, 320.f, 230.f);
}
//^^^this function to display the results as text on the screen

void Game_logic::draw_elements(sf::RenderWindow& tmp)
{	
	tmp.clear();
	draw_drums(tmp);
	back_texture.print_back_picture(tmp);
	interface_texture.draw_interface(tmp);
	button_texture.draw_objects(tmp);
	draw_text(tmp);
	tmp.display();
}
//^^^a function that is always executed while the program is running, 
//...it displays all the elements of the program

void Game_logic::check_drum_pos(bool& pos, string& simbol_name)
{
	if ((slots_drum_1.check_slot_pos(simbol_name) != 0) && (slots_drum_2.check_slot_pos(simbol_name) != 0)
		&& (slots_drum_3.check_slot_pos(simbol_name) != 0) && (slots_drum_4.check_slot_pos(simbol_name) !=0))
	{
		pos = 1;
	}
	else
	{
		pos = 0;
	}
}
//^^^the function checks the position of the reels, in which the result is assigned to the pos variable, 
//...if pos is 1, then the stop is possible, otherwise the reels are crooked and the stop is impossible

void Game_logic::check_press(sf::RenderWindow& tmp, bool& mouse)
{
	user_mouse.update_poz(tmp);
	if (user_mouse.check_button_press(button_texture) == 1) {
		mouse = 1;
	}
	else if (user_mouse.check_button_press(button_texture) == 0) {
		mouse = 0;
	}
}
//^^^this function checks if the mouse button is pressed and passes the result
//...to the bool variable, if 1 - then it is pressed, otherwise 0 - not pressed accordingly

int main()
{
	//application window size variables
	int Screen_x_size = 1280, Screen_y_size = 720; 
	//starting position of the reels
	float start_drum_posX = 375.f; 
	//rotation speed, animation stop timer and number of rotation attempts
	int speed = 10; 
	int sleep_timer = 100; 
	int spin_amount = 7;
	//mouse status (clicked on start or stop) and a variable to check the position of the drum
	bool status = 0; bool check_pos = 0;
	int player_score = 0;// <- player account total

	vector<int> spin_counter{ 150,200,250,300,350}; //a vector to store the number of ticks to stop
	int drum_spawn_counter = 0; //variable for counting beats made
	string simbols_result; //rotation result as a stringр
	Game_logic test; //creating a variable where all data about the game and all functions are stored

	sf::Event event;
	sf::RenderWindow window(sf::VideoMode(Screen_x_size, Screen_y_size), "My first Slot Machine");
	//^^^ creating the main window
	window.setFramerateLimit(35); //FPS limit 

	test.initDrums(start_drum_posX);
	test.draw_elements(window);
	
	while (window.isOpen())
	{
		//function to be executed on event vvv
		while (window.pollEvent(event))
		{

			if (event.type == sf::Event::Closed)
				window.close(); 
			//^^^if you press exit button on window, function to be executed on event

			if (event.type == sf::Event::MouseButtonPressed)
			{
				test.check_press(window, status);
			}
			//^^^if the mouse button is pressed, the condition for assigning the mouse status to a variable is met
		}
		
		drum_spawn_counter = 0; //each time the counter of the rotation of the reels to stop is reset
		
		while (status != 0 && spin_amount != 0) //executed while mouse status == pressed and number of rotation attempts != 0
		{
			Sleep(sleep_timer);
			if (event.type == sf::Event::MouseButtonPressed)
			{
				test.check_press(window, status);
				test.get_score(player_score, spin_amount);
			}
			///^^^if the mouse button is pressed, the condition for assigning the mouse status to a variable is met

			test.draw_elements(window);
			test.drum_animation(window, drum_spawn_counter);

			if (sleep_timer != 0)
				sleep_timer -= 2;

			test.get_score(player_score, spin_amount); //player account transfer
			if ((status == 0) || ( status == 1 && drum_spawn_counter >= spin_counter[Rand() % 5]))
			{
				//if the mouse button is pressed on the stop button, 
				//or the rotation of the reels has stepped over the value, the reels will autopathically stop
				--spin_amount;

				//... the sleep timer variable is designed to smooth the 
				//vvv movement of the reels during the start of rotation and the stop of the reels
				while (sleep_timer != 100) 
				{
					if (sleep_timer == 98)
					{
						sleep_timer += 2;
						simbols_result = "";
						test.drum_stop_animation(window, simbols_result);
						//...the loop for calculating the player's points, works like searching for 
						//...pairs of dropped elements, the search is performed by the text in which the rule is written,
						//vvv p.s only the last 4 characters count 
						for (int i = simbols_result.size() - 4, j = simbols_result.size() - 3
							; i < simbols_result.size(); ++j)
						{
							if (simbols_result[i] == simbols_result[j] && i != j)
								++player_score;
							test.get_score(player_score, spin_amount);
							if (j == simbols_result.size())
							{
								j = 0;
								++i;
							}
						}
						//Below is the output of information for understanding what is happening in the game (for the developer)
						cout << "Remaining spins: " << spin_amount << endl;
						cout << "Text result: " << simbols_result << endl;
						cout << "Total points: " << player_score << endl;
						cout << "Elapsed number of beats of drums: " << drum_spawn_counter << endl;

						//vvv reset data on the mouse and passed cycles to stop
						drum_spawn_counter = 0;
						status = 0;
						break;//exit from the reel stop loop
					}

					//spinning reels and updating player data
					Sleep(sleep_timer);
					test.get_score(player_score, spin_amount);
					test.draw_elements(window);
					test.drum_animation(window, drum_spawn_counter);
					sleep_timer += 2;
				}
			}
		}
	}
	return 0;
}