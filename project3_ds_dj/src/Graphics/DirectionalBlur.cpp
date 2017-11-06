#include "Graphics/DirectionalBlur.h"

DirectionalBlur::DirectionalBlur (sf::Vector2f direction)
	: m_direction (direction)
{
	std::stringstream fragment;
	std::string line;
	std::ifstream myfile("directionalblur.frag");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
			fragment << line << "\n";

		myfile.close();
	}

	std::string fragmentShader = fragment.str();

	if (!m_directionalBlurShader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
		std::cout << "unable to load directional blur fragment shader\n" + fragmentShader << std::endl;

    m_renderStates.shader = &m_directionalBlurShader;
    m_renderStates.blendMode = sf::BlendNone;
}

void DirectionalBlur::setDirection(const sf::Vector2f &direction)
{
    m_direction = direction;
}

void DirectionalBlur::applyTreatment(const sf::Texture &inputTexture, sf::RenderTarget &target)
{
    sf::Vector2f texSize(target.getSize().x, target.getSize().y);
	m_directionalBlurShader.setUniform("inputTexture", inputTexture);
	m_directionalBlurShader.setUniform("inputSize", texSize);
	m_directionalBlurShader.setUniform("direction", m_direction);
    sf::RectangleShape square(texSize);
    target.draw (square, m_renderStates);
}
