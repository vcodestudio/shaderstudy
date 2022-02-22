vec2 random(vec2 pos) {
    vec2 p = vec2(0.);
    p.x = fract(sin(dot(pos,vec2(34.324234,534.34243)))*12424.3213);
    p.y = fract(sin(dot(pos,vec2(143.3423,342.35324)))*32131.4214);

    return -1. + 2. * fract(sin(pos) * 231231.4214);
}

float noise(vec2 pos) {
    vec2 p = vec2(0.);
    p.xy = 
    
    return 
}

void mainImage(out vec4 fragColor,in vec2 fragCoord) {
    vec2 uv = fragCoord.xy/iResolution.xy;
    

    fragColor = vec4(1.);
}