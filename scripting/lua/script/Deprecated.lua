--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--functions of _G will be deprecated begin
local function ccpLineIntersect(a,b,c,d,s,t)
    deprecatedTip("ccpLineIntersect","CCPoint:isLineIntersect")
    return CCPoint:isLineIntersect(a,b,c,d,s,t)
end
rawset(_G,"ccpLineIntersect",ccpLineIntersect)


local function CCPointMake(x,y)
    deprecatedTip("CCPointMake(x,y)","CCPoint(x,y)")
    return CCPoint(x,y)
end 
rawset(_G,"CCPointMake",CCPointMake)

local function ccp(x,y)
    deprecatedTip("ccp(x,y)","CCPoint(x,y)")
    return CCPoint(x,y)
end 
rawset(_G,"ccp",ccp)

local function CCSizeMake(width,height)
    deprecatedTip("CCSizeMake(width,height)","CCSize(width,height)")
    return CCSize(width,height)
end
rawset(_G,"CCSizeMake",CCSizeMake)

local function CCRectMake(x,y,width,height)
    deprecatedTip("CCRectMake(x,y,width,height)","CCRect(x,y,width,height)")
    return CCRect(x,y,width,height)
end
rawset(_G,"CCRectMake",CCRectMake)

local function ccpNeg(pt)
    deprecatedTip("ccpNeg","CCPoint.__sub")
    return CCPoint.__sub(CCPoint:new_local(0,0),pt)
end
rawset(_G,"ccpNeg",ccpNeg)

local function ccpAdd(pt1,pt2)
    deprecatedTip("ccpAdd","CCPoint.__add")
    return CCPoint.__add(pt1,pt2)
end
rawset(_G,"ccpAdd",ccpAdd)

local function ccpSub(pt1,pt2)
    deprecatedTip("ccpSub","CCPoint.__sub")
    return CCPoint.__sub(pt1,pt2)
end
rawset(_G,"ccpSub",ccpSub)

local function ccpMult(pt,factor)
    deprecatedTip("ccpMult","CCPoint.__mul")
    return CCPoint.__mul(pt,factor)
end
rawset(_G,"ccpMult",ccpMult)

local function ccpMidpoint(pt1,pt2)
    deprecatedTip("ccpMidpoint","CCPoint:getMidpoint")
    return pt1:getMidpoint(pt2)
end
rawset(_G,"ccpMidpoint",ccpMidpoint)

local function ccpDot(pt1,pt2)
    deprecatedTip("ccpDot","CCPoint:dot")
    return pt1:dot(pt2)
end
rawset(_G,"ccpDot",ccpDot)

local function ccpCross(pt1,pt2)
    deprecatedTip("ccpCross","CCPoint:cross")
    return pt1:cross(pt2)
end
rawset(_G,"ccpCross",ccpCross)

local function ccpPerp(pt)
    deprecatedTip("ccpPerp","CCPoint:getPerp")
    return pt:getPerp()
end
rawset(_G,"ccpPerp",ccpPerp)

local function ccpRPerp(pt)
    deprecatedTip("ccpRPerp","CCPoint:getRPerp")
    return pt:getRPerp()
end
rawset(_G,"ccpRPerp",ccpRPerp)

local function ccpProject(pt1,pt2)
    deprecatedTip("ccpProject","CCPoint:project")
    return pt1:project(pt2)
end
rawset(_G,"ccpProject",ccpProject)

local function ccpRotate(pt1,pt2)
    deprecatedTip("ccpRotate","CCPoint:rotate")
    return pt1:rotate(pt2)
end
rawset(_G,"ccpRotate",ccpRotate)

local function ccpUnrotate(pt1,pt2)
    deprecatedTip("ccpUnrotate","CCPoint:unrotate")
    return pt1:unrotate(pt2)
end
rawset(_G,"ccpUnrotate",ccpUnrotate)

local function ccpLengthSQ(pt)
    deprecatedTip("ccpLengthSQ","CCPoint:getLengthSq")
    return pt:getLengthSq(pt)
end
rawset(_G,"ccpLengthSQ",ccpLengthSQ)

local function ccpDistanceSQ(pt1,pt2)
    deprecatedTip("ccpDistanceSQ","CCPoint:__sub(pt1,pt2):getLengthSq")
    return (CCPoint.__sub(pt1,pt2)):getLengthSq()
end
rawset(_G,"ccpDistanceSQ",ccpDistanceSQ)

local function ccpLength(pt)
    deprecatedTip("ccpLength","CCPoint:getLength")
    return pt:getLength()
end
rawset(_G,"ccpLength",ccpLength)

local function ccpDistance(pt1,pt2)
    deprecatedTip("ccpDistance","CCPoint:getDistance")
    return pt1:getDistance(pt2)
end
rawset(_G,"ccpDistance",ccpDistance)

local function ccpNormalize(pt)
    deprecatedTip("ccpNormalize","CCPoint:normalize")
    return pt:normalize()
end
rawset(_G,"ccpNormalize",ccpNormalize)

local function ccpForAngle(angle)
    deprecatedTip("ccpForAngle","CCPoint:forAngle")
    return CCPoint:forAngle(angle)
end
rawset(_G,"ccpForAngle",ccpForAngle)

local function ccpToAngle(pt)
    deprecatedTip("ccpToAngle","CCPoint:getAngle")
    return pt:getAngle()
end
rawset(_G,"ccpToAngle",ccpToAngle)

