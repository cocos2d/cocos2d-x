/****************************************************************************
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

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

var OpenGLTestIdx = -1;

// the class inherit from TestScene
// every Scene each test used must inherit from TestScene,
// make sure the test have the menu item for back to main menu
var OpenGLTestScene = TestScene.extend({
    runThisTest:function (num) {
        OpenGLTestIdx = (num || num == 0) ? (num - 1) : -1;
        this.addChild(nextOpenGLTest());
        director.runScene(this);
    }
});

cc.GLNode = cc.GLNode || cc.Node.extend({
    ctor:function(){
        this._super();
        this.init();
    },
    init:function(){
        this._renderCmd._needDraw = true;
        this._renderCmd.rendering =  function(ctx){
            cc.kmGLMatrixMode(cc.KM_GL_MODELVIEW);
            cc.kmGLPushMatrix();
            cc.kmGLLoadMatrix(this._stackMatrix);

            this._node.draw(ctx);

            cc.kmGLPopMatrix();
        };
    },
    draw:function(ctx){
        this._super(ctx);
    }
});

var OpenGLTestLayer = BaseTestLayer.extend({
    _grossini:null,
    _tamara:null,
    _kathia:null,
    _code:null,

    ctor:function() {
        this._super(cc.color(0,0,0,255), cc.color(98,99,117,255) );
    },

    title:function () {
        return "OpenGLTest";
    },
    subtitle:function () {
        return "";
    },
    onBackCallback:function (sender) {
        var s = new OpenGLTestScene();
        s.addChild(previousOpenGLTest());
        director.runScene(s);
    },
    onRestartCallback:function (sender) {
        var s = new OpenGLTestScene();
        s.addChild(restartOpenGLTest());
        director.runScene(s);
    },
    onNextCallback:function (sender) {
        var s = new OpenGLTestScene();
        s.addChild(nextOpenGLTest());
        director.runScene(s);
    },

    // automation
    numberOfPendingTests:function() {
        return ( (arrayOfOpenGLTest.length-1) - OpenGLTestIdx );
    },

    getTestNumber:function() {
        return OpenGLTestIdx;
    }
});

//------------------------------------------------------------------
//
// ReadPixelsTest
//
//------------------------------------------------------------------
var GLReadPixelsTest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            var x = winSize.width;
            var y = winSize.height;

            var blue = new cc.LayerColor(cc.color(0, 0, 255, 255));
            var red = new cc.LayerColor(cc.color(255, 0, 0, 255));
            var green = new cc.LayerColor(cc.color(0, 255, 0, 255));
            var white = new cc.LayerColor(cc.color(255, 255, 255, 255));

            blue.scale = 0.5;
            blue.x = -x / 4;
            blue.y = -y / 4;

            red.scale = 0.5;
            red.x = x / 4;
            red.y = -y / 4;

            green.scale = 0.5;
            green.x = -x / 4;
            green.y = y / 4;

            white.scale = 0.5;
            white.x = x / 4;
            white.y = y / 4;

            this.addChild(blue,10);
            this.addChild(white,11);
            this.addChild(green,12);
            this.addChild(red,13);
        }
    },

    title:function () {
        return "gl.ReadPixels()";
    },
    subtitle:function () {
        return "Tests ReadPixels. See console";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // red, green, blue, white
        var ret = [{"0":255,"1":0,"2":0,"3":255},{"0":0,"1":255,"2":0,"3":255},{"0":0,"1":0,"2":255,"3":255},{"0":255,"1":255,"2":255,"3":255}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var x = winSize.width;
        var y = winSize.height;

        var rPixels = new Uint8Array(4);
        var gPixels = new Uint8Array(4);
        var bPixels = new Uint8Array(4);
        var wPixels = new Uint8Array(4);

        // blue
        gl.readPixels(0,   0,   1, 1, gl.RGBA, gl.UNSIGNED_BYTE, bPixels);

        // red
        gl.readPixels(x-1, 0,   1, 1, gl.RGBA, gl.UNSIGNED_BYTE, rPixels);

        // green
        gl.readPixels(0,   y-1, 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, gPixels);

        // white
        gl.readPixels(x-1, y-1, 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, wPixels);

        var ret = [ rPixels, gPixels, bPixels, wPixels];
        return JSON.stringify(ret);
    }

});


//------------------------------------------------------------------
//
// GLClearTest
//
//------------------------------------------------------------------
var GLClearTest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {

            var blue = new cc.LayerColor(cc.color(0, 0, 255, 255));
            this.addChild( blue, 1 );

            var node = new cc.GLNode();
            node.init();
            node.draw = function() {
                gl.clear( gl.COLOR_BUFFER_BIT );
            };

            this.addChild( node, 10 );
            node.x = winSize.width/2;
            node.y = winSize.height/2 ;
        }
    },

    title:function () {
        return "gl.clear(gl.COLOR_BUFFER_BIT)";
    },
    subtitle:function () {
        return "Testing gl.clear() with cc.GLNode\n The layer should be in black";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // black pixel, not a blue pixel
        var ret = {"0":0,"1":0,"2":0,"3":255};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = this.readPixels(winSize.width/2,  winSize.height/2,  1, 1);
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// GLNodeWebGLAPITest
//
//------------------------------------------------------------------
var GLNodeWebGLAPITest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {

            // simple shader example taken from:
            // http://learningwebgl.com/blog/?p=134
            var vsh = "\n" +
                "attribute vec3 aVertexPosition;\n" +
                "attribute vec4 aVertexColor;\n" +
                "uniform mat4 uMVMatrix;\n" +
                "uniform mat4 uPMatrix;\n" +
                "varying vec4 vColor;\n" +
                "void main(void) {\n" +
                " gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);\n" +
                " vColor = aVertexColor;\n" +
                "}\n";

            var fsh = "\n" +
                "#ifdef GL_ES\n" +
                "precision mediump float;\n" +
                "#endif\n" +
                "varying vec4 vColor;\n" +
                "void main(void) {\n"+
                " gl_FragColor = vColor;\n" +
                "}\n";

            var fshader = this.compileShader(fsh, 'fragment');
            var vshader = this.compileShader(vsh, 'vertex');

            var shaderProgram = this.shader = gl.createProgram();

            gl.attachShader(shaderProgram, vshader);
            gl.attachShader(shaderProgram, fshader);
            gl.linkProgram(shaderProgram);

            if (!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS)) {
                throw("Could not initialise shaders");
            }

            gl.useProgram(shaderProgram);

            shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram, "aVertexPosition");
            gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute);

            shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram, "aVertexColor");
            gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute);

            shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram, "uPMatrix");
            shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram, "uMVMatrix");

            this.initBuffers();

            var glnode = new cc.GLNode();
            this.addChild(glnode,10);
            this.glnode = glnode;

            glnode.draw = function() {
                var pMatrix = [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1];
                this.pMatrix = pMatrix = new Float32Array(pMatrix);

                var mvMatrix = [1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1];
                this.mvMatrix = mvMatrix = new Float32Array(mvMatrix);

                gl.useProgram(this.shader);
                gl.uniformMatrix4fv(this.shader.pMatrixUniform, false, this.pMatrix);
                gl.uniformMatrix4fv(this.shader.mvMatrixUniform, false, this.mvMatrix);

                gl.enableVertexAttribArray(this.shader.vertexPositionAttribute);
                gl.enableVertexAttribArray(this.shader.vertexColorAttribute);

                // Draw fullscreen Square
                gl.bindBuffer(gl.ARRAY_BUFFER, this.squareVertexPositionBuffer);
                gl.vertexAttribPointer(this.shader.vertexPositionAttribute, this.squareVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);

                gl.bindBuffer(gl.ARRAY_BUFFER, this.squareVertexColorBuffer);
                gl.vertexAttribPointer(this.shader.vertexColorAttribute, this.squareVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0);

                this.setMatrixUniforms();
                gl.drawArrays(gl.TRIANGLE_STRIP, 0, this.squareVertexPositionBuffer.numItems);

                // Draw fullscreen Triangle
                gl.bindBuffer(gl.ARRAY_BUFFER, this.triangleVertexPositionBuffer);
                gl.vertexAttribPointer(this.shader.vertexPositionAttribute, this.triangleVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0);

                gl.bindBuffer(gl.ARRAY_BUFFER, this.triangleVertexColorBuffer);
                gl.vertexAttribPointer(this.shader.vertexColorAttribute, this.triangleVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0);

                gl.drawArrays(gl.TRIANGLES, 0, this.triangleVertexPositionBuffer.numItems);

                gl.bindBuffer(gl.ARRAY_BUFFER, null);

            }.bind(this);

        }
    },

    setMatrixUniforms:function() {
        gl.uniformMatrix4fv(this.shader.pMatrixUniform, false, this.pMatrix);
        gl.uniformMatrix4fv(this.shader.mvMatrixUniform, false, this.mvMatrix);
    },

    initBuffers:function() {
        var triangleVertexPositionBuffer = this.triangleVertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
        var vertices = [
            0.0,  1.0,  0.0,
            -1.0, -1.0,  0.0,
            1.0, -1.0,  0.0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
        triangleVertexPositionBuffer.itemSize = 3;
        triangleVertexPositionBuffer.numItems = 3;

        var triangleVertexColorBuffer = this.triangleVertexColorBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);
        var colors = [
            1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
        triangleVertexColorBuffer.itemSize = 4;
        triangleVertexColorBuffer.numItems = 3;


        var squareVertexPositionBuffer = this.squareVertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
        vertices = [
            1.0,  1.0,  0.0,
            -1.0,  1.0,  0.0,
            1.0, -1.0,  0.0,
            -1.0, -1.0,  0.0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
        squareVertexPositionBuffer.itemSize = 3;
        squareVertexPositionBuffer.numItems = 4;

        var squareVertexColorBuffer = this.squareVertexColorBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer);
        colors = [
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
        squareVertexColorBuffer.itemSize = 4;
        squareVertexColorBuffer.numItems = 4;

        gl.bindBuffer(gl.ARRAY_BUFFER, null);
    },

    compileShader:function(source, type) {
        var shader;
        if( type == 'fragment' )
            shader = gl.createShader(gl.FRAGMENT_SHADER);
        else
            shader = gl.createShader(gl.VERTEX_SHADER);
        gl.shaderSource(shader, source);
        gl.compileShader(shader);
        if( !gl.getShaderParameter(shader, gl.COMPILE_STATUS) ) {
            cc.log( gl.getShaderInfoLog(shader) );
            throw("Could not compile " + type + " shader");
        }
        return shader;
    },

    title:function () {
        return "GLNode + WebGL API";
    },
    subtitle:function () {
        return "blue background with a red triangle in the middle";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // blue, red, blue
        var ret = [{"0":0,"1":0,"2":255,"3":255},{"0":0,"1":0,"2":255,"3":255},{"0":255,"1":0,"2":0,"3":255}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret1 = this.readPixels(10, winSize.height-1,  1, 1);
        var ret2 = this.readPixels(winSize.width-10, winSize.height-1,  1, 1);
        var ret3 = this.readPixels(winSize.width/2, winSize.height/2,  1, 1);

        return JSON.stringify([ret1,ret2,ret3]);
    }
});

//------------------------------------------------------------------
//
// GLNodeCCAPITest
//
//------------------------------------------------------------------
var GLNodeCCAPITest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {


            var glnode = new cc.GLNode();
            this.addChild(glnode,10);
            this.glnode = glnode;

            this.shader = cc.shaderCache.getProgram("ShaderPositionColor");
            this.initBuffers();

            glnode.draw = function() {

                this.shader.use();
                this.shader.setUniformsForBuiltins();
                gl.enableVertexAttribArray(cc.VERTEX_ATTRIB_COLOR);
                gl.enableVertexAttribArray(cc.VERTEX_ATTRIB_POSITION);

                // Draw fullscreen Square
                gl.bindBuffer(gl.ARRAY_BUFFER, this.squareVertexPositionBuffer);
                gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0);

                gl.bindBuffer(gl.ARRAY_BUFFER, this.squareVertexColorBuffer);
                gl.vertexAttribPointer(cc.VERTEX_ATTRIB_COLOR, 4, gl.FLOAT, false, 0, 0);

                gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);

                // Draw fullscreen Triangle
                gl.bindBuffer(gl.ARRAY_BUFFER, this.triangleVertexPositionBuffer);
                gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0);

                gl.bindBuffer(gl.ARRAY_BUFFER, this.triangleVertexColorBuffer);
                gl.vertexAttribPointer(cc.VERTEX_ATTRIB_COLOR, 4, gl.FLOAT, false, 0, 0);

                gl.drawArrays(gl.TRIANGLE_STRIP, 0, 3);

                gl.bindBuffer(gl.ARRAY_BUFFER, null);

            }.bind(this);

        }
    },

    initBuffers:function() {
        //
        // Triangle
        //
        var triangleVertexPositionBuffer = this.triangleVertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer);
        var vertices = [
                winSize.width/2,   winSize.height,
            0,                 0,
            winSize.width,     0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

        var triangleVertexColorBuffer = this.triangleVertexColorBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer);
        var colors = [
            1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);

        //
        // Square
        //
        var squareVertexPositionBuffer = this.squareVertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
        vertices = [
            winSize.width,  winSize.height,
            0,              winSize.height,
            winSize.width,  0,
            0,              0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

        var squareVertexColorBuffer = this.squareVertexColorBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer);
        colors = [
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(colors), gl.STATIC_DRAW);
        gl.bindBuffer(gl.ARRAY_BUFFER, null);
    },
    title:function () {
        return "GLNode + cocos2d API";
    },
    subtitle:function () {
        return "blue background with a red triangle in the middle";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // blue, red, blue
        var ret = [{"0":0,"1":0,"2":255,"3":255},{"0":0,"1":0,"2":255,"3":255},{"0":255,"1":0,"2":0,"3":255}];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret1 = this.readPixels(10, winSize.height-1,  1, 1);
        var ret2 = this.readPixels(winSize.width-10, winSize.height-1,  1, 1);
        var ret3 = this.readPixels(winSize.width/2, winSize.height/2,  1, 1);

        return JSON.stringify([ret1,ret2,ret3]);
    }
});

//------------------------------------------------------------------
//
// ShaderNode
//
//------------------------------------------------------------------
var ShaderNode = cc.GLNode.extend({
    ctor:function(vertexShader, framentShader) {
        this._super();
        this.init();

        if( 'opengl' in cc.sys.capabilities ) {
            this.width = 256;
            this.height = 256;
            this.anchorX = 0.5;
            this.anchorY = 0.5;

            this.shader = cc.GLProgram.create(vertexShader, framentShader);
            this.shader.retain();
            this.shader.addAttribute("aVertex", cc.VERTEX_ATTRIB_POSITION);
            this.shader.link();
            this.shader.updateUniforms();

            var program = this.shader.getProgram();
            this.uniformCenter = gl.getUniformLocation( program, "center");
            this.uniformResolution = gl.getUniformLocation( program, "resolution");
            this.initBuffers();

            this.scheduleUpdate();
            this._time = 0;
        }
    },
    draw:function() {
        this.shader.use();
        this.shader.setUniformsForBuiltins();

        //
        // Uniforms
        //
        var frameSize = cc.view.getFrameSize();
        var visibleSize = cc.view.getVisibleSize();
        var retinaFactor = cc.view.getDevicePixelRatio();
        var position = this.getPosition();

        var centerx = position.x * frameSize.width/visibleSize.width * retinaFactor;
        var centery = position.y * frameSize.height/visibleSize.height * retinaFactor;
        this.shader.setUniformLocationF32( this.uniformCenter, centerx, centery);
        this.shader.setUniformLocationF32( this.uniformResolution, 256, 256);

        gl.enableVertexAttribArray( cc.VERTEX_ATTRIB_POSITION );

        // Draw fullscreen Square
        gl.bindBuffer(gl.ARRAY_BUFFER, this.squareVertexPositionBuffer);
        gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0);
        gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);

        gl.bindBuffer(gl.ARRAY_BUFFER, null);
    },

    update:function(dt) {
        this._time += dt;
    },
    initBuffers:function() {

        //
        // Square
        //
        var squareVertexPositionBuffer = this.squareVertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
        vertices = [
            256,            256,
            0,              256,
            256,            0,
            0,              0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
        gl.bindBuffer(gl.ARRAY_BUFFER, null);
    }
});
//------------------------------------------------------------------
//
// ShaderHeartTest
//
//------------------------------------------------------------------
var ShaderHeartTest = OpenGLTestLayer.extend({
    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            var shaderNode = new ShaderNode(ccbjs + "Shaders/example_Heart.vsh", ccbjs + "Shaders/example_Heart.fsh");
            this.addChild(shaderNode,10);
            shaderNode.x = winSize.width/2;
            shaderNode.y = winSize.height/2;
        }
    },

    title:function () {
        return "Shader Heart Test";
    },
    subtitle:function () {
        return "You should see a heart in the center";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // redish pixel
        var ret = {"0":255,"1":0,"2":0,"3":255};
        return JSON.stringify(ret);
    },
    getCurrentResult:function() {
        var ret = this.readPixels(winSize.width/2, winSize.height/2,  1, 1);
        ret[0] = ret[0] > 240 ? 255 : 0;
        ret[3] = ret[3] > 240 ? 255 : 0;
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// ShaderMandelbrotTest
//
//------------------------------------------------------------------
var ShaderMandelbrotTest = OpenGLTestLayer.extend({
    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            var shaderNode = new ShaderNode(ccbjs + "Shaders/example_Mandelbrot.vsh", ccbjs + "Shaders/example_Mandelbrot.fsh");
            this.addChild(shaderNode,10);
            shaderNode.x = winSize.width/2;
            shaderNode.y = winSize.height/2;
        }
    },

    title:function () {
        return "Shader Mandelbrot Test";
    },
    subtitle:function () {
        return "Mandelbrot shader with Zoom";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        throw "Automation Test Not implemented yet";
    },
    getCurrentResult:function() {
        throw "Automation Test Not implemented yet";
    }
});

//------------------------------------------------------------------
//
// ShaderMonjoriTest
//
//------------------------------------------------------------------
var ShaderMonjoriTest = OpenGLTestLayer.extend({
    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            var shaderNode = new ShaderNode(ccbjs + "Shaders/example_Monjori.vsh", ccbjs + "Shaders/example_Monjori.fsh");
            this.addChild(shaderNode,10);
            shaderNode.x = winSize.width/2;
            shaderNode.y = winSize.height/2;
        }
    },

    title:function () {
        return "Shader Monjori Test";
    },
    subtitle:function () {
        return "Monjori plane deformations";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        throw "Automation Test Not implemented yet";
    },
    getCurrentResult:function() {
        throw "Automation Test Not implemented yet";
    }
});

//------------------------------------------------------------------
//
// ShaderPlasmaTest
//
//------------------------------------------------------------------
var ShaderPlasmaTest = OpenGLTestLayer.extend({
    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            var shaderNode = new ShaderNode(ccbjs + "Shaders/example_Plasma.vsh", ccbjs + "Shaders/example_Plasma.fsh");
            this.addChild(shaderNode,10);
            shaderNode.x = winSize.width/2;
            shaderNode.y = winSize.height/2;
        }
    },
    title:function () {
        return "Shader Plasma Test";
    },
    subtitle:function () {
        return "You should see a plasma in the center";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // redish pixel
        return JSON.stringify(true);
    },
    getCurrentResult:function() {
        var ret = this.readPixels(winSize.width/2, winSize.height/2,  1, 1);
        var sum = ret[0] + ret[1] + ret[2];
        return JSON.stringify(sum>300);
    }
});

//------------------------------------------------------------------
//
// ShaderFlowerTest
//
//------------------------------------------------------------------
var ShaderFlowerTest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {

            var shaderNode = new ShaderNode(ccbjs + "Shaders/example_Flower.vsh", ccbjs + "Shaders/example_Flower.fsh");
            this.addChild(shaderNode,10);
            shaderNode.x = winSize.width/2;
            shaderNode.y = winSize.height/2;
        }
    },
    title:function () {
        return "Shader Flower Test";
    },
    subtitle:function () {
        return "You should see a moving Flower in the center";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // redish pixel
        return JSON.stringify(true);
    },
    getCurrentResult:function() {
        var ret = this.readPixels(winSize.width/2, winSize.height/2,  1, 1);
        var sum = ret[0] + ret[1] + ret[2];
        return JSON.stringify(sum<30);
    }
});

//------------------------------------------------------------------
//
// ShaderJuliaTest
//
//------------------------------------------------------------------
var ShaderJuliaTest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {

            var shaderNode = new ShaderNode(ccbjs + "Shaders/example_Julia.vsh", ccbjs + "Shaders/example_Julia.fsh");
            this.addChild(shaderNode,10);
            shaderNode.x = winSize.width/2;
            shaderNode.y = winSize.height/2;
        }
    },
    title:function () {
        return "Shader Julia Test";
    },
    subtitle:function () {
        return "You should see Julia effect";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // redish pixel
        return JSON.stringify(true);
    },
    getCurrentResult:function() {
        var ret = this.readPixels(winSize.width/2, winSize.height/2,  1, 1);
        var sum = ret[0] + ret[1] + ret[2];
        return JSON.stringify(sum>300);
    }
});

//------------------------------------------------------------------
//
// ShaderOutline
//
//------------------------------------------------------------------
//FIX ME:
//The renderers of webgl and opengl is quite different now, so we have to use different shader and different js code
//This is a bug, need to be fixed in the future
var ShaderOutlineEffect = OpenGLTestLayer.extend({
    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            if(cc.sys.isNative){
                this.shader = new cc.GLProgram(ccbjs + "Shaders/example_Outline_noMVP.vsh", ccbjs + "Shaders/example_Outline.fsh");
                this.shader.link();
                this.shader.updateUniforms();
            }
            else{
                this.shader = new cc.GLProgram(ccbjs + "Shaders/example_Outline.vsh", ccbjs + "Shaders/example_Outline.fsh");
                this.shader.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
                this.shader.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
                this.shader.addAttribute(cc.ATTRIBUTE_NAME_COLOR, cc.VERTEX_ATTRIB_COLOR);

                this.shader.link();
                this.shader.updateUniforms();
                this.shader.use();
                this.shader.setUniformLocationWith1f(this.shader.getUniformLocationForName('u_threshold'), 1.75);
                this.shader.setUniformLocationWith3f(this.shader.getUniformLocationForName('u_outlineColor'), 0 / 255, 255 / 255, 0 / 255);
            }

            this.sprite = new cc.Sprite('Images/grossini.png');
            this.sprite.attr({
                x: winSize.width / 2,
                y: winSize.height / 2
            });
            this.sprite.runAction(cc.sequence(cc.rotateTo(1.0, 10), cc.rotateTo(1.0, -10)).repeatForever());

            if(cc.sys.isNative){
                var glProgram_state = cc.GLProgramState.getOrCreateWithGLProgram(this.shader);
                glProgram_state.setUniformFloat("u_threshold", 1.75);
                glProgram_state.setUniformVec3("u_outlineColor", {x: 0/255, y: 255/255, z: 0/255});
                this.sprite.setGLProgramState(glProgram_state);
            }else{
                this.sprite.shaderProgram = this.shader;
            }

            this.addChild(this.sprite);

            this.scheduleUpdate();
        }
    },
    update:function(dt) {
        if( 'opengl' in cc.sys.capabilities ) {
            if(cc.sys.isNative){
                this.sprite.getGLProgramState().setUniformFloat("u_radius", Math.abs(this.sprite.getRotation() / 500));
            }else{
                this.shader.use();
                this.shader.setUniformLocationWith1f(this.shader.getUniformLocationForName('u_radius'), Math.abs(this.sprite.getRotation() / 500));
                this.shader.updateUniforms();
            }
        }
    },
    title:function () {
        return "Shader Outline Effect";
    },
    subtitle:function () {
        return "Should see rotated image with animated outline effect";
    }

    //
    // Automation
    //
});

//------------------------------------------------------------------
//
// ShaderRetro
//
//------------------------------------------------------------------

// Fix me:
// The implemetation of LabelBMFont is quite defferent between html5 and native
// That is why we use 'if (cc.sys.isNative){...}else{...}' in this test case
// It should be fixed in the future.
var ShaderRetroEffect = OpenGLTestLayer.extend({
    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            var program = new cc.GLProgram(ccbjs + "Shaders/example_ColorBars.vsh", ccbjs + "Shaders/example_ColorBars.fsh");
            program.addAttribute(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION);
            program.addAttribute(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORDS);
            program.link();
            program.updateUniforms();

            var label = new cc.LabelBMFont("RETRO EFFECT","fonts/west_england-64.fnt");
            
            if(cc.sys.isNative)
                label.children[0].shaderProgram = program;
            else
                label.shaderProgram = program;
            
            label.x = winSize.width/2;

            label.y = winSize.height/2;
            this.addChild(label);

            this.scheduleUpdate();

            this.label = label;
            this.accum = 0;
        }
    },
    update:function(dt) {
        this.accum += dt;

        if(cc.sys.isNative){
            var letters = this.label.children[0];
            for(var i = 0; i< letters.getStringLength(); ++i){
                var sprite = letters.getLetter(i);
                sprite.y = Math.sin( this.accum * 2 + i/2.0) * 20;
                sprite.scaleY  = ( Math.sin( this.accum * 2 + i/2.0 + 0.707) );       
            }
        }else{
            var children = this.label.children;

            for( var i in children ) {
                var sprite = children[i];
                sprite.y = Math.sin( this.accum * 2 + i/2.0) * 20;

                // add fabs() to prevent negative scaling
                var scaleY = ( Math.sin( this.accum * 2 + i/2.0 + 0.707) );

                sprite.scaleY = scaleY;
            }
        }
    },
    title:function () {
        return "Shader Retro Effect";
    },
    subtitle:function () {
        return "Should see moving colors, and a sin effect on the letters";
    }

    //
    // Automation
    //
});
//------------------------------------------------------------------
//
// GLGetActiveTest
//
//------------------------------------------------------------------
var GLGetActiveTest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            var sprite = this.sprite = new cc.Sprite("Images/grossini.png");
            sprite.x = winSize.width/2;
            sprite.y = winSize.height/2;
            this.addChild( sprite );

            // after auto test
            this.scheduleOnce( this.onTest, 0.5 );
        }
    },

    onTest:function(dt) {
        cc.log( this.getCurrentResult() );
    },

    title:function () {
        return "gl.getActiveXXX Function Test";
    },
    subtitle:function () {
        return "Tests gl.getActiveUniform / getActiveAttrib. See console";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // redish pixel
        var ret = [{"size":1,"type":35666,"name":"a_position"},{"size":1,"type":35678,"name":"CC_Texture"},[2,3]];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = [];
        var p = this.sprite.shaderProgram.getProgram();
        ret.push( gl.getActiveAttrib( p, 0 ) );
        ret.push( gl.getActiveUniform( p, 0 ) );
        ret.push( gl.getAttachedShaders( p ) );
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// TexImage2DTest
//
//------------------------------------------------------------------
var TexImage2DTest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            var glnode = new cc.GLNode();
            this.addChild(glnode,10);
            this.glnode = glnode;
            glnode.x = winSize.width/2;
            glnode.y = winSize.height/2;
            glnode.width = 128;
            glnode.height = 128;
            glnode.anchorX = 0.5;
            glnode.anchorY = 0.5;

            this.shader = cc.shaderCache.getProgram("ShaderPositionTexture");
            this.initGL();

            glnode.draw = function() {
                this.shader.use();
                this.shader.setUniformsForBuiltins();

                gl.bindTexture(gl.TEXTURE_2D, this.my_texture);
                gl.enableVertexAttribArray(cc.VERTEX_ATTRIB_POSITION);
                gl.enableVertexAttribArray(cc.VERTEX_ATTRIB_TEX_COORDS);

                // Draw fullscreen Square
                gl.bindBuffer(gl.ARRAY_BUFFER, this.squareVertexPositionBuffer);
                gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0);

                gl.bindBuffer(gl.ARRAY_BUFFER, this.squareVertexTextureBuffer);
                gl.vertexAttribPointer(cc.VERTEX_ATTRIB_TEX_COORDS, 2, gl.FLOAT, false, 0, 0);

                gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);

                gl.bindTexture(gl.TEXTURE_2D, null);
                gl.bindBuffer(gl.ARRAY_BUFFER, null);

            }.bind(this);

        }
    },

    initGL:function() {
        var texture = this.my_texture = gl.createTexture();
        gl.bindTexture( gl.TEXTURE_2D, texture );

        var pixels = new Uint8Array(4096);
        for( var i=0; i<pixels.length; ) {
            pixels[i++] = i/4;    // Red
            pixels[i++] = i/16;    // Green
            pixels[i++] = i/8;    // Blue
            pixels[i++] = 255;    // Alpha
        }
        gl.texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 32, 32, 0, gl.RGBA, gl.UNSIGNED_BYTE, pixels);

        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.bindTexture(gl.TEXTURE_2D, null);

        //
        // Square
        //
        var squareVertexPositionBuffer = this.squareVertexPositionBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer);
        var vertices = [
            128,  128,
            0,    128,
            128,  0,
            0,    0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);

        var squareVertexTextureBuffer = this.squareVertexTextureBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexTextureBuffer);
        var texcoords = [
            1, 1,
            0, 1,
            1, 0,
            0, 0
        ];
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(texcoords), gl.STATIC_DRAW);
        gl.bindBuffer(gl.ARRAY_BUFFER, null);
    },
    title:function () {
        return "TexImage2DTest";
    },
    subtitle:function () {
        return "Testing Texture creation";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        // blue, red, blue
        var ret = {"0":239,"1":123,"2":247,"3":255,"4":239,"5":123,"6":247,"7":255,"8":240,"9":124,"10":248,"11":255,"12":240,"13":124,"14":248,"15":255,"16":239,"17":123,"18":247,"19":255,"20":239,"21":123,"22":247,"23":255,"24":240,"25":124,"26":248,"27":255,"28":240,"29":124,"30":248,"31":255,"32":15,"33":131,"34":7,"35":255,"36":15,"37":131,"38":7,"39":255,"40":16,"41":132,"42":8,"43":255,"44":16,"45":132,"46":8,"47":255,"48":15,"49":131,"50":7,"51":255,"52":15,"53":131,"54":7,"55":255,"56":16,"57":132,"58":8,"59":255,"60":16,"61":132,"62":8,"63":255};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = this.readPixels(winSize.width/2-2, winSize.height/2-2,  4, 4);
        return JSON.stringify(ret);
    }
});
//------------------------------------------------------------------
//
// GetSupportedExtensionsTest
//
//------------------------------------------------------------------
var GetSupportedExtensionsTest = OpenGLTestLayer.extend({
    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            if( ! autoTestEnabled ) {
                var array = gl.getSupportedExtensions();
                cc.log( JSON.stringify( array ) );
                if( array.length > 0 )
                    cc.log( gl.getExtension( array[0] ) );
            }
        }
    },

    title:function () {
        return "GetSupportedExtensionsTest";
    },
    subtitle:function () {
        return "See console for the supported GL extensions";
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        var ret = ["[object Array]",null];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        // Extensions varies from machine to machine. Just check for typeof Array
        var ext = gl.getSupportedExtensions();
        var type = Object.prototype.toString.call( ext );
        var n = gl.getExtension('do_no_exist');
        return JSON.stringify([type,n]);
    }
});

//------------------------------------------------------------------
//
// GLTexParamterTest
//
//------------------------------------------------------------------
var GLTexParamterTest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {
            if( ! autoTestEnabled ) {
                cc.log( "[Max, MIN, WRAP_S, WRAP_T]" );
                cc.log( this.getTexValues() );
            }
        }
    },

    title:function () {
        return "GLTexParamterTest";
    },
    subtitle:function () {
        return "tests texParameter()\n See the Console";
    },
    getTexValues:function() {
        if(!cc.sys.isNative){
            var texture2d = cc.textureCache.getTextureForKey(s_pathGrossini);
            gl.bindTexture(gl.TEXTURE_2D, texture2d.getName());
        } else {
            gl.bindTexture(gl.TEXTURE_2D, null);
        }
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST);
        gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST);
        gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE );
        gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE );

        var mag = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER);
        var min = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER);
        var w_s = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S);
        var w_t = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_WRAP_T);

        var a = [mag, min, w_s, w_t];
        return a;
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        var ret = [9728,9728,33071,33071];
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = this.getTexValues();
        return JSON.stringify(ret);
    }
});

//------------------------------------------------------------------
//
// GLGetUniformTest
//
//------------------------------------------------------------------
var GLGetUniformTest = OpenGLTestLayer.extend({

    ctor:function() {
        this._super();

        if( 'opengl' in cc.sys.capabilities ) {

            if( ! autoTestEnabled ) {
                cc.log( JSON.stringify( this.runTest() ));
            }

        }
    },

    title:function () {
        return "GLGetUniformTest";
    },
    subtitle:function () {
        return "tests texParameter()\n See the Console";
    },
    runTest:function() {

        var shader = cc.shaderCache.getProgram("ShaderPositionTextureColor");
        var program = shader.getProgram();
        shader.use();

        var loc = cc.sys.isNative ? gl.getUniformLocation(program, "CC_MVPMatrix") : gl.getUniformLocation(program, "CC_MVMatrix");

        var pMatrix = [1,2,3,4, 4,3,2,1, 1,2,4,8, 1.1,1.2,1.3,1.4];
        this.pMatrix = new Float32Array(pMatrix);

        gl.uniformMatrix4fv(loc, false, this.pMatrix);

        return gl.getUniform( program, loc );
    },

    //
    // Automation
    //
    getExpectedResult:function() {
        var ret = {"0":1,"1":2,"2":3,"3":4,"4":4,"5":3,"6":2,"7":1,"8":1,"9":2,"10":4,"11":8,"12":1.100000023841858,"13":1.2000000476837158,"14":1.2999999523162842,"15":1.399999976158142};
        return JSON.stringify(ret);
    },

    getCurrentResult:function() {
        var ret = this.runTest();
        return JSON.stringify(ret);
    }
});

//-
//
// Flow control
//
var arrayOfOpenGLTest = [
    ShaderOutlineEffect,
    ShaderRetroEffect,
    ShaderMonjoriTest,
    ShaderMandelbrotTest,
    ShaderHeartTest,
    ShaderPlasmaTest,
    ShaderFlowerTest,
    ShaderJuliaTest,
    GLGetActiveTest,
    TexImage2DTest,
    GetSupportedExtensionsTest,
    GLReadPixelsTest,
    GLClearTest,
    GLNodeWebGLAPITest,
    GLNodeCCAPITest,
    GLTexParamterTest,
    GLGetUniformTest
];

var nextOpenGLTest = function () {
    OpenGLTestIdx++;
    OpenGLTestIdx = OpenGLTestIdx % arrayOfOpenGLTest.length;

    return new arrayOfOpenGLTest[OpenGLTestIdx]();
};
var previousOpenGLTest = function () {
    OpenGLTestIdx--;
    if (OpenGLTestIdx < 0)
        OpenGLTestIdx += arrayOfOpenGLTest.length;

    return new arrayOfOpenGLTest[OpenGLTestIdx]();
};
var restartOpenGLTest = function () {
    return new arrayOfOpenGLTest[OpenGLTestIdx]();
};
