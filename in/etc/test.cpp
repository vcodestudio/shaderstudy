float circle(vec2 pos) {
    return length(pos - iMouse.xy/iResolution.xy);
}

float random(vec2 pos) {
    return -1. + 2. * fract(sin(dot(pos,vec2(32.34234,124.32434 + iTime)))*12313.231);
}

void mainImage(out vec4 fragColor, in vec2 coord) {
    vec2 uv = coord.xy / iResolution.xy;
    float c = circle(uv + .01*random(uv));

    for(int i=0;i<6;i++) {
        c += circle(uv + random(i))
    }
    c = step(.1,c);
    c = 1. - c;
    fragColor = vec4(vec3(c),1.);
}