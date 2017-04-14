#version 130

in vec4 outColor;
in vec2 TexCoord0;

struct DirectionalLight
{
    vec3 color;
    float ambientIntensity;
};

uniform sampler2D Sampler;
uniform DirectionalLight directionalLight;
out vec4 FragColor;

void main()
{
    //FragColor = texture2D(Sampler, TexCoord0.xy);
    //FragColor = texture2D(Sampler, TexCoord0.st) + 0.50 * outColor;
    FragColor = (texture2D(Sampler, TexCoord0.xy) + 0.50 * outColor) * vec4(directionalLight.color, 1.0f) 
        * directionalLight.ambientIntensity;
}    
