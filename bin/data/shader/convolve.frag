/* 
this is a port from https://www.shadertoy.com/view/Xds3W8
*/

#version 130

#define PI2 6.283184

//#define CV 0.3
#define ST 0.05

uniform sampler2DRect tex0;
uniform vec2 resolution;
uniform vec4 controlVal;

float CV = controlVal.x;

out vec4 fragColor;

vec4 colorat(vec2 uv) {
	vec4 col = texture(tex0, uv*resolution);
	return col;
}

vec4 blur(vec2 uv) {
	vec4 col = vec4(0.0);
	for(float r0 = 0.0; r0 < 1.0; r0 += ST) {
		float r = r0 * CV;
		for(float a0 = 0.0; a0 < 1.0; a0 += ST) {
			float a = a0 * PI2;
			col += colorat(uv + vec2(cos(a), sin(a)) * r);
		}
	}
	col *= ST * ST;
	return col;
}

void main() {
	 vec2 uv =  gl_FragCoord.xy / resolution;
	 fragColor = blur(uv);
}
