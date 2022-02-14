#iChannel0 "../images/tex.jpg"

vec3 noise(vec2 pos,float divide) {
    pos *= divide;
    vec2 i = floor(pos);
    vec2 f = fract(pos);

    vec2 a = i + vec2(.0,.0);
    vec2 b = i + vec2(1.,.0);
    vec2 c = i + vec2(.0,1.);
    vec2 d = i + vec2(1.,1.);

    a /= divide;
    b /= divide;
    c /= divide;
    d /= divide;

    vec3 aa = texture(iChannel0,a).rgb;
    vec3 bb = texture(iChannel0,b).rgb;
    vec3 cc = texture(iChannel0,c).rgb;
    vec3 dd = texture(iChannel0,d).rgb;

    // f /= divide;
    // f = smoothstep(0.,1.,f);
    // f = step(.5,f);

    vec3 sd = mix(aa,bb,f.x);
    vec3 sf = mix(cc,dd,f.x);
    vec3 sc = mix(sd,sf,f.y);

    return sc;
}

void mainImage(out vec4 fragColor, in vec2 coord) {
    
    vec2 uv = coord.xy/iResolution.xy;
    float divide = 20.;
    vec3 ac = noise(uv,divide);
    vec3 ad = noise(uv + vec2(.05,.0),divide);

    vec3 color = mix(ac,ad,.5);

    fragColor = vec4(color,1.);
}