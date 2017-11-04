#version 130

uniform sampler2D inputTexture;
uniform vec2 inputSize;
uniform vec2 direction;
uniform uint kernelSize;
out vec4 fragColor;

void main()
{
	const float[kernelSize] kernel = float[]" << kernel.str() << ";" << std::endl << std::endl
	vec2 texCoord = gl_FragCoord.xy / inputSize;
	vec2 dCoord = direction / inputSize;

	fragColor = kernel[0] * texture(inputTexture, texCoord);" << std::endl
	for (uint i = 1u ; i < kernelSize ; ++i) 
	{
		vec4 color1 = texture(inputTexture, texCoord + i * dCoord);
		vec4 color2 = texture(inputTexture, texCoord - i * dCoord);
		fragColor += kernel[i] * (color1 + color2);
	}
}