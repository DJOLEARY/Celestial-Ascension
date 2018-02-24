/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include "Widget.h"
#include <functional>

/// <summary>
// RadioButton class used for creating radioButtons
/// </summary>
class RadioButton : public Widget 
{
public:
	RadioButton(sf::Color & focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn,
		sf::Vector2f & positionIn, std::vector<RadioButton *> & radGroup, sf::Vector2f &endPos = sf::Vector2f(),
		int characterSize = 22.f, float boxWidth = 40.f, float boxHeight = 40.f);
	bool processInput(XboxController & controller);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	void deActivate();
	bool getState() const;
	void activate();

	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;

private:
	void setColors() override;
	bool m_state = false;
	sf::RectangleShape m_radioButtonRect; 
	std::vector<RadioButton *> &m_otherButtons;

	sf::Color focusColor;
	sf::Color noFocusColor;
	sf::Color fillColor;
};

#endif
