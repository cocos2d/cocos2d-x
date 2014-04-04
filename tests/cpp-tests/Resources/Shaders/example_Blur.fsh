// Shader taken from: http://webglsamples.googlecode.com/hg/electricflower/electricflower.html

#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D CC_Texture0;

uniform vec4 gaussianCoefficient;
uniform vec2 onePixelSize;

void main() {
	if(gaussianCoefficient.x > 0.0) {
	    vec4 sum = vec4(0.0);
	    vec2 offset;
	    float weight;    
	    float squareX;
	    
	    for(float dx = 0.0; dx <= gaussianCoefficient.x; dx += 1.0) {
	        squareX = dx * dx;
	        weight = gaussianCoefficient.z * exp(squareX * gaussianCoefficient.y);
	        
	        offset.x = -dx * onePixelSize.x;
	        offset.y = 0.0;
	        sum += texture2D(CC_Texture0, v_texCoord + offset) * weight;
	        
	        offset.x = dx * onePixelSize.x;
	        sum += texture2D(CC_Texture0, v_texCoord + offset) * weight;
	        
	        for(float dy = 1.0; dy <= gaussianCoefficient.x; dy += 1.0) {
	            weight = gaussianCoefficient.z * exp((squareX + dy * dy) * gaussianCoefficient.y);
	            
	            offset.x = -dx * onePixelSize.x;
	            offset.y = -dy * onePixelSize.y;
	            sum += texture2D(CC_Texture0, v_texCoord + offset) * weight;
	            
	            offset.y = dy * onePixelSize.y;
	            sum += texture2D(CC_Texture0, v_texCoord + offset) * weight;
	            
	            offset.x = dx * onePixelSize.x;
	            sum += texture2D(CC_Texture0, v_texCoord + offset) * weight;
	            
	            offset.y = -dy * onePixelSize.y;
	            sum += texture2D(CC_Texture0, v_texCoord + offset) * weight;
	        }
	    }
	    sum -= texture2D(CC_Texture0, v_texCoord) * gaussianCoefficient.z;
	    sum /= gaussianCoefficient.w;
	    gl_FragColor = sum * v_fragmentColor;
	}
	else {
	    gl_FragColor = texture2D(CC_Texture0, v_texCoord) * v_fragmentColor;
	}
}

