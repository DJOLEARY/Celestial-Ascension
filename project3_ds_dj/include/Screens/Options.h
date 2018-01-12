/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef OPITIONS_SCREEN_H
#define OPITIONS_SCREEN_H

#include <SFML\Graphics.hpp>
#include "XboxController.h"
#include "GUI\Slider.h"
#include "GUI\Button.h"
#include "GUI\RadioButton.h"
#include "GUI\CheckBox.h"
#include "GUI\Label.h"
#include "Screen.h"

class Options : public Screen
{
public:
	Options(sf::View &view);
	void update(XboxController& controller, sf::Int32 dt) override;
	void reset() override;
	bool m_goToFullscreenMode, m_goToWindowedMode;

private:
	void volumeUpSliderMusic();
	void volumeDownSliderMusic();
	void volumeUpSliderEffects();
	void volumeDownSliderEffects();
	void applyButtonSelected();
	void checkBoxSwitched();
	void setColorSliders();
	void setColor();
	void changeDifficulty();
	void windowedSelected();
	void fullscreenSelected();

	// GUI elements
	Label *m_optionsTitle;
	Label *m_musicTitle;
	Slider *m_musicVolume;
	Label *m_effectsTitle;
	Slider *m_effectsVolume;
	Label *m_muteTitle;
	CheckBox *m_muteCheckBox;
	Label *m_windowedLabel;
	std::vector<RadioButton*> m_windowStyleOptions;
	Label *m_fullscreenLabel;
	// @todo(darren): Should i make apply button 'Back' instead? 
	// Going to apply changes when player interacts with UI
	Button *m_applyButton;
	sf::Texture m_applyTexure;

	bool m_applyButtonPressed;
	bool transitionIn;
	float interpolation;
};

#endif