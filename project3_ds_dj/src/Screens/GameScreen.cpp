#include "Screens\GameScreen.h"

GameScreen::GameScreen(XboxController & controller) :
    Screen(GameState::GamePlay)
{
    player = new Player(controller);
    m_entityManager.Add(player);
    m_entityManager.Add(new Enemy(player->getPos()));
}

GameScreen::~GameScreen()
{
}

void GameScreen::update(XboxController& controller, sf::Int32 dt)
{
    m_entityManager.Update(dt);

	if (controller.isButtonHeldDown(XBOX360_A))
	{
		m_entityManager.Add(new Bullet(*player->getPos(), player->getVelocity()));
	}

}

void GameScreen::render(sf::RenderWindow & window)
{
    m_entityManager.Draw(window);
}
