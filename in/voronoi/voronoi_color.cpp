#iChannel0 "../images/tex.jpg"
//진행중
vec2 random2(vec2 pos) {
    return fract(sin(vec2(
        dot(pos,vec2(32.342432,135.34243)),
        dot(pos,vec2(54.4324,512.34243))
    )) * 143243.124);
}

vec3 voronoiNoise(vec2 pos, float div) {
    pos *= div;
    vec2 i = floor(pos);
    vec2 f = fract(pos);

    float diff = 1.;
    vec3 color = vec3(0.);
    for(int y = -1;y<=1;y++) {
        for(int x = -1;x<=1;x++) {
            //양옆위아래원점
            vec2 neighbor = vec2(float(x),float(y));
            //무작위로 배열된 포인트들의 이웃과 자신들 모두 선택. 0~1사이 값
            vec2 points = random2(i + neighbor);
            
            points = .3*(1. + (sin(3.14 * iMouse.xy/iResolution.xy + 3.14 * 2. * points)));
            
            vec2 uv = points + neighbor;
            vec3 pointcolor = texture(iChannel0,uv).rgb;
            vec2 between = points + neighbor - f;
            
            float diff = length(between);
            color = mix(color,pointcolor,diff);
        }
    }

    return color;
}

void mainImage(out vec4 fragColor, in vec2 coord) {
    
    vec2 uv = coord.xy/iResolution.xy;

    vec3 color = voronoiNoise(uv,10.);
    // color = smoothstep(.0,1.,color);
    // color = 1. - color;
    // color = step(.9,color);
    fragColor = vec4(vec3(color),1.);
}