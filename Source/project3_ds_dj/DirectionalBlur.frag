#version 130

uniform sampler2D inputTexture;
uniform vec2 inputSize;
uniform vec2 direction;
const uint kernelSize = 10u;
float kernel[kernelSize] =  float[] (0.0884756148, 0.0865071416, 0.0808606222, 0.0722568333, 0.0617273413, 0.0504118875, 0.0393590890, 0.0293774344, 0.0209623277, 0.0142995324);
out vec4 fragColor;

void main()
{
	vec2 texCoord = gl_FragCoord.xy / inputSize;
	vec2 dCoord = direction / inputSize;

	fragColor = kernel[0] * texture(inputTexture, texCoord);
	for (uint i = 1u; i < kernelSize ; ++i) 
	{
		vec4 color1 = texture(inputTexture, texCoord + i * dCoord);
		vec4 color2 = texture(inputTexture, texCoord - i * dCoord);
		fragColor += kernel[i] * (color1 + color2);
	}
}