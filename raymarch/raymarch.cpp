
#define MAX_STEPS 200
#define MAX_DIST 200.
#define SURF_D .01
#define PARTICLES 30
#iChannel0 "../images/tex1.jpg"

float Random(vec2 p) {
    return fract(sin(dot(p,vec2(23.242,34.43242)))*13240.32);
}

float RandomF(float p) {
    return fract(sin(p) * 3.);
}

float smoothUnionSDF(float distA, float distB, float k ) {
  float h = clamp(0.5 + 0.5*(distA-distB)/k, 0., 1.);
  return mix(distA, distB, h) - k*h*(1.-h); 
}

float GetDist(vec3 p) {
    //해당 좌표에서 가장 가까운 sd 출력
    //모델링이 여기에 들어감.
    vec4 s = vec4(0.,1.,4.,.3);

    float pd = p.y;
    float d = 1.;
    float ind = 0.;
    for(int i=0;i<PARTICLES;i++) {
        ind ++;
        float ss = length(p - s.xyz - vec3(RandomF(ind + 3.) + .1 * sin(iTime * RandomF(ind + 1.)),RandomF(ind + 1.) + .1 * cos(iTime * RandomF(ind + 4.)),0)) - max(.05,s.w * RandomF(ind + 2.));
        d = smoothUnionSDF(d,ss,.05);
    }

    return d;
}

float raymarching(vec3 p, vec3 d) {
    float rd = 0.;
    for(int i=0;i<MAX_STEPS;i++) {

        //점점 전진시키는 스캔지점
        vec3 pp = p + d * rd;

        float ds = GetDist(pp);
        rd += ds;

        if(rd > MAX_DIST || ds < SURF_D) break;
    }
    return rd;
}

vec3 GetNormal(vec3 p) {
    float d = GetDist(p);//distance
    vec2 e = vec2(.01,0); // epsilon
    vec3 n = d - vec3(
        GetDist(p-e.xyy),
        GetDist(p-e.yxy),
        GetDist(p-e.yyx)
    );

    return normalize(n);
}

float GetLight(vec3 p) {
    vec3 lp = vec3(5.,5.,-5.);
    vec3 l = normalize(lp - p);
    vec3 n = GetNormal(p);

    float dif = dot(l,n);
    dif = clamp(dif,0.,1.);//스칼라 = 해당 지점의 빛의 밝기

    //shadow
    float d = raymarching(p+n*SURF_D*2.,l);
    if(d<length(lp - p)) dif *= .1;

    return dif;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
    //평면 uv랑은 다르게 구성하였네.
    vec2 uv = (fragCoord - .5*iResolution.xy)/iResolution.y;
    vec3 cam = vec3(0.,1.,0.);
    vec3 rd = normalize(vec3(uv.xy,1));

    float c = raymarching(cam,rd);
    // c /= 10.;
    vec3 p = cam + rd * c;

    // vec3 color = GetNormal(p);
    float lc = GetLight(p);
    vec3 nor = GetNormal(p);
    vec4 tex = texture(iChannel0,sin(nor.xz));
    tex.rgb *= lc;
    vec3 color = vec3(lc);
    fragColor = vec4(tex.rgb,1.0);
}