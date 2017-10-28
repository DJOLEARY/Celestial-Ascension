#include "GUI/Widget.h"

/// <summary>
/// The constructor takes in a pointer to a parent widget (if it has one).
/// Sets all realtive pointers that the gui might have to nullptr
/// </summary>
Widget::Widget()
	: m_alpha(255)
{
	m_up = nullptr;
	m_down = nullptr;
}

/// <summary>
/// A virtual method sub classes can implement for specific functionality
/// </summary>
/// <returns> A bool value, should this widget be updated
bool Widget::processInput(XboxController &controller)
{
	return false;
}

/// <summary>
/// Sets the widget focus value to true (promotes)
/// </summary>
void Widget::promoteFocus()
{
	m_hasFocus = true;
}

/// <summary>
/// Sets the widget focus value to false (demotes)
/// </summary>
void Widget::demoteFocus()
{
	m_hasFocus = false;
}

/// <summary>
/// Simply sets the position of the inherited widget
/// </summary>
/// <param name="pos">position</param>
void Widget::setPosition(sf::Vector2f &pos)
{
	widgetPos = pos;
}

/// <summary>
/// Function simply gets the position of the inherited widget
/// </summary>
/// <returns>Widget position</returns>
sf::Vector2f Widget::getPosition()
{
	return widgetPos;
}

/// <summary>
/// Getter function for the widget start position
/// </summary>
/// <returns>The start position before a transition</returns>
sf::Vector2f Widget::getStartPos()
{
	return widgetStartPos;
}

/// <summary>
/// Getter function for the widget end position
/// </summary>
/// <returns>The end position after a transition</returns>
sf::Vector2f Widget::getEndPos()
{
	return widgetEndPos;
}

void Widget::setAlpha(float alpha)
{
	m_alpha = alpha;
}

/// <summary>
/// A virtual function that the sub class can implement.
/// </summary>
void Widget::draw(sf::RenderTarget & target, sf::RenderStates states) const { }