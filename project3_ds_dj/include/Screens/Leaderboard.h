/// <summary>
/// @author Darren Sweeney & D.J. O'Leary
/// </summary>

#include <SFML\Graphics.hpp>
#include "XboxController.h"
#include "Screen.h"
#include "GUI\Button.h"
#include "GUI\Label.h"

class Leaderboard : public Screen
{
public:
	Leaderboard(sf::View &view);
	void update(XboxController &controller, sf::Int32 dt) override;
	void reset();

private:
	void updateLeaderboard();
	bool leaderboardUpdated;
	bool gameOpen;

	bool m_backButtonPressed;
	bool m_transitionIn;
	float m_interpolation;

	sf::Texture m_backTexure;
	Label *m_leaderboardTitle;
	Label *m_numbers[10];
	Label *m_names[10];
	Label *m_scores[10];
	std::string m_readInNames[10];
	uint32_t m_readInScores[10];
};