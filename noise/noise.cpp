float randf(float p) {
    return fract(sin(p)*5.);
}

float rand(vec2 pos) {
    return fract(sin(dot(pos,vec2(23.4324,35.3525)))*104214.2414);
}

vec2 skew (vec2 st) {
    vec2 r = vec2(0.0);
    r.x = 1.1547*st.x;
    r.y = st.y+0.5*r.x;
    return r;
}

vec3 simplexGrid (vec2 st) {
    vec3 xyz = vec3(0.0);

    vec2 p = fract(skew(st));
    if (p.x > p.y) {
        xyz.xy = 1.0-vec2(p.x,p.y-p.x);
        xyz.z = p.y;
    } else {
        xyz.yz = 1.0-vec2(p.x-p.y,p.y);
        xyz.x = p.x;
    }

    return fract(xyz);
}

void mainImage(out vec4 color, in vec2 pos) {
    vec2 uv = pos.xy/iResolution.xy;
    vec2 p = uv * 10.;
    vec2 i = floor(p);
    vec2 f = fract(p);

    vec3 col = vec3(0.);
    col = simplexGrid(p);

    // float det = 1.;

    // //4 corners
    // float a = rand(i);
    // float b = rand(i + vec2(det,0.));
    // float c = rand(i + vec2(0.,det));
    // float d = rand(i + vec2(det,det));

    // vec2 u = smoothstep(0.,1.,f);

    // float col = mix(a,b,u.x) + (c - a)*u.y * (1. - u.x) + (d - b) * u.x * u.y;
    // float lcol = smoothstep(.15,.2,col);
    // float dcol = smoothstep(.35,.4,col);
    // col = lcol - dcol;
    color = vec4(col,1.);
}