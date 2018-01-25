#ifndef PLAY_MENU_H
#define PLAY_MENU_H

#include "GUI\Button.h"
#include "Screen.h"

class PlayMenu : public Screen
{
public:
	PlayMenu(sf::View &view, sf::Sound *confirmSound);
	void update(XboxController &controller, sf::Int32 dt) override;
	void reset() override;

private:
	void playButtonSelected();
	void upgradeButtonSelected();

	Button *m_playButton, *m_upgradeButton;
	sf::Texture m_playTexture, m_upgradeTexture;

	bool m_playButtonPressed, m_upgradeButtonPressed;
	bool m_backButtonPressed;
	bool transitionIn;
	float interpolation;
	sf::Sound *m_confirmSound;
};

#endif