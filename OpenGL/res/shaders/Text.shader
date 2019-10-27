#shader vertex
#version 450

layout(location = 0) in vec2 vertex;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoords;

uniform mat4 P;
uniform mat4 M;

void main()
{
	gl_Position = P * M * vec4(vertex, 0.0, 1.0);
	TexCoords = texCoord;
}



#shader fragment
#version 450

in vec2 TexCoords;
out vec4 color;

uniform sampler2D tex;
uniform vec3 textColor;

void main()
{
	color = texture(tex, TexCoords);
	//color = vec4(textColor.x, textColor.y, textColor.z, texture(tex, TexCoords).w);
	//vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, TexCoords).r);
	//color = vec4(textColor, 1.0) * sampled;
}