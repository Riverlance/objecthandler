#version 330 core

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  float shininess;
};

struct Light
{
  vec3 position;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform vec3 viewPosition;
uniform Material material;
uniform Light light;

in vec3 FragmentPosition;
in vec3 Normal;

out vec4 color;

void main()
{
  // Ambient lighting
  vec3 ambient = light.ambient * material.ambient;

  // Diffuse lighting
  vec3 normalized = normalize(Normal);
  vec3 lightDirection = normalize(light.position - FragmentPosition);
  float _diffuse = max(dot(normalized, lightDirection), 0.0f);
  vec3 diffuse = light.diffuse * (_diffuse * material.diffuse);

  // Specular lighting
  vec3 viewDirection = normalize(viewPosition - FragmentPosition);
  vec3 reflectDirection = reflect(-lightDirection, normalized);
  float _specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
  vec3 specular = light.specular * (_specular * material.specular);



  // Result
  vec3 result = ambient + diffuse + specular;
  color = vec4(result, 1.0f);
}
