#version 130
in vec4 outColor;
in vec2 TexCoord0;
uniform sampler2D Sampler;
out vec4 FragColor;

void main()
{
    //FragColor = texture2D(Sampler, TexCoord0.xy);
    //FragColor = texture2D(Sampler, TexCoord0.st) + vec4(0.5, 0.5, 0.5, 0);
    //FragColor = texture2D(Sampler, TexCoord0.st) + 0.25 * outColor;
    //FragColor = vec4(1.0, 1.0, 1.0, 1.0);



    FragColor = texture2D(Sampler, TexCoord0.xy);
}    