local function ccpClamp(pt1,pt2,pt3)
    deprecatedTip("ccpClamp","CCPoint:getClampPoint")
    return pt1:getClampPoint(pt2, pt3)
end
rawset(_G,"ccpClamp",ccpClamp)


local function ccpFromSize(sz)
    deprecatedTip("ccpFromSize(sz)","CCPoint(sz)")
    return CCPoint(sz)
end
rawset(_G,"ccpFromSize",ccpFromSize)

local function ccpLerp(pt1,pt2,alpha)
    deprecatedTip("ccpLerp","CCPoint:lerp")
    return pt1:lerp(pt2,alpha)
end
rawset(_G,"ccpLerp",ccpLerp)

local function ccpFuzzyEqual(pt1,pt2,variance)
    deprecatedTip("ccpFuzzyEqual","CCPoint:fuzzyEquals")
    return pt1:fuzzyEquals(pt2,variance)
end
rawset(_G,"ccpFuzzyEqual",ccpFuzzyEqual)

local function ccpCompMult(pt1,pt2)
    deprecatedTip("ccpCompMult","CCPoint")
    return CCPoint(pt1.x * pt2.x , pt1.y * pt2.y)
end
rawset(_G,"ccpCompMult",ccpCompMult)

local function ccpAngleSigned(pt1,pt2)
    deprecatedTip("ccpAngleSigned","CCPoint:getAngle")
    return pt1:getAngle(pt2)
end
rawset(_G,"ccpAngleSigned",ccpAngleSigned)

local function ccpAngle(pt1,pt2)
    deprecatedTip("ccpAngle","CCPoint:getAngle")
    return pt1:getAngle(pt2)
end
rawset(_G,"ccpAngle",ccpAngle)

local function ccpRotateByAngle(pt1,pt2,angle)
    deprecatedTip("ccpRotateByAngle","CCPoint:rotateByAngle")
    return pt1:rotateByAngle(pt2, angle)
end
rawset(_G,"ccpRotateByAngle",ccpRotateByAngle)

local function ccpSegmentIntersect(pt1,pt2,pt3,pt4)
    deprecatedTip("ccpSegmentIntersect","CCPoint:isSegmentIntersect")
    return CCPoint:isSegmentIntersect(pt1,pt2,pt3,pt4)
end
rawset(_G,"ccpSegmentIntersect",ccpSegmentIntersect)

local function ccpIntersectPoint(pt1,pt2,pt3,pt4)
    deprecatedTip("ccpIntersectPoint","CCPoint:getIntersectPoint")
    return CCPoint:getIntersectPoint(pt1,pt2,pt3,pt4)
end
rawset(_G,"ccpIntersectPoint",ccpIntersectPoint)

local function ccc3(r,g,b)
    deprecatedTip("ccc3(r,g,b)","ccColor3B(r,g,b)")
    return ccColor3B(r,g,b)
end
rawset(_G,"ccc3",ccc3)

local function ccc4(r,g,b,a)
    deprecatedTip("ccc4(r,g,b,a)","Color4B(r,g,b,a)")
    return Color4B(r,g,b,a)
end
rawset(_G,"ccc4",ccc4)

local function ccc4FFromccc3B(color3B)
    deprecatedTip("ccc4FFromccc3B(color3B)","Color4F(color3B.r / 255.0,color3B.g / 255.0,color3B.b / 255.0,1.0)")
    return Color4F(color3B.r/255.0, color3B.g/255.0, color3B.b/255.0, 1.0)
end
rawset(_G,"ccc4FFromccc3B",ccc4FFromccc3B)

local function ccc4f(r,g,b,a)
    deprecatedTip("ccc4f(r,g,b,a)","Color4F(r,g,b,a)")
    return Color4F(r,g,b,a)
end
rawset(_G,"ccc4f",ccc4f)

local function ccc4FFromccc4B(color4B)
    deprecatedTip("ccc4FFromccc4B(color4B)","Color4F(color4B.r/255.0, color4B.g/255.0, color4B.b/255.0, color4B.a/255.0)")
    return Color4F(color4B.r/255.0, color4B.g/255.0, color4B.b/255.0, color4B.a/255.0)   
end
rawset(_G,"ccc4FFromccc4B",ccc4FFromccc4B)

local function ccc4FEqual(a,b)
    deprecatedTip("ccc4FEqual(a,b)","a:equals(b)")
    return a:equals(b)
end
rawset(_G,"ccc4FEqual",ccc4FEqual)

local function vertex2(x,y)
    deprecatedTip("vertex2(x,y)","Vertex2F(x,y)")
    return Vertex2F(x,y)
end
rawset(_G,"vertex2",vertex2)

local function vertex3(x,y,z)
    deprecatedTip("vertex3(x,y,z)","Vertex3F(x,y,z)")
    return Vertex3F(x,y,z)
end
rawset(_G,"vertex3",vertex3)

local function tex2(u,v)
    deprecatedTip("tex2(u,v)","Tex2F(u,v)")
    return Tex2F(u,v)
end
rawset(_G,"tex2",tex2) 

local function ccc4BFromccc4F(color4F)
    deprecatedTip("ccc4BFromccc4F(color4F)","Color4B(color4F.r * 255.0, color4F.g * 255.0, color4F.b * 255.0, color4B.a * 255.0)")
    return Color4B(color4F.r * 255.0, color4F.g * 255.0, color4F.b * 255.0, color4B.a * 255.0) 
