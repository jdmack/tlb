#version 130

in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;
in float SpecularIntensity;
in float SpecularPower;
uniform mat4x4 World;
uniform mat4x4 Camera;
uniform mat4x4 Projection;
uniform vec4 Color;
out vec3 WorldPosition;
out vec4 outColor;
out vec2 TexCoord0;
out vec3 Normal0;
out float SpecularIntensity0;
out float SpecularPower0;

void main()
{
    gl_Position = Projection * Camera * World * vec4(Position, 1.0);
    outColor = Color;
    TexCoord0 = TexCoord;
    Normal0 = (World * vec4(Normal, 0.0)).xyz;
    WorldPosition = (World * vec4(Position, 1.0)).xyz;
    SpecularIntensity0 = SpecularIntensity;
    SpecularPower0 = SpecularPower;
}
