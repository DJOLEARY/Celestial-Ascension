#include "GUI/CheckBox.h"

/// <summary>
/// Constructor function for the CheckBox class
/// </summary>
/// <param name="focusColorIn">The colour of the outline of the checkbox when in focus</param>
/// <param name="noFocusColorIn">The colour of the outline of the checkbox when not in focus</param>
/// <param name="fillColorIn">The fill color of the check box when selected</param>
/// <param name="positionIn">position of the Check Box</param>
/// <param name="boxWidth">Width of the Check Box</param>
/// <param name="boxHeight">Height of the Check Box</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
CheckBox::CheckBox(sf::Sound *confirmSound, sf::Sound *navigateSound, sf::Vector2f & positionIn, sf::Color &focusColor, sf::Color &outOfFocus, sf::Color &fillInColor, float boxWidth,
	float boxHeight, sf::Vector2f &endPos):
	focusColor(focusColor),
	noFocusColor(outOfFocus),
	fillColor(fillInColor),
	m_confirmSound(confirmSound),
	m_navigateSound(navigateSound)
{
	widgetPos = positionIn; // Set the position in the base class
	widgetStartPos = positionIn;
	widgetEndPos = endPos;
	// Set the position, size, colours and outlines of the CheckBox
	m_checkBoxRect.setPosition(widgetPos);
	m_checkBoxRect.setSize(sf::Vector2f(boxWidth, boxHeight));
	m_checkBoxRect.setOutlineThickness(3.f);
	m_checkBoxRect.setOrigin(m_checkBoxRect.getLocalBounds().width / 2.0f, m_checkBoxRect.getLocalBounds().height / 2.0f);
	m_checkBoxRect.setFillColor(sf::Color(0, 0, 0, 0));
}

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
void CheckBox::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_checkBoxRect.setPosition(widgetPos);
}

/// <summary>
/// Processes the input from a controller and updates the CheckBox as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool CheckBox::processInput(XboxController & controller)
{
	if (!m_hasFocus)
	{
		noFocusColor.a = m_alpha;
		m_checkBoxRect.setOutlineColor(noFocusColor);
		return false;
	}
	else
	{
		focusColor.a = m_alpha;
		m_checkBoxRect.setOutlineColor(focusColor); 
		if (controller.isButtonPressed(XBOX360_UP) || controller.getLeftStickFlickUp())
		{
			if (m_up != nullptr)
			{
				m_up->promoteFocus(); // Set the button above *this to be in focus
				demoteFocus(); // Set the check box to be out of focus
				m_navigateSound->play();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN) || controller.getLeftStickFlickDown())
		{
			if (m_down != nullptr)
			{
				m_down->promoteFocus();
				demoteFocus();
				m_navigateSound->play();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_A))
		{
			switchState(); // Change the state of the checkbox
			try
			{
				select();
				m_confirmSound->play();
			}
			catch (const std::bad_function_call &e) {}
		}
	}
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void CheckBox::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_checkBoxRect); // Draw the checkBoxRect
}

/// <summary>
/// Switches the state of the current check box
/// </summary>
void CheckBox::switchState()
{
	m_state = !m_state; // Flip the state of the bool

	if (m_state)
	{
		m_checkBoxRect.setFillColor(fillColor);
	}
	else
	{
		m_checkBoxRect.setFillColor(sf::Color(0, 0, 0, 0));
	}
}

/// <summary>
/// Sets the state of the checkbox
/// </summary>
/// <param name="stateIn">The state of the checkbox</param>
void CheckBox::setState(bool stateIn)
{
	if (stateIn)
	{
		switchState();
	}
}

void CheckBox::setColors()
{
	if (m_hasFocus)
	{
		focusColor.a = m_alpha;
		m_checkBoxRect.setOutlineColor(focusColor);
	}
	else
	{
		noFocusColor.a = m_alpha;
		m_checkBoxRect.setOutlineColor(noFocusColor);
	}

	if (m_state)
	{
		fillColor.a = m_alpha;
		m_checkBoxRect.setFillColor(fillColor);
	}
	else
	{
		m_checkBoxRect.setFillColor(sf::Color(0, 0, 0, 0));
	}
}

/// <summary>
/// Returns the current state of the checkbox
/// </summary>
/// <returns>The current state of the checkbox</returns>
bool CheckBox::getState()
{
	return m_state;
}