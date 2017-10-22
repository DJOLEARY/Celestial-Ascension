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
	Button(sf::Texture &texture, sf::Vector2f &positionIn, sf::Color &focusColor = sf::Color(), sf::Color &outOfFocuseColor = sf::Color(), float scaleWidth = 1.0f,
		float scaleHeight = 1.0f, sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & xboxController);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;
private:
	const int BUTTON_BUFFER = 15; // Buffer for increasing the edge of the button slightly

	sf::Texture &m_buttonTexture;
	sf::Sprite m_buttonSprite;
};
#endif
