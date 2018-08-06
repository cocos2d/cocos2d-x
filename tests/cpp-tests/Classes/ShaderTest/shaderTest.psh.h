/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#define STRINGIFY(A)  #A

static const char* starFlame = STRINGIFY(
                                         
                                         
                                         uniform vec2 center;
                                         uniform vec2 resolution;
                                         
                                         
                                         vec2   iResolution = resolution;           // viewport resolution (in pixels)
                                         float  iGlobalTime = CC_Time[1];           // shader playback time (in seconds)
                                         //uniform float     iChannelTime[4];       // channel playback time (in seconds)
                                         //uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
                                         vec4      iMouse = vec4(0,0,0,0);                // mouse pixel coords. xy: current (if MLB down), zw: click
                                         //uniform sampler2D iChannel0;          // input channel. XX = 2D/Cube
                                         
                                         float noise(vec3 p) //Thx to Las^Mercury
{
	vec3 i = floor(p);
	vec4 a = dot(i, vec3(1., 57., 21.)) + vec4(0., 57., 21., 78.);
	vec3 f = cos((p-i)*acos(-1.))*(-.5)+.5;
	a = mix(sin(cos(a)*a),sin(cos(1.+a)*(1.+a)), f.x);
	a.xy = mix(a.xz, a.yw, f.y);
	return mix(a.x, a.y, f.z);
}
                                         
                                         float sphere(vec3 p, vec4 spr)
{
	return length(spr.xyz-p) - spr.w;
}
                                         
                                         float flame(vec3 p)
{
	float d = sphere(p*vec3(1.,.5,1.), vec4(.0,-1.,.0,1.));
	return d + (noise(p+vec3(.0,iGlobalTime*2.,.0)) + noise(p*3.)*.5)*.25*(p.y) ;
}
                                         
                                         float scene(vec3 p)
{
	return min(100.-length(p) , abs(flame(p)) );
}
                                         
                                         vec4 raymarch(vec3 org, vec3 dir)
{
	float d = 0.0 ;
    float glow = 0.0;
    float eps = 0.02;
	vec3  p = org;
	bool glowed = false;
	
	for(int i=0; i<64; i++)
	{
		d = scene(p) + eps;
		p += d * dir;
		if( d>eps )
		{
			if(flame(p) < .0)
				glowed=true;
			if(glowed)
       			glow = float(i)/64.;
		}
	}
	return vec4(p,glow);
}
                                         
                                         void main()
{
	vec2 v = -1.0 + (2.0 * gl_FragCoord.xy)/ iResolution.xy;
    //vec2 v = 2.0 * gl_FragCoord.xy / iResolution.xy;
	v.x *= iResolution.x/iResolution.y;
	
	vec3 org = vec3(0., -2., 4.);
	vec3 dir = normalize(vec3(v.x*1.6, -v.y, -1.5));
	
	vec4 p = raymarch(org, dir);
	float glow = p.w;
	
	vec4 col = mix(vec4(1.,.5,.1,1.), vec4(0.1,.5,1.,1.), p.y*.02+.4);
	
	gl_FragColor = mix(vec4(0.), col, pow(glow*2.,4.));
    //gl_FragColor = col;
	//gl_FragColor = mix(vec4(1.), mix(vec4(1.,.5,.1,1.),vec4(0.1,.5,1.,1.),p.y*.02+.4), pow(glow*2.,4.));
    
}
                                    
);




