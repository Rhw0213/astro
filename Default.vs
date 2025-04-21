// vertex shader
#version 330

// raylib 기본 attribute 입력
in vec3 vertexPosition;
in vec2 vertexTexCoord;
in vec4 vertexColor;

out vec2 TexCoords;
out vec4 fragColor;

// raylib 기본 uniform
uniform mat4 mvp;

void main()
{
    gl_Position = mvp * vec4(vertexPosition, 1.0);
    TexCoords = vertexTexCoord;
    fragColor = vertexColor;
}