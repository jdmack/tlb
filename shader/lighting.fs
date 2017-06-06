#version 130

in vec4 outColor;
in vec2 TexCoord0;
in vec3 Normal0;
in vec3 WorldPosition;

in float SpecularIntensity0;
in float SpecularPower0;

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 direction;
};

uniform sampler2D Sampler;
uniform DirectionalLight directionalLight;
uniform vec3 CameraPosition;
out vec4 FragColor;

void main()
{
    
    vec4 AmbientColor = vec4(directionalLight.color * directionalLight.ambientIntensity, 1.0f);
    vec3 LightDirection = -directionalLight.direction;
    vec3 Normal = normalize(Normal0);

    float DiffuseFactor = dot(Normal, LightDirection);

    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if(DiffuseFactor > 0) {
        DiffuseColor = vec4(directionalLight.color, 1.0f) * directionalLight.diffuseIntensity * DiffuseFactor;
        
        vec3 VertexToEye = normalize(CameraPosition - WorldPosition);
        vec3 LightReflect = normalize(reflect(directionalLight.direction, Normal));

        float SpecularFactor = dot(VertexToEye, LightReflect);

        if(SpecularFactor > 0) {
            SpecularFactor = pow(SpecularFactor, SpecularPower0);
            SpecularColor = vec4(directionalLight.color * SpecularIntensity0 * SpecularFactor, 1.0f);
        }
    }

    FragColor = (texture2D(Sampler, TexCoord0.xy) + (0.50 * outColor)) * (AmbientColor + DiffuseColor + SpecularColor);
}    
