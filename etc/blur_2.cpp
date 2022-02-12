#iChannel0 "../images/tex.jpg"

float rand(vec2 pos) {
    return fract(sin(dot(pos,vec2(24.34243,35.43242)))*(12421.212 + iTime));
}
vec2 random2(vec2 st){
    st = vec2( dot(st,vec2(127.1,311.7)),
              dot(st,vec2(269.5,183.3)) );
    return -1.0 + 2.0*fract(sin(st)*(43758.5453123));
}

float noise(vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    vec2 u = smoothstep(.0,1.,f);

    return mix( mix( dot( random2(i + vec2(0.0,0.0) ), f - vec2(0.0,0.0) ),
                     dot( random2(i + vec2(1.0,0.0) ), f - vec2(1.0,0.0) ), u.x),
                mix( dot( random2(i + vec2(0.0,1.0) ), f - vec2(0.0,1.0) ),
                     dot( random2(i + vec2(1.0,1.0) ), f - vec2(1.0,1.0) ), u.x), u.y);
}

void mainImage(out vec4 fragColor, in vec2 coord) {
    vec2 st = coord.xy/iResolution.xy;
    // st.x *= iResolution.x/iResolution.y;

    vec2 mpoint = iMouse.xy/iResolution.xy;
    float dl = length(coord.xy/iResolution.xy - mpoint);

    // st.xy += iTime;

    float rad = .01;
    rad = clamp(rad,0.,1.);
    dl = smoothstep(rad,rad + .2,dl);
    dl *= dl;

    vec2 di = normalize(mpoint - st);
    vec2 nuv = st + di * dl;
    // nuv = clamp(nuv,0.,1.);
    
    vec4 tex = texture(iChannel0,nuv);

    float blue = tex.b;
    blue = smoothstep(.65,.9,blue);

    tex.rgb = vec3((tex.r + tex.g + tex.b)/3.);
    tex.rgb *= tex.rgb;
    tex.rgb *= tex.rgb;

    float samples = .01;
    for(int i=0;i<30;i++) {
        float map = texture(iChannel0,nuv + di*dl*samples).b;
        map*=map;
        map = samples * smoothstep(.6,.9,map);
        map = clamp(map,.0,1.);
        samples += min(1.,map);
        samples = clamp(samples,0.,1.);
        blue += map;
    }
    
    tex.rgb = mix(vec3(0.),vec3(.1,.4,.99),blue);

    fragColor = vec4(blue);
}