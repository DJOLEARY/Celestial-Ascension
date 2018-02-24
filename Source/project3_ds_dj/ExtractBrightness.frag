#version 130
             
uniform sampler2D inputTexture;
uniform vec2 inputSize;
uniform float threshold;
out vec4 fragColor;

void main()
{
	vec3 color = texture(inputTexture, gl_FragCoord.xy / inputSize).rgb;
	float perceivedBrightness = dot(vec3(0.299, 0.587, 0.114), color.rgb);
	fragColor.rgb = color * step(threshold, perceivedBrightness);
	fragColor.a = 1.0;
}