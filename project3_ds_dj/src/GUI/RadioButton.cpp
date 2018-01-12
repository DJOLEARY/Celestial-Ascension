#include "GUI\RadioButton.h"

RadioButton::RadioButton(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, 
	sf::Vector2f & positionIn, std::vector<RadioButton *> & radGroup, sf::Vector2f &endPos,
	int characterSize, float boxWidth, float boxHeight)
	:  m_otherButtons(radGroup), focusColor(focusColorIn), noFocusColor(noFocusColorIn), fillColor(fillColorIn)
{
	widgetPos = positionIn;
	widgetStartPos = positionIn;
	widgetEndPos = endPos;
	// Set the position, size, colour and outline of the RadioButton Box
	m_radioButtonRect.setPosition(widgetPos);
	m_radioButtonRect.setSize(sf::Vector2f(boxWidth, boxHeight));
	m_radioButtonRect.setOutlineColor(sf::Color::White);
	m_radioButtonRect.setOutlineThickness(3.0f);
	// Set the position of the Label
	sf::Vector2f textOffset(widgetPos.x, widgetPos.y - m_radioButtonRect.getGlobalBounds().height); // We offset the Label to be directly above the RadioButton
	m_radioButtonRect.setOrigin(m_radioButtonRect.getLocalBounds().width / 2.0f, m_radioButtonRect.getLocalBounds().height / 2.0f);
}

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
void RadioButton::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_radioButtonRect.setPosition(widgetPos);
}

/// <summary>
/// Processes the input from a controller / keyboard and updates the RadioButton as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool RadioButton::processInput(XboxController & controller)
{
	if (!m_hasFocus)
	{
		m_radioButtonRect.setOutlineColor(noFocusColor);
		return false;
	}
	else
	{
		m_radioButtonRect.setOutlineColor(focusColor);
		if (controller.isButtonPressed(XBOX360_UP))
		{
			if (m_up != nullptr)
			{
				// @todo(darren): Play sound here
				m_up->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN))
		{
			if (m_down != nullptr)
			{
				// @todo(darren): Play sound here
				m_down->promoteFocus();
				demoteFocus();
				return true;
			}
			
		}
		else if (controller.isButtonPressed(XBOX360_LEFT))
		{
			if (m_left  != nullptr)
			{
				// @todo(darren): Play sound here
				m_left->promoteFocus();
				demoteFocus();
				return true;
			}
			
		}
		else if (controller.isButtonPressed(XBOX360_RIGHT))
		{
			if (m_right != nullptr)
			{
				// @todo(darren): Play sound here
				m_right->promoteFocus();
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_A))
		{
			for (RadioButton * radioButton : m_otherButtons)
			{
				radioButton->deActivate(); // De-activate all other radio buttons in a group
			}
			m_state = true;

			m_radioButtonRect.setFillColor(fillColor);
			try
			{
				select();
			}
			catch (std::bad_function_call) {}
		}
	}
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void RadioButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_radioButtonRect);
}

/// <summary>
/// Function simply sets the m_state bolean to false and changes the fillcolor
/// </summary>
void RadioButton::deActivate()
{
	m_radioButtonRect.setFillColor(sf::Color(0, 0, 0, 0)); // Change the fill color
	m_state = false; // Set the state to false
}

/// <summary>
/// Simple getter method for the m_state member variable
/// </summary>
/// <returns>The state of the RadioButton</returns>
bool RadioButton::getState() const
{
	return m_state;
}

/// <summary>
/// Function used to set the state of a radiobutton
/// </summary>
/// <param name="stateIn">The state you want to set the radioButton to</param>
void RadioButton::activate()
{
	m_radioButtonRect.setFillColor(fillColor);
	m_state = true;
	for (auto & otherRadioButton : m_otherButtons)
	{
		if (otherRadioButton != this)
		{
			otherRadioButton->deActivate(); // This is done so as to ensure that no two radio buttons in a set are ever on similtaneously
		}
	}
}

/// <summary>
/// Function used to reset all of the colours used by the radio button if those colours are changed
/// </summary>
void RadioButton::setColors()
{
	if (m_hasFocus)
	{
		m_radioButtonRect.setOutlineColor(focusColor);
	}
	else
	{
		m_radioButtonRect.setOutlineColor(noFocusColor);
	}
	if (m_state)
	{
		m_radioButtonRect.setFillColor(fillColor);
	}
	else
	{
		m_radioButtonRect.setFillColor(sf::Color(0, 0, 0, 0));
	}
}