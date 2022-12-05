#version 460 core

in vec2 vTextureCoords;
in vec4 vColor;

out vec4 fragColor;

uniform sampler2D uTexture;
uniform vec4 uColor;
uniform float uTime;

uniform bool uDestroyed;

vec2 uv = vTextureCoords;


vec4 ash = vec4(0.2, 0.2, 0.2, 1.0);
vec4 fire = mix(vec4(0.72, 0.17, 0.07, 1.0), uColor, 0.2);

int OCTAVES = 6;

// values that need to be set from a script
uniform float uStartTime;
uniform float uDuration;

float rand(vec2 coord){
	return fract(sin(dot(coord, vec2(12.9898, 78.233)))* 43758.5453123);
}

float noise(vec2 coord){
	vec2 i = floor(coord);
	vec2 f = fract(coord);

	// 4 corners of a rectangle surrounding our point
	float a = rand(i);
	float b = rand(i + vec2(1.0, 0.0));
	float c = rand(i + vec2(0.0, 1.0));
	float d = rand(i + vec2(1.0, 1.0));

	vec2 cubic = f * f * (3.0 - 2.0 * f);

	return mix(a, b, cubic.x) + (c - a) * cubic.y * (1.0 - cubic.x) + (d - b) * cubic.x * cubic.y;
}

float fbm(vec2 coord){
	float value = 0.0;
	float scale = 0.5;

	for(int i = 0; i < OCTAVES; i++){
		value += noise(coord) * scale;
		coord *= 2.0;
		scale *= 0.5;
	}
	return value;
}

vec4 burn(vec4 original, vec2 uv, float time) {
	
	vec4 new_col = original; // value that will be returned
	
	float noise = fbm(uv);
	
	float thickness = 0.1;
	float outer_edge = (time - uStartTime) / uDuration;
	float inner_edge = outer_edge + thickness;
	
	// fade-in to the orange/black gradient
	if (noise < inner_edge) {
		float grad_factor = (inner_edge - noise) / thickness;
		grad_factor = clamp(grad_factor, 0.0, 1.0);
		vec4 fire_grad = mix(fire, ash, grad_factor);
		
		float inner_fade = (inner_edge - noise) / 0.02;
		inner_fade = clamp(inner_fade, 0.0, 1.0);
		
		new_col = mix(new_col, fire_grad, inner_fade);
	}
	
	// fade-out of the black at the end of the gradient
	if (noise < outer_edge) {
		new_col.a = 1.0 - (outer_edge - noise) / 0.03;
		new_col.a = clamp(new_col.a, 0.0, 1.0);
	}
	
	new_col.a *= original.a;
	return new_col;
}

void main(){
    vec4 color = texture(uTexture, uv) * uColor;
	if(!uDestroyed){
		fragColor = color;
	}
	else{
		fragColor = burn(color, uv, uTime);
	}
}