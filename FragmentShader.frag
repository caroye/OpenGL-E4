#version 330 core
out vec4 color;
  
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; //Suffit à déterminer la lumière diffuse, pas besoin de dessiner une lampe
uniform vec3 viewPos;

void main()
{
	//Ambient Lighting
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

	//Diffuse Lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff*lightColor;

	//Specular Lighting
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0),32);
	vec3 specular = specularStrength*spec*lightColor;

    vec3 result = (ambient+diffuse+specular) * objectColor;
    color = vec4(result, 1.0f);
}