/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include <functional>

/// <summary>
/// Button Class used for creating buttons onscreen.
/// </summary>
class Button : public Widget
{
public:
	// @refactor(darren): Change the order of these paramters
	Button(sf::Texture &texture, sf::Vector2f &positionIn, sf::Color &focusColor = sf::Color(), sf::Color &outOfFocusColor = sf::Color(), 
		float scaleWidth = 1.0f, float scaleHeight = 1.0f, sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & xboxController);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;

private:
	sf::Texture m_buttonTexture;
	sf::Sprite m_buttonSprite;
	sf::Color inFocusColor, OutOfFocusColor;
};
#endif
