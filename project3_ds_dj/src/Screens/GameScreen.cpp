#include "Screens\GameScreen.h"

GameScreen::GameScreen(XboxController & controller) :
    Screen(GameState::GamePlay)
{
	m_entityManager = EntityManager();
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
}

void GameScreen::render(sf::RenderTexture &renderTexture)
{
    m_entityManager.Draw(renderTexture);
}
