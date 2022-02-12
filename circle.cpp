#iChannel0 "./images/tex.jpg"

float random2(vec2 st){
    st = vec2( dot(st,vec2(127.1,311.7)),
              dot(st,vec2(269.5,183.3)) );
    
    return -1.0 + 2.0 * fract( sin( dot( st.xy, vec2(12.9898,78.233) )) * 43758.5453123);
}

// 2D Random
float random (in vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))
                 * 43758.5453123);
}

// 2D Noise based on Morgan McGuire @morgan3d
// https://www.shadertoy.com/view/4dS3Wd
float noise (in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random2(i);
    float b = random2(i + vec2(1.0, 0.0));
    float c = random2(i + vec2(0.0, 1.0));
    float d = random2(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f*f*(3.0-2.0*f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
            (c - a)* u.y * (1.0 - u.x) +
            (d - b) * u.x * u.y;
}

void mainImage(out vec4 c, in vec2 coord) {
    vec2 st = coord.xy/iResolution.xy;
    st.x *= iResolution.x/iResolution.y;

    // Scale the coordinate system to see
    // some noise in action
    vec2 pos = vec2(st*100.0);

    // Use the noise function
    float n = noise(pos)*.5 + .5;

    vec3 cam = vec3(0.5,0.5,.5);
    vec3 o_n = vec3(st,n);
    vec3 normal = normalize(cam - o_n);

    vec4 tex = texture(iChannel0,st*.9 + .1*normal.xy);

    c = vec4(vec3(n), 1.0);
}