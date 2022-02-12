float drawMap(vec2 coord) {
    vec2 sdfPos = vec2(250.,250.);
    vec2 sdfPos2 = vec2(450.,250.);
    float sdfRad = 30.;
    float sdf = length(coord - sdfPos) - sdfRad;
    float sdf2 = length(coord - sdfPos2) - sdfRad;
    sdf = 1. - sdf;
    sdf2 = 1. - sdf2;

    sdf = clamp(sdf,0.,1.);
    sdf2 = clamp(sdf2,0.,1.);

    sdf = max(sdf,sdf2);
    sdf = clamp(sdf,0.,1.);

    return sdf;
}

void mainImage(out vec4 color, in vec2 coord) {
    vec2 uv = coord.xy/iResolution.xy;

    //light fallof
    vec2 lightPos = vec2(iMouse);
    float radius = 600.;
    float lightLength = length(coord - lightPos);
    float light = (radius - lightLength)/radius;
    light = smoothstep(0.,1.,light);
    light *= light;
    light = clamp(light,0.,1.);

    //shadow
    float sdf = drawMap(coord);
    vec2 lightDir = normalize(lightPos - coord);

    float samples = .01;
    float dray = 0.;
    
    if(lightLength > radius) {}
    else {
    for(float i=0.;i<34.;i++) {
        float dray = drawMap(coord + lightDir * samples);//빛 방향반대방향으로 그림그리기
        // samples += 3.141*max(1.,abs(dray));
        
        // dray *= lightLength/radius;
        dray = 1. - dray;
        samples += max(1.,abs(dray));
        light = min(light,dray);
        if(samples > lightLength) break; //이게 중심에서 그림자 생기는거 막아줌
    }

    // light = lightLength * light / radius;
    light = smoothstep(.0,1.0,light);
    }
    
    
    // light = min(light,1. - sdf);
    // light -= sdf;

    vec4 c_ = vec4(vec3(light),1.);
    c_ = mix(c_,vec4(1.0,.3,.5,1.),sdf);
    color = vec4(c_);

    // color = vec4(vec3(light),1.);
}