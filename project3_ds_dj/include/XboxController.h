/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef XBOX_CONTROLLER_H
#define XBOX_CONTROLLER_H

#include <SFML\Graphics.hpp>
#include <iostream>

#define CONTROLLER_ONE   0
#define CONTROLLER_TWO   1
#define CONTROLLER_THREE 2
#define CONTROLLER_FOUR  3

// Defined marcos to represent the index of button on each controller and
// the index of where in the array a button is.
#define XBOX360_A		0
#define XBOX360_B		1
#define XBOX360_X		2
#define XBOX360_Y		3
#define XBOX360_LB		4
#define XBOX360_RB		5
#define XBOX360_BACK	6
#define XBOX360_START	7
#define XBOX360_LEFT_JOY_BUTTON	 8
#define XBOX360_RIGHT_JOY_BUTTON 9
#define XBOX360_LEFT	10
#define XBOX360_RIGHT	11
#define XBOX360_UP		12
#define XBOX360_DOWN	13

#define XBOX360_MAX_BUTTONS 14

class XboxController
{
private:
	// Holds the current index of the connected controller. Range: 0 - 3
	unsigned int m_controllerIndex;
	// Store a threshold for the dPad as it is a joystick
	const int DPAD_THRESHHOLD = 20;
	// The controller connected if any
	sf::Joystick m_controller;

	/// Tracks the state on a connected controller
	/// 
	/// Provides functionality to check the buttons, triggers and joysticks
	/// current and previous state.
	struct XboxControllerState
	{
		// Positions of the triggers and joystick along their respective axis.
		float RTrigger;
		float LTrigger;
		sf::Vector2f rightThumbStick;
		sf::Vector2f leftThumbStick;

		// buttons[] occupies same memory as stuct (same stride in memory)
		// useful to index array, a continues memory block instead of checking
		// each bool with if statements and updating.
		union
		{
			bool buttons[XBOX360_MAX_BUTTONS];
			struct
			{
				bool A;
				bool B;
				bool X;
				bool Y;
				bool LB;
				bool RB;
				bool back;
				bool start;
				bool leftThumbStickClick;
				bool rightThumbStickClick;
				bool DpadUp;
				bool DpadDown;
				bool DpadLeft;
				bool DpadRight;
			};
		};
	};

public:
	XboxController(unsigned int controllerIndex);

	bool isConnected();
	bool isButtonPressed(unsigned int button);
	bool isButtonHeldDown(unsigned int button);
	sf::Vector2f getLeftStick();
	bool getLeftStickFlickUp();
	bool getLeftStickFlickDown();
	sf::Vector2f getRightStick();
	float getLeftTrigger();
	float getRightTrigger();
	unsigned int getIndex();
	// Stores the current state of all the buttons, triggers and joystick
	XboxControllerState m_currentState;
	// Stores the previous state of all the buttons, triggers and joystick
	XboxControllerState m_previousState;
};

#endif // !XBOX_CONTROLLER_H