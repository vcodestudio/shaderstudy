#iChannel0 "../images/tex.jpg"

void mainImage(out vec4 fragColor, in vec2 coord) {
    
    vec2 uv = coord.xy/iResolution.xy;

    vec2 points[5];
    vec3 color = vec3(0.);

    points[0] = vec2(.3,.1);
    points[1] = vec2(.1,.9);
    points[2] = vec2(.8,.8);
    points[3] = vec2(.4,.4);
    points[4] = iMouse.xy/iResolution.xy;

    fragColor = vec4(color,1.);
}