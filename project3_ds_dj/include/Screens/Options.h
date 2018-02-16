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
	Options(sf::View &view, sf::Music *music, sf::Sound *confirmSound, sf::Sound *shotSound,
		sf::Sound *waveCompleteSound, sf::Sound *pickUpSound, sf::Sound *deathSound,
		sf::Sound *turretShotSound, sf::Sound *hitWallSound, sf::Sound *navigateSound,
		sf::Sound *backSound);
	void update(XboxController& controller, sf::Int32 dt) override;
	void reset() override;
	bool m_goToFullscreenMode, m_goToWindowedMode;

private:
	void volumeChangeSliderMusic();
	void volumeChangeSliderEffects();
	void backButtonSelected();
	void checkBoxSwitched();
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

	bool m_backButtonPressed;
	bool transitionIn;
	float interpolation;

	sf::Music *m_music;
	sf::Sound *m_confirmSound;
	sf::Sound *m_shotSound;
	sf::Sound *m_waveCompleteSound;
	sf::Sound *m_pickUpSound;
	sf::Sound *m_deathSound;
	sf::Sound *m_turretShotSound;
	sf::Sound *m_hitWallSound; 
	sf::Sound *m_navigateSound;
	sf::Sound *m_backSound;

	int m_musicVolumeValue;
	int m_effectsVolumeValue;
	bool m_muted;
};

#endif