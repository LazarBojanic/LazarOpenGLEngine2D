#version 460 core

in vec2 vTextureCoords;
in vec4 vColor;

out vec4 fragColor;


void main(){
    fragColor = vColor;
}