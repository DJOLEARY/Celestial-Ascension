/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef RADIO_BUTTONS_H
#define RADIO_BUTTONS_H

#include "CheckBox.h"

class RadioButtons : public Widget
{
public:
	RadioButtons();

	virtual bool processInput(XboxController &controller) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void add(CheckBox *button);
	// @refactor(darren): If this is the case where i make a radio buttons class i will not need m_left and m_right for any
	//						widget, just refactor m_up and m_down into widget
	Widget *m_up;
	Widget *m_down;

protected:
	sf::Vector2f m_widgetPos;
	std::vector<CheckBox*> m_checkBoxes;
	uint8_t m_currentIndex;
};

#endif