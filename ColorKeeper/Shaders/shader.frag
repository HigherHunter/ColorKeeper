#version 330

in vec4 vCol;
in vec3 customCol;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 DirectionalLightSpacePos;

out vec4 color;

const int MAX_POINT_LIGHTS = 8;
const int MAX_SPOT_LIGHTS = 2;

struct Light
{
	vec3 color;
	float ambientIntensity;
	float diffuseIntensity;
};

struct DirectionalLight 
{
	Light base;
	vec3 direction;
};

struct PointLight
{
	Light base;
	vec3 position;
	float constant;
	float linear;
	float exponent;
};

struct SpotLight
{
	PointLight base;
	vec3 direction;
	float edge;
};

struct Material
{
	float specularIntensity;
	float shininess;
};

uniform int pointLightCount;
uniform int spotLightCount;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform sampler2D theTexture;
uniform sampler2D directionalShadowMap;

uniform Material material;

uniform vec3 eyePosition;

float CalcDirectionalShadowFactor(DirectionalLight light)
{
	vec3 projCoords = DirectionalLightSpacePos.xyz / DirectionalLightSpacePos.w; // -1, 1 
	projCoords = (projCoords * 0.5) + 0.5; // 0, 1

	float currentDepth = projCoords.z;

	// looking angle from light to calculate bias for shadow acne
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(light.direction);

	float bias = max(0.05 * (1 - dot(normal, lightDir)), 0.005);

	float shadow = 0.0;

	// PCF calculation
	vec2 texelSize = 1.0 / textureSize(directionalShadowMap, 0);
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(directionalShadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	shadow /= 9.0;

	if (projCoords.z > 1.0)
	{
		shadow = 0.0;
	}

	if (projCoords.x > 1.0)
	{
		shadow = 1.0;
	}

	return shadow;
}

vec4 CalcLightByDirection(Light light, vec3 direction, float shadowFactor)
{
	vec4 ambientColor = vec4(light.color, 1.0f) * light.ambientIntensity;

	// cos of angle between light and normal which gives us intensity of the light (0 - 1 value)
	float diffuseFactor = max(dot(normalize(Normal), normalize(direction)), 0.0f);
	vec4 diffuseColor = vec4(light.color * light.diffuseIntensity * diffuseFactor, 1.0f);

	vec4 specularColor = vec4(0, 0, 0, 0);

	// we need to have any diffuse light in order to have specular
	if (diffuseFactor > 0.0f)
	{
		vec3 fragToEye = normalize(eyePosition - FragPos);
		vec3 reflectedVertex = normalize(reflect(direction, normalize(Normal)));

		float specularFactor = dot(fragToEye, reflectedVertex);
		if (specularFactor > 0.0f)
		{
			specularFactor = pow(specularFactor, material.shininess);
			specularColor = vec4(light.color * material.specularIntensity * specularFactor, 1.0f);
		}
	}

	return (ambientColor + (1.0 - shadowFactor) * (diffuseColor + specularColor));
}

vec4 CalcDirectionalLight()
{
	float shadowFactor = CalcDirectionalShadowFactor(directionalLight);
	return CalcLightByDirection(directionalLight.base, directionalLight.direction, shadowFactor);
}

vec4 CalcPointLight(PointLight pLight)
{
	vec3 direction = FragPos - pLight.position;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 color = CalcLightByDirection(pLight.base, direction, 0.0);

	float attenuation = pLight.exponent * distance * distance +
							pLight.linear * distance +
							pLight.constant;

	return (color / attenuation);
}

vec4 CalcSpotLight(SpotLight sLight)
{
	vec3 rayDirection = normalize(FragPos - sLight.base.position);
	float spotLightFactor = dot(rayDirection, sLight.direction);

	if (spotLightFactor > sLight.edge)
	{
		vec4 color = CalcPointLight(sLight.base);

		// convert to new scale for soft edges
		return color  * (1.0f - (1.0f - spotLightFactor) * (1.0f / (1.0f - sLight.edge)));
	}
	else
	{
		return vec4(0, 0, 0, 0);
	}
}

vec4 CalcPointLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);

	for (int i = 0; i < pointLightCount; i++)
	{
		totalColor += CalcPointLight(pointLights[i]);
	}

	return totalColor;
}

vec4 CalcSpotLights()
{
	vec4 totalColor = vec4(0, 0, 0, 0);

	for (int i = 0; i < spotLightCount; i++)
	{
		totalColor += CalcSpotLight(spotLights[i]);
	}

	return totalColor;
}

void main()
{
	vec4 texColor = vec4(customCol,0);
	vec4 finalColor = CalcDirectionalLight();
	finalColor += CalcPointLights();
	finalColor += CalcSpotLights();

	//color = texture(theTexture, TexCoord) * finalColor;
	color = (texture(theTexture, TexCoord) * texColor) * finalColor;
}