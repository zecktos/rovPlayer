/* 
default shader loaded when player is created
*/

#version 130

uniform sampler2DRect tex0;
out vec4 fragColor;



void main() {
	fragColor = texture(tex0, gl_FragCoord.xy);
}
