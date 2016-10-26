#version 330 core
out vec4 color;
  
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos; //Suffit à déterminer la lumière diffuse, pas besoin de dessiner une lampe
uniform vec3 viewPos;
uniform vec3 indirectLightPos1;
uniform vec3 indirectLightPos2;
uniform vec3 indirectLightPos3;

void main()
{
	//Ambient Lighting
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

	//Diffuse Lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);

	float accentuation = 0.5f;									//A modifier pour observer sur la reflexion de lumière
	vec3 iLightDir1 = normalize(indirectLightPos1 - FragPos);	
	float diff1 = max(dot(norm,iLightDir1),0.0)*accentuation;
	vec3 iLightDir2 = normalize(indirectLightPos2 - FragPos);
	float diff2 = max(dot(norm,iLightDir2),0.0)*accentuation;
	vec3 iLightDir3 = normalize(indirectLightPos3 - FragPos);
	float diff3 = max(dot(norm,iLightDir3),0.0)*accentuation;
	
	vec3 diffuse = max(diff,max(diff1,max(diff2,diff3)))*lightColor;

	//Specular Lighting
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir),0.0),32);

	vec3 reflectDir1 = reflect(-iLightDir1, norm);				//Les spéculaires sont égalements gérées ^^
	float spec1 = pow(max(dot(viewDir, reflectDir1), 0.0),32)*accentuation;
	vec3 reflectDir2 = reflect(-iLightDir1, norm);
	float spec2 = pow(max(dot(viewDir, reflectDir2), 0.0),32)*accentuation;
	vec3 reflectDir3 = reflect(-iLightDir1, norm);
	float spec3 = pow(max(dot(viewDir, reflectDir3), 0.0),32)*accentuation;


	vec3 specular = specularStrength*max(spec,max(spec1,max(spec2,spec3)))*lightColor;

    vec3 result = (ambient+diffuse+specular) * objectColor;
    color = vec4(result, 1.0f);
}