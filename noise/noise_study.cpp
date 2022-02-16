float random(vec2 pos) {
    float x = fract(sin(dot(pos,vec2(24.34224,342.34243)))*12321.32);
    float y = fract(sin(dot(pos,vec2(533.34224,23.34243)))*323421.32);
    vec2 n = vec2(x,y);

    return fract(sin(dot(n,vec2(53.4324,125.34243)))*4142.211);
}

float noiseInterpolation(vec2 pos) {

	//셀 변환
	vec2 i = floor(pos);
	vec2 f = fract(pos);

	//각 꼭짓점 좌표
	float Q11 = random(i + vec2(0.,0.));
	float Q21 = random(i + vec2(1.,0.));
	float Q12 = random(i + vec2(0.,1.));
	float Q22 = random(i + vec2(1.,1.));

    f = f * f * (3. - 2.*f);
	// f = smoothstep(0.,1.,f);
	// 1. Q11과 Q21 두점 사이에 있는 R1의 값을 선형보간법을 사용하여 알아낸다.
	float R1 = mix(Q11,Q21,f.x);
	// 2. Q12과 Q22 두점 사이에 있는 R2의 값을 선형보간법을 사용하여 알아낸다.
	float R2 = mix(Q12,Q22,f.x);
	// 3. R1과 R2 두점 사이에 있는 P의 값을 선형보간법을 사용하여 알아낸다.
	float P = mix(R1,R2,f.y);

	return P;
}

void mainImage(out vec4 fragColor, in vec2 coord) {
    vec2 uv = coord.xy/iResolution.xy;
	vec3 lightpos = vec3(iMouse.xy/iResolution.xy,1.0);
	vec3 campos = vec3(uv,1.1);
	float z = noiseInterpolation(uv * 20.);
	z = clamp(z,0.,1.);
	vec2 normal = -vec2(dFdx(z), dFdy(z));
	normal *= 3.;
	normal += .5;
	vec3 normalmap = vec3(normal,1.);
	vec3 norm = normalize(normalmap - campos);
	vec3 ld = normalize(vec3(normal,z) - lightpos);
	float diff = dot(norm,ld);
	diff = smoothstep(0.,1.,diff);
	diff *= diff;

	float circle = length(coord.xy - iMouse.xy) - 45.;
	circle = 1. - circle;
	
	// diff += circle;
	diff = clamp(diff,0.,1.);
    fragColor = vec4(vec3(diff),1.);
}