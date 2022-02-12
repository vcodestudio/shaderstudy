float random(vec2 p) {
    return fract(sin(dot(p,vec2(24.325,43.35252)))*1341341.24);
}
float randomf(float p) {
    return fract(sin(p));
}

void mainImage(out vec4 color, in vec2 pos) {
    vec2 uv = pos.xy/iResolution.xy;
    float c = 0.;
    // c = smoothstep(.2,.1,c);
    float d = 1.;
    vec2 coord = floor(uv * 10.)/10.;
    for(int i=0;i<30;i++) {
        d++;
        float cc = length(uv - vec2(.1) - 1.*vec2(randomf(d + 1.),randomf(d + 2.))) - .01;
        cc = smoothstep(max(.1,.3 * randomf(d + 4.)),.0,cc);
        c = max(c,cc);
    }

    vec2 muv = iMouse.xy/iResolution.xy;
    vec3 ld = vec3(muv,-.0);
    vec3 sdf = vec3(uv,1. - c);
    vec3 n = normalize(ld - sdf);
    vec3 l = normalize(sdf - vec3(.5,.5,.5));
    float diff = dot(l,n);
    diff = clamp(diff,0.,1.);

    // if(diff < 1. - c) diff *= .1;
    color = vec4(vec3(diff),1.);
}