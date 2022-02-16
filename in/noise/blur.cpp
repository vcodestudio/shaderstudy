#iChannel0 "../images/tex.jpg"

float random(float x) {
    return fract(sin(x)*1231231.2131);
}

vec3 noise(vec2 pos,float divide) {
    pos *= divide;
    // float xi = floor(pos.x);
    // pos.y += .3*random(xi) * pos.x;
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
    float divide = 30.;
    vec2 res = 10./iResolution.xy;
    vec3 origin = texture(iChannel0,uv).rgb;
    vec3 aa = noise(uv + vec2(.0,-res.y),divide);
    vec3 ab = noise(uv + vec2(res.x,.0),divide);
    vec3 ac = noise(uv + vec2(-res.x,.0),divide);
    vec3 ad = noise(uv + vec2(.0,res.y),divide);

    vec3 color1 = mix(aa,ab,.5);
    vec3 color2 = mix(ac,ad,.5);
    vec3 color3 = mix(color1,color2,.5);
    vec3 color = mix(color3,origin,.2);

    fragColor = vec4(color3,1.);
}