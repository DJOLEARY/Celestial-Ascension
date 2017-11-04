#ifndef GAUSSIANBLUR_H
#define GAUSSIANBLUR_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Graphics/DirectionalBlur.h"

/* 
	Gaussian blur effect.
	It is implemented as two orthogonal directional blurs.
 
	For better performance, the texture can be downscaled,
	blurred and then upscaled. Typically, shrinking the blurred
	texture by x2 enables x4 performance for a visually
	equivalent result.
*/
class GaussianBlur
{
public:
	GaussianBlur(sf::Vector2u textureSize, unsigned int kernelSize, unsigned int sizeFactor = 1);

	void apply(const sf::Texture &inputTexture,
		sf::RenderTarget& target);

private:
	DirectionalBlur m_directionalBlur;
	unsigned int m_sizeFactor;

	sf::RenderTexture m_scalingBuffer; // Used for downscaling/upscaling
	sf::RenderTexture m_blurBuffer;
};

#endif