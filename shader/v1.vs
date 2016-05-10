#version 130
in vec3 Position;
uniform mat4 World;
uniform vec4 Color;
out vec4 outColor;
void main()
{
    gl_Position = World * vec4(Position, 1.0);
    outColor = Color;
    //outColor = vec4(1.0, 0.0, 0.0, 1.0);
    //outColor = vec4(clamp(Position, 0.0, 1.0), 1.0);
}
