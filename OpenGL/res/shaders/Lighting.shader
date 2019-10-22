#shader vertex
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec2 texCoord;
in layout(location = 2) vec3 normal;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;

out vec2 o_TexCoord;
out vec3 o_Normal;
out vec3 o_Fragpos;

void main()
{
	gl_Position = P * V * M * vec4(position, 1.0);
	o_TexCoord = texCoord;
	o_Normal = mat3(transpose(inverse(M))) * normal;
	o_Fragpos = vec3(M * vec4(position, 1.0));
}

#shader fragment
#version 430

out vec4 color;
in vec2 o_TexCoord;
in vec3 o_Normal;
in vec3 o_Fragpos;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform sampler2D tex;

void main()
{
	vec4 texColor = texture(tex, o_TexCoord);



	float ambientStrength = 0.25;
	vec3 ambient = ambientStrength * lightColor;



	vec3 norm = normalize(o_Normal);
	vec3 lightDir = normalize(lightPos - o_Fragpos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;


	color = vec4(ambient + diffuse, 1.0) * texColor;
}