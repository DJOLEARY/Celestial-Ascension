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

	// @refactor(darren): Take out keyboard input from testing, it's in some widgets
	virtual bool processInput(XboxController &controller);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Pointers to adjacent widgets if any
	Widget *m_left;
	Widget *m_right;
	Widget *m_up;
	Widget *m_down;

	virtual void promoteFocus();
	void demoteFocus();
	virtual void setPosition(sf::Vector2f &pos);
	sf::Vector2f getPosition();
	sf::Vector2f getStartPos();
	sf::Vector2f getEndPos();

protected:
	sf::Vector2f widgetPos;
	bool m_hasFocus; // The widget the player is currenly on and can interact with
	sf::Vector2f widgetStartPos, widgetEndPos;
};

#endif