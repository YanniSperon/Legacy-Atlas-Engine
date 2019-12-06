#shader vertex
#version 450

in layout(location = 0) vec2 position;
in layout(location = 1) vec2 texCoord;

uniform mat4 P;
uniform mat4 M;

out vec2 u_TexCoord;

void main()
{
	gl_Position = P * M * vec4(position, 0.0, 1.0);
	u_TexCoord = texCoord;
}

#shader fragment
#version 450

out vec4 color;
in vec2 u_TexCoord;

uniform sampler2D tex;

void main(void) {
	float u_lumaThreshold = 0.5f;
	float u_mulReduceReciprocal = 8.0f;
	float u_minReduceReciprocal = 128.0f;
	float u_maxSpan = 8.0f;

	float u_mulReduce = 0.125;
	float u_minReduce = 0.0078125;

	vec2 u_texelStep = vec2(0.00052083333, 0.00092592592);
	vec3 rgbM = texture(tex, u_TexCoord).rgb;
	vec3 rgbNW = textureOffset(tex, u_TexCoord, ivec2(-1, 1)).rgb;
	vec3 rgbNE = textureOffset(tex, u_TexCoord, ivec2(1, 1)).rgb;
	vec3 rgbSW = textureOffset(tex, u_TexCoord, ivec2(-1, -1)).rgb;
	vec3 rgbSE = textureOffset(tex, u_TexCoord, ivec2(1, -1)).rgb;

	const vec3 toLuma = vec3(0.2126, 0.7152, 0.0722);
	float lumaNW = dot(rgbNW, toLuma);
	float lumaNE = dot(rgbNE, toLuma);
	float lumaSW = dot(rgbSW, toLuma);
	float lumaSE = dot(rgbSE, toLuma);
	float lumaM = dot(rgbM, toLuma);
	float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
	float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));
	if (lumaMax - lumaMin <= lumaMax * u_lumaThreshold)
	{
		color = vec4(rgbM, 1.0);
		return;
	}
	
	vec2 samplingDirection;
	samplingDirection.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));
	samplingDirection.y = ((lumaNW + lumaSW) - (lumaNE + lumaSE));
	float samplingDirectionReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * 0.25 * u_mulReduce, u_minReduce);
	float minSamplingDirectionFactor = 1.0 / (min(abs(samplingDirection.x), abs(samplingDirection.y)) + samplingDirectionReduce);
	samplingDirection = clamp(samplingDirection * minSamplingDirectionFactor, vec2(-u_maxSpan), vec2(u_maxSpan)) * u_texelStep;
	vec3 rgbSampleNeg = texture(tex, u_TexCoord + samplingDirection * (1.0 / 3.0 - 0.5)).rgb;
	vec3 rgbSamplePos = texture(tex, u_TexCoord + samplingDirection * (2.0 / 3.0 - 0.5)).rgb;
	vec3 rgbTwoTab = (rgbSamplePos + rgbSampleNeg) * 0.5;
	vec3 rgbSampleNegOuter = texture(tex, u_TexCoord + samplingDirection * (0.0 / 3.0 - 0.5)).rgb;
	vec3 rgbSamplePosOuter = texture(tex, u_TexCoord + samplingDirection * (3.0 / 3.0 - 0.5)).rgb;
	vec3 rgbFourTab = (rgbSamplePosOuter + rgbSampleNegOuter) * 0.25 + rgbTwoTab * 0.5;
	float lumaFourTab = dot(rgbFourTab, toLuma);
	if (lumaFourTab < lumaMin || lumaFourTab > lumaMax)
	{
		color = vec4(rgbTwoTab, 1.0);
	}
	else
	{
		color = vec4(rgbFourTab, 1.0);
	}
}