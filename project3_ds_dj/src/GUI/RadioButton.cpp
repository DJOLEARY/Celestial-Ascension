#include "GUI/RadioButton.h"

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

void RadioButton::promoteFocus()
{
	m_hasFocus = true;
	m_radioButtonCircle.setOutlineColor(focusColor);
}

void RadioButton::demoteFocus()
{
	m_hasFocus = false;
	m_radioButtonCircle.setOutlineColor(noFocusColor);
}

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

void RadioButton::turnOff()
{
	m_isOn = false;
	m_radioButtonCircle.setFillColor(sf::Color::White);
}

void RadioButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_radioButtonCircle);
}