end
rawset(_G,"ccc4BFromccc4F",ccc4BFromccc4F)

local function ccColor3BDeprecated()
    deprecatedTip("ccColor3B","Color3B")
    return Color3B
end
_G["ccColor3B"] = ccColor3BDeprecated()

local function ccColor4BDeprecated()
    deprecatedTip("ccColor4B","Color4B")
    return Color4B
end
_G["ccColor4B"] = ccColor4BDeprecated()

local function ccColor4FDeprecated()
    deprecatedTip("ccColor4F","Color4F")
    return Color4F
end
_G["ccColor4F"] = ccColor4FDeprecated()

local function ccVertex2FDeprecated()
    deprecatedTip("ccVertex2F","Vertex2F")
    return Vertex2F
end
_G["ccVertex2F"] = ccVertex2FDeprecated()

local function ccVertex3FDeprecated()
    deprecatedTip("ccVertex3F","Vertex3F")
    return Vertex3F
end
_G["ccVertex3F"] = ccVertex3FDeprecated()

local function ccTex2FDeprecated()
    deprecatedTip("ccTex2F","Tex2F")
    return Tex2F
end
_G["ccTex2F"] = ccTex2FDeprecated()

local function ccPointSpriteDeprecated()
    deprecatedTip("ccPointSprite","PointSprite")
    return PointSprite
end
_G["ccPointSprite"] = ccPointSpriteDeprecated()

local function ccQuad2Deprecated()
    deprecatedTip("ccQuad2","Quad2")
    return Quad2
end
_G["ccQuad2"] = ccQuad2Deprecated()

local function ccQuad3Deprecated()
    deprecatedTip("ccQuad3","Quad3")
    return Quad3
end
_G["ccQuad3"] = ccQuad3Deprecated()

local function ccV2FC4BT2FDeprecated()
    deprecatedTip("ccV2F_C4B_T2F","V2F_C4B_T2F")
    return V2F_C4B_T2F
end
_G["ccV2F_C4B_T2F"] = ccV2FC4BT2FDeprecated()


local function ccV2FC4FT2FDeprecated()
    deprecatedTip("ccV2F_C4F_T2F","V2F_C4F_T2F")
    return V2F_C4F_T2F
end
_G["ccV2F_C4F_T2F"] = ccV2FC4FT2FDeprecated()

local function ccV3FC4BT2FDeprecated()
    deprecatedTip("ccV3F_C4B_T2F","V3F_C4B_T2F")
    return V3F_C4B_T2F
end
_G["ccV3F_C4B_T2F"] = ccV3FC4BT2FDeprecated()

local function ccV2FC4BT2FQuadDeprecated()
    deprecatedTip("ccV2F_C4B_T2F_Quad","V2F_C4B_T2F_Quad")
    return V2F_C4B_T2F_Quad
end
_G["ccV2F_C4B_T2F_Quad"] = ccV2FC4BT2FQuadDeprecated()

local function ccV3FC4BT2FQuadDeprecated()
    deprecatedTip("ccV3F_C4B_T2F_Quad","V3F_C4B_T2F_Quad")
    return V3F_C4B_T2F_Quad
end
_G["ccV3F_C4B_T2F_Quad"] = ccV3FC4BT2FQuadDeprecated()

local function ccV2FC4FT2FQuadDeprecated()
    deprecatedTip("ccV2F_C4F_T2F_Quad","V2F_C4F_T2F_Quad")
    return V2F_C4F_T2F_Quad
end
_G["ccV2F_C4F_T2F_Quad"] = ccV2FC4FT2FQuadDeprecated()

local function ccBlendFuncDeprecated()
    deprecatedTip("ccBlendFunc","BlendFunc")
    return BlendFunc
end
_G["ccBlendFunc"] = ccBlendFuncDeprecated()

local function ccT2FQuadDeprecated()
    deprecatedTip("ccT2F_Quad","T2F_Quad")
    return T2F_Quad
end
_G["ccT2F_Quad"] = ccT2FQuadDeprecated()

local function ccAnimationFrameDataDeprecated()
    deprecatedTip("ccAnimationFrameData","AnimationFrameData")
    return AnimationFrameData
end
_G["ccAnimationFrameData"] = ccAnimationFrameDataDeprecated()

local function CCCallFuncNDeprecated( )
    deprecatedTip("CCCallFuncN","CCCallFunc")
    return CCCallFunc
end
_G["CCCallFuncN"] = CCCallFuncNDeprecated()
--functions of _G will be deprecated end


--functions of CCControl will be deprecated end
local CCControlDeprecated = { }
function CCControlDeprecated.addHandleOfControlEvent(self,func,controlEvent)
    deprecatedTip("addHandleOfControlEvent","registerControlEventHandler")
    print("come in addHandleOfControlEvent")
    self:registerControlEventHandler(func,controlEvent)
end
rawset(CCControl,"addHandleOfControlEvent",CCControlDeprecated.addHandleOfControlEvent)
--functions of CCControl will be deprecated end


--functions of CCEGLView will be deprecated end
local CCEGLViewDeprecated = { }
function CCEGLViewDeprecated.sharedOpenGLView()
    deprecatedTip("CCEGLView:sharedOpenGLView","CCEGLView:getInstance")
    return CCEGLView:getInstance()
