#iChannel0 "../images/tex.jpg"

vec2 random2(vec2 pos) {
    return fract(sin(vec2(
        dot(pos,vec2(32.342432,135.34243)),
        dot(pos,vec2(54.4324,512.34243))
    )) * 143243.124);
}

float voronoiNoise(vec2 pos, float div) {
    pos *= div;
    vec2 i = floor(pos);
    vec2 f = fract(pos);

    float diff = 1.;
    for(int y = -1;y<=1;y++) {
        for(int x = -1;x<=1;x++) {
            //양옆위아래원점
            vec2 neighbor = vec2(float(x),float(y));
            //무작위로 배열된 포인트들의 이웃과 자신들 모두 선택. 0~1사이 값
            vec2 points = random2(i + neighbor);
            
            // points = .3*(1. + (sin(3.14 * iMouse.xy/iResolution.xy + 3.14 * 2. * points)));
            points = .5 * (1. + sin(1. * random2(i + neighbor) * iTime + 3.14 * 2. * points));

            vec2 uv = points + neighbor;
            
            vec2 between = points + neighbor - f;

            float d = length(between) * .5;
            // d = smoothstep(.0,1.,d);
            diff = min(diff,d);
        }
    }

    return diff;
}

void mainImage(out vec4 fragColor, in vec2 coord) {
    
    vec2 uv = coord.xy/iResolution.xy;
    uv.x *= iResolution.x/iResolution.y;

    float color = voronoiNoise(uv,10.);
    float cstep = 0.;
    // color *= color;
    color = smoothstep(.0,1.,color);

    vec2 muv = iMouse.xy/iResolution.xy;
    muv.x *= iResolution.x/iResolution.y;

    float mouseP = length(uv - muv) - .1;
    mouseP = smoothstep(.1,.3,mouseP);
    mouseP = 1. - mouseP;
    // color = min(mouseP,color);
    color *= mouseP;

    color = clamp(color,0.,1.);

    float wall = step(.8,color);
    // color = 1. - color;
    // color = step(.9,color);
    cstep = fract(fract(.99 * (color - .1 * 0.5))*5.);//???????????
    cstep = smoothstep(.0,.8,cstep);

    vec2 normal = -vec2(dFdx(color),dFdy(color));
    vec3 normalmap = vec3(10.*normal + .5,1.);

    vec3 lightpos = vec3(vec2(1.),1.5);
    vec3 campos = vec3(vec2(.5),1.2);

    vec3 on = normalize(campos - normalmap);
    vec3 ln = normalize(lightpos - normalmap);
    float diff = dot(on,ln);

    diff = max(diff,cstep);
    diff = clamp(diff,0.,1.);

    float circle = length(uv - vec2(.5)) - .0;
    circle = smoothstep(0.,.8,1. - circle);
    diff *= circle;

    // diff = 1. - diff;

    fragColor = vec4(vec3(diff),1.);
}