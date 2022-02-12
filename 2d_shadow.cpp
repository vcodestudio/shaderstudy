vec2 translate(vec2 p, vec2 t)
{
	return p - t;
}


//////////////////////////////
// Distance field functions //
//////////////////////////////


float circleDist(vec2 p, float radius)
{
	return length(p) - radius;
}



///////////////////////
// Masks for drawing //
///////////////////////


float fillMask(float dist)
{
	return clamp(-dist, 0.0, 1.0);
}


///////////////
// The scene //
///////////////


float sceneDist(vec2 p)
{
	float c = circleDist(translate(p, vec2(100, 250)), 50.0);	
	return c;
}

vec4 drawLight(vec2 p, vec2 pos, vec4 color, float dist, float range, float radius)
{
    // p = fragCoord
	// distance to light : 각 픽셀포인트마다 빛 원점까지 거리
	float ld = length(p - pos);
	
	// out of range : 범위 넘어가면 0처리
	if (ld > range) return vec4(0.0);
	
	// shadow and falloff : 조명 -> 픽셀 노멀 방향 계산
    vec2 dir = normalize(pos - p);
    //위랑 똑같은 계산
    float lightDistance = ld;
	float dl = lightDistance;
	
	// fraction of light visible, starts at one radius (second half added in the end);
    // 
	float lightFraction = radius * dl;
	
	// distance traveled 초기값. 하단에서 계속 중첩되어 커진다.
	float dt = 0.01;

	for (int i = 0; i < 12; i++)
	{				
		// distance to scene at current position
		float mask = sceneDist(p + dir * dt);

        // early out when this ray is guaranteed to be full shadow

		// width of cone-overlap at light
		// 0 in center, so 50% overlap: add one radius outside of loop to get total coverage
		// should be '(sd / dt) * dl', but '*dl' outside of loop
		lightFraction = min(lightFraction, mask / dt);
		
		// move ahead
		dt += max(1.0, abs(mask));
		if (dt > dl) break; //dt > dl 일시 종료.
	}

	// multiply by dl to get the real projected overlap (moved out of loop)
	// add one radius, before between -radius and + radius
	// normalize to 1 ( / 2*radius)
	// lightFraction = clamp((lightFraction * dl + radius) / (2.0 * radius), 0.0, 1.0);
    lightFraction = lightFraction * dl / radius;//위 clamp는 안전장치
	lightFraction = smoothstep(0.0, 1., lightFraction); //그림자 퍼지는거 조절, 최대값 보정

	float fall = (range - lightDistance)/range;//0~1안에 있는 숫자여야하니, 상대비율로 치환. range보다 ld가 더 적다.
	fall *= fall; //더 바깥이 옅어지게
	float source = fillMask(circleDist(p - pos, radius)); //광원 중앙 하이라이트
	return (lightFraction * fall + source) * color; //shad에 그림자정보다 다 들어가있음.
    // return vec4(sceneDist(p + dir * dt));
}


float luminance(vec4 col)
{
	return 0.2126 * col.r + 0.7152 * col.g + 0.0722 * col.b;
}


void setLuminance(inout vec4 col, float lum)
{
	lum /= luminance(col);
	col *= lum;
}

/////////////////
// The program //
/////////////////

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
	vec2 p = fragCoord.xy;
	vec2 c = iResolution.xy;
	
	// float dist = sceneSmooth(p, 5.0);
	float dist = sceneDist(p);

	vec2 light2Pos = vec2(150. + 50. * sin(iTime), 175.0);
	vec4 light2Col = vec4(1.0, 0.75, 0.5, 1.0);
	// setLuminance(light2Col, 0.5);
	
    vec4 col = vec4(vec3(0.),1.);

    //dist자체는 검게 칠해진 맵이 깔린다.
	col += drawLight(p, light2Pos, light2Col, dist, 600., 8.0);

	// col = mix(col, vec4(1.), fillMask(dist));
    //sceneDist 는 도형들이 검은색, 배경 흰색. fillMask가 반전시켜줌. 즉, 흰부분들만 색칠해주는 식이 됨.

	fragColor = col;
}
