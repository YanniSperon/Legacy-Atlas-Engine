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

void main()
{
	vec4 tempColor = texture(tex, u_TexCoord);
	float value = (0.2126 * tempColor.r) + (0.7152 * tempColor.g) + (0.0722 * tempColor.b);
	color = vec4(value, value, value, 1.0);
}