#include "GUI/Gui.h"

/// <summary>
/// Constructor for the Gui class
/// </summary>
/// <param name="parent">parent widget(defaults to nullptr)</param>
Gui::Gui(Widget *parent) { }

/// <summary>
/// Delets all widgets added to the widgets vector
/// </summary>
Gui::~Gui()
{
	for (Widget* widget : m_widgets)
		delete widget;
}

/// <summary>
/// Process all the widgets added and only updates the current widget has current focus
/// </summary>
/// <param name="controller">A refernce to an instance of XboxController class</param>
/// <returns> A bool value, if to process the input
bool Gui::processInput(XboxController &controller)
{
	for (Widget* widget : m_widgets)
	{
		if (!widget->processInput(controller))
		{
			// If the current widget is not in focus continue onto the next
			continue;
		}
	}
	return true;
}

/// <summary>
/// Adds a widget to the vector for widgets
/// </summary>
/// <param name="widget">widget to be added to this</param>
void Gui::add(Widget* widget)
{
	m_widgets.emplace_back(widget);
}

/// <summary>
/// Transition the Gui element from the end position to it's start position
/// </summary>
/// <param name="transitionSpeed">The speed of the transition</param>
/// <param name="interpolation">Number from [0, 1] of far along the transition is</param>
void Gui::transitionOut(float transitionSpeed, float &interpolation)
{
	if (interpolation < 1.0f)
		interpolation += transitionSpeed;
	else
		interpolation = 1.0f;

	for (Widget* widget : m_widgets)
	{
		sf::Vector2f transitionPos = lerp(widget->getStartPos(), widget->getEndPos(), interpolation); // Transition from end to start using lerp
		widget->setPosition(transitionPos);
	}
}

/// <summary>
/// Transition the Gui element from the start position to it's end position
/// </summary>
/// <param name="transitionSpeed">The speed of the transition</param>
/// <param name="interpolation">Number from [0, 1] of far along the transition is</param>
void Gui::transitionIn(float transitionSpeed, float &interpolation)
{
	if (interpolation < 1.0f)
		interpolation += transitionSpeed;
	else
		interpolation = 1.0f;

	for (Widget* widget : m_widgets)
	{
		// Get the start and end positions of the widget
		sf::Vector2f startPos = widget->getStartPos();
		sf::Vector2f endPos = widget->getEndPos();

		sf::Vector2f transitionPos = lerp(widget->getEndPos(), widget->getStartPos(), interpolation); // Transition from start to end using lerp
		widget->setPosition(transitionPos);
	}
}

/// <summary>
/// Draws all widgets contained in the widgets
/// </summary>
/// <param name="target">A refenrence to a RenderTarget</param>
/// <param name="states">RenderState which defines the state for drawing</param>
void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (Widget* widget : m_widgets)
	{
		target.draw(*widget, states);
	}
}

/// <summary>
/// Clear 
/// </summary>
void Gui::clear()
{
	for (Widget* widget : m_widgets)
		delete widget;

	m_widgets.clear(); // Clear the vector full of widget pointers
}