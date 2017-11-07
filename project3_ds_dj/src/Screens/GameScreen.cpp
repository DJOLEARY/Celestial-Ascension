#include "Screens\GameScreen.h"

GameScreen::GameScreen(XboxController & controller) :
    Screen(GameState::GamePlay)
{
	m_entityManager = EntityManager(&m_numOfBullets);
    m_player = new Player(controller);
    m_entityManager.Add(m_player);
    m_entityManager.Add(new Enemy(m_player->getPosition()));
}

GameScreen::~GameScreen()
{
}

void GameScreen::update(XboxController& controller, sf::Int32 dt)
{
    m_entityManager.Update(dt);

	if (controller.isButtonHeldDown(XBOX360_A) && m_numOfBullets < MAX_BULLETS)
	{
		m_entityManager.Add(new Bullet(m_player->getPos(), m_player->getOrientation()));
		m_numOfBullets++;
	}

}

void GameScreen::render(sf::RenderWindow & window)
{
    m_entityManager.Draw(window);
}
