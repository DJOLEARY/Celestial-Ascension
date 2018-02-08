#ifndef PLAY_MENU_H
#define PLAY_MENU_H

#include "GUI\Button.h"
#include "Screen.h"

class PlayMenu : public Screen
{
public:
	PlayMenu(sf::View &view, sf::Sound *confirmSound, sf::Sound *m_navigateSound);
	void update(XboxController &controller, sf::Int32 dt) override;
	void reset() override;

private:
	void playButtonSelected();
	void leaderboardButtonSelected();

	Button *m_playButton, *m_leaderboardButton;
	sf::Texture m_playTexture, m_leaderboardTexture;

	bool m_playButtonPressed, m_leaderboardButtonPressed;
	bool m_backButtonPressed;
	bool transitionIn;
	float interpolation;
	sf::Sound *m_confirmSound;
	sf::Sound *m_navigateSound;
};

#endif