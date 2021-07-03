/*
this is port from https://www.shadertoy.com/view/4lVSRm
*/

#version 130

//#define PIXEL_SIZE 10.0

uniform sampler2DRect tex0;
uniform vec2 resolution;
uniform vec4 controlVal;
out vec4 fragColor;

float PIXEL_SIZE = controlVal.x;

void main() {
    vec2 uv = gl_FragCoord.xy / resolution.xy;
    fragColor = vec4(0);
    
    float dx = 1.0 / resolution.x;
    float dy = 1.0 / resolution.y;
    uv.x = (dx * PIXEL_SIZE) * floor(uv.x / (dx * PIXEL_SIZE));
    uv.y = (dy * PIXEL_SIZE) * floor(uv.y / (dy * PIXEL_SIZE));

	for (int i = 0; i < int(PIXEL_SIZE); i++)
		for (int j = 0; j < int(PIXEL_SIZE); j++)
			fragColor += texture(tex0, vec2(uv.x + dx * float(i), uv.y + dy * float(j))*resolution);

	fragColor /= pow(PIXEL_SIZE, 2.0);
}
