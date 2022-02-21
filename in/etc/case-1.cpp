#iChannel0 "../images/tex.jpg"
#iChannel1 "../images/tex.jpg"

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    float switcher = step(0., -sin(1.2*cos(iTime)));
    
    // Grid parameters
    vec2 cellcount = vec2(9., 5.);
    float zoom = 0.83;
    
    // Cell coordinates
    vec2 uv = fragCoord / iResolution.xy;
    vec2 cellcoord = fract(uv * cellcount);
    vec2 cellgrid = floor(uv * cellcount) / cellcount;
    vec2 ratio = vec2(iResolution.x / cellcount.x / iResolution.y * cellcount.y , 1.0);
    vec2 xy = (2. * cellcoord - 1.) / zoom * ratio;
    
    // Mask and normals
    float aa_mask = smoothstep(1. + 0.02*cellcount.y, 1., dot(xy, xy));
    vec3 N = vec3(xy, sqrt(1. - clamp(dot(xy, xy), 0., 1.)));
    
    // Light and material paremeters
    vec3 base_color = vec3(0.12);
    vec3 L = normalize(vec3(sin(sin(iTime)),cos(sin(iTime)), 0.15));
    vec3 V = vec3(0.,0.,1.);
    float r0 = 0.3;
    
    // Ambient color
    vec3 ambient = base_color;
    
    // Diffuse light
    float ldotn = clamp(dot(L, N), 0., 1.);
    vec3 diffuse = mix(vec3(0.0), 1.0 - base_color, ldotn);
    
    // Specular light
    vec3 Rm = 2.0 * ldotn * N - L;
    float specular = pow(dot(Rm, V), 30.);
    
    // Reflection light with Schlick's approximation
    float r = r0 + (1.0 - r0) * pow(1. - dot(V, N), 5.0);
    vec3 reflection = r * texture(iChannel1, reflect(-V, N)).xyz;
    
    // Grid variator
    diffuse *= cellgrid.y;
    specular *= cellgrid.x;
    reflection *= cellgrid.x * switcher;
    
    // Output color
    vec3 balls = ambient + diffuse + specular + reflection;
    vec3 world = texture(iChannel0, normalize(vec3(uv-0.5, 0.9))).xyz * switcher;
    fragColor = vec4(mix(world, balls, aa_mask), 1.);
}