end
rawset(CCEGLView,"sharedOpenGLView",CCEGLViewDeprecated.sharedOpenGLView)
--functions of CCFileUtils will be deprecated end


--functions of CCFileUtils will be deprecated end
local CCFileUtilsDeprecated = { }
function CCFileUtilsDeprecated.sharedFileUtils()
    deprecatedTip("CCFileUtils:sharedFileUtils","CCFileUtils:getInstance")
    return CCFileUtils:getInstance()
end
rawset(CCFileUtils,"sharedFileUtils",CCFileUtilsDeprecated.sharedFileUtils)

function CCFileUtilsDeprecated.purgeFileUtils()
    deprecatedTip("CCFileUtils:purgeFileUtils","CCFileUtils:destroyInstance")
    return CCFileUtils:destroyInstance()
end
rawset(CCFileUtils,"purgeFileUtils",CCFileUtilsDeprecated.purgeFileUtils)
--functions of CCFileUtils will be deprecated end


--functions of CCApplication will be deprecated end
local CCApplicationDeprecated = { }
function CCApplicationDeprecated.sharedApplication()
    deprecatedTip("CCApplication:sharedApplication","CCApplication:getInstance")
    return CCApplication:getInstance()
end
rawset(CCApplication,"sharedApplication",CCApplicationDeprecated.sharedApplication)
--functions of CCApplication will be deprecated end


--functions of CCDirector will be deprecated end
local CCDirectorDeprecated = { }
function CCDirectorDeprecated.sharedDirector()
    deprecatedTip("CCDirector:sharedDirector","CCDirector:getInstance")
    return CCDirector:getInstance()
end
rawset(CCDirector,"sharedDirector",CCDirectorDeprecated.sharedDirector)
--functions of CCDirector will be deprecated end


--functions of CCUserDefault will be deprecated end
local CCUserDefaultDeprecated = { }
function CCUserDefaultDeprecated.sharedUserDefault()
    deprecatedTip("CCUserDefault:sharedUserDefault","CCUserDefault:getInstance")
    return CCUserDefault:getInstance()
end
rawset(CCUserDefault,"sharedUserDefault",CCUserDefaultDeprecated.sharedUserDefault)

function CCUserDefaultDeprecated.purgeSharedUserDefault()
    deprecatedTip("CCUserDefault:purgeSharedUserDefault","CCUserDefault:destroyInstance")
    return CCUserDefault:destroyInstance()
end
rawset(CCUserDefault,"purgeSharedUserDefault",CCUserDefaultDeprecated.purgeSharedUserDefault)
--functions of CCUserDefault will be deprecated end


--functions of CCNotificationCenter will be deprecated end
local CCNotificationCenterDeprecated = { }
function CCNotificationCenterDeprecated.sharedNotificationCenter()
    deprecatedTip("CCNotificationCenter:sharedNotificationCenter","CCNotificationCenter:getInstance")
    return CCNotificationCenter:getInstance()
end
rawset(CCNotificationCenter,"sharedNotificationCenter",CCNotificationCenterDeprecated.sharedNotificationCenter)

function CCNotificationCenterDeprecated.purgeNotificationCenter()
    deprecatedTip("CCNotificationCenter:purgeNotificationCenter","CCNotificationCenter:destroyInstance")
    return CCNotificationCenter:destroyInstance()
end
rawset(CCNotificationCenter,"purgeNotificationCenter",CCNotificationCenterDeprecated.purgeNotificationCenter)
--functions of CCNotificationCenter will be deprecated end


--functions of CCTextureCache will be deprecated begin
local CCTextureCacheDeprecated = { }
function CCTextureCacheDeprecated.sharedTextureCache()
    deprecatedTip("CCTextureCache:sharedTextureCache","CCTextureCache:getInstance")
    return CCTextureCache:getInstance()
end
rawset(CCTextureCache,"sharedTextureCache",CCTextureCacheDeprecated.sharedTextureCache)

function CCTextureCacheDeprecated.purgeSharedTextureCache()
    deprecatedTip("CCTextureCache:purgeSharedTextureCache","CCTextureCache:destroyInstance")
    return CCTextureCache:destroyInstance()
end
rawset(CCTextureCache,"purgeSharedTextureCache",CCTextureCacheDeprecated.purgeSharedTextureCache)
--functions of CCTextureCache will be deprecated end


--functions of CCGrid3DAction will be deprecated begin
local CCGrid3DActionDeprecated = { }
function CCGrid3DActionDeprecated.vertex(self,pt)
    deprecatedTip("vertex","CCGrid3DAction:getVertex")
    return self:getVertex(pt)
end
rawset(CCGrid3DAction,"vertex",CCGrid3DActionDeprecated.vertex)

function CCGrid3DActionDeprecated.originalVertex(self,pt)
    deprecatedTip("originalVertex","CCGrid3DAction:getOriginalVertex")
    return self:getOriginalVertex(pt)
end
rawset(CCGrid3DAction,"originalVertex",CCGrid3DActionDeprecated.originalVertex)
--functions of CCGrid3DAction will be deprecated end


--functions of CCTiledGrid3DAction will be deprecated begin
local CCTiledGrid3DActionDeprecated = { }
function CCTiledGrid3DActionDeprecated.tile(self,pt)
    deprecatedTip("tile","CCTiledGrid3DAction:getTile")
    return self:getTile(pt)
end
rawset(CCTiledGrid3DAction,"tile",CCTiledGrid3DActionDeprecated.tile)

