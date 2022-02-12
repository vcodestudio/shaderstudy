
#iChannel0 "./images/tex.jpg"

float random(vec2 pos) {
    return fract(sin(dot(pos,vec2(24.342,34.2342)))*12313.321);
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    
    vec2 uv = fragCoord/iResolution.xy;

    float cols = 100.;
    float rows = 50.;
    vec2 coord = vec2(0.);

    float dir = 1.;
    if(floor(mod(floor(uv.y * rows),2.)) > 0.) dir = -1.;

    float randomness = .01;
    // uv.x *= randomness*uv.x + (1. - randomness)*random(uv);
    uv.x += randomness*random(uv);
    uv.x += dir * iTime * .1;

    coord.x = floor(cols * uv.x)/cols;
    coord.y = floor(rows * uv.y)/rows;

    float color = random(vec2(coord));

    color = step(.5,color);

    float st_ = fract(rows * uv.y);
    float st_r = step(max(.2,random(rows * vec2(coord))),st_);

    // color += st_r;

    float stripe = step(.99,st_);
    // color += stripe;
    
    vec4 tex = texture(iChannel0,fragCoord/iResolution.xy + .02*vec2(st_r,0.));

    fragColor = tex;
}