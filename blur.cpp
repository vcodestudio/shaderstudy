#iChannel0 "./images/tex2.jpeg"

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
    st.x *= iResolution.x/iResolution.y;
    st *= 1.;

    //mix 이용한 블러 만들기 mipmap
    float tile = 50.;
    vec2 pos = tile*st;
    vec2 i = floor(pos);
    vec2 f = fract(pos);

    vec2 u = smoothstep(.5,1.,f);

    vec2 a = i;
    vec2 b = i + vec2(1.0, 0.0);
    vec2 c = i + vec2(0.0, 1.0);
    vec2 d = i + vec2(1.0, 1.0);

    vec2 nuv = mix(a, b, u.x) + (c - a)* u.y * (1.0 - u.x) + (d - b) * u.x * u.y;

    vec2 uv1 = nuv/tile;

    float circle = length(coord.xy/iResolution.xy - vec2(.5));
    circle = smoothstep(.1,1.,circle);
    float rr = .1;
    vec2 uv2 = random2(st);
    float no = noise(st*10. + vec2(-1.,0.) * iTime);
    no = no*1. + .0;
    no = max(0.,no);
    uv2 = mix(st,uv2,.5*min(1. - circle,rr * no));
    vec4 tex = texture(iChannel0,uv2);

    fragColor = tex;
}