static const char* starNestFrg = STRINGIFY(

                                           
                                           
                                           uniform vec2 center;
                                           uniform vec2 resolution;
                                           
                                           vec2   iCenter = center;
                                           vec2   iResolution = resolution;           // viewport resolution (in pixels)
                                           float  iGlobalTime = CC_Time[1];           // shader playback time (in seconds)
                                           //uniform float     iChannelTime[4];       // channel playback time (in seconds)
                                           //uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
                                           vec4      iMouse = vec4(0,0,0,0);                // mouse pixel coords. xy: current (if MLB down), zw: click
                                           //uniform sampler2D iChannel0;          // input channel. XX = 2D/Cube
                                           
                                           // Star Nest by Pablo Román Andrioli
                                           
                                           // This content is under the MIT License.
                                           
                                           int iterations =  17;
                                           float formuparam = 0.53;
                                           
                                           int volsteps = 20;
                                           float stepsize = 0.1;
                                           
                                           float zoom =  0.800;
                                           float tile =  0.850;
                                           float speed =  0.010;
                                           
                                           float brightness = 0.0015;
                                           float darkmatter = 0.300;
                                           float distfading = 0.730;
                                           float saturation = 0.850;
                                           
                                           
void main(void)
{
    //	iCenter = vec2(300, 300);
	//get coords and direction
    vec2 uv=gl_FragCoord.xy/iResolution.xy -.5;
	//vec2 uv=gl_FragCoord.xy/iResolution.xy     ;
	//vec2 uv = ( 2* gl_FragCoord.xy - iCenter.xy) /  resolution.xy;
	uv.y*=iResolution.y/iResolution.x;
	
	//vec2 uv = 2.0* (gl_FragCoord.xy-iResolution.xy)/min(iResolution.y,iResolution.x);
	
	vec3 dir=vec3(uv*zoom,1.);
	float time=iGlobalTime*speed+.25;
    
	//mouse rotation
	float a1=.5+iMouse.x/iResolution.x*2.;
	float a2=.8+iMouse.y/iResolution.y*2.;
	mat2 rot1=mat2(cos(a1),sin(a1),-sin(a1),cos(a1));
	mat2 rot2=mat2(cos(a2),sin(a2),-sin(a2),cos(a2));
	dir.xz*=rot1;
	dir.xy*=rot2;
	vec3 from=vec3(1.,.5,0.5);
	from+=vec3(time*2.,time,-2.);
	from.xz*=rot1;
	from.xy*=rot2;
	
	//volumetric rendering
	float s=0.1;
    float fade=1.;
	vec3 v=vec3(0.);
	for (int r=0; r<volsteps; r++) {
		vec3 p=from+s*dir*.5;
		p = abs(vec3(tile)-mod(p,vec3(tile*2.))); // tiling fold

        float a= 0.;
        float pa=0.;
		for (int i=0; i<iterations; i++) {
			p=abs(p)/dot(p,p)-formuparam; // the magic formula
			a+=abs(length(p)-pa); // absolute sum of average change
			pa=length(p);
		}
		float dm=max(0.,darkmatter-a*a*.001); //dark matter
		a*=a*a; // add contrast
		if (r>6) fade*=1.-dm; // dark matter, don't render near
		//v+=vec3(dm,dm*.5,0.);
		v+=fade;
		v+=vec3(s,s*s,s*s*s*s)*a*brightness*fade; // coloring based on distance
		fade*=distfading; // distance fading
		s+=stepsize;
	}
	v=mix(vec3(length(v)),v,saturation); //color adjust
	gl_FragColor = vec4(v*.01,1.);
	
}
);


