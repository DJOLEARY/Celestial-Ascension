/// <summary>
/// @author Darren Sweeney
/// </summary>

#ifndef EXTRACTBRIGHTPARTS_H
#define EXTRACTBRIGHTPARTS_H

#include <SFML/Graphics.hpp>
#include <sstream>
#include <fstream>
#include <iostream>

/* 
	Extracts bright parts of an image.
	Only the perceived brightness is took into account:
	perceived brightness = 0.299 * red + 0.587 * green + 0.114 * blue.
 
	The threshold value, bewteen 0 and 1, tells which parts are kept.
 
	Sets dark parts to pure black.
*/
class ExtractBrightParts
{
public:
	ExtractBrightParts(float threshold);

	void apply(const sf::Texture &inputTexture, sf::RenderTarget& target);

private:
	float m_threshold;
	sf::Shader m_extractBrightnessShader;
	sf::RenderStates m_renderStates;
};

#endif