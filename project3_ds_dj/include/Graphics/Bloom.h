/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef BLOOM_H
#define BLOOM_H

#include "Graphics/GaussianBlur.h"
#include "Graphics/ExtractBrightParts.h"

#include <SFML/Graphics.hpp>

#include <sstream>
#include <fstream>
#include <iostream>

/*	
	Bloom post-treatment.
	Makes bright parts of the image shinier.
 
	The treatment works in 3 steps:
		- extraction of the bright parts of the image
		- blurring of the resulting image
		- adding of the blurred bright parts to the input image.
 */
class Bloom
{
    public:
         Bloom (sf::Vector2u textureSize, float threshold = 0.8f, float force = 1.0f);

        void apply(const sf::Texture &inputTexture, sf::RenderTarget& target);

    private:

        float m_threshold;
        float m_force;

        GaussianBlur m_blur;
        ExtractBrightParts m_brightPartsExtractor;

        sf::Shader m_bloomShader;
		sf::RenderTexture m_lightParts;
		sf::RenderTexture m_blurred;
        sf::RenderStates m_renderStates;
};

#endif