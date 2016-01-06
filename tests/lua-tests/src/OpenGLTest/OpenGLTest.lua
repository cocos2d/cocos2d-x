local vertDefaultSource = "\n".."\n" ..
                  "attribute vec4 a_position;\n" ..
                  "attribute vec2 a_texCoord;\n" ..
                  "attribute vec4 a_color;\n\n" ..
                  "\n#ifdef GL_ES\n" .. 
                  "varying lowp vec4 v_fragmentColor;\n" ..
                  "varying mediump vec2 v_texCoord;\n" ..
                  "\n#else\n" ..
                  "varying vec4 v_fragmentColor;" ..
                  "varying vec2 v_texCoord;" ..
                  "\n#endif\n" ..
                  "void main()\n" ..
                  "{\n" .. 
                  "   gl_Position = CC_MVPMatrix * a_position;\n"..
                  "   v_fragmentColor = a_color;\n"..
                  "   v_texCoord = a_texCoord;\n" ..
                  "} \n"

local scaleFactor = cc.Director:getInstance():getContentScaleFactor()

local function OpenGLTestMainLayer()
    local kItemTagBasic = 1000
    local testCount = 16
    local maxCases = testCount
    local curCase  = 0
    local accum    = 0
    local labelBMFont = nil
    local size = cc.Director:getInstance():getWinSize()
    local curLayer = nil
    local schedulEntry = nil
    local  function OrderCallbackMenu()
        local function backCallback()
            curCase = curCase - 1
            if curCase < 0 then
                curCase = curCase + maxCases
            end
            ShowCurrentTest()
        end
    
        local function restartCallback()
            ShowCurrentTest()
        end
    
        local function nextCallback()
            curCase = curCase + 1
            curCase = curCase % maxCases
            ShowCurrentTest()
        end

        local ordercallbackmenu = cc.Menu:create()
        local size = cc.Director:getInstance():getWinSize()
        local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
        item1:registerScriptTapHandler(backCallback)
        ordercallbackmenu:addChild(item1,kItemTagBasic)
        local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
        item2:registerScriptTapHandler(restartCallback)
        ordercallbackmenu:addChild(item2,kItemTagBasic)
        local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
        ordercallbackmenu:addChild(item3,kItemTagBasic) 
        item3:registerScriptTapHandler(nextCallback)
                
        item1:setPosition(cc.p(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
        item2:setPosition(cc.p(size.width / 2, item2:getContentSize().height / 2))
        item3:setPosition(cc.p(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
        
        ordercallbackmenu:setPosition(cc.p(0, 0))

        return ordercallbackmenu
    end

    local function GetTitle()
        if 0 == curCase then
            return "Shader Retro Effect"
        elseif 1 == curCase then
            return "Shader Monjori Test"
        elseif 2 == curCase then
            return "Shader Mandelbrot Test"
        elseif 3 == curCase then
            return "Shader Heart Test"
        elseif 4 == curCase then
            return "Shader Plasma Test"
        elseif  5 == curCase then
            return "Shader Flower Test"
        elseif 6 == curCase then
            return "Shader Julia Test"
        elseif 7 == curCase then
            return "gl.getActive***"
        elseif 8 == curCase then
            return "TexImage2DTest"
        elseif 9 == curCase then
            return "GetSupportedExtensionsTest"
        elseif 10 == curCase then
            return "gl.ReadPixels()"
        elseif 11 == curCase then
            return "gl.clear(gl.COLOR_BUFFER_BIT)"
        elseif 12 == curCase then
            return "GLNode + WebGL API"
        elseif 13 == curCase then
            return "GLNode + cocos2d API"
        elseif 14 == curCase then
            return "GLTexParamterTest"
        elseif 15 == curCase then
            return "GLGetUniformTest"
        end
    end
    
    local function GetSubTitle()
        if 0 == curCase then
            return "Should see moving colors, and a sin effect on the letters"
        elseif 1 == curCase then
            return "Monjori plane deformations"
        elseif 2 == curCase then
            return "Mandelbrot shader with Zoom"
        elseif 3 == curCase then
            return "You should see a heart in the center"
        elseif 4 == curCase then
            return "You should see a plasma in the center"
        elseif 5 == curCase then
            return "You should see a moving Flower in the center"
        elseif 6 == curCase then
            return "You should see Julia effect"
        elseif 7 == curCase then
            return "Tests gl.getActiveUniform / getActiveAttrib. See console"
        elseif 8 == curCase then
            return "Testing Texture creation"
        elseif 9 == curCase then
            return "See console for the supported GL extensions"
        elseif 10 == curCase then
            return "Tests ReadPixels. See console"
        elseif 11 == curCase then
            return "Testing gl.clear() with cc.GLNode"
        elseif 12 == curCase then
            return "blue background with a red triangle in the middle"
        elseif 13 == curCase then
            return "blue background with a red triangle in the middle"
        elseif 14 == curCase then
            return "tests texParameter()"
        elseif 15 == curCase then
            return "tests texParameter()"
        end
    end

    local function InitTitle(layer)
        --Title
        local lableTitle = cc.Label:createWithTTF(GetTitle(), s_arialPath, 40)
        layer:addChild(lableTitle, 15)
        lableTitle:setAnchorPoint(cc.p(0.5, 0.5))
        lableTitle:setPosition(cc.p(size.width/2, size.height-32))
        lableTitle:setColor(cc.c3b(255,255,40))
        --SubTitle
        local subLabelTitle = cc.Label:createWithTTF(GetSubTitle(), s_thonburiPath, 16)
        layer:addChild(subLabelTitle, 15)
        subLabelTitle:setAnchorPoint(cc.p(0.5, 0.5))
        subLabelTitle:setPosition(cc.p(size.width/2, size.height-80)) 
    end

    local function updateRetroEffect(fTime)
        if nil == labelBMFont then
            return
        end
        accum = accum + fTime
        local letterCount = labelBMFont:getStringLength()
        local i = 0
        for i= 0 ,letterCount - 1 do
            local sprite = labelBMFont:getLetter(i)
            local oldPosX,oldPosY = sprite:getPosition()
            sprite:setPosition(oldPosX, math.sin(accum * 2 + i / 2.0) * 20)
            local scaleY = math.sin(accum * 2 + i / 2.0 + 0.707)
            sprite:setScaleY(scaleY)
        end
    end

    local function createShaderRetroEffect()
        local RetroEffectlayer = cc.Layer:create()
        InitTitle(RetroEffectlayer)
        local program = cc.GLProgram:create("Shaders/example_ColorBars.vsh", "Shaders/example_ColorBars.fsh")
        program:bindAttribLocation(cc.ATTRIBUTE_NAME_POSITION, cc.VERTEX_ATTRIB_POSITION) 
        program:bindAttribLocation(cc.ATTRIBUTE_NAME_TEX_COORD, cc.VERTEX_ATTRIB_TEX_COORD)
        program:link()
        program:updateUniforms()

        label = cc.Label:createWithBMFont("fonts/west_england-64.fnt", "RETRO EFFECT")
        label:setAnchorPoint(cc.p(0.5, 0.5))
        label:setGLProgram( program )

        label:setPosition(size.width/2, size.height/2)
        RetroEffectlayer:addChild(label)
        labelBMFont = label
        RetroEffectlayer:scheduleUpdateWithPriorityLua(updateRetroEffect,0)
        return RetroEffectlayer
    end

    local function createShaderNodeLayer(vSource, fSource)
        local shaderNodeLayer = cc.Layer:create()

        InitTitle(shaderNodeLayer)

        local vertSource = vSource
        local fragSource = fSource
        local glProgram = cc.GLProgram:createWithByteArrays(vertSource, fragSource)
        glProgram:retain()

        local glNode  = gl.glNodeCreate()

        local resolution = cc.p(256, 256)
        local director = cc.Director:getInstance()
        local frameSize = director:getOpenGLView():getFrameSize()
        local visibleSize = director:getVisibleSize()
        local retinaFactor = director:getOpenGLView():getRetinaFactor()
        local center = cc.p( size.width / 2 * frameSize.width / visibleSize.width * retinaFactor, size.height / 2 * frameSize.height / visibleSize.height * retinaFactor)

        local function initBuffers()
            local w = 256
            local h = 256
            local x = size.width / 2 - w / 2
            local y = size.height / 2 -h / 2
            local vertices ={ x,y, x+w,y, x+w,y+h, x,y, x,y+h, x+w,y+h }
            local vbo = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, vbo)
            gl.bufferData(gl.ARRAY_BUFFER, table.getn(vertices), vertices, gl.STATIC_DRAW)
            gl.bindBuffer(gl.ARRAY_BUFFER, 0)
            return vbo
        end

        local vbo = initBuffers()

        local function update(fTime)
            time = time + fTime
        end

        local function draw(transform, transformUpdated)
            glProgram:use()
            glProgram:setUniformsForBuiltins()

            local uniformCenter = gl.getUniformLocation(glProgram:getProgram(), "center")
            glProgram:setUniformLocationF32(uniformCenter, center.x, center.y)
            local uniformResolution = gl.getUniformLocation(glProgram:getProgram(), "resolution")
            glProgram:setUniformLocationF32(uniformResolution, resolution.x, resolution.y)

            gl.glEnableVertexAttribs(cc.VERTEX_ATTRIB_FLAG_POSITION)
            gl.bindBuffer(gl.ARRAY_BUFFER, vbo)
            gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0);
            gl.drawArrays(gl.TRIANGLES, 0, 6)
            gl.bindBuffer(gl.ARRAY_BUFFER, 0)
        end
  
        shaderNodeLayer:scheduleUpdateWithPriorityLua(update,0)
        glNode:registerScriptDrawHandler(draw)
        time = 0
        shaderNodeLayer:addChild(glNode,-10)
        glNode:setPosition( size.width/2, size.height/2)

        local function onNodeEvent(event)
            if "exit" == event then
                glProgram:release()
            end
        end
        
        shaderNodeLayer:registerScriptHandler(onNodeEvent)

        return shaderNodeLayer
    end

    local function createShaderMajoriTest()
        local vSource = vertDefaultSource
        local fSource = cc.FileUtils:getInstance():getStringFromFile("Shaders/example_Monjori.fsh")
        return createShaderNodeLayer(vSource, fSource)
    end

    local function createShaderMandelbrotTest()
        local vSource = vertDefaultSource
        local fSource = cc.FileUtils:getInstance():getStringFromFile("Shaders/example_Mandelbrot.fsh")
        return createShaderNodeLayer(vSource, fSource)
    end

    local function createShaderHeartTest()
        local vSource = vertDefaultSource
        local fSource = cc.FileUtils:getInstance():getStringFromFile("Shaders/example_Heart.fsh")
        return createShaderNodeLayer(vSource, fSource)
    end

    local function createShaderPlasmaTest()
        local vSource = vertDefaultSource
        local fSource = cc.FileUtils:getInstance():getStringFromFile("Shaders/example_Plasma.fsh")
        return createShaderNodeLayer(vSource, fSource)
    end

    local function createShaderFlowerTest()
        local vSource = vertDefaultSource
        local fSource = cc.FileUtils:getInstance():getStringFromFile("Shaders/example_Flower.fsh")
        return createShaderNodeLayer(vSource, fSource)
    end

    local function createShaderJuliaTest()
        local vSource = vertDefaultSource
        local fSource = cc.FileUtils:getInstance():getStringFromFile("Shaders/example_Julia.fsh")
        return createShaderNodeLayer(vSource, fSource)
    end

    local function createGLGetActiveTest()
        local glGetActiveLayer = cc.Layer:create()
        InitTitle(glGetActiveLayer)
        local sprite = cc.Sprite:create("Images/grossini.png")
        sprite:setPosition( size.width/2, size.height/2)
        glGetActiveLayer:addChild(sprite)
        local glNode = gl.glNodeCreate()
        glGetActiveLayer:addChild(glNode,-10)
        local scheduler = cc.Director:getInstance():getScheduler()

        local function getCurrentResult()
            local var = {}
            local glProgram = sprite:getGLProgram()
            if nil ~= glProgram then
                local p = glProgram:getProgram()
                local aaSize,aaType,aaName = gl.getActiveAttrib(p,0)
                local strFmt = "size:"..aaSize.." type:"..aaType.." name:"..aaName
                print(strFmt)
                local auSize,auType,auName = gl.getActiveUniform(p,0)
                strFmt = "size:"..auSize.." type:"..auType.." name:"..auName
                print(strFmt)
                local shadersTable         = gl.getAttachedShaders(p)
                if type(shadersTable) == "table" then
                    local count = table.getn(shadersTable)
                    local i = 1
                    strFmt = ""
                    for i=1, count do
                        strFmt = strFmt..shadersTable[i].." "
                    end
                    print(strFmt)
                end 
  
                if nil ~= schedulEntry then
                    scheduler:unscheduleScriptEntry(schedulEntry)
                end
            end
        end
        
        if nil ~= schedulEntry then
            scheduler:unscheduleScriptEntry(schedulEntry)
        end
        schedulEntry = scheduler:scheduleScriptFunc(getCurrentResult, 0.5, false)

        return glGetActiveLayer
    end

    --Have problem
    local function createTexImage2DTest()
        local texture = {}
        local squareVertexPositionBuffer = {}
        local squareVertexTextureBuffer  = {}
        local texImage2dLayer = cc.Layer:create()
        InitTitle(texImage2dLayer)
        local glNode   = gl.glNodeCreate()
        texImage2dLayer:addChild(glNode, 10)
        glNode:setPosition(size.width/2, size.height/2)
        glNode:setContentSize(cc.size(128,128))
        glNode:setAnchorPoint(cc.p(0.5,0.5))
        local shaderCache = cc.ShaderCache:getInstance()
        local shader = shaderCache:getProgram("ShaderPositionTexture")

        local function initGL()
            texture.texture_id  = gl.createTexture()
            gl.bindTexture(gl.TEXTURE_2D,texture.texture_id )
            local pixels = {}
            local i = 1
            while i <= 4096 do
                pixels[i] = math.floor(i / 4)
                i = i + 1
                pixels[i] = math.floor(i / 16)
                i = i + 1
                pixels[i] = math.floor(i / 8)
                i = i + 1
                pixels[i] = 255
                i = i + 1
            end

            gl._texImage2D(gl.TEXTURE_2D, 0, gl.RGBA, 32, 32, 0, gl.RGBA, gl.UNSIGNED_BYTE, table.getn(pixels),pixels)
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST)
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST)
            gl.bindTexture(gl.TEXTURE_2D, 0)

            --Square
            squareVertexPositionBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
            local vertices = { 128, 128, 0, 128, 128, 0, 0, 0 }
            gl.bufferData(gl.ARRAY_BUFFER,table.getn(vertices),vertices,gl.STATIC_DRAW)

            squareVertexTextureBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexTextureBuffer.buffer_id)
            local texcoords = { 1, 1, 0, 1, 1, 0, 0, 0 }
            gl.bufferData(gl.ARRAY_BUFFER,table.getn(texcoords),texcoords,gl.STATIC_DRAW)
            gl.bindBuffer(gl.ARRAY_BUFFER,0)
        end

        local function TexImage2DDraw(transform, transformUpdated)
            if nil ~= shader then
                shader:use()
                shader:setUniformsForBuiltins(transform)

                gl.bindTexture(gl.TEXTURE_2D, texture.texture_id)
                gl.glEnableVertexAttribs(bit._or(cc.VERTEX_ATTRIB_FLAG_TEX_COORDS, cc.VERTEX_ATTRIB_FLAG_POSITION))

                gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
                gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION,2,gl.FLOAT,false,0,0)


                gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexTextureBuffer.buffer_id)
                gl.vertexAttribPointer(cc.VERTEX_ATTRIB_TEX_COORD,2,gl.FLOAT,false,0,0)

                gl.drawArrays(gl.TRIANGLE_STRIP,0,4)

                gl.bindTexture(gl.TEXTURE_2D,0)
                gl.bindBuffer(gl.ARRAY_BUFFER,0)
            end
        end

        initGL()
        glNode:registerScriptDrawHandler(TexImage2DDraw)
        return texImage2dLayer
    end

    local function CreateSupportedExtensionsLayer()
        local extensionsLayer = cc.Layer:create()
        InitTitle(extensionsLayer)
        local glNode = gl.glNodeCreate()
        extensionsLayer:addChild(glNode,-10)
        local supportExtensions = gl.getSupportedExtensions()
        if type(supportExtensions) ~= "table" then
            print("error:return value not table")
            return
        end
        local count = table.getn(supportExtensions)
        local i = 1
        for i=1,count do
            print(supportExtensions[i])
        end

        return extensionsLayer
    end

    local function CreateReadPixelsTest()
        local readPixelsLayer = cc.Layer:create()
        InitTitle(readPixelsLayer)
        local glNode = gl.glNodeCreate()
        readPixelsLayer:addChild(glNode,-10)

        local x = size.width
        local y = size.height

        local blue = cc.LayerColor:create(cc.c4b(0, 0, 255, 255))
        local red = cc.LayerColor:create(cc.c4b(255, 0, 0, 255))
        local green = cc.LayerColor:create(cc.c4b(0, 255, 0, 255))
        local white = cc.LayerColor:create(cc.c4b(255, 255, 255, 255))

        blue:setScale(0.5)
        blue:setPosition(-x / 4, -y / 4)

        red:setScale(0.5)
        red:setPosition(x / 4, -y / 4)

        green:setScale(0.5)
        green:setPosition(-x / 4, y / 4)

        white:setScale(0.5)
        white:setPosition(x / 4, y / 4)

        readPixelsLayer:addChild(blue,10)
        readPixelsLayer:addChild(white,11)
        readPixelsLayer:addChild(green,12)
        readPixelsLayer:addChild(red,13)

        local scheduler = cc.Director:getInstance():getScheduler()

        local function getCurrentResult()
            local x = size.width
            local y = size.height

            local pixelCount = 4
            local i = 1
            local strFmt = ""
            --blue
            local bPixels = gl.readPixels(0,   0,   1, 1, gl.RGBA, gl.UNSIGNED_BYTE, pixelCount)
            for i=1,pixelCount do
                local strTmp = string.format("%d:%d ",i,bPixels[i])
                strFmt = strFmt .. strTmp
            end
            print(strFmt)
            strFmt = ""
            --red
            local rPixels = gl.readPixels(x-1, 0,   1, 1, gl.RGBA, gl.UNSIGNED_BYTE, pixelCount)
            for i=1,pixelCount do
                local strTmp = string.format("%d:%d ",i,rPixels[i])
                strFmt = strFmt .. strTmp
            end
            print(strFmt)
            strFmt = ""
            --green
            local gPixels = gl.readPixels(0,   y-1, 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, pixelCount)
            for i=1,pixelCount do
                local strTmp = string.format("%d:%d ",i,gPixels[i])
                strFmt = strFmt .. strTmp
            end
            print(strFmt)
            strFmt = ""
            --white
            local wPixels = gl.readPixels(x-1, y-1, 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, pixelCount)
            for i=1,pixelCount do
                local strTmp = string.format("%d:%d ",i,wPixels[i])
                strFmt = strFmt .. strTmp
            end
            print(strFmt)

            if nil ~= schedulEntry then
                scheduler:unscheduleScriptEntry(schedulEntry)
            end
        end
        
        if nil ~= schedulEntry then
            scheduler:unscheduleScriptEntry(schedulEntry)
        end

        schedulEntry = scheduler:scheduleScriptFunc(getCurrentResult, 0.5, false)

        return readPixelsLayer
    end

    local function createClearTest()
        local clearLayer = cc.Layer:create()
        InitTitle(clearLayer)

        local blue = cc.LayerColor:create(cc.c4b(0, 0, 255, 255))
        clearLayer:addChild( blue, 1 )

        local glNode = gl.glNodeCreate()
        clearLayer:addChild(glNode,10)
        --gl.init()
        local scheduler = cc.Director:getInstance():getScheduler()

        local function clearDraw()
            gl.clear(gl.COLOR_BUFFER_BIT)
        end

        local function getCurrentResult()

            local pixels = gl.readPixels(math.floor(size.width/2), math.floor(size.height/2), 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, 4)
            local strFmt = ""
            for i=1,4 do
                local strTmp = string.format("%d:%d ",i,pixels[i])
                strFmt = strFmt .. strTmp
            end
            print(strFmt)
            if nil ~= schedulEntry then
                scheduler:unscheduleScriptEntry(schedulEntry)
            end
        end
        glNode:setPosition( size.width/2, size.height/2 )
        glNode:registerScriptDrawHandler(clearDraw)

        if nil ~= schedulEntry then
            scheduler:unscheduleScriptEntry(schedulEntry)
        end

        schedulEntry = scheduler:scheduleScriptFunc(getCurrentResult, 0.5, false)
        return clearLayer
    end

    local function createNodeWebGLAPITest()
        local nodeWebGLAPILayer = cc.Layer:create()
        InitTitle(nodeWebGLAPILayer)
        local glNode = gl.glNodeCreate()
        nodeWebGLAPILayer:addChild(glNode,10)
        local shaderProgram = {}
        local triangleVertexPositionBuffer = {}
        local triangleVertexColorBuffer = {}
        local squareVertexPositionBuffer = {}
        local squareVertexColorBuffer = {}
        local pMatrix = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}
        local mvMatrix = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1}

        local vsh =  "\n".."attribute vec3 aVertexPosition;\n".."attribute vec4 aVertexColor;\n"..
                     "uniform mat4 uMVMatrix;\n".."uniform mat4 uPMatrix;\n".."varying vec4 vColor;\n"..
                     "void main(void) {\n".." gl_Position = uPMatrix * uMVMatrix * vec4(aVertexPosition, 1.0);\n".." vColor = aVertexColor;\n"..
                     "}\n"

        local fsh = "\n"..
                    "#ifdef GL_ES\n"..
                    "precision mediump float;\n"..
                    "#endif\n"..
                    "varying vec4 vColor;\n"..
                    "void main(void) {\n"..
                    " gl_FragColor = vColor;\n"..
                    "}\n"

        local function compileShader(source,type)
            local shader
            if type == "fragment" then
                shader = gl.createShader(gl.FRAGMENT_SHADER)
            else
                shader = gl.createShader(gl.VERTEX_SHADER)
            end
            gl.shaderSource(shader,source)
            gl.compileShader(shader)
            local ret = gl.getShaderParameter(shader,gl.COMPILE_STATUS)
            if not ret then
                --throw
                print("Could not compile "..type.." shader")
            end
            return shader
        end

        local function initBuffers()
            triangleVertexPositionBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer.buffer_id)
            local vertices = {
             0.0,  1.0,  0.0,
            -1.0, -1.0,  0.0,
             1.0, -1.0,  0.0
            }
            gl.bufferData(gl.ARRAY_BUFFER, 9, vertices,gl.STATIC_DRAW)
            triangleVertexPositionBuffer.itemSize = 3
            triangleVertexPositionBuffer.numItems = 3

            triangleVertexColorBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer.buffer_id)
            local colors = {
            1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0
            }
            gl.bufferData(gl.ARRAY_BUFFER, 12, colors , gl.STATIC_DRAW)
            triangleVertexColorBuffer.itemSize = 4
            triangleVertexColorBuffer.numItems = 3

            squareVertexPositionBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
            vertices = {
             1.0,  1.0,  0.0,
            -1.0,  1.0,  0.0,
             1.0, -1.0,  0.0,
            -1.0, -1.0,  0.0
            }
            gl.bufferData(gl.ARRAY_BUFFER, 12, vertices,gl.STATIC_DRAW)
            squareVertexPositionBuffer.itemSize = 3
            squareVertexPositionBuffer.numItems = 4

            squareVertexColorBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer.buffer_id)
            colors = {
                0.0, 0.0, 1.0, 1.0,
                0.0, 0.0, 1.0, 1.0,
                0.0, 0.0, 1.0, 1.0,
                0.0, 0.0, 1.0, 1.0
            }
            gl.bufferData(gl.ARRAY_BUFFER, 16,colors, gl.STATIC_DRAW)
            squareVertexColorBuffer.itemSize = 4
            squareVertexColorBuffer.numItems = 4

            gl.bindBuffer(gl.ARRAY_BUFFER, 0)
        end

        local function setMatrixUniforms()
            gl.uniformMatrix4fv(shaderProgram.pMatrixUniform,false,table.getn(pMatrix), pMatrix)
            gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform,false,table.getn(mvMatrix),mvMatrix)
        end

        local function nodeWebGLDraw()
            gl.useProgram(shaderProgram.program_id)
            gl.uniformMatrix4fv(shaderProgram.pMatrixUniform,false,table.getn(pMatrix),pMatrix)
            gl.uniformMatrix4fv(shaderProgram.mvMatrixUniform,false,table.getn(mvMatrix),mvMatrix)

            gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute)
            gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute)

            --Draw
            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
            gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, squareVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0)

            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer.buffer_id)
            gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, squareVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0)

            setMatrixUniforms()

            gl.drawArrays(gl.TRIANGLE_STRIP, 0, squareVertexPositionBuffer.numItems)

            --DrawArray
            gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer.buffer_id)
            gl.vertexAttribPointer(shaderProgram.vertexPositionAttribute, triangleVertexPositionBuffer.itemSize, gl.FLOAT, false, 0, 0)

            gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer.buffer_id)
            gl.vertexAttribPointer(shaderProgram.vertexColorAttribute, triangleVertexColorBuffer.itemSize, gl.FLOAT, false, 0, 0)

            gl.drawArrays(gl.TRIANGLES, 0, triangleVertexPositionBuffer.numItems)

            gl.bindBuffer(gl.ARRAY_BUFFER, 0)          
        end

        local fshader = compileShader(fsh, 'fragment')
        local vshader = compileShader(vsh, 'vertex')
        shaderProgram.program_id = gl.createProgram()
        gl.attachShader(shaderProgram.program_id,vshader)
        gl.attachShader(shaderProgram.program_id,fshader)
        gl.linkProgram(shaderProgram.program_id)
        if not gl.getProgramParameter(shaderProgram.program_id, gl.LINK_STATUS) then
            --throw
            print("Could not initialise shaders")
        end
        gl.useProgram(shaderProgram.program_id)

        shaderProgram.vertexPositionAttribute = gl.getAttribLocation(shaderProgram.program_id,"aVertexPosition")
        gl.enableVertexAttribArray(shaderProgram.vertexPositionAttribute)

        shaderProgram.vertexColorAttribute = gl.getAttribLocation(shaderProgram.program_id,"aVertexColor")
        gl.enableVertexAttribArray(shaderProgram.vertexColorAttribute)

        shaderProgram.pMatrixUniform = gl.getUniformLocation(shaderProgram.program_id, "uPMatrix")
        shaderProgram.mvMatrixUniform = gl.getUniformLocation(shaderProgram.program_id, "uMVMatrix")

        initBuffers()

        glNode:registerScriptDrawHandler(nodeWebGLDraw)

        return nodeWebGLAPILayer
    end

    local function createGLNodeCCAPITest()
        local nodeCCAPILayer = cc.Layer:create()
        InitTitle(nodeCCAPILayer)
        local glNode = gl.glNodeCreate()
        nodeCCAPILayer:addChild(glNode,10)
        local shader = cc.ShaderCache:getInstance():getProgram("ShaderPositionColor")
        local triangleVertexPositionBuffer = {}
        local triangleVertexColorBuffer = {}
        local squareVertexPositionBuffer = {}
        local squareVertexColorBuffer    = {}

        local function initBuffers()
            triangleVertexPositionBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer.buffer_id)  
            local vertices = {
             size.width / 2,   size.height,
             0,                 0,
             size.width,     0
            }
            gl.bufferData(gl.ARRAY_BUFFER, table.getn(vertices), vertices, gl.STATIC_DRAW)

            triangleVertexColorBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer.buffer_id) 
            local colors = {
            1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0,
            1.0, 0.0, 0.0, 1.0
            }
            gl.bufferData(gl.ARRAY_BUFFER, table.getn(colors),colors, gl.STATIC_DRAW)

            --Square
            squareVertexPositionBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
            vertices = {
                size.width,  size.height,
                0,           size.height,
                size.width,  0,
                0,           0
            }
            gl.bufferData(gl.ARRAY_BUFFER, table.getn(vertices), vertices, gl.STATIC_DRAW)
            
            squareVertexColorBuffer.buffer_id = gl.createBuffer()
            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer.buffer_id)
            colors = {
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0,
            0.0, 0.0, 1.0, 1.0
            };
            gl.bufferData(gl.ARRAY_BUFFER, table.getn(colors), colors, gl.STATIC_DRAW)
            gl.bindBuffer(gl.ARRAY_BUFFER, 0)
        end

        local function GLNodeCCAPIDraw(transform, transformUpdated)
            shader:use()
            shader:setUniformsForBuiltins(transform)
            gl.glEnableVertexAttribs(cc.VERTEX_ATTRIB_FLAG_COLOR or cc.VERTEX_ATTRIB_FLAG_POSITION)

            --
            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexPositionBuffer.buffer_id)
            gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)

            gl.bindBuffer(gl.ARRAY_BUFFER, squareVertexColorBuffer.buffer_id)
            gl.vertexAttribPointer(cc.VERTEX_ATTRIB_COLOR, 4, gl.FLOAT, false, 0, 0)

            gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4)

            gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexPositionBuffer.buffer_id)
            gl.vertexAttribPointer(cc.VERTEX_ATTRIB_POSITION, 2, gl.FLOAT, false, 0, 0)

            gl.bindBuffer(gl.ARRAY_BUFFER, triangleVertexColorBuffer.buffer_id)
            gl.vertexAttribPointer(cc.VERTEX_ATTRIB_COLOR, 4, gl.FLOAT, false, 0, 0)

            gl.drawArrays(gl.TRIANGLE_STRIP, 0, 3)

            gl.bindBuffer(gl.ARRAY_BUFFER, 0)

        end

        initBuffers()
        glNode:registerScriptDrawHandler(GLNodeCCAPIDraw)

        return nodeCCAPILayer
    end

    local function createGLTexParamterTest()
        local glTexParamLayer = cc.Layer:create()
        InitTitle(glTexParamLayer)
        local glNode  = gl.glNodeCreate()
        glTexParamLayer:addChild(glNode,10)
        local function getTexValues()
            gl.bindTexture(gl.TEXTURE_2D, 0)
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER, gl.NEAREST)
            gl.texParameteri(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER, gl.NEAREST)
            gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE )
            gl.texParameteri( gl.TEXTURE_2D, gl.TEXTURE_WRAP_S, gl.CLAMP_TO_EDGE )

            local mag = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_MAG_FILTER)
            local min = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_MIN_FILTER)
            local w_s = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S)
            local w_t = gl.getTexParameter(gl.TEXTURE_2D, gl.TEXTURE_WRAP_S)
            local strFmt = string.format("%d %d %d %d",mag,min,w_s,w_t)
            print(strFmt)
        end
        getTexValues()
        return glTexParamLayer
    end

    local function createGetUniformTest()
        local getUniformLayer = cc.Layer:create()
        InitTitle(getUniformLayer)
        local glNode  = gl.glNodeCreate()
        getUniformLayer:addChild(glNode,10)
        local pMatrix = {1,2,3,4, 4,3,2,1, 1,2,4,8, 1.1,1.2,1.3,1.4}

        local function runTest()
            local shader = cc.ShaderCache:getInstance():getProgram("ShaderPositionTextureColor")
            local program = shader:getProgram()

            shader:use()

            local loc = gl.getUniformLocation( program, "CC_MVPMatrix")

            gl.uniformMatrix4fv(loc, false, table.getn(pMatrix), pMatrix)

            local uniformTable = gl.getUniform( program, loc )
            local count = table.getn(uniformTable)
            local strFmt = ""
            for i=1,count do
                local  strTmp = string.format("%d: %.16f ",i - 1, uniformTable[i])
                strFmt = strFmt..strTmp
            end
            print(strFmt)
        end

        runTest()

        return getUniformLayer
    end

    local function createLayerByCurCase(curCase)
        if 0 == curCase then
            return createShaderRetroEffect()
        elseif 1 == curCase then
            return createShaderMajoriTest()
        elseif 2 == curCase then
            return createShaderMandelbrotTest()
        elseif 3 == curCase then
            return createShaderHeartTest()
        elseif 4 == curCase then
            return createShaderPlasmaTest()
        elseif 5 == curCase then
            return createShaderFlowerTest()
        elseif 6 == curCase then
            return createShaderJuliaTest()
        elseif 7 == curCase then
            return createGLGetActiveTest()
        elseif 8 == curCase then
            return createTexImage2DTest()
        elseif 9 == curCase then
            return CreateSupportedExtensionsLayer()
        elseif 10 == curCase then
            return CreateReadPixelsTest()
        elseif 11 == curCase then
            return createClearTest()
        elseif 12 == curCase then
            return createNodeWebGLAPITest()
        elseif 13 == curCase then
            return createGLNodeCCAPITest()
        elseif 14 == curCase then
            return createGLTexParamterTest()
        elseif 15 == curCase then
            return createGetUniformTest()
        end
    end

    function ShowCurrentTest()    
        local curScene = cc.Scene:create()
        if nil ~= curScene then
            if nil ~= curLayer then
                local scheduler = cc.Director:getInstance():getScheduler()
                if nil ~= schedulEntry then
                    scheduler:unscheduleScriptEntry(schedulEntry)
                end
            end
            curLayer = createLayerByCurCase(curCase)
            if nil ~= curLayer then
                curScene:addChild(curLayer)
                curLayer:addChild(OrderCallbackMenu(),15)
                curScene:addChild(CreateBackMenuItem())
                cc.Director:getInstance():replaceScene(curScene)
            end            
        end 
    end
    curLayer = createLayerByCurCase(curCase)
    curLayer:addChild(OrderCallbackMenu(),15)
    return curLayer
end

function OpenGLTestMain()
    local scene = cc.Scene:create()
    scene:addChild(OpenGLTestMainLayer())
    scene:addChild(CreateBackMenuItem())
    return scene
end
