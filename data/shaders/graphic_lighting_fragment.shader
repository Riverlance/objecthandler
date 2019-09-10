#version 330 core

struct Material
{
  sampler2D diffuse;
  sampler2D specular;
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
in vec2 TextureCoordinates;

out vec4 color;

void main()
{
  // Ambient lighting
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoordinates));

  // Diffuse lighting
  vec3 normalized = normalize(Normal);
  vec3 lightDirection = normalize(light.position - FragmentPosition);
  float _diffuse = max(dot(normalized, lightDirection), 0.0f);
  vec3 diffuse = light.diffuse * _diffuse * vec3(texture(material.diffuse, TextureCoordinates));

  // Specular lighting
  vec3 viewDirection = normalize(viewPosition - FragmentPosition);
  vec3 reflectDirection = reflect(-lightDirection, normalized);
  float _specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);
  vec3 specular = light.specular * _specular * vec3(texture(material.specular, TextureCoordinates));



  // Result
  vec3 result = ambient + diffuse + specular;
  color = vec4(result, 1.0f);
}
