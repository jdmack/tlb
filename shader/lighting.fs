#version 130

const int MAX_POINT_LIGHTS = 2;
const int MAX_SPOT_LIGHTS = 2;

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

struct PointLight
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 position;
    float attenConstant;
    float attenLinear;
    float attenExp;
};

struct SpotLight
{
    vec3 color;
    float ambientIntensity;
    float diffuseIntensity;
    vec3 position;
    float attenConstant;
    float attenLinear;
    float attenExp;
    vec3 direction;
    float cutoff;
};

uniform sampler2D f_Sampler;

uniform int f_NumDirectionalLights;
uniform int f_NumPointLights;
uniform int f_NumSpotLights;
uniform DirectionalLight f_DirectionalLight;
uniform PointLight f_PointLights[MAX_POINT_LIGHTS];
uniform vec3 f_CameraPosition;
out vec4 FragColor;

vec4 CalcLightInternal(vec3 Color, float AmbientIntensity, float DiffuseIntensity, vec3 Direction, vec3 Normal)
{
    vec4 AmbientColor = vec4(Color * AmbientIntensity, 1.0f);
    float DiffuseFactor = dot(Normal, -Direction);

    vec4 DiffuseColor  = vec4(0, 0, 0, 0);
    vec4 SpecularColor = vec4(0, 0, 0, 0);

    if(DiffuseFactor > 0) {

        DiffuseColor = vec4(Color * DiffuseIntensity * DiffuseFactor, 1.0f);

        vec3 VertexToCamera = normalize(f_CameraPosition - f_WorldPosition);
        vec3 LightReflect = normalize(reflect(Direction, Normal));
        float SpecularFactor = dot(VertexToCamera, LightReflect);

        if(SpecularFactor > 0) {
            SpecularFactor = pow(SpecularFactor, f_SpecularPower);
            SpecularColor = vec4(Color * f_SpecularIntensity * SpecularFactor, 1.0f);
        }
    }

    //return vec4(1, 1, 1, 0);
    return (AmbientColor + DiffuseColor + SpecularColor);
}

vec4 CalcDirectionalLight(vec3 Normal)
{
    if(f_NumDirectionalLights > 0) {
        return CalcLightInternal(f_DirectionalLight.color, f_DirectionalLight.ambientIntensity, 
            f_DirectionalLight.diffuseIntensity, f_DirectionalLight.direction, Normal);
    }
    else {
        return vec4(0, 0, 0, 0);
    }
}

vec4 CalcPointLight(int Index, vec3 Normal)
{
    vec3 LightDirection = f_WorldPosition - f_PointLights[Index].position;
    float Distance = length(LightDirection);
    LightDirection = normalize(LightDirection);

    vec4 Color = CalcLightInternal(f_PointLights[Index].color, f_PointLights[Index].ambientIntensity, 
        f_PointLights[Index].diffuseIntensity,  LightDirection, Normal);

    float Attenuation =  f_PointLights[Index].attenConstant +
                         f_PointLights[Index].attenLinear * Distance +
                         f_PointLights[Index].attenExp * Distance * Distance;

    //return Color;
    //return vec4(1,0,0,0);
    return Color / Attenuation;
}

void main()
{
    vec3 Normal = normalize(f_Normal);
    vec4 TotalLight = CalcDirectionalLight(Normal);

    for (int i = 0; i < f_NumPointLights; i++) {
        TotalLight += CalcPointLight(i, Normal);
    }

    //FragColor = texture2D(gSampler, TexCoord0.xy) * TotalLight;
    FragColor = (texture2D(f_Sampler, f_TexCoord.xy) + (0.50 * f_Color)) * TotalLight;
}

