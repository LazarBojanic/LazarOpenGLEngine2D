#version 460 core
layout (location = 0) in vec3 iPos;
layout (location = 1) in vec3 iColor;
layout (location = 2) in vec2 iTextureCoords;

out vec4 vColor;
out vec2 vTextureCoords;

uniform mat4 uTransform;

void main(){
    gl_Position = uTransform * vec4(iPos, 1.0);
    vColor = vec4(iColor, 1.0);
    vTextureCoords = iTextureCoords;
}