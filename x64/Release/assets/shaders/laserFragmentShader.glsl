#version 460 core

in vec2 vTextureCoords;
in vec4 vColor;

out vec4 fragColor;

uniform float uTime;
uniform vec2 uResolution;
uniform sampler2D uTexture;

uniform vec4 uColor;

void main(){
	//fragColor = mix(texture(uTexture, vTextureCoords), uColor, 1.0);
	fragColor = texture(uTexture, vTextureCoords) * uColor;
}