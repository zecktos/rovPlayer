/***

    Port of  https://www.shadertoy.com/view/XssGz8
	Original idea by Kusma: https://github.com/kusma/vlee/blob/master/data/postprocess.fx
    Adapted by CGVIRUS for the Olive-Editor Community

***/

#version 130

uniform sampler2DRect tex0;
uniform vec2 resolution;
uniform float time;
uniform vec4 controlVal;

out vec4 fragColor;

float uPower = controlVal.x; // barrel power - (values between 0-1 work well)
float uSpeed = controlVal.y;
float uFrequency = 3.0;

vec2 Distort(vec2 p, float power, float speed, float freq)
{
    float theta  = atan(p.y, p.x);
    float radius = length(p);
    radius = pow(radius, power*sin(radius*freq-time*speed)+1.0);
    p.x = radius * cos(theta);
    p.y = radius * sin(theta);
    return 0.5 * (p + 1.0);
}

void main() {
  vec2 xy = 2.0 * gl_FragCoord.xy/resolution.xy - 1.0;
  vec2 uvt;
  float d = length(xy);

  //distance of distortion
  if (d < 1.0 && uPower != 0.0)
  {
    //if power is 0, then don't call the distortion function since there's no reason to do it :)
    uvt = Distort(xy, uPower, uSpeed, uFrequency);
  }
  else
  {
    uvt = gl_FragCoord.xy / resolution.xy;
  }
  vec4 c = texture(tex0, uvt*resolution);
  fragColor = c;
}
