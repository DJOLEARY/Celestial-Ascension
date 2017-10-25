/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef RADIO_BUTTONS_H
#define RADIO_BUTTONS_H

#include <GUI\RadioButton.h>

class RadioButtons : public Widget
{
public:
	RadioButtons();

	virtual bool processInput(XboxController &controller) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void promoteFocus() override;
	virtual void demoteFocus() override;

	void add(RadioButton *button);

protected:
	sf::Vector2f m_widgetPos;
	uint8_t m_currentIndex;
	std::vector<RadioButton*> buttons;
};

#endif