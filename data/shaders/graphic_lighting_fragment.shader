#version 330 core

#define NUMBER_OF_POINT_LIGHTS 4

struct Material
{
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct DirectionalLight
{
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct PointLight
{
  vec3 position;

  float constant;
  float linear;
  float quadratic;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

struct SpotLight
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
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[NUMBER_OF_POINT_LIGHTS];
uniform SpotLight spotLight;

in vec3 FragmentPosition;
in vec3 Normal;
in vec2 TextureCoordinates;

out vec4 color;

// Header
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection);

void main()
{
  // Properties
  vec3 normalized = normalize(Normal);
  vec3 viewDirection = normalize(viewPosition - FragmentPosition);

  // Directional light
  vec3 result = CalculateDirectionalLight(directionalLight, normalized, viewDirection);

  // Point lights
  for (int i = 0; i < NUMBER_OF_POINT_LIGHTS; i++)
  {
    result += CalculatePointLight(pointLights[i], normalized, FragmentPosition, viewDirection);
  }

  // Spot light
  result += CalculateSpotLight(spotLight, normalized, FragmentPosition, viewDirection);

  color = vec4(result, 1.0f);
}

// Calculates the color when using a directional light
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDirection)
{
  vec3 lightDirection = normalize(-light.direction);

  // Diffuse shading
  float _diffuse = max(dot(normal, lightDirection), 0.0f);

  // Specular shading
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float _specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

  // Combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoordinates));
  vec3 diffuse = light.diffuse * _diffuse * vec3(texture(material.diffuse, TextureCoordinates));
  vec3 specular = light.specular * _specular * vec3(texture(material.specular, TextureCoordinates));

  return (ambient + diffuse + specular);
}

// Calculates the color when using a point light
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection)
{
  vec3 lightDirection = normalize(light.position - fragmentPosition);

  // Diffuse shading
  float _diffuse = max(dot(normal, lightDirection), 0.0f);

  // Specular shading
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float _specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

  // Attenuation
  float distance = length(light.position - fragmentPosition);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  // Combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoordinates));
  vec3 diffuse = light.diffuse * _diffuse * vec3(texture(material.diffuse, TextureCoordinates));
  vec3 specular = light.specular * _specular * vec3(texture(material.specular, TextureCoordinates));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return (ambient + diffuse + specular);
}

// Calculates the color when using a spot light
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragmentPosition, vec3 viewDirection)
{
  vec3 lightDirection = normalize(light.position - fragmentPosition);

  // Diffuse shading
  float _diffuse = max(dot(normal, lightDirection), 0.0f);

  // Specular shading
  vec3 reflectDirection = reflect(-lightDirection, normal);
  float _specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), material.shininess);

  // Attenuation
  float distance = length(light.position - fragmentPosition);
  float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

  // Spotlight intensity
  float theta = dot(lightDirection, normalize(-light.direction));
  float epsilon = light.cutOff - light.outerCutOff;
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

  // Combine results
  vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoordinates));
  vec3 diffuse = light.diffuse * _diffuse * vec3(texture(material.diffuse, TextureCoordinates));
  vec3 specular = light.specular * _specular * vec3(texture(material.specular, TextureCoordinates));

  ambient *= attenuation * intensity;
  diffuse *= attenuation * intensity;
  specular *= attenuation * intensity;

  return (ambient + diffuse + specular);
}