function CCTiledGrid3DActionDeprecated.originalTile(self,pt)
    deprecatedTip("originalTile","CCTiledGrid3DAction:getOriginalTile")
    return self:getOriginalTile(pt)
end
rawset(CCTiledGrid3DAction,"originalTile",CCTiledGrid3DActionDeprecated.originalTile)
--functions of CCTiledGrid3DAction will be deprecated end


--functions of CCAnimationCache will be deprecated begin
local CCAnimationCacheDeprecated = { }
function CCAnimationCacheDeprecated.sharedAnimationCache()
    deprecatedTip("CCAnimationCache:sharedAnimationCache","CCAnimationCache:getInstance")
    return CCAnimationCache:getInstance()
end
rawset(CCAnimationCache,"sharedAnimationCache",CCAnimationCacheDeprecated.sharedAnimationCache)

function CCAnimationCacheDeprecated.purgeSharedAnimationCache()
    deprecatedTip("CCAnimationCache:purgeSharedAnimationCache","CCAnimationCache:destroyInstance")
    return CCAnimationCache:destroyInstance()
end
rawset(CCAnimationCache,"purgeSharedAnimationCache",CCAnimationCacheDeprecated.purgeSharedAnimationCache)
--functions of CCAnimationCache will be deprecated end


--functions of CCNode will be deprecated begin
local CCNodeDeprecated = { }
function CCNodeDeprecated.boundingBox(self)
    deprecatedTip("CCNode:boundingBox","CCNode:getBoundingBox")
    return self:getBoundingBox()
end
rawset(CCNode,"boundingBox",CCNodeDeprecated.boundingBox)

function CCNodeDeprecated.numberOfRunningActions(self)
    deprecatedTip("CCNode:numberOfRunningActions","CCNode:getNumberOfRunningActions")
    return self:getNumberOfRunningActions()
end
rawset(CCNode,"numberOfRunningActions",CCNodeDeprecated.numberOfRunningActions)
--functions of CCNode will be deprecated end


--functions of CCTexture2D will be deprecated begin
local CCTexture2DDeprecated = { }
function CCTexture2DDeprecated.stringForFormat(self)
    deprecatedTip("Texture2D:stringForFormat","Texture2D:getStringForFormat")
    return self:getStringForFormat()
end
rawset(CCTexture2D,"stringForFormat",CCTexture2DDeprecated.stringForFormat)

function CCTexture2DDeprecated.bitsPerPixelForFormat(self)
    deprecatedTip("Texture2D:bitsPerPixelForFormat","Texture2D:getBitsPerPixelForFormat")
    return self:getBitsPerPixelForFormat()
end
rawset(CCTexture2D,"bitsPerPixelForFormat",CCTexture2DDeprecated.bitsPerPixelForFormat)

function CCTexture2DDeprecated.bitsPerPixelForFormat(self,pixelFormat)
    deprecatedTip("Texture2D:bitsPerPixelForFormat","Texture2D:getBitsPerPixelForFormat")
    return self:getBitsPerPixelForFormat(pixelFormat)
end
rawset(CCTexture2D,"bitsPerPixelForFormat",CCTexture2DDeprecated.bitsPerPixelForFormat)

function CCTexture2DDeprecated.defaultAlphaPixelFormat(self)
    deprecatedTip("Texture2D:defaultAlphaPixelFormat","Texture2D:getDefaultAlphaPixelFormat")
    return self:getDefaultAlphaPixelFormat()
end
rawset(CCTexture2D,"defaultAlphaPixelFormat",CCTexture2DDeprecated.defaultAlphaPixelFormat)
--functions of CCTexture2D will be deprecated end


--functions of CCSpriteFrameCache will be deprecated begin
local CCSpriteFrameCacheDeprecated = { }
function CCSpriteFrameCacheDeprecated.spriteFrameByName(self,szName)
    deprecatedTip("CCSpriteFrameCache:spriteFrameByName","CCSpriteFrameCache:getSpriteFrameByName")
    return self:getSpriteFrameByName(szName)
end
rawset(CCSpriteFrameCache,"spriteFrameByName",CCSpriteFrameCacheDeprecated.spriteFrameByName)

function CCSpriteFrameCacheDeprecated.sharedSpriteFrameCache()
    deprecatedTip("CCSpriteFrameCache:sharedSpriteFrameCache","CCSpriteFrameCache:getInstance")
    return CCSpriteFrameCache:getInstance()
end
rawset(CCSpriteFrameCache,"sharedSpriteFrameCache",CCSpriteFrameCacheDeprecated.sharedSpriteFrameCache)

function CCSpriteFrameCacheDeprecated.purgeSharedSpriteFrameCache()
    deprecatedTip("CCSpriteFrameCache:purgeSharedSpriteFrameCache","CCSpriteFrameCache:destroyInstance")
    return CCSpriteFrameCache:destroyInstance()
end
rawset(CCSpriteFrameCache,"purgeSharedSpriteFrameCache",CCSpriteFrameCacheDeprecated.purgeSharedSpriteFrameCache)
--functions of CCSpriteFrameCache will be deprecated end


--functions of CCTimer will be deprecated begin
local CCTimerDeprecated = { }
function CCTimerDeprecated.timerWithScriptHandler(handler,seconds)
    deprecatedTip("CCTimer:timerWithScriptHandler","CCTimer:createWithScriptHandler")
    return CCTimer:createWithScriptHandler(handler,seconds)
