#version 130
in vec4 outColor;
in vec2 TexCoord0;
out vec4 FragColor;
uniform sampler2D gSampler;

void main()
{
    FragColor = texture2D(gSampler, TexCoord0.st);
}    
