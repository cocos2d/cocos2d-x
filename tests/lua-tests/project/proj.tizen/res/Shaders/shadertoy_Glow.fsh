
uniform vec2 center;
uniform vec2 resolution;


vec2   iResolution = resolution;           // viewport resolution (in pixels)
float  iGlobalTime = CC_Time[1];           // shader playback time (in seconds)
//uniform float     iChannelTime[4];       // channel playback time (in seconds)
//uniform vec3      iChannelResolution[4]; // channel resolution (in pixels)
vec4      iMouse = vec4(0,0,0,0);                // mouse pixel coords. xy: current (if MLB down), zw: click
//uniform sampler2D iChannel0;          // input channel. XX = 2D/Cube



void main(void)
{
	float pointRadius = 0.06;
	float linkSize = 0.04;
	float noiseStrength = 0.08; // range: 0-1
	
	float minDimension = min(iResolution.x, iResolution.y);
	vec2 bounds = vec2(iResolution.x / minDimension, iResolution.y / minDimension);
	//vec2 uv = gl_FragCoord.xy / minDimension;
	vec2 uv = (2. * gl_FragCoord.xy - center.xy) / iResolution.xy;
    
	vec3 pointR = vec3(0.0, 0.0, 1.0);
	vec3 pointG = vec3(0.0, 0.0, 1.0);
	vec3 pointB = vec3(0.0, 0.0, 1.0);
	
	// Make the points orbit round the origin in 3 dimensions.
	// Coefficients are arbitrary to give different behaviours.
	// The Z coordinate should always be >0.0, as it's used directly to
	//  multiply the radius to give the impression of depth.
	pointR.x += 0.32 * sin(1.32 * iGlobalTime);
	pointR.y += 0.3 * sin(1.03 * iGlobalTime);
	pointR.z += 0.4 * sin(1.32 * iGlobalTime);
	
	pointG.x += 0.31 * sin(0.92 * iGlobalTime);
	pointG.y += 0.29 * sin(0.99 * iGlobalTime);
	pointG.z += 0.38 * sin(1.24 * iGlobalTime);
	
	pointB.x += 0.33 * sin(1.245 * iGlobalTime);
	pointB.y += 0.3 * sin(1.41 * iGlobalTime);
	pointB.z += 0.41 * sin(1.11 * iGlobalTime);
	
	// Centre the points in the display
	vec2 midUV = vec2(bounds.x * 0.5, bounds.y * 0.5);
	pointR.xy += midUV;
	pointG.xy += midUV;
	pointB.xy += midUV;
	
	// Calculate the vectors from the current fragment to the coloured points
	vec2 vecToR = pointR.xy - uv;
	vec2 vecToG = pointG.xy - uv;
	vec2 vecToB = pointB.xy - uv;
	
	vec2 dirToR = normalize(vecToR.xy);
	vec2 dirToG = normalize(vecToG.xy);
	vec2 dirToB = normalize(vecToB.xy);
	
	float distToR = length(vecToR);
	float distToG = length(vecToG);
	float distToB = length(vecToB);
	
	// Calculate the dot product between vectors from the current fragment to each pair
	//  of adjacent coloured points. This helps us determine how close the current fragment
	//  is to a link between points.
	float dotRG = dot(dirToR, dirToG);
	float dotGB = dot(dirToG, dirToB);
	float dotBR = dot(dirToB, dirToR);
	
	// Start with a bright coloured dot around each point
	gl_FragColor.x = 1.0 - smoothstep(distToR, 0.0, pointRadius * pointR.z);
	gl_FragColor.y = 1.0 - smoothstep(distToG, 0.0, pointRadius * pointG.z);
	gl_FragColor.z = 1.0 - smoothstep(distToB, 0.0, pointRadius * pointB.z);
	gl_FragColor.w = 1.0;
	
	// We want to show a coloured link between adjacent points.
	// Determine the strength of each link at the current fragment.
	// This tends towards 1.0 as the vectors to each point tend towards opposite directions.
	float linkStrengthRG = 1.0 - smoothstep(dotRG, -1.01, -1.0 + (linkSize * pointR.z * pointG.z));
	float linkStrengthGB = 1.0 - smoothstep(dotGB, -1.01, -1.0 + (linkSize * pointG.z * pointB.z));
	float linkStrengthBR = 1.0 - smoothstep(dotBR, -1.01, -1.0 + (linkSize * pointB.z * pointR.z));
	
	// If the current fragment is in a link, we need to know how much the
	//  linked points contribute of their colour.
	float sumDistRG = distToR + distToG;
	float sumDistGB = distToG + distToB;
	float sumDistBR = distToB + distToR;
	
	float contribRonRG = 1.0 - (distToR / sumDistRG);
	float contribRonBR = 1.0 - (distToR / sumDistBR);
	
	float contribGonRG = 1.0 - (distToG / sumDistRG);
	float contribGonGB = 1.0 - (distToG / sumDistGB);
	
	float contribBonGB = 1.0 - (distToB / sumDistGB);
	float contribBonBR = 1.0 - (distToB / sumDistBR);
	
	// Additively blend the link colours into the fragment.
	gl_FragColor.x += (linkStrengthRG * contribRonRG) + (linkStrengthBR * contribRonBR);
	gl_FragColor.y += (linkStrengthGB * contribGonGB) + (linkStrengthRG * contribGonRG);
	gl_FragColor.z += (linkStrengthBR * contribBonBR) + (linkStrengthGB * contribBonGB);
	
	// Use an underlying texture to provide some noise
	float noiseMin = 1.0 - noiseStrength;
	gl_FragColor.xyz *= (1.0 - noiseStrength) + (noiseStrength * 0.);
}