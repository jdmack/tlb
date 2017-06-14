#version 130

in vec3 v_Position;
in vec2 v_TexCoord;
in vec3 v_Normal;
in float v_SpecularIntensity;
in float v_SpecularPower;
uniform mat4x4 v_World;
uniform mat4x4 v_Camera;
uniform mat4x4 v_Projection;
uniform vec4 v_Color;
out vec3 f_WorldPosition;
out vec4 f_Color;
out vec2 f_TexCoord;
out vec3 f_Normal;
out float f_SpecularIntensity;
out float f_SpecularPower;

void main()
{
    gl_Position = v_Projection * v_Camera * v_World * vec4(v_Position, 1.0);
    f_Color = v_Color;
    f_TexCoord = v_TexCoord;
    f_Normal = (v_World * vec4(v_Normal, 0.0)).xyz;
    f_WorldPosition = (v_World * vec4(v_Position, 1.0)).xyz;
    f_SpecularIntensity = v_SpecularIntensity;
    f_SpecularPower = v_SpecularPower;
}
