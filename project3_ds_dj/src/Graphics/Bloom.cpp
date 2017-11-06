#include "Graphics/Bloom.h"

/*
	textureSize: dimensions of the texture to be processed.	
	threshold: which bright parts to extract.
	force: force of the effect
*/
Bloom::Bloom (sf::Vector2u bufferSize, float threshold, float force):
	m_threshold (threshold), m_force(force), m_blur (bufferSize, 10, 2), m_brightPartsExtractor(m_threshold)
{
    if (!m_lightParts.create (bufferSize.x, bufferSize.y))
		std::cout << "Error: Bloom, buffer creation failed" << std::endl;

	if (!m_blurred.create(bufferSize.x, bufferSize.y))
		std::cout << "Error: Bloom, buffer creation failed" << std::endl;

	std::stringstream fragment;
	std::string line;
	std::ifstream myfile("Bloom.frag");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
			fragment << line << "\n";

		myfile.close();
	}

	std::string fragmentShader = fragment.str();

    if (!m_bloomShader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
		std::cout << "unable to load bloom fragment shader\n" + fragmentShader;

	m_renderStates.shader = &m_bloomShader;
	m_renderStates.blendMode = sf::BlendNone;
}

void Bloom::apply(const sf::Texture &inputTexture, sf::RenderTarget& target)
{
    // First extract the bright parts
    m_brightPartsExtractor.apply(inputTexture, m_lightParts);
    m_lightParts.display();

    // Then blur
    m_blur.apply(m_lightParts.getTexture(), m_blurred);
    m_blurred.display();

    // Finally render the input texture + the blurred bright parts
    sf::Vector2f texSize(target.getSize().x, target.getSize().y);
	m_bloomShader.setUniform("clearTexture", inputTexture);
	m_bloomShader.setUniform("blurredLightsTexture", m_blurred.getTexture());
	m_bloomShader.setUniform("inputSize", texSize);
	m_bloomShader.setUniform("force", m_force);
    sf::RectangleShape square(texSize);
    target.draw (square, m_renderStates);
}