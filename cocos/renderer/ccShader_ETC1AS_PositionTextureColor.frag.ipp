/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2011 Ricardo Quesada
 * Copyright (c) 2012 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
 /* References:
#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform vec4  u_add_color;
uniform float u_percent;

void main() {
    vec4 color1 = texture2D(CC_Texture0, v_texCoord);
    vec4 color2 = texture2D(CC_Texture1, v_texCoord);
    
    gl_FragColor.rgb = v_fragmentColor.a * color1.rgb * color2.r ;
    gl_FragColor.a   = v_fragmentColor.a * color2.r;
}
 */
 
extern CC_DLL const char* ccETC1ASPositionTextureColor_frag = STRINGIFY(
\n#ifdef GL_ES\n
    precision mediump float;
\n#endif\n

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

void main() {
    vec4 texColor = vec4(texture2D(CC_Texture0, v_texCoord).rgb, texture2D(CC_Texture1, v_texCoord).r);

    texColor.rgb *= texColor.a; // Premultiply with Alpha channel
    
    gl_FragColor = v_fragmentColor * texColor;
}
);
