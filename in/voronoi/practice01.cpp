
vec2 random2(vec2 pos) {
    vec2 st = vec2(
        dot(pos,vec2(24.3525,531.423342)),
        dot(pos,vec2(423.432432,123.43242))
    );
    return fract(sin(st) * 12321.3232);
    //-1 + 2.*~~ 하면 안됨.
}

float rand(vec2 pos) {
    return fract(sin(dot(pos,vec2(23.4324,513.432442)))*213231.321);
}

float voronoi(vec2 pos) {
    vec2 i = floor(pos);
    vec2 f = fract(pos);

    float diff = 1.;

    for(int y=-1;y<=1;y++) {
        for(int x=-1;x<=1;x++) {
            vec2 neighbors = vec2(float(x),float(y));
            vec2 points = random2(i + neighbors);

            float val = rand(points);

            points = .5 + .5*(sin(iTime + 3.14 * 2. * points));


            //이건 왜 사이값이될까
            vec2 between = points + neighbors - f;
            float c = length(between) * .5;
            diff = min(diff,c);
        }
    }

    return diff;
}

void mainImage(out vec4 fragColor, in vec2 coord) {
    vec2 uv = coord.xy / iResolution.xy;
    uv.x *= iResolution.x/iResolution.y;
    float voronoi = voronoi(uv * 10.);
    // voronoi -= step(.7,abs(sin(voronoi * 3.14 * 10.))*1.);
    vec3 color = vec3(voronoi);
    fragColor = vec4(color,1.);
}