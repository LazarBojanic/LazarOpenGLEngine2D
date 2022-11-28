#version 460 core

in vec4 vColor;
in vec2 vTextureCoords;

out vec4 fragColor;

void main(){
    fragColor = vColor;
}