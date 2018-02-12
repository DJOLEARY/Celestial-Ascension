#include "XboxController.h"
#include <Windows.h>
#include <Xinput.h>

#pragma comment(lib, "XInput.lib") 

/// <summary>
/// Takes in a controller index which is between range [0, 3] or [CONTROLLER_ONE, CONTROLLER_FOUR]
/// If it is outside this bound it will default back to index 0 or CONTROLLER_ONE and print a message.
/// </summary>
/// <param name="controllerIndex">controller index to check for input, range [0, 3] or [CONTROLLER_ONE, CONTROLLER_FOUR]</param>
XboxController::XboxController(unsigned int controllerIndex)
	: m_controllerIndex(controllerIndex)
{
	if (m_controllerIndex < CONTROLLER_ONE || m_controllerIndex > CONTROLLER_FOUR)
	{
		m_controllerIndex = 0;
		std::cout << "Xbox Controller parameter controller index out of bound, \ndefaulted to index 0 (CONTROLLER_ONE)" << std::endl;
	}
}

/// <summary>
/// Checks if a controller is connected giving the controller index.
/// </summary>
/// <returns>Returns true if the controller is connected, false otherwise</returns>
bool XboxController::isConnected()
{
	bool connected = m_controller.isConnected(m_controllerIndex);

	return connected;
}

/// <summary>
/// Checks if a button on the controller is pressed not held down.
/// Updates the currentstate and previous state of the controller.
/// </summary>
/// <param name="button">The index of the button</param>
/// <returns>Returns true if the button is pressed, false otherwise</returns>
bool XboxController::isButtonPressed(unsigned int button)
{
	bool buttonPressed = false;

	// Check if the input parameter is a face button, shoulder button, back/start button or joystick button
	if (button >= XBOX360_A && button <= XBOX360_RIGHT_JOY_BUTTON)
	{
		buttonPressed = m_controller.isButtonPressed(m_controllerIndex, button);

		if (buttonPressed)
		{
			// Check if the previous button state is false (button up)
			if (!m_previousState.buttons[button])
			{
				m_currentState.buttons[button] = buttonPressed;
			}
			else  // If the previous state is true (button down) then button can't be down agian
			{
				buttonPressed = false;
			}
		}
		else
		{
			// Button is not pressed so update the current state
			m_currentState.buttons[button] = false;
		}

		// Update the previous face button state
		m_previousState.buttons[button] = m_currentState.buttons[button];
	}

	// Treating the D-Pad on the xbox controller as buttons.
	else if (button == XBOX360_LEFT || button == XBOX360_RIGHT)
	{
		float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::PovX);

		if (axis < -DPAD_THRESHHOLD && button == XBOX360_LEFT)
		{
			buttonPressed = true;
		}
		else if (axis > DPAD_THRESHHOLD && button == XBOX360_RIGHT)
		{
			buttonPressed = true;
		}

		if (buttonPressed)
		{
			// Check if the previous button state is false (button up)
			if (!m_previousState.buttons[button])
			{
				m_currentState.buttons[button] = buttonPressed;
			}
			else  // If the previous state is true (button down) then button can't be down agian
			{
				buttonPressed = false;
			}
		}
		else
		{
			// Button is not pressed so update the current state
			m_currentState.buttons[button] = false;
		}

		// Update the previous face button state
		m_previousState.buttons[button] = m_currentState.buttons[button];
	}
	else if (button == XBOX360_UP || button == XBOX360_DOWN)
	{
		float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::PovY);

		if (axis < -DPAD_THRESHHOLD && button == XBOX360_DOWN)
		{
			buttonPressed = true;
		}
		else if (axis > DPAD_THRESHHOLD && button == XBOX360_UP)
		{
			buttonPressed = true;
		}

		if (buttonPressed)
		{
			// Check if the previous button state is false (button up)
			if (!m_previousState.buttons[button])
			{
				m_currentState.buttons[button] = buttonPressed;
			}
			else  // If the previous state is true (button down) then button can't be down agian
			{
				buttonPressed = false;
			}
		}
		else
		{
			// Button is not pressed so update the current state
			m_currentState.buttons[button] = false;
		}

		// Update the previous face button state
		m_previousState.buttons[button] = m_currentState.buttons[button];
	}

	return buttonPressed;
}

/// <summary>
/// Checks if a button on the controller is held down.
/// Updates the currentstate state of the controller.
/// </summary>
/// <param name="button">The index of the button</param>
/// <returns>Returns true if the button is held down, false otherwise</returns>
bool XboxController::isButtonHeldDown(unsigned int button)
{
	bool buttonPressed = false;

	if (button >= XBOX360_A && button <= XBOX360_RIGHT_JOY_BUTTON)
	{
		buttonPressed = m_controller.isButtonPressed(m_controllerIndex, button);

		// Update the current face button state
		m_currentState.buttons[button] = buttonPressed;
	}

	else if (button == XBOX360_LEFT || button == XBOX360_RIGHT)
	{
		float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::PovX);

		if (axis < -DPAD_THRESHHOLD && button == XBOX360_LEFT)
		{
			buttonPressed = true;
		}
		else if (axis > DPAD_THRESHHOLD && button == XBOX360_RIGHT)
		{
			buttonPressed = true;
		}

		// Update the current face button state
		m_currentState.buttons[button] = buttonPressed;
	}
	else if (button == XBOX360_UP || button == XBOX360_DOWN)
	{
		float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::PovY);

		if (axis < -DPAD_THRESHHOLD && button == XBOX360_UP)
		{
			buttonPressed = true;
		}
		else if (axis > DPAD_THRESHHOLD && button == XBOX360_DOWN)
		{
			buttonPressed = true;
		}

		// Update the current face button state
		m_currentState.buttons[button] = buttonPressed;
	}

	return buttonPressed;
}

