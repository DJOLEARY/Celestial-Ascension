#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "Entity.h"
#include "MathHelper.h"
#include <vector>
#include <typeinfo>
#include <iostream>
#include "Entitys\Player.h"
#include "Enemy.h"
#include "Entitys\PowerUps\PowerUp.h"
#include "Bullets\Bullet.h"

struct EntityScore
{
	sf::Vector2f scoreDisplayPos;
	uint16_t score;
	uint16_t displayTime;
	sf::Color color = sf::Color(226.0f, 96.0f, 9.0f, 255.0f);
	bool removeScore;
};

/// <summary>
/// Handles all game entites update and render in the game.
/// </summary>
class EntityManager
{
public:
	EntityManager(sf::Sound *deathSound, sf::Sound *shiledSound, sf::Sound *doubleBulletSound,
						sf::Sound *heartSound, sf::Sound *hitWallSound);
	~EntityManager();

	void AddBullet(Bullet *entity);
	void AddEnemy(Enemy *entity);
	void AddPowerUp(PowerUp *entity);
	void SetPlayer(Player* player);
	void Update(sf::Int32 dt, uint32_t &score);
	void Draw(sf::RenderTexture &renderTexture);
	std::vector<Enemy*> &GetEnemies();
	std::vector<EntityScore> &GetEnemyScores();
	int GetEnemiesSize();
	Entity* GetPowerUp();
	float GetMultiplier();
	void Multiplier();
	void reset();

private:
	PowerUp *m_powerUp;
	std::vector<Enemy*> m_enemies;
	std::vector<Bullet*> m_bullets;
	std::vector<EntityScore> m_entityScores;
	Player* m_player;
	sf::Font *m_font;
	sf::Text m_scoreText;

	sf::Sound *m_deathSound;
	sf::Sound *m_shieldSound, *m_doubleBulletSound, *m_heartSound;
	sf::Sound *m_hitWallSound;

	bool m_collision;

	const uint16_t SPREE_TIME = 3;
	sf::Clock m_clock;
	bool m_enemyKilled;
	int m_currentSpree;
	int m_multiplier;

	bool Collision(Entity* entity1, Entity* entity2, float radius);
	bool SimpleCollision(Entity* entity1, Entity* entity2);
};

#endif