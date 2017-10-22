/// <summary>
/// @author Darren Sweeney 
/// </summary>

#ifndef SLIDER_H
#define SLIDER_H

#include <SFML\Graphics.hpp>
#include "Widget.h"
#include <functional>

/// <summary>
/// Brief: Slider class used for creating Sliders onscreen
/// 
/// Detail: Class inherits from Label and thus is a widget
/// </summary>
class Slider : public Widget
{
public:
	Slider(sf::Color &focusColorIn, sf::Color &noFocusColorIn, sf::Color &fillColorIn, sf::Vector2f &position, 
		float sliderWidth = 100.0f, float sliderHeight = 15.0f, sf::Vector2f &startPos = sf::Vector2f(), sf::Vector2f &endPos = sf::Vector2f());
	virtual bool processInput(XboxController & controller) override;
	virtual void setPosition(sf::Vector2f &position) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	float getPercentageFull();
	void setPercentageFull(float percentageIn);
	bool getFocus();

	// Callback function to link to external functions
	typedef std::function<void()> Callback;
	Callback increase, decrease;

private:
	sf::RectangleShape m_bar, m_base;

	//Rectangle attributes
	float m_barBaseWidth;
	float m_barBaseHeight;
	float m_barSize;

	sf::Color &focusColor;
	sf::Color &noFocusColor;
	sf::Color &fillColor;
};

#endif