#include "Graphics/ExtractBrightParts.h"

ExtractBrightParts::ExtractBrightParts(float threshold)
	: m_threshold (std::min(1.0f, std::max(threshold, 0.0f)))
{
    std::stringstream fragment;
	std::string line;
	std::ifstream myfile("ExtractBrightness.frag");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
			fragment << line << "\n";

		myfile.close();
	}
	else
		std::cout << "Unable to open file -> Bloom.frag";

	std::string fragmentShader = fragment.str();

    if (!m_extractBrightnessShader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
        throw std::runtime_error("unable to load ExtractBrightParts fragment shader\n" + fragmentShader);

    m_renderStates.shader = &m_extractBrightnessShader;
    m_renderStates.blendMode = sf::BlendNone;
}

void ExtractBrightParts::apply(const sf::Texture &inputTexture, sf::RenderTarget& target)
{
    sf::Vector2f texSize(target.getSize().x, target.getSize().y);
	m_extractBrightnessShader.setUniform("inputTexture", inputTexture);
	m_extractBrightnessShader.setUniform("inputSize", texSize);
	m_extractBrightnessShader.setUniform("threshold", m_threshold);

    sf::RectangleShape square(texSize);
    target.draw (square, m_renderStates);
}