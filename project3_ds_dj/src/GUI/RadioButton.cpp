#include "GUI/RadioButton.h"

/// <summary>
/// 
/// </summary>
/// <param name="positionIn">The display position</param>
/// <param name="_focusColor">The color when in focus</param>
/// <param name="outOfFocus">The color when out of focus</param>
/// <param name="fillInColor">The color when turned on</param>
/// <param name="buttonRadius">The radius of the circle graphic</param>
/// <param name="startPos">The transition start position</param>
/// <param name="endPos">The transition end position</param>
RadioButton::RadioButton(sf::Vector2f & positionIn, sf::Color & _focusColor, sf::Color & outOfFocus,
	sf::Color & fillInColor, float buttonRadius, sf::Vector2f & startPos, sf::Vector2f & endPos)
	: focusColor(_focusColor), noFocusColor(outOfFocus), fillColor(fillInColor), m_radius(buttonRadius), m_isOn(false)
{
	m_radioButtonCircle.setFillColor(fillInColor);
	m_radioButtonCircle.setOutlineColor(outOfFocus);
	m_radioButtonCircle.setPosition(positionIn);
	m_radioButtonCircle.setRadius(buttonRadius);
	m_radioButtonCircle.setOutlineThickness(3.0f);
	m_radioButtonCircle.setFillColor(sf::Color::White);
	m_radioButtonCircle.setOrigin(m_radioButtonCircle.getLocalBounds().width / 2.0f, m_radioButtonCircle.getLocalBounds().height / 2.0f);
}

/// <summary>
/// Sets the outline color and has focus to true
/// </summary>
void RadioButton::promoteFocus()
{
	m_hasFocus = true;
	m_radioButtonCircle.setOutlineColor(focusColor);
}

/// <summary>
/// Sets the outline color and has focus to false
/// </summary>
void RadioButton::demoteFocus()
{
	m_hasFocus = false;
	m_radioButtonCircle.setOutlineColor(noFocusColor);
}

/// <summary>
/// Toogles the current state of the radio button
/// </summary>
void RadioButton::toggle()
{
	m_isOn = !m_isOn;

	if (m_isOn)
	{
		m_radioButtonCircle.setFillColor(fillColor);
	}
	else
	{
		m_radioButtonCircle.setFillColor(sf::Color::White);
	}
}

/// <summary>
/// Turns the radio button to a false or off state
/// </summary>
void RadioButton::turnOff()
{
	m_isOn = false;
	m_radioButtonCircle.setFillColor(sf::Color::White);
}

/// <summary>
/// Renders the radio button to the render target
/// </summary>
/// <param name="target">Targets used for drawing</param>
/// <param name="states">States used for drawing</param>
void RadioButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_radioButtonCircle);
}