void XboxController::setVibration(float leftMotor, float rightMotor)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	vibration.wLeftMotorSpeed = static_cast <WORD> (leftMotor  * 65535.0f);
	vibration.wRightMotorSpeed = static_cast <WORD> (rightMotor * 65535.0f);

	XInputSetState(m_controllerIndex, &vibration);
}

/// <summary>
/// Gets the coordinates of the x and y axis on the left joystick in the range of [-100, 100]. 
/// The current state of left joystick is updated
/// </summary>
/// <returns>Returns a sf::Vector2f contaning the x and y coordinates of the left joystick</returns>
sf::Vector2f XboxController::getLeftStick()
{
	sf::Vector2f leftThumbStick;
	leftThumbStick.x = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::X);
	leftThumbStick.y = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::Y);

	m_currentState.leftThumbStick = leftThumbStick;

	return leftThumbStick;
}

bool XboxController::getLeftStickFlickUp()
{
	bool flickUp = false;
	float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::Y);

	if (axis < -DPAD_THRESHHOLD)
		flickUp = true;

	if (flickUp)
	{
		if (!m_previousState.leftStickFlickUp)
			m_currentState.leftStickFlickUp = flickUp;
		else
			flickUp = false;
	}
	else
		m_currentState.leftStickFlickUp = false;

	m_previousState.leftStickFlickUp = m_currentState.leftStickFlickUp;

	return flickUp;
}

bool XboxController::getLeftStickFlickDown()
{
	bool flickDown = false;
	float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::Y);

	if (axis > DPAD_THRESHHOLD)
		flickDown = true;

	if (flickDown)
	{
		if (!m_previousState.leftStickFlickDown)
			m_currentState.leftStickFlickDown = flickDown;
		else
			flickDown = false;
	}
	else
		m_currentState.leftStickFlickDown = false;

	m_previousState.leftStickFlickDown = m_currentState.leftStickFlickDown;

	return flickDown;
}

bool XboxController::getLeftStickFlickLeft()
{
	bool flickLeft = false;
	float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::X);

	if (axis < -DPAD_THRESHHOLD)
		flickLeft = true;

	if (flickLeft)
	{
		if (!m_previousState.leftStickFlickLeft)
			m_currentState.leftStickFlickLeft = flickLeft;
		else
			flickLeft = false;
	}
	else
		m_currentState.leftStickFlickLeft = false;

	m_previousState.leftStickFlickLeft = m_currentState.leftStickFlickLeft;

	return flickLeft;
}

bool XboxController::getLeftStickFlickRight()
{
	bool flickRight = false;
	float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::X);

	if (axis > DPAD_THRESHHOLD)
		flickRight = true;

	if (flickRight)
	{
		if (!m_previousState.leftStickFlickRight)
			m_currentState.leftStickFlickRight = flickRight;
		else
			flickRight = false;
	}
	else
		m_currentState.leftStickFlickRight = false;

	m_previousState.leftStickFlickRight = m_currentState.leftStickFlickRight;

	return flickRight;
}

/// <summary>
/// Gets the coordinates of the x and y axis on the right joystick in the range of [-100, 100].
/// The current state of the right joystick is updated
/// </summary>
/// <returns>Returns a sf::Vector2f contaning the x and y coordinates of the right joystick</returns>
sf::Vector2f XboxController::getRightStick()
{
	sf::Vector2f rightThumbStick;
	rightThumbStick.x = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::U);
	rightThumbStick.y = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::R);

	m_currentState.rightThumbStick = rightThumbStick;

	return rightThumbStick;
}

/// <summary>
/// Gets the position of where the left trigger is in a range from [-100, 100]
/// </summary>
/// <returns>Returns a float value of the current position of the left trigger</returns>
float XboxController::getLeftTrigger()
{
	float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::Z);

	m_currentState.LTrigger = axis;

	return axis;
}

/// <summary>
/// Gets the position of where the right trigger is in a range from [-100, 100]
/// </summary>
/// <returns>Returns a float value of the current position of the right trigger</returns>
float XboxController::getRightTrigger()
{
	float axis = m_controller.getAxisPosition(m_controllerIndex, sf::Joystick::Axis::Z);

	m_currentState.RTrigger = axis;

	return axis;
}

/// <summary>
/// Gets the current index of the controller and returns it.
/// </summary>
/// <returns>Returns the index of a connected contoller</returns>
unsigned int XboxController::getIndex()
{
	return m_controllerIndex;
}