end
rawset(CCTimer,"timerWithScriptHandler",CCTimerDeprecated.timerWithScriptHandler)

function CCTimerDeprecated.numberOfRunningActionsInTarget(self,target)
    deprecatedTip("CCActionManager:numberOfRunningActionsInTarget","CCActionManager:getNumberOfRunningActionsInTarget")
    return self:getNumberOfRunningActionsInTarget(target)
end
rawset(CCTimer,"numberOfRunningActionsInTarget",CCTimerDeprecated.numberOfRunningActionsInTarget)
--functions of CCTimer will be deprecated end


--functions of CCMenuItemFont will be deprecated begin
local CCMenuItemFontDeprecated = { }
function CCMenuItemFontDeprecated.fontSize()
    deprecatedTip("CCMenuItemFont:fontSize","CCMenuItemFont:getFontSize")
    return CCMenuItemFont:getFontSize()
end
rawset(CCMenuItemFont,"fontSize",CCMenuItemFontDeprecated.fontSize)

function CCMenuItemFontDeprecated.fontName()
    deprecatedTip("CCMenuItemFont:fontName","CCMenuItemFont:getFontName")
    return CCMenuItemFont:getFontName()
end
rawset(CCMenuItemFont,"fontName",CCMenuItemFontDeprecated.fontName)

function CCMenuItemFontDeprecated.fontSizeObj(self)
    deprecatedTip("CCMenuItemFont:fontSizeObj","CCMenuItemFont:getFontSizeObj")
    return self:getFontSizeObj()
end
rawset(CCMenuItemFont,"fontSizeObj",CCMenuItemFontDeprecated.fontSizeObj)

function CCMenuItemFontDeprecated.fontNameObj(self)
    deprecatedTip("CCMenuItemFont:fontNameObj","CCMenuItemFont:getFontNameObj")
    return self:getFontNameObj()
end
rawset(CCMenuItemFont,"fontNameObj",CCMenuItemFontDeprecated.fontNameObj)
--functions of CCMenuItemFont will be deprecated end


--functions of CCMenuItemToggle will be deprecated begin
local CCMenuItemToggleDeprecated = { }
function CCMenuItemToggleDeprecated.selectedItem(self)
    deprecatedTip("CCMenuItemToggle:selectedItem","CCMenuItemToggle:getSelectedItem")
    return self:getSelectedItem()
end
rawset(CCMenuItemToggle,"selectedItem",CCMenuItemToggleDeprecated.selectedItem)
--functions of CCMenuItemToggle will be deprecated end


--functions of CCTileMapAtlas will be deprecated begin
local CCTileMapAtlasDeprecated = { }
function CCTileMapAtlasDeprecated.tileAt(self,pos)
    deprecatedTip("CCTileMapAtlas:tileAt","CCTileMapAtlas:getTileAt")
    return self:getTileAt(pos)
end
rawset(CCTileMapAtlas,"tileAt",CCTileMapAtlasDeprecated.tileAt)
--functions of CCTileMapAtlas will be deprecated end


--functions of CCTMXLayer will be deprecated begin
local CCTMXLayerDeprecated = { }
function CCTMXLayerDeprecated.tileAt(self,tileCoordinate)
    deprecatedTip("CCTMXLayer:tileAt","CCTMXLayer:getTileAt")
    return self:getTileAt(tileCoordinate)
end
rawset(CCTMXLayer,"tileAt",CCTMXLayerDeprecated.tileAt)

function CCTMXLayerDeprecated.tileGIDAt(self,tileCoordinate)
    deprecatedTip("CCTMXLayer:tileGIDAt","CCTMXLayer:getTileGIDAt")
    return self:getTileGIDAt(tileCoordinate)
end
rawset(CCTMXLayer,"tileGIDAt",CCTMXLayerDeprecated.tileGIDAt)

function CCTMXLayerDeprecated.positionAt(self,tileCoordinate)
    deprecatedTip("CCTMXLayer:positionAt","CCTMXLayer:getPositionAt")
    return self:getPositionAt(tileCoordinate)
end
rawset(CCTMXLayer,"positionAt",CCTMXLayerDeprecated.positionAt)

function CCTMXLayerDeprecated.propertyNamed(self,propertyName)
    deprecatedTip("CCTMXLayer:propertyNamed","CCTMXLayer:getProperty")
    return self:getProperty(propertyName)
end
rawset(CCTMXLayer,"propertyNamed",CCTMXLayerDeprecated.propertyNamed)
--functions of CCTMXLayer will be deprecated end


--functions of SimpleAudioEngine will be deprecated begin
local SimpleAudioEngineDeprecated = { }
function SimpleAudioEngineDeprecated.sharedEngine()
    deprecatedTip("SimpleAudioEngine:sharedEngine","SimpleAudioEngine:getInstance")
    return SimpleAudioEngine:getInstance()
end
rawset(SimpleAudioEngine,"sharedEngine",SimpleAudioEngineDeprecated.sharedEngine)
--functions of SimpleAudioEngine will be deprecated end


--functions of CCTMXTiledMap will be deprecated begin
local CCTMXTiledMapDeprecated = { }
function CCTMXTiledMapDeprecated.layerNamed(self,layerName)
    deprecatedTip("CCTMXTiledMap:layerNamed","CCTMXTiledMap:getLayer")
    return self:getLayer(layerName)
