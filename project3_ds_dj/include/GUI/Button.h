/// <summary>
/// @author Darren Sweeney

/// </summary>

#ifndef BUTTON_H
#define BUTTON_H

#include "Widget.h"
#include <functional>

/// <summary>
/// Brief: Button Class used for creating buttons onscreen.
/// 
/// Detail: Class inherits from Label and thus is a widget.
/// </summary>
class Button : public Widget
{
public:
	Button(sf::Texture &texture, sf::Vector2f & positionIn, float buttonWidth = 100.0f,
		float buttonHeight = 40.f, sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	bool processInput(XboxController & xboxController);
	virtual void setPosition(sf::Vector2f &position) override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setColors() override;
	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback select;
private:
	sf::RectangleShape m_buttonRect;
	const int BUTTON_BUFFER = 15; // Buffer for increasing the edge of the button slightly

	sf::Texture &m_buttonTexture;
};
#endif
