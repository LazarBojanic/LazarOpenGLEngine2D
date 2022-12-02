#version 460 core

in vec2 vTextureCoords;
in vec4 vColor;

out vec4 fragColor;

uniform float uTime;
uniform vec2 uResolution;
vec2 uv = vTextureCoords;


void main(){

    fragColor = vec4(sin(uTime) * uv.x, 0.0, sin(uTime) * uv.y, 1.0);
}