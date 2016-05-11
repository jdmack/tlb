#version 130
in vec3 Position;
uniform mat4 World;
uniform mat4x4 Camera;
uniform mat4x4 Projection;
uniform vec4 Color;
out vec4 outColor;
void main()
{
    gl_Position = Projection * Camera * World * vec4(Position, 1.0);
    outColor = Color;

    //outColor = vec4(1.0, 0.0, 0.0, 1.0);
    //outColor = vec4(clamp(Position, 0.0, 1.0), 1.0);
}
