#include "GUI/RadioButtons.h"

RadioButtons::RadioButtons() 
	: m_currentIndex(0) { }

/// <summary>
/// Delete all alloacted memory for the radio buttons
/// </summary>
RadioButtons::~RadioButtons()
{
	for (RadioButton* button : buttons)
		delete button;
}

/// <summary>
/// Processes the input from a controller and updates the CheckBox as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool RadioButtons::processInput(XboxController &controller)
{
	if (!m_hasFocus)
	{
		return false;
	}
	else
	{
		if (controller.isButtonPressed(XBOX360_UP))
		{
			if (m_up != nullptr)
			{
				m_up->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN))
		{
			if (m_down != nullptr)
			{
				m_down->promoteFocus();
				demoteFocus();
				return true;
			}
		}

		// Cycle through radio buttons
		else if (controller.isButtonPressed(XBOX360_LEFT))
		{
			if (m_currentIndex > 0)
			{
				buttons[m_currentIndex]->demoteFocus();
				m_currentIndex--;
				buttons[m_currentIndex]->promoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT))
		{
			if (m_currentIndex < buttons.size() - 1)
			{
				buttons[m_currentIndex]->demoteFocus();
				m_currentIndex++;
				buttons[m_currentIndex]->promoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_A))
		{
			buttons[m_currentIndex]->toggle();

			for (size_t buttonIndex = 0; buttonIndex < buttons.size(); buttonIndex++)
			{
				if (m_currentIndex == buttonIndex)
					continue;

				buttons[buttonIndex]->turnOff();
			}
		}
	}
}

/// <summary>
/// Adds a radio button to the vector of radio buttons to manage
/// </summary>
/// <param name="button">The radio button to add</param>
void RadioButtons::add(RadioButton *button)
{
	buttons.push_back(button);
}


/// <summary>
/// Renders the all radio buttons add to the vector to the render target
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void RadioButtons::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (RadioButton *rb : buttons)
	{
		rb->draw(target, states);
	}
}

/// <summary>
/// Set the has focus of this widget manager to true and assings 
/// the last widget used to promote focus
/// </summary>
void RadioButtons::promoteFocus()
{
	m_hasFocus = true;
	buttons[m_currentIndex]->promoteFocus();
}

/// <summary>
/// Set the has focus of this widget manager to false and demotes
/// the focus of the last widget used
/// </summary>
void RadioButtons::demoteFocus()
{
	m_hasFocus = false;
	buttons[m_currentIndex]->demoteFocus();
}