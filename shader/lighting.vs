#version 130
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;
uniform mat4x4 World;
uniform mat4x4 Camera;
uniform mat4x4 Projection;
uniform vec4 Color;
out vec4 outColor;
out vec2 TexCoord0;
out vec3 Normal0;

void main()
{
    gl_Position = Projection * Camera * World * vec4(Position, 1.0);
    outColor = Color;
    TexCoord0 = TexCoord;
    Normal0 = (World * vec4(Normal, 0.0)).xyz;
}
