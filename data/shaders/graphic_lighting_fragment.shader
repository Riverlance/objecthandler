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
  vec3 direction;
  float cutOff;
  float outerCutOff;

  float constant;
  float linear;
  float quadratic;

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

  // Spotlight (soft edges)
  float theta = dot(lightDirection, normalize(-light.direction));
  float epsilon = (light.cutOff - light.outerCutOff);
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);
  diffuse *= intensity;
  specular *= intensity;

  // Attenuation
  float distance = length(light.position - FragmentPosition);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;



  // Result
  color = vec4(ambient + diffuse + specular, 1.0f);
}
