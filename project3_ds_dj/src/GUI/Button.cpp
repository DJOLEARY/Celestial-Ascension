#include "GUI/Button.h"

/// <summary>
/// Constructor function for the Button Class
/// </summary>
/// <param name="texture">The texture of the button</param>
/// <param name="positionIn">Position of the Button</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
Button::Button(sf::Texture &texture, sf::Vector2f &positionIn, sf::Color &focusColor, sf::Color &_outOfFocuseColor, 
	float scaleWidth, float scaleHeight, sf::Vector2f &endPos)
	: m_buttonTexture(texture)
{
	m_buttonSprite.setTexture(m_buttonTexture);
	m_buttonSprite.setPosition(positionIn);
	m_buttonSprite.setScale(scaleWidth, scaleHeight);
	m_buttonSprite.setOrigin(m_buttonSprite.getLocalBounds().width / 2.0f, m_buttonSprite.getLocalBounds().height / 2.0f);

	widgetPos = positionIn; // Set the position in the base class
	widgetStartPos = positionIn;
	widgetEndPos = endPos;

	inFocusColor = focusColor;
	OutOfFocusColor = _outOfFocuseColor;
}

/// <summary>
/// Processes the input from a controller and updates the Button as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool Button::processInput(XboxController & controller)
{
	if (!m_hasFocus)
	{
		OutOfFocusColor.a = m_alpha;
		m_buttonSprite.setColor(OutOfFocusColor);
		return false;
	}
	else
	{
		inFocusColor.a = m_alpha;
		m_buttonSprite.setColor(inFocusColor);

		if (controller.isButtonPressed(XBOX360_UP))
		{
			if (m_up != nullptr)
			{
				// @todo(darren): Add in button sound
				m_up->promoteFocus(); 
				demoteFocus();
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN))
		{
			if (m_down != nullptr)
			{
				// @todo(darren): Add in button sound
				m_down->promoteFocus();
				demoteFocus();
				return true;
			}
		}

		try
		{
			if (controller.isButtonPressed(XBOX360_A))
			{
				select(); // Call the callback function
				return true;
			}
		}
		catch (std::bad_function_call &e)
		{// The callback function may not be assinged here.
		}
	}
}

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
void Button::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_buttonSprite.setPosition(position);
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_buttonSprite);
}