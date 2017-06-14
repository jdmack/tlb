#version 130

in vec4 f_Color;
in vec2 f_TexCoord;
in vec3 f_Normal;
in vec3 f_WorldPosition;

in float f_SpecularIntensity;
in float f_SpecularPower;

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 direction;
};

uniform sampler2D f_Sampler;
uniform DirectionalLight f_DirectionalLight;
uniform vec3 f_CameraPosition;
out vec4 FragColor;

void main()
{
    
    vec4 AmbientColor = vec4(f_DirectionalLight.color * f_DirectionalLight.ambientIntensity, 1.0f);
    vec3 LightDirection = -f_DirectionalLight.direction;
    vec3 Normal = normalize(f_Normal);

    float DiffuseFactor = dot(Normal, LightDirection);

    vec4 DiffuseColor = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if(DiffuseFactor > 0) {
        DiffuseColor = vec4(f_DirectionalLight.color, 1.0f) * f_DirectionalLight.diffuseIntensity * DiffuseFactor;
        
        vec3 VertexToEye = normalize(f_CameraPosition - f_WorldPosition);
        vec3 LightReflect = normalize(reflect(f_DirectionalLight.direction, Normal));

        float SpecularFactor = dot(VertexToEye, LightReflect);

        if(SpecularFactor > 0) {
            SpecularFactor = pow(SpecularFactor, f_SpecularPower);
            SpecularColor = vec4(f_DirectionalLight.color * f_SpecularIntensity * SpecularFactor, 1.0f);
        }
    }

    FragColor = (texture2D(f_Sampler, f_TexCoord.xy) + (0.50 * f_Color)) * (AmbientColor + DiffuseColor + SpecularColor);
}    
