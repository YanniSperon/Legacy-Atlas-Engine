#shader vertex
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec2 texCoord;

uniform mat4 VP;
uniform mat4 M;

out vec2 u_TexCoord;

void main()
{
	gl_Position = VP * M * vec4(position, 1.0);
	u_TexCoord = texCoord;
}

#shader fragment
#version 430

out vec4 color;
in vec2 u_TexCoord;

uniform sampler2D tex;

void main()
{
	color = texture(tex, u_TexCoord);
}