end
rawset(CCTMXTiledMap,"layerNamed", CCTMXTiledMapDeprecated.layerNamed)

function CCTMXTiledMapDeprecated.propertyNamed(self,propertyName)
    deprecatedTip("CCTMXTiledMap:propertyNamed","CCTMXTiledMap:getProperty")
    return self:getProperty(propertyName)
end
rawset(CCTMXTiledMap,"propertyNamed", CCTMXTiledMapDeprecated.propertyNamed )

function CCTMXTiledMapDeprecated.propertiesForGID(self,GID)
    deprecatedTip("CCTMXTiledMap:propertiesForGID","CCTMXTiledMap:getPropertiesForGID")
    return self:getPropertiesForGID(GID)
end
rawset(CCTMXTiledMap,"propertiesForGID", CCTMXTiledMapDeprecated.propertiesForGID)

function CCTMXTiledMapDeprecated.objectGroupNamed(self,groupName)
    deprecatedTip("CCTMXTiledMap:objectGroupNamed","CCTMXTiledMap:getObjectGroup")
    return self:getObjectGroup(groupName)
end
rawset(CCTMXTiledMap,"objectGroupNamed", CCTMXTiledMapDeprecated.objectGroupNamed)
--functions of CCTMXTiledMap will be deprecated end


--functions of CCTMXMapInfo will be deprecated begin
local CCTMXMapInfoDeprecated = { }
function CCTMXMapInfoDeprecated.getStoringCharacters(self)
    deprecatedTip("CCTMXMapInfo:getStoringCharacters","CCTMXMapInfo:isStoringCharacters")
    return self:isStoringCharacters()
end
rawset(CCTMXMapInfo,"getStoringCharacters", CCTMXMapInfoDeprecated.getStoringCharacters)

function CCTMXMapInfoDeprecated.formatWithTMXFile(infoTable,tmxFile)
    deprecatedTip("CCTMXMapInfo:formatWithTMXFile","CCTMXMapInfo:create")
    return CCTMXMapInfo:create(tmxFile)
end
rawset(CCTMXMapInfo,"formatWithTMXFile", CCTMXMapInfoDeprecated.formatWithTMXFile)

function CCTMXMapInfoDeprecated.formatWithXML(infoTable,tmxString,resourcePath)
    deprecatedTip("CCTMXMapInfo:formatWithXML","TMXMapInfo:createWithXML")
    return CCTMXMapInfo:createWithXML(tmxString,resourcePath)
end
rawset(CCTMXMapInfo,"formatWithXML", CCTMXMapInfoDeprecated.formatWithXML)
--functions of CCTMXMapInfo will be deprecated end


--functions of CCTMXObject will be deprecated begin
local CCTMXObjectGroupDeprecated = { }
function CCTMXObjectGroupDeprecated.propertyNamed(self,propertyName)
    deprecatedTip("CCTMXObjectGroup:propertyNamed","CCTMXObjectGroup:getProperty")
    return self:getProperty(propertyName)
end
rawset(CCTMXObjectGroup,"propertyNamed", CCTMXObjectGroupDeprecated.propertyNamed)

function CCTMXObjectGroupDeprecated.objectNamed(self, objectName)
    deprecatedTip("CCTMXObjectGroup:objectNamed","CCTMXObjectGroup:getObject")
    return self:getObject(objectName)
end
rawset(CCTMXObjectGroup,"objectNamed", CCTMXObjectGroupDeprecated.objectNamed)
--functions of CCTMXObject will be deprecated end


--functions of WebSocket will be deprecated begin
local targetPlatform = CCApplication:getInstance():getTargetPlatform()
if (kTargetIphone == targetPlatform) or (kTargetIpad == targetPlatform) or (kTargetAndroid == targetPlatform) or (kTargetWindows == targetPlatform) then
    local WebSocketDeprecated = { }
    function WebSocketDeprecated.sendTextMsg(self, string)
        deprecatedTip("WebSocket:sendTextMsg","WebSocket:sendString")
        return self:sendString(string)
    end
    rawset(WebSocket,"sendTextMsg", WebSocketDeprecated.sendTextMsg)

    function WebSocketDeprecated.sendBinaryMsg(self, table,tablesize)
        deprecatedTip("WebSocket:sendBinaryMsg","WebSocket:sendString")
        string.char(unpack(table))
        return self:sendString(string.char(unpack(table)))
    end
    rawset(WebSocket,"sendBinaryMsg", WebSocketDeprecated.sendBinaryMsg)
end
--functions of WebSocket will be deprecated end


--functions of CCDrawPrimitives will be deprecated begin
local CCDrawPrimitivesDeprecated = { }
function CCDrawPrimitivesDeprecated.ccDrawPoint(pt)
    deprecatedTip("ccDrawPoint","CCDrawPrimitives.ccDrawPoint")
    return CCDrawPrimitives.ccDrawPoint(pt)
end
rawset(_G, "ccDrawPoint", CCDrawPrimitivesDeprecated.ccDrawPoint)

function CCDrawPrimitivesDeprecated.ccDrawLine(origin,destination)
    deprecatedTip("ccDrawLine","CCDrawPrimitives.ccDrawLine")
    return CCDrawPrimitives.ccDrawLine(origin,destination)
end
rawset(_G, "ccDrawLine", CCDrawPrimitivesDeprecated.ccDrawLine)

