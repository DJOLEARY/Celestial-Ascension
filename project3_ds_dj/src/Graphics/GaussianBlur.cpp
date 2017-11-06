#include "Graphics/GaussianBlur.h"

/// <summary>
/// Adds an entity to the entity manager.
/// </summary>
/// <param name="textureSize">The size of the texture to be blurred</param>
/// <param name="kernelSize">semi-width of the gaussian blur. 1 = no blur</param>
/// <param name="sizeFactor">Downscaling factor</param>
GaussianBlur::GaussianBlur (sf::Vector2u textureSize, unsigned int kernelSize, unsigned int sizeFactor)
	: m_directionalBlur(sf::Vector2f(1.f, 0.0f), kernelSize), m_sizeFactor(sizeFactor)
{
    m_sizeFactor = std::max(m_sizeFactor, 1u);

    sf::Vector2i bufferSize (textureSize.x / m_sizeFactor, textureSize.y / m_sizeFactor);

    if (m_sizeFactor > 1) 
	{
		if (!m_scalingBuffer.create(bufferSize.x, bufferSize.y))
			std::cout << "Error: GaussianBlur, buffer creation failed" << std::endl;

        m_scalingBuffer.setSmooth(true);
    }

	if (!m_blurBuffer.create(bufferSize.x, bufferSize.y))
		std::cout << "Error: GaussianBlur, buffer creation failed" << std::endl;
}


void GaussianBlur::apply(sf::Texture const& inputTexture,
                                   sf::RenderTarget& target)
{
    if (m_sizeFactor == 1) 
	{
        m_directionalBlur.setDirection(sf::Vector2f(0.f,1.f));
        m_directionalBlur.applyTreatment(inputTexture, m_blurBuffer);
        m_blurBuffer.display();

        m_directionalBlur.setDirection(sf::Vector2f(1.f,0.f));
        m_directionalBlur.applyTreatment(m_blurBuffer.getTexture(), target);
    } 
	else 
	{
        float downcaling = 1.0f / static_cast<float>(m_sizeFactor);
        float upscaling = m_sizeFactor;

        // First shrink the source so that we work on less pixels with linear interpolation
        sf::Sprite sprite (inputTexture);
        sprite.setScale(downcaling, downcaling);
        m_scalingBuffer.draw (sprite, sf::RenderStates(sf::BlendNone));
        m_scalingBuffer.display();

        // Processes the blur on the small texture
        m_directionalBlur.setDirection(sf::Vector2f(0.f,1.f));
        m_directionalBlur.applyTreatment(m_scalingBuffer.getTexture(), m_blurBuffer);
        m_blurBuffer.display();

        m_directionalBlur.setDirection(sf::Vector2f(1.f,0.f));
        m_directionalBlur.applyTreatment(m_blurBuffer.getTexture(), m_scalingBuffer);
        m_scalingBuffer.display();

        // Upscales the blurred texture
        sprite.setTexture (m_scalingBuffer.getTexture());
        sprite.setScale (upscaling, upscaling);
        target.draw (sprite, sf::RenderStates(sf::BlendNone));
    }
}