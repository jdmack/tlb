#version 130

in vec4 outColor;
in vec2 TexCoord0;
in vec3 Normal0;

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 direction;
};

uniform sampler2D Sampler;
uniform DirectionalLight directionalLight;
out vec4 FragColor;

void main()
{
    vec4 AmbientColor = vec4(directionalLight.color * directionalLight.ambientIntensity, 1.0f);
    float DiffuseFactor = dot(normalize(Normal0), -directionalLight.direction);

    vec4 DiffuseColor;

    if(DiffuseFactor > 0) {
        DiffuseColor = vec4(directionalLight.color * directionalLight.diffuseIntensity * DiffuseFactor, 1.0f);
    }
    else {
        DiffuseColor = vec4(0, 0, 0, 0);
    }

    FragColor = (texture2D(Sampler, TexCoord0.xy) + 0.50 * outColor) * (AmbientColor + DiffuseColor);
}    
