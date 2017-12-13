#include "Entitys\Bullets\HomingMissile.h"

HomingMissile::HomingMissile(const sf::Vector2f &position, const sf::Vector2f &direction)
{
	// @refactor(darren): remove this
	if (!m_texture.loadFromFile("Assets/missile.png"))
	{
		std::cout << "ERROR::Bullet::Image not loaded";
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(sf::Vector2f(0.3f, 0.3f));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2.0f, m_sprite.getLocalBounds().height / 2.0f);

	m_speed = 0.1f;
	m_rotation = 0.0f;
	m_rotationDiff = 0.0f;
	m_targetRotation = 0.0f;
	m_position = position;
	m_orientation = atan2f(m_velocity.y, m_velocity.x);
	m_sprite.setRotation((m_orientation * 180) / 3.14);
	setAlive(true);

	setEnemyPosition(sf::Vector2f(200.0f, 200.0f));
}

void HomingMissile::setEnemyPosition(sf::Vector2f &pos)
{
	m_enemyPosition = pos;
}

void HomingMissile::Update(double dt)
{
	m_position += m_velocity * (float)dt;

	float targetAngle = acos(sf::dot(m_enemyPosition, m_position) / (sf::magnitude(m_enemyPosition) * sf::magnitude(m_position)));
	targetAngle = sf::radiansToDegress(targetAngle);

	if (m_rotation != targetAngle) 
	{
		// Calculate difference between the current angle and targetAngle
		float delta = targetAngle - m_rotation;

		// Keep it in range from -180 to 180 to make the most efficient turns.
		if (delta > 180)
			delta -= 360;
		if (delta < -180) 
			delta += 360;

		if (delta > 0) 
			m_rotation += TURN_RATE;
		else 
			m_rotation -= TURN_RATE;

		// Just set angle to target angle if they are close
		if (abs(delta) < sf::degressToRadians(TURN_RATE)) 
			m_rotation = targetAngle;
	}

	// Calculate velocity vector based on rotation and speed
	m_velocity.x = cos(sf::degressToRadians(m_rotation)) * m_speed;
	m_velocity.y = sin(sf::degressToRadians(m_rotation)) * m_speed;

	m_sprite.setRotation(m_rotation);
}