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

const float offsetX = 1.0 / 1920.0;
const float offsetY = 1.0 / 1080.0;



void main()
{
	float kernel[9] = float[](
		1.0/16.0, 2.0/16.0, 1.0/16.0,
		2.0/16.0, 4.0/16.0, 2.0/16.0,
		1.0/16.0, 2.0/16.0, 1.0/16.0
	);
	
	vec4 col = vec4(0.0);
	
	col += kernel[0] * texture(tex, u_TexCoord.st + vec2(-offsetX,   offsetY));
	col += kernel[1] * texture(tex, u_TexCoord.st + vec2(0.0,        offsetY));
	col += kernel[2] * texture(tex, u_TexCoord.st + vec2(offsetX,    offsetY));
	col += kernel[3] * texture(tex, u_TexCoord.st + vec2(-offsetX,   0.0));
	col += kernel[4] * texture(tex, u_TexCoord.st + vec2(0.0,        0.0));
	col += kernel[5] * texture(tex, u_TexCoord.st + vec2(offsetX,    0.0));
	col += kernel[6] * texture(tex, u_TexCoord.st + vec2(-offsetX,  -offsetY));
	col += kernel[7] * texture(tex, u_TexCoord.st + vec2(0.0,       -offsetY));
	col += kernel[8] * texture(tex, u_TexCoord.st + vec2(offsetX,   -offsetY));

	color = col;
}