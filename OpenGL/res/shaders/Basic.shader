#shader vertex
#version 450

in layout(location = 0) vec3 position;
in layout(location = 1) vec2 texCoord;
in layout(location = 2) vec3 normal;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec2 o_TexCoord;

void main()
{
	gl_Position = P * V * M * vec4(position, 1.0);
	o_TexCoord = texCoord;
}

#shader fragment
#version 450

out vec4 color;
in vec2 o_TexCoord;

uniform sampler2D tex;

void main()
{
	color = texture(tex, o_TexCoord);
}