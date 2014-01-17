// Inputs
attribute vec2 a_position;
attribute vec2 a_texCoord;

// Varying
varying vec2 v_texCoord;


#define MAX_CLICKS	8

// vec4.xy	中心位置
// vec4.z	影响半径
// vec4.w	扰动强度
uniform vec4 u_clicks[MAX_CLICKS];

void main()
{
    gl_Position = vec4(a_position, 0.0, 1.0);
    
    vec2 offset = vec2(0.0, 0.0);
    for (int i = 0; i < MAX_CLICKS; i++)
    {
	    vec4 click = u_clicks[i];
    	if ( click.z > 0.0 )
    	{
    		vec2 dir = a_texCoord-click.xy;
    		float dis = length(dir);
    		if ( dis <= click.z )
    		{
				float power = pow(dis/click.z, click.w);
				
				offset -= (1.0-power)*dir;//(1-power)*normalize(dir)*click.z;
    		}
    	}
    }
    
    v_texCoord = a_texCoord+offset;
}