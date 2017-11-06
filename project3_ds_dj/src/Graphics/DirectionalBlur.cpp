#include "Graphics/DirectionalBlur.h"

DirectionalBlur::DirectionalBlur (sf::Vector2f direction, int kernelSize)
	: m_direction (direction)
{
    if (kernelSize == 0u) 
	{
        std::cout << "Warning: DirectionalBlur, kernelSize must be >  0. It will be set to 1." << std::endl;
        kernelSize = 1u;
    }

    // First we compute the Gaussian distribution coeffs
    //std::vector<float> kernel(kernelSize);
	//const int kernelArraySize = kernelSize;

    // Gaussian function will be sampled from 0 to 1.5 with a regular step
    float step = 1.5f / static_cast<float>(kernelSize);
    for (unsigned int i = 0 ; i < kernelSize ; i++) 
	{
        float f = step * static_cast<float>(i);
		kernel[i] = std::exp(-f*f);
    }

    // The kernel is normalized to preserve energy
    float total = kernel[0];
    for (std::size_t i = 1 ; i < kernelSize; ++i)
        total += 2.f * kernel[i];
    for (float &value : kernel)
        value /= total;

	std::stringstream fragment;
	std::string line;
	std::ifstream myfile("DirectionalBlur.frag");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
			fragment << line << "\n";

		myfile.close();
	}

	std::string fragmentShader = fragment.str();

	if (!m_directionalBlurShader.loadFromMemory(fragmentShader, sf::Shader::Fragment))
		std::cout << "unable to load directional blur fragment shader\n" + fragmentShader << std::endl;

	//m_directionalBlurShader.setUniform("kernelSize", kernelSize);

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
	m_directionalBlurShader.setUniformArray("kernel", kernel, 10);
    sf::RectangleShape square(texSize);
    target.draw (square, m_renderStates);
}