function CCDrawPrimitivesDeprecated.ccDrawRect(origin,destination)
    deprecatedTip("ccDrawRect","CCDrawPrimitives.ccDrawRect")
    return CCDrawPrimitives.ccDrawRect(origin,destination)
end
rawset(_G, "ccDrawRect", CCDrawPrimitivesDeprecated.ccDrawRect)

function CCDrawPrimitivesDeprecated.ccDrawSolidRect(origin,destination,color)
    deprecatedTip("ccDrawSolidRect","CCDrawPrimitives.ccDrawSolidRect")
    return CCDrawPrimitives.ccDrawSolidRect(origin,destination,color)
end
rawset(_G, "ccDrawSolidRect", CCDrawPrimitivesDeprecated.ccDrawSolidRect)

-- params:... may represent two param(xScale,yScale) or nil
function CCDrawPrimitivesDeprecated.ccDrawCircle(center,radius,angle,segments,drawLineToCenter,...)
    deprecatedTip("ccDrawCircle","CCDrawPrimitives.ccDrawCircle")
    return CCDrawPrimitives.ccDrawCircle(center,radius,angle,segments,drawLineToCenter,...)
end
rawset(_G, "ccDrawCircle", CCDrawPrimitivesDeprecated.ccDrawCircle)

-- params:... may represent two param(xScale,yScale) or nil
function CCDrawPrimitivesDeprecated.ccDrawSolidCircle(center,radius,angle,segments,...)
    deprecatedTip("ccDrawSolidCircle","CCDrawPrimitives.ccDrawSolidCircle")
    return CCDrawPrimitives.ccDrawSolidCircle(center,radius,angle,segments,...)
end
rawset(_G, "ccDrawSolidCircle", CCDrawPrimitivesDeprecated.ccDrawSolidCircle)

function CCDrawPrimitivesDeprecated.ccDrawQuadBezier(origin,control,destination,segments)
    deprecatedTip("ccDrawQuadBezier","CCDrawPrimitives.ccDrawQuadBezier")
    return CCDrawPrimitives.ccDrawQuadBezier(origin,control,destination,segments)
end
rawset(_G, "ccDrawQuadBezier", CCDrawPrimitivesDeprecated.ccDrawQuadBezier)

function CCDrawPrimitivesDeprecated.ccDrawCubicBezier(origin,control1,control2,destination,segments)
    deprecatedTip("ccDrawCubicBezier","CCDrawPrimitives.ccDrawCubicBezier")
    return CCDrawPrimitives.ccDrawCubicBezier(origin,control1,control2,destination,segments)
end
rawset(_G, "ccDrawCubicBezier", CCDrawPrimitivesDeprecated.ccDrawCubicBezier)

function CCDrawPrimitivesDeprecated.ccDrawCatmullRom(arrayOfControlPoints,segments)
    deprecatedTip("ccDrawCatmullRom","CCDrawPrimitives.ccDrawCatmullRom")
    return CCDrawPrimitives.ccDrawCatmullRom(arrayOfControlPoints,segments)
end
rawset(_G, "ccDrawCatmullRom", CCDrawPrimitivesDeprecated.ccDrawCatmullRom)

function CCDrawPrimitivesDeprecated.ccDrawCardinalSpline(config,tension,segments)
    deprecatedTip("ccDrawCardinalSpline","CCDrawPrimitives.ccDrawCardinalSpline")
    return CCDrawPrimitives.ccDrawCardinalSpline(config,tension,segments)
end
rawset(_G, "ccDrawCardinalSpline", CCDrawPrimitivesDeprecated.ccDrawCardinalSpline)

function CCDrawPrimitivesDeprecated.ccDrawColor4B(r,g,b,a)
    deprecatedTip("ccDrawColor4B","CCDrawPrimitives.ccDrawColor4B")
    return CCDrawPrimitives.ccDrawColor4B(r,g,b,a)
end
rawset(_G, "ccDrawColor4B", CCDrawPrimitivesDeprecated.ccDrawColor4B)

function CCDrawPrimitivesDeprecated.ccDrawColor4F(r,g,b,a)
    deprecatedTip("ccDrawColor4F","CCDrawPrimitives.ccDrawColor4F")
    return CCDrawPrimitives.ccDrawColor4F(r,g,b,a)
end
rawset(_G, "ccDrawColor4F", CCDrawPrimitivesDeprecated.ccDrawColor4F)

function CCDrawPrimitivesDeprecated.ccPointSize(pointSize)
    deprecatedTip("ccPointSize","CCDrawPrimitives.ccPointSize")
    return CCDrawPrimitives.ccPointSize(pointSize)
end
rawset(_G, "ccPointSize", CCDrawPrimitivesDeprecated.ccPointSize)
--functions of CCDrawPrimitives will be deprecated end

--enums of CCParticleSystem will be deprecated begin
_G["kParticleStartSizeEqualToEndSize"] = _G["kCCParticleStartSizeEqualToEndSize"]
_G["kParticleDurationInfinity"] = _G["kCCParticleDurationInfinity"]
--enums of CCParticleSystem will be deprecated end

--enums of CCRenderTexture will be deprecated begin
local CCRenderTextureDeprecated = { }
function CCRenderTextureDeprecated.newCCImage(self)
    deprecatedTip("CCRenderTexture:newCCImage","CCRenderTexture:newImage")
    return self:newImage()
end
rawset(CCRenderTexture, "newCCImage", CCRenderTextureDeprecated.newCCImage)
--enums of CCRenderTexture will be deprecated end
