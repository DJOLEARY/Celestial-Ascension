#include "Graphics/DirectionalBlur.h"

DirectionalBlur::DirectionalBlur (sf::Vector2f direction, unsigned int kernelSize)
	: m_direction (direction)
{
    if (kernelSize == 0u) 
	{
        std::cout << "Warning: DirectionalBlur, kernelSize must be >  0. It will be set to 1." << std::endl;
        kernelSize = 1u;
    }

    // First we compute the Gaussian distribution coeffs
    std::vector<float> _kernel(kernelSize);

    // Gaussian function will be sampled from 0 to 1.5 with a regular step
    float step = 1.5f / static_cast<float>(kernelSize);
    for (unsigned int i = 0 ; i < kernelSize ; ++i) {
        float f = step * static_cast<float>(i);
        _kernel[i] = std::exp(-f*f);
    }

    // The kernel is normalized to preserve energy
    float total = _kernel[0];
    for (std::size_t i = 1 ; i < _kernel.size() ; ++i)
        total += 2.f * _kernel[i];
    for (float& value : _kernel)
        value /= total;

    // Writing of the fragment shader
    std::string tab = "    ";
    std::stringstream kernel;
    kernel << "(";
    for (std::size_t i = 0 ; i < _kernel.size()-1 ; ++i)
        kernel << _kernel[i] << ", ";
    kernel << _kernel[_kernel.size()-1] << ")";

    std::stringstream fragment;
    fragment << "#version 130" << std::endl << std::endl << std::endl
             << "uniform sampler2D inputTexture;" << std::endl
             << "uniform vec2 inputSize;" << std::endl
             << "uniform vec2 direction;" << std::endl << std::endl
             << "out vec4 fragColor;" << std::endl << std::endl << std::endl
             << "void main()" << std::endl
             << "{" << std::endl
             << tab << "const uint kernelSize = " << kernelSize << "u;" << std::endl
             << tab << "const float[kernelSize] kernel = float[]" << kernel.str() << ";" << std::endl << std::endl
             << tab << "vec2 texCoord = gl_FragCoord.xy / inputSize;" << std::endl
             << tab << "vec2 dCoord = direction / inputSize;" << std::endl << std::endl
             << tab << "fragColor = kernel[0] * texture(inputTexture, texCoord);" << std::endl
             << tab << "for (uint i = 1u ; i < kernelSize ; ++i) {" << std::endl
             << tab << tab << "vec4 color1 = texture(inputTexture, texCoord + i*dCoord);" << std::endl
             << tab << tab << "vec4 color2 = texture(inputTexture, texCoord- i*dCoord);" << std::endl
             << tab << tab << "fragColor += kernel[i] * (color1 + color2);" << std::endl
             << tab << "}" << std::endl
             << "}";

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
