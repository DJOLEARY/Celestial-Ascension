#version 130

uniform sampler2D clearTexture;
uniform sampler2D blurredLightsTexture;
uniform vec2 inputSize;
uniform float force;
out vec4 fragColor;

void main()
{
	vec2 texCoord = gl_FragCoord.xy / inputSize;
	vec4 clear = texture(clearTexture, texCoord);
	vec4 blurred = texture(blurredLightsTexture, texCoord);
	fragColor = clear + force * blurred;
}