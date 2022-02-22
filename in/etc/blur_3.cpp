#iChannel0 "../images/tex.jpg"

vec2 random2d(vec2 pos) {
    vec2 st = vec2(
        fract(sin(dot(pos,vec2(1231.23132,42.31231)))*132132.213),
        fract(sin(dot(pos,vec2(42.23132,123.31231)))*142132.213)
    );
    return -1. + 2. * fract(sin(st)*123213.2414);
}

float random(vec2 pos) {
    return fract(sin(dot(pos,vec2(233.432432,24.34234)))*4214.2414);
}

void mainImage(out vec4 fragColor, in vec2 coord) {
    
    float interval = .02;
    interval = iMouse.x/iResolution.y;
    interval = smoothstep(.1,.9,interval) * .1;
    vec2 uv = coord/iResolution.xy;
    uv.x *= iResolution.x/iResolution.y;
    uv.x += .01*iTime;
    vec4 color = texture(iChannel0,(1. - interval)*uv + interval*random2d(coord/iResolution.x));
    for(int i=1;i<20;i++) {
        // vec4 color_b = texture(iChannel0,(1. - float(i)*interval)*uv + float(i)*interval*random2d(uv + random(vec2(i))));
        vec4 color_b = texture(iChannel0,(1. - interval)*uv + interval*random2d(coord/iResolution.x+vec2(float(i))));
        float dist = length(color_b - color);
        dist = smoothstep(0.,1.,dist)*.1;
        // float dist = .05;
        color = mix(color,color_b,dist);
    }

    // float dist = .5;

    fragColor = color;
}