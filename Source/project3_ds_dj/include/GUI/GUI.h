/// <summary>
/// @author Darren Sweeney & D.J. O'Leary
/// </summary>

#ifndef GUI_H
#define GUI_H

#include <SFML\Graphics.hpp>
#include "Widget.h"
#include "MathHelper.h"

/// <summary>
/// Brief: Handles all Gui elements added to it
///
/// Detail: Updates and renders all Gui elements that was added to it 
/// through the use of the add(...) function
/// </summary>
class Gui : public Widget
{
public:
	Gui();
	~Gui();
	bool processInput(XboxController &controller);
	void add(Widget* widget);
	void setWidgetsAlpha(float alpha);
	void transitionOut(float transitionSpeed, float &interpolation);
	void transitionIn(float transitionSpeed, float &interpolation);
	void clear();

	// A vector of all the widgets this Gui handles
	std::vector<Widget*> m_widgets;
	std::vector<Widget*> m_controlWidget;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif