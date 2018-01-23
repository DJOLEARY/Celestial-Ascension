#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "MathHelper.h"
#include <vector>
#include <typeinfo>
#include <iostream>
#include "Physics\ParticleManager.h"

/// <summary>
/// Handles all game entites update and render in the game.
/// </summary>
class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	void AddBullet(Entity *entity);
	void AddEnemy(Entity *entity);
	void AddPowerUp(Entity *entity);
	void SetPlayer(Entity* player);
	void Update(sf::Int32 dt, uint32_t &score);
	void Draw(sf::RenderTexture &renderTexture);
	std::vector<Entity*> GetEnemies();
	std::vector<Entity*> GetPowerUps();

private:
	std::vector<Entity*> m_powerUps;
	std::vector<Entity*> m_enemies;
	std::vector<Entity*> m_bullets;
	Entity* m_player;
	sf::Font *m_font;
	sf::Text m_scoreText;

	struct EntityScore
	{
		sf::Vector2f scoreDisplayPos;
		uint16_t score;
		uint16_t displayTime;
		bool removeScore;
	};
	std::vector<EntityScore> m_entityScores;

	bool Collision(Entity* entity1, Entity* entity2);
};

#endif