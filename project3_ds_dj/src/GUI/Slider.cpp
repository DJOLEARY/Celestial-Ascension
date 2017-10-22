#include "GUI/Slider.h"

/// <summary>
/// Constructor function for the slider class
/// </summary>
/// <param name="focusColorIn">Focus color used by the slider</param>
/// <param name="noFocusColorIn">No focus color used by the slider</param>
/// <param name="fillColorIn">Fill color used by the slider</param>
/// <param name="position">position of the slider</param>
/// <param name="characterSize">Size of the font used for drawing the text</param>
/// <param name="sliderWidth">Width of the slider</param>
/// <param name="sliderHeight">Height of the slider</param>
/// <param name="startPos">The start position of the transition</param>
/// <param name="endPos">The end position of the transition</param>
Slider::Slider(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Vector2f &position, float sliderWidth,
	float sliderHeight, sf::Vector2f &startPos, sf::Vector2f &endPos):
	focusColor(focusColorIn), noFocusColor(noFocusColorIn), fillColor(fillColorIn), 
	m_barBaseWidth(sliderWidth), m_barSize(m_barBaseWidth), m_barBaseHeight(sliderHeight)
{
	widgetPos = position;
	widgetStartPos = startPos;
	widgetEndPos = endPos;

	// Base under the moving slider bar
	m_base.setSize(sf::Vector2f(m_barBaseWidth, m_barBaseHeight));
	m_base.setOutlineThickness(2);
	m_base.setPosition(widgetPos);

	// The slider bar the player changes
	m_bar.setFillColor(fillColor);
	m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight));
	m_bar.setPosition(widgetPos);
	m_base.setOrigin(m_base.getLocalBounds().width / 2.0f, m_base.getLocalBounds().height / 2.0f);
	m_bar.setOrigin(m_base.getLocalBounds().width / 2.0f, m_base.getLocalBounds().height / 2.0f);
}

/// <summary>
/// Sets the position of the button at it's origin
/// </summary>
/// <param name="position">The position origin of the button</param>
void Slider::setPosition(sf::Vector2f &position)
{
	widgetPos = position;
	m_base.setPosition(widgetPos);
	m_bar.setPosition(widgetPos);
}

/// <summary>
/// Processes the input from a controller / keyboard and updates the CheckBox as well as other widgets
/// </summary>
/// <param name="controller">Controller object used for checking input</param>
/// <returns>Bool to tell whether the input was used or not</returns>
bool Slider::processInput(XboxController &controller)
{
	//m_base.setFillColor(fillColor);
	if (!m_hasFocus)
	{
		m_base.setOutlineColor(noFocusColor); // Set the outline color to Cyan if the Widget is out of focus
		return false;
	}
	if (m_hasFocus)
	{
		m_base.setOutlineColor(focusColor); // Otherwise set the color to Magenta
		if (controller.isButtonHeldDown(XBOX360_RIGHT) // Right input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (m_barSize < m_barBaseWidth - 2)
			{
				m_barSize += 2.0f; // Increase the bar size
			}
			else
			{
				m_barSize = m_barBaseWidth;
			}
			try
			{
				increase(); // Call the associated callback function
			}
			catch (std::bad_function_call &e) {}
			m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight)); // Set the new size of the bar
			return true;
		}
		else if (controller.isButtonHeldDown(XBOX360_LEFT) // Left input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (m_barSize >= 2)
			{
				m_barSize -= 2.0f; // Decrease the bar size
			}
			else
			{
				m_barSize = 0.f;
			}
			try
			{
				decrease(); // Call the associtaed callback function
			}
			catch (std::bad_function_call &e) {}
			m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight)); // Set the new size of the bar
			return true;
		}
		else if (controller.isButtonPressed(XBOX360_UP)  // Up input
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			if (m_up != nullptr)
			{
				// @todo(darren): Play sound here
				m_up->promoteFocus(); // Set the button above *this to be in focus
				demoteFocus(); // Set the slider to be out of focus
				return true;
			}
		}
		else if (controller.isButtonPressed(XBOX360_DOWN) // Down input (See up input)
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (m_down != nullptr)
			{
				// @todo(darren): Play sound here
				m_down->promoteFocus();
				demoteFocus();
				return true;
			}
		}
	}
}

/// <summary>
/// Draw function allows the window to draw the object directly
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void Slider::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	// Draw the slider.
	target.draw(m_base);
	target.draw(m_bar, states);
}

/// <summary>
/// Function simply returns how full the slider bar is as a percentage   
/// </summary>
/// <returns>The percentage of the slider Bar that is full as a float</returns>
float Slider::getPercentageFull()
{
	return (m_barSize / m_barBaseWidth); // Simple conversion to a percentage
}

/// <summary>
/// Function allows the sliders bar size to be set
/// </summary>
/// <param name="percentageIn">A value between zero and one representing how full the slider is</param>
void Slider::setPercentageFull(float percentageIn)
{
	m_barSize = percentageIn * m_barBaseWidth;
	m_bar.setSize(sf::Vector2f(m_barSize, m_barBaseHeight));
}

/// <summary>
/// Set the colors of the Slider
/// </summary>
void Slider::setColors()
{
	if (m_hasFocus)
	{
		m_base.setOutlineColor(focusColor); // If the slider is in focus set the outline to focus color
	}
	else
	{
		m_base.setOutlineColor(noFocusColor); // otherwise set it to no focus color
	}
	m_bar.setFillColor(fillColor); // Set the fill color
}

/// <summary>
/// Simple getter function for m_hasFocus
/// </summary>
/// <returns>the focus state of the slider</returns>
bool Slider::getFocus()
{
	return m_hasFocus;
}