/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef DIRECTIONALBLUR_H
#define DIRECTIONALBLUR_H

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <sstream>
#include <iostream>
#include <fstream>

/* 
	Directional gaussian blur.
	Two parameters:
		- kernelSize: force of the blur, 1 for no blur, n for a size 2 * n blur
		- direction: step of the blur. If normalized, the blur will be smooth.
					otherwise, neightbouring pixels might be "missed", resulting
					in a pixelated effect.
*/
class DirectionalBlur
{
public:
	DirectionalBlur(sf::Vector2f direction);
	void setDirection(const sf::Vector2f &direction);
	void applyTreatment(const sf::Texture &inputTexture, sf::RenderTarget& target);

private:
	sf::Vector2f m_direction;
	sf::Shader m_directionalBlurShader;
	sf::RenderStates m_renderStates;
};

#endif