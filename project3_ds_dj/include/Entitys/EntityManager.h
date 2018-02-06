#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "MathHelper.h"
#include <vector>
#include <typeinfo>
#include <iostream>
#include "Entitys\Player.h"
#include "Entitys\PowerUps\PowerUp.h"
#include "Bullets\Bullet.h"

struct EntityScore
{
	sf::Vector2f scoreDisplayPos;
	uint16_t score;
	uint16_t displayTime;
	bool removeScore;
};

/// <summary>
/// Handles all game entites update and render in the game.
/// </summary>
class EntityManager
{
public:
	EntityManager(sf::Sound *deathSound, sf::Sound *pickUpSound, sf::Sound *hitWallSound);
	~EntityManager();

	void AddBullet(Bullet *entity);
	void AddEnemy(Entity *entity);
	void AddPowerUp(PowerUp *entity);
	void SetPlayer(Player* player);
	void Update(sf::Int32 dt, uint32_t &score);
	void Draw(sf::RenderTexture &renderTexture);
	std::vector<Entity*> &GetEnemies();
	std::vector<EntityScore> &GetEnemyScores();
	int GetEnemiesSize();
	Entity* GetPowerUp();

private:
	PowerUp *m_powerUp;
	std::vector<Entity*> m_enemies;
	std::vector<Bullet*> m_bullets;
	std::vector<EntityScore> m_entityScores;
	Player* m_player;
	sf::Font *m_font;
	sf::Text m_scoreText;

	sf::Sound *m_deathSound;
	sf::Sound *m_pickUpSound;
	sf::Sound *m_hitWallSound;

	bool Collision(Entity* entity1, Entity* entity2);
	bool SimpleCollision(Entity* entity1, Entity* entity2);
};

#endif