static const char* shadertoyRelentlessFrag = STRINGIFY(


uniform vec2 center;
uniform vec2 resolution;
                                                       
vec2   iCenter = center;
vec2   iResolution = resolution;           // viewport resolution (in pixels)
float  iGlobalTime = CC_Time[1];           // shader playback time (in seconds)
 //uniform float     iChannelTime[4];       // channel playback time (in seconds)
//uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)

vec4      iMouse = vec4(0,0,0,0);                // mouse pixel coords. xy: current (if MLB down), zw: click
//uniform sampler2D iChannel0;          // input channel. XX = 2D/Cube
                                                       
// srtuss, 2013
// collecting some design ideas for a new game project.
// no raymarching is used.
                                                       
// if i could add a custom soundtrack, it'd use this one (essential for desired sensation)
// http://www.youtube.com/watch?v=1uFAu65tZpo
                                                       
                                                       
//#define GREEN_VERSION
                                                       
// ** improved camera shaking
// ** cleaned up code
// ** added stuff to the gates
                                                       
                                                       
                                                       
float time = iGlobalTime;
                                                       
vec2 rotate(vec2 p, float a)
{
	return vec2(p.x * cos(a) - p.y * sin(a), p.x * sin(a) + p.y * cos(a));
}
                                                       float box(vec2 p, vec2 b, float r)
{
	return length(max(abs(p) - b, 0.0)) - r;
}
                                                       
// iq's ray-plane-intersection code
vec3 intersect(in vec3 o, in vec3 d, vec3 c, vec3 u, vec3 v)
{
	vec3 q = o - c;
	return vec3(
                dot(cross(u, v), q),
                dot(cross(q, u), d),
                dot(cross(v, q), d)) / dot(cross(v, u), d);
}
                                                       
// some noise functions for fast developing
float rand11(float p)
{
    return fract(sin(p * 591.32) * 43758.5357);
}
                                                       
float rand12(vec2 p)
{
    return fract(sin(dot(p.xy, vec2(12.9898, 78.233))) * 43758.5357);
}
                                                       
vec2 rand21(float p)
{
	return fract(vec2(sin(p * 591.32), cos(p * 391.32)));
}
                                                       
vec2 rand22(in vec2 p)
{
	return fract(vec2(sin(p.x * 591.32 + p.y * 154.077), cos(p.x * 391.32 + p.y * 49.077)));
}
   
                                                       
float noise11(float p)
{
	float fl = floor(p);
	return mix(rand11(fl), rand11(fl + 1.0), fract(p));//smoothstep(0.0, 1.0, fract(p)));
}
                                                       
float fbm11(float p)
{
	return noise11(p) * 0.5 + noise11(p * 2.0) * 0.25 + noise11(p * 5.0) * 0.125;
}
          
vec3 noise31(float p)
{
	return vec3(noise11(p), noise11(p + 18.952), noise11(p - 11.372)) * 2.0 - 1.0;
}
                                                       
// something that looks a bit like godrays coming from the surface
float sky(vec3 p)
{
	float a = atan(p.x, p.z);
	float t = time * 0.1;
	float v = rand11(floor(a * 4.0 + t)) * 0.5 + rand11(floor(a * 8.0 - t)) * 0.25 + rand11(floor(a * 16.0 + t)) * 0.125;
	return v;
}
                                                       
vec3 voronoi(in vec2 x)
{
	vec2 n = floor(x); // grid cell id
	vec2 f = fract(x); // grid internal position
	vec2 mg; // shortest distance...
	vec2 mr; // ..and second shortest distance
	float md = 8.0;
    float md2 = 8.0;
	for(int j = -1; j <= 1; j ++)
	{
		for(int i = -1; i <= 1; i ++)
		{
			vec2 g = vec2(float(i), float(j)); // cell id
			vec2 o = rand22(n + g); // offset to edge point
			vec2 r = g + o - f;
            
			float d = max(abs(r.x), abs(r.y)); // distance to the edge
            
			if(d < md)
            {md2 = md; md = d; mr = r; mg = g;}
			else if(d < md2)
            {md2 = d;}
		}
	}
	return vec3(n + mg, md2 - md);
}
                                                       
//#define A2V(a) vec2(sin((a) * 6.28318531 / 100.0), cos((a) * 6.28318531 / 100.0))
vec2 A2V(float a)
{
    return vec2(sin((a) * 6.28318531 / 100.0), cos((a) * 6.28318531 / 100.0));
}
                                                
                                                       
                                                       
float circles(vec2 p)
{
	float v;
    float w;
    float l;
    float c;
	vec2 pp;
	l = length(p);
    
    
	pp = rotate(p, time * 3.0);
	c = max(dot(pp, normalize(vec2(-0.2, 0.5))), -dot(pp, normalize(vec2(0.2, 0.5))));
	c = min(c, max(dot(pp, normalize(vec2(0.5, -0.5))), -dot(pp, normalize(vec2(0.2, -0.5)))));
	c = min(c, max(dot(pp, normalize(vec2(0.3, 0.5))), -dot(pp, normalize(vec2(0.2, 0.5)))));
    
	// innerest stuff
	v = abs(l - 0.5) - 0.03;
	v = max(v, -c);
	v = min(v, abs(l - 0.54) - 0.02);
	v = min(v, abs(l - 0.64) - 0.05);
    
	pp = rotate(p, time * -1.333);
	c = max(dot(pp, A2V(-5.0)), -dot(pp, A2V(5.0)));
	c = min(c, max(dot(pp, A2V(25.0 - 5.0)), -dot(pp, A2V(25.0 + 5.0))));
	c = min(c, max(dot(pp, A2V(50.0 - 5.0)), -dot(pp, A2V(50.0 + 5.0))));
	c = min(c, max(dot(pp, A2V(75.0 - 5.0)), -dot(pp, A2V(75.0 + 5.0))));
    
	w = abs(l - 0.83) - 0.09;
	v = min(v, max(w, c));
    
	return v;
}
                                                       
float shade1(float d)
{
	float v = 1.0 - smoothstep(0.0, mix(0.012, 0.2, 0.0), d);
	float g = exp(d * -20.0);
	return v + g * 0.5;
}
                                                       
void main(void)
{
	vec2 uv = gl_FragCoord.xy / iResolution.xy;
	uv = uv * 2.0 - 1.0;
	uv.x *= iResolution.x / iResolution.y;
    
    
	// using an iq styled camera this time :)
	// ray origin
	vec3 ro = 0.7 * vec3(cos(0.2 * time), 0.0, sin(0.2 * time));
	ro.y = cos(0.6 * time) * 0.3 + 0.65;
	// camera look at
	vec3 ta = vec3(0.0, 0.2, 0.0);
    
	// camera shake intensity
	float shake = clamp(3.0 * (1.0 - length(ro.yz)), 0.3, 1.0);
	float st = mod(time, 10.0) * 143.0;
    
	// build camera matrix
	vec3 ww = normalize(ta - ro + noise31(st) * shake * 0.01);
	vec3 uu = normalize(cross(ww, normalize(vec3(0.0, 1.0, 0.2 * sin(time)))));
	vec3 vv = normalize(cross(uu, ww));
	// obtain ray direction
	vec3 rd = normalize(uv.x * uu + uv.y * vv + 1.0 * ww);
    
	// shaking and movement
	ro += noise31(-st) * shake * 0.015;
	ro.x += time * 2.0;
    
	float inten = 0.0;
    
	// background
	float sd = dot(rd, vec3(0.0, 1.0, 0.0));
	inten = pow(1.0 - abs(sd), 20.0) + pow(sky(rd), 5.0) * step(0.0, rd.y) * 0.2;
    
	vec3 its;
	float v;
    float g;
    
	// voronoi floor layers
	for(int i = 0; i < 4; i ++)
	{
		float layer = float(i);
		its = intersect(ro, rd, vec3(0.0, -5.0 - layer * 5.0, 0.0), vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));
		if(its.x > 0.0)
		{
			vec3 vo = voronoi((its.yz) * 0.05 + 8.0 * rand21(float(i)));
			v = exp(-100.0 * (vo.z - 0.02));
            
			float fx = 0.0;
            
			// add some special fx to lowest layer
			if(i == 3)
			{
				float crd = 0.0;//fract(time * 0.2) * 50.0 - 25.0;
				float fxi = cos(vo.x * 0.2 + time * 1.5);//abs(crd - vo.x);
				fx = clamp(smoothstep(0.9, 1.0, fxi), 0.0, 0.9) * 1.0 * rand12(vo.xy);
				fx *= exp(-3.0 * vo.z) * 2.0;
			}
			inten += v * 0.1 + fx;
		}
	}
    
	// draw the gates, 4 should be enough
	float gatex = floor(ro.x / 8.0 + 0.5) * 8.0 + 4.0;
	float go = -16.0;
	for(int i = 0; i < 4; i ++)
	{
		its = intersect(ro, rd, vec3(gatex + go, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0));
		if(dot(its.yz, its.yz) < 2.0 && its.x > 0.0)
		{
			v = circles(its.yz);
			inten += shade1(v);
		}
        
		go += 8.0;
	}
    
	// draw the stream
	for(int j = 0; j < 20; j ++)
	{
		float id = float(j);
        
		vec3 bp = vec3(0.0, (rand11(id) * 2.0 - 1.0) * 0.25, 0.0);
		vec3 its = intersect(ro, rd, bp, vec3(1.0, 0.0, 0.0), vec3(0.0, 0.0, 1.0));
        
		if(its.x > 0.0)
		{
			vec2 pp = its.yz;
			float spd = (1.0 + rand11(id) * 3.0) * 2.5;
			pp.y += time * spd;
			pp += (rand21(id) * 2.0 - 1.0) * vec2(0.3, 1.0);
			float rep = rand11(id) + 1.5;
			pp.y = mod(pp.y, rep * 2.0) - rep;
			float d = box(pp, vec2(0.02, 0.3), 0.1);
			float foc = 0.0;
			float v = 1.0 - smoothstep(0.0, 0.03, abs(d) - 0.001);
			float g = min(exp(d * -20.0), 2.0);
            
			inten += (v + g * 0.7) * 0.5;
            
		}
	}
    
	inten *= 0.4 + (sin(time) * 0.5 + 0.5) * 0.6;
    
	// find a color for the computed intensity
#ifdef GREEN_VERSION
	vec3 col = pow(vec3(inten), vec3(2.0, 0.15, 9.0));
#else
	vec3 col = pow(vec3(inten), 1.5 * vec3(0.15, 2.0, 9.0));
#endif
    
	gl_FragColor = vec4(col, 1.0);
}


);
