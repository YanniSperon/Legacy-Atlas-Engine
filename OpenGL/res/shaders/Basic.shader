#shader vertex
#version 430

in layout(location = 0) vec3 position;
in layout(location = 1) vec2 texCoord;
in layout(location = 2) vec3 normal;

uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 camPos;

out vec2 o_TexCoord;
out vec3 o_Normal;
out vec3 o_Fragpos;
out vec3 o_CameraPos;

void main()
{
	gl_Position = P * V * M * vec4(position, 1.0);
	o_TexCoord = texCoord;
	o_Normal = mat3(transpose(inverse(M))) * normal;
	o_Fragpos = vec3(M * vec4(position, 1.0));
	o_CameraPos = camPos;
}

#shader fragment
#version 430

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 color;
in vec2 o_TexCoord;
in vec3 o_Normal;
in vec3 o_Fragpos;
in vec3 o_CameraPos;

uniform Material material;
uniform Light light;
uniform sampler2D tex;

void main()
{
	vec4 texColor = texture(tex, o_TexCoord);



	vec3 ambient = light.ambient * material.ambient;



	vec3 norm = normalize(o_Normal);
	vec3 lightDir = normalize(light.position - o_Fragpos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);



	vec3 viewDir = normalize(o_CameraPos - o_Fragpos);
	vec3 reflectDir = reflect(-lightDir, o_Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);



	color = texColor;
}