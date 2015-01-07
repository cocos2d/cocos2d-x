attribute vec4 a_position;
attribute vec2 a_texCoord;
varying float fogFactor;              //weight for fog
varying vec2 v_texture_coord;

uniform float fogDensity;// For exp and exp2 equation
uniform float fStart; // This is only for linear fog
uniform float fEnd; // This is only for linear fog
uniform int iEquation; // 0 = linear, 1 = exp, 2 = exp2

void main(void)
{
    gl_Position = CC_MVPMatrix * a_position;
    v_texture_coord = a_texCoord; 

    float FogFragCoord = abs(gl_Position.z);                                     //get fog distance


    if(iEquation == 0)
            fogFactor = (fEnd-FogFragCoord )/(fEnd-fStart);                      //linear fog
    else if(iEquation == 1)
            fogFactor = exp(-fogDensity*FogFragCoord  );                         //exp fog
    else if(iEquation == 2)
	    fogFactor = exp(-pow(fogDensity*FogFragCoord , 2.0));                //exp2 fog


    fogFactor = clamp(fogFactor, 0.0, 1.0);                                     //clamp 0 to 1
    
}
