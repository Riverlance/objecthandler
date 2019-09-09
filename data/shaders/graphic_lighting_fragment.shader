#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 viewPosition;

in vec3 FragmentPosition;
in vec3 Normal;

out vec4 color;

void main()
{
  // Ambient lighting
  float ambientStrength = 0.1f;
  vec3 ambient = ambientStrength * lightColor;

  // Diffuse lighting
  vec3 normalized = normalize(Normal);
  vec3 lightDirection = normalize(lightPosition - FragmentPosition);
  float _diffuse = max(dot(normalized, lightDirection), 0.0f);
  vec3 diffuse = _diffuse * lightColor;

  // Specular lighting
  float specularStrength = 1.0f;
  vec3 viewDirection = normalize(viewPosition - FragmentPosition);
  vec3 reflectDirection = reflect(-lightDirection, normalized);
  float _specular = pow(max(dot(viewDirection, reflectDirection), 0.0f), 32);
  vec3 specular = specularStrength * _specular * lightColor;



  // Result
  vec3 result = (ambient + diffuse + specular) * objectColor;
  color = vec4(result, 1.0f);
}
