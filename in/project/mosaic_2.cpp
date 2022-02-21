#iChannel0 "../images/tex2.jpeg"

vec2 mos(vec2 pos, float step) {
    return floor(pos * step)/step;
}

float random(vec2 pos) {
    return -1. + 2. * fract(sin(dot(pos,vec2(24.342,34.34234)))*11332.321);
}

vec2 random2d(vec2 pos) {
    vec2 st = vec2(
        fract(sin(dot(pos,vec2(245.342,32.432423)))*1232.24142),
        fract(sin(dot(pos,vec2(32.342,434.432423)))*13252.24142)
    );
    return fract(sin(st)*1231.23213);
}

float colorstep = 10.;
float cellstep = 350.;

void mainImage(out vec4 fragColor,in vec2 coord) {

    vec2 uv = coord/iResolution.xy;
    uv.x *= iResolution.y/iResolution.x;

    vec2 st = mos(uv,cellstep);
    float circle = length(fract(uv * cellstep) - vec2(.5));
    circle = step(.2 + .1*random(st + floor(iTime*8.)),circle);
    vec4 tex = texture(iChannel0,st + .001*random2d(st + floor(iTime*6.)));
    tex.rgb = smoothstep(0.,1.01,tex.rgb);
    tex.rgb = ceil(tex.rgb * colorstep)/colorstep;

    float gray = (tex.r + tex.g + tex.b) / 3.;
    gray = smoothstep(0.,1.,gray);
    float bg = step(.3,gray);
    float dg = 1. - step(.65,gray);
    float diff = 1.;
    diff = min(bg,diff);
    diff = min(dg,diff);
    // diff = 1. - diff;

    circle += diff;
    circle = clamp(circle,0.,1.);
    // tex.a = step(.9,tex.a);

    float backlit = 1.;
    backlit = min(backlit,gray);
    backlit = min(1. - backlit,step(.05,gray));
    backlit = clamp(backlit,0.,1.);
    backlit = smoothstep(.85,.95,backlit);

    // if(gray > .99999) circle = 1.;
    tex.rgb = .7*tex.rgb + .3*tex.rgb*circle;
    // if(gray < .3) tex.rgb += .2*(1. - gray)*(1. - circle);
    tex.rgb = mix(tex.rgb,vec3(0.5,.9,0.5),backlit*.5);
    if(tex.a < .015) tex.rgb = vec3(0.);
    fragColor = tex;
}