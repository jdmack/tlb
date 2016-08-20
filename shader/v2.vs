#version 130
in vec3 Position;
in vec2 TexCoord;
uniform mat4 World;
uniform mat4x4 Camera;
uniform mat4x4 Projection;
uniform vec4 Color;
out vec4 outColor;
out vec2 TexCoord0;

void main()
{
    gl_Position = Projection * Camera * World * vec4(Position, 1.0);
    outColor = Color;
    TextCoord0 = TexCoord;
}
