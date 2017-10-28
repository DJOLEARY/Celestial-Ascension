/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef WIDGET_H
#define WIDGET_H

#include <SFML\Graphics.hpp>
#include "XboxController.h"

/// <summary>
/// Allows the subclasses to overload the how the player will control a
/// widget, render it and how it's updated. Provides pointers to other widgets
/// which hold the relative location of the next gui the player can move to
/// </summary>
class Widget : public sf::Drawable
{
public:
	Widget();
	virtual ~Widget() {};

	virtual bool processInput(XboxController &controller);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Pointers to up and down widgets if any
	Widget *m_up;
	Widget *m_down;

	// @refactor(darren): May override these in other child classes and 
	// take out change color in the process input
	virtual void promoteFocus();
	virtual void demoteFocus();
	virtual void setPosition(sf::Vector2f &pos);
	sf::Vector2f getPosition();
	sf::Vector2f getStartPos();
	sf::Vector2f getEndPos();
	void setAlpha(float alpha);

protected:
	sf::Vector2f widgetPos;
	bool m_hasFocus;
	sf::Vector2f widgetStartPos, widgetEndPos;
	float m_alpha;
};

#endif