
--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--functions of CCDirector will be deprecated,begin
local CCDirectorDeprecated = { }
function CCDirectorDeprecated.sharedDirector()
    deprecatedTip("CCDirector:sharedDirector","cc.Director:getInstance")
    return cc.Director:getInstance()
end
CCDirector.sharedDirector = CCDirectorDeprecated.sharedDirector
--functions of CCDirector will be deprecated,end


--functions of CCTextureCache will be deprecated begin
local TextureCacheDeprecated = {}
function TextureCacheDeprecated.getInstance(self)
    deprecatedTip("cc.TextureCache:getInstance","cc.Director:getInstance():getTextureCache")
    return cc.Director:getInstance():getTextureCache()
end
cc.TextureCache.getInstance = TextureCacheDeprecated.getInstance

function TextureCacheDeprecated.destroyInstance(self)
    deprecatedTip("cc.TextureCache:destroyInstance","cc.Director:getInstance():destroyTextureCache")
    return cc.Director:getInstance():destroyTextureCache()
end
cc.TextureCache.destroyInstance = TextureCacheDeprecated.destroyInstance

function TextureCacheDeprecated.dumpCachedTextureInfo(self)
    deprecatedTip("self:dumpCachedTextureInfo","self:getCachedTextureInfo")
    return print(self:getCachedTextureInfo())
end
cc.TextureCache.dumpCachedTextureInfo = TextureCacheDeprecated.dumpCachedTextureInfo

local CCTextureCacheDeprecated = { }
function CCTextureCacheDeprecated.sharedTextureCache()
    deprecatedTip("CCTextureCache:sharedTextureCache","CCTextureCache:getInstance")
    return cc.TextureCache:getInstance()
end
rawset(CCTextureCache,"sharedTextureCache",CCTextureCacheDeprecated.sharedTextureCache)

function CCTextureCacheDeprecated.purgeSharedTextureCache()
    deprecatedTip("CCTextureCache:purgeSharedTextureCache","CCTextureCache:destroyInstance")
    return cc.TextureCache:destroyInstance()
end
rawset(CCTextureCache,"purgeSharedTextureCache",CCTextureCacheDeprecated.purgeSharedTextureCache)

function CCTextureCacheDeprecated.addUIImage(self, image, key)
    deprecatedTip("CCTextureCache:addUIImage","CCTextureCache:addImage")
    return self:addImage(image,key)
end
CCTextureCache.addUIImage = CCTextureCacheDeprecated.addUIImage
--functions of CCTextureCache will be deprecated end

--functions of CCAnimation will be deprecated begin
local CCAnimationDeprecated = {}
function CCAnimationDeprecated.addSpriteFrameWithFileName(self,...)
    deprecatedTip("CCAnimationDeprecated:addSpriteFrameWithFileName","cc.Animation:addSpriteFrameWithFile")
    return self:addSpriteFrameWithFile(...)
end
CCAnimation.addSpriteFrameWithFileName = CCAnimationDeprecated.addSpriteFrameWithFileName
--functions of CCAnimation will be deprecated end


--functions of CCAnimationCache will be deprecated begin
local CCAnimationCacheDeprecated = { }
function CCAnimationCacheDeprecated.sharedAnimationCache()
    deprecatedTip("CCAnimationCache:sharedAnimationCache","CCAnimationCache:getInstance")
    return CCAnimationCache:getInstance()
end
CCAnimationCache.sharedAnimationCache = CCAnimationCacheDeprecated.sharedAnimationCache

function CCAnimationCacheDeprecated.purgeSharedAnimationCache()
    deprecatedTip("CCAnimationCache:purgeSharedAnimationCache","CCAnimationCache:destroyInstance")
    return CCAnimationCache:destroyInstance()
end
CCAnimationCache.purgeSharedAnimationCache = CCAnimationCacheDeprecated.purgeSharedAnimationCache

function CCAnimationCacheDeprecated.addAnimationsWithFile(self,...)
    deprecatedTip("CCAnimationCache:addAnimationsWithFile","cc.AnimationCache:addAnimations")
    return self:addAnimations(...)
end
CCAnimationCache.addAnimationsWithFile = CCAnimationCacheDeprecated.addAnimationsWithFile

function CCAnimationCacheDeprecated.animationByName(self,...)
    deprecatedTip("CCAnimationCache:animationByName","cc.AnimationCache:getAnimation")
    return self:getAnimation(...)
end
CCAnimationCache.animationByName = CCAnimationCacheDeprecated.animationByName

function CCAnimationCacheDeprecated.removeAnimationByName(self)
    deprecatedTip("CCAnimationCache:removeAnimationByName","cc.AnimationCache:removeAnimation")
    return self:removeAnimation()
end
CCAnimationCache.removeAnimationByName = CCAnimationCacheDeprecated.removeAnimationByName
--functions of CCAnimationCache will be deprecated end

--functions of CCFileUtils will be deprecated end
local CCFileUtilsDeprecated = { }
function CCFileUtilsDeprecated.sharedFileUtils()
    deprecatedTip("CCFileUtils:sharedFileUtils","CCFileUtils:getInstance")
    return cc.FileUtils:getInstance()
end
CCFileUtils.sharedFileUtils = CCFileUtilsDeprecated.sharedFileUtils

function CCFileUtilsDeprecated.purgeFileUtils()
    deprecatedTip("CCFileUtils:purgeFileUtils","CCFileUtils:destroyInstance")
    return cc.FileUtils:destroyInstance()
end
CCFileUtils.purgeFileUtils = CCFileUtilsDeprecated.purgeFileUtils
--functions of CCFileUtils will be deprecated end

--functions of CCMenu will be deprecated begin
local CCMenuDeprecated = { }
function CCMenuDeprecated.createWithItem(self,...)
    deprecatedTip("CCMenuDeprecated:createWithItem","cc.Menu:createWithItem")
    return self:create(...)
end
CCMenu.createWithItem = CCMenuDeprecated.createWithItem

function CCMenuDeprecated.setHandlerPriority(self)
    print("\n********** \n".."setHandlerPriority was deprecated in 3.0. \n**********")
end
CCMenu.setHandlerPriority = CCMenuDeprecated.setHandlerPriority
--functions of CCMenu will be deprecated end

--functions of CCNode will be deprecated begin
local CCNodeDeprecated = { }

function CCNodeDeprecated.boundingBox(self)
    deprecatedTip("CCNode:boundingBox","cc.Node:getBoundingBox")
    return self:getBoundingBox()
end
CCNode.boundingBox = CCNodeDeprecated.boundingBox


function CCNodeDeprecated.numberOfRunningActions(self)
    deprecatedTip("CCNode:numberOfRunningActions","cc.Node:getNumberOfRunningActions")
    return self:getNumberOfRunningActions()
end
CCNode.numberOfRunningActions = CCNodeDeprecated.numberOfRunningActions


function CCNodeDeprecated.removeFromParentAndCleanup(self,...)
    deprecatedTip("CCNode:removeFromParentAndCleanup","cc.Node:removeFromParent")
    return self:removeFromParent(...)
end
CCNode.removeFromParentAndCleanup = CCNodeDeprecated.removeFromParentAndCleanup
--functions of CCNode will be deprecated end

--CCDrawPrimitives will be deprecated begin
local function CCDrawPrimitivesClassDeprecated()
    deprecatedTip("CCDrawPrimitives","cc.DrawPrimitives")
    return cc.DrawPrimitives
end
_G.CCDrawPrimitives = CCDrawPrimitivesClassDeprecated()
--functions of CCDrawPrimitives will be deprecated begin
local CCDrawPrimitivesDeprecated = { }
function CCDrawPrimitivesDeprecated.ccDrawPoint(pt)
    deprecatedTip("ccDrawPoint","cc.DrawPrimitives.drawPoint")
    return cc.DrawPrimitives.drawPoint(pt)
end
_G.ccDrawPoint = CCDrawPrimitivesDeprecated.ccDrawPoint

function CCDrawPrimitivesDeprecated.ccDrawLine(origin,destination)
    deprecatedTip("ccDrawLine","cc.DrawPrimitives.drawLine")
    return cc.DrawPrimitives.drawLine(origin,destination)
end
_G.ccDrawLine = CCDrawPrimitivesDeprecated.ccDrawLine

function CCDrawPrimitivesDeprecated.ccDrawRect(origin,destination)
    deprecatedTip("ccDrawRect","cc.DrawPrimitives.drawRect")
    return cc.DrawPrimitives.drawRect(origin,destination)
end
_G.ccDrawRect = CCDrawPrimitivesDeprecated.ccDrawRect

function CCDrawPrimitivesDeprecated.ccDrawSolidRect(origin,destination,color)
    deprecatedTip("ccDrawSolidRect","cc.DrawPrimitives.drawSolidRect")
    return cc.DrawPrimitives.drawSolidRect(origin,destination,color)
end
_G.ccDrawSolidRect = CCDrawPrimitivesDeprecated.ccDrawSolidRect

-- params:... may represent two param(xScale,yScale) or nil
function CCDrawPrimitivesDeprecated.ccDrawCircle(center,radius,angle,segments,drawLineToCenter,...)
    deprecatedTip("ccDrawCircle","cc.DrawPrimitives.drawCircle")
    return cc.DrawPrimitives.drawCircle(center,radius,angle,segments,drawLineToCenter,...)
end
_G.ccDrawCircle = CCDrawPrimitivesDeprecated.ccDrawCircle

-- params:... may represent two param(xScale,yScale) or nil
function CCDrawPrimitivesDeprecated.ccDrawSolidCircle(center,radius,angle,segments,...)
    deprecatedTip("ccDrawSolidCircle","cc.DrawPrimitives.drawSolidCircle")
    return cc.DrawPrimitives.drawSolidCircle(center,radius,angle,segments,...)
end
_G.ccDrawSolidCircle = CCDrawPrimitivesDeprecated.ccDrawSolidCircle

function CCDrawPrimitivesDeprecated.ccDrawQuadBezier(origin,control,destination,segments)
    deprecatedTip("ccDrawQuadBezier","cc.DrawPrimitives.drawQuadBezier")
    return cc.DrawPrimitives.drawQuadBezier(origin,control,destination,segments)
end
_G.ccDrawQuadBezier = CCDrawPrimitivesDeprecated.ccDrawQuadBezier

function CCDrawPrimitivesDeprecated.ccDrawCubicBezier(origin,control1,control2,destination,segments)
    deprecatedTip("ccDrawCubicBezier","cc.DrawPrimitives.drawCubicBezier")
    return cc.DrawPrimitives.drawCubicBezier(origin,control1,control2,destination,segments)
end
_G.ccDrawCubicBezier = CCDrawPrimitivesDeprecated.ccDrawCubicBezier

function CCDrawPrimitivesDeprecated.ccDrawCatmullRom(arrayOfControlPoints,segments)
    deprecatedTip("ccDrawCatmullRom","cc.DrawPrimitives.drawCatmullRom")
    return cc.DrawPrimitives.drawCatmullRom(arrayOfControlPoints,segments)
end
_G.ccDrawCatmullRom = CCDrawPrimitivesDeprecated.ccDrawCatmullRom

function CCDrawPrimitivesDeprecated.ccDrawCardinalSpline(config,tension,segments)
    deprecatedTip("ccDrawCardinalSpline","cc.DrawPrimitives.drawCardinalSpline")
    return cc.DrawPrimitives.drawCardinalSpline(config,tension,segments)
end
_G.ccDrawCardinalSpline = CCDrawPrimitivesDeprecated.ccDrawCardinalSpline

function CCDrawPrimitivesDeprecated.ccDrawColor4B(r,g,b,a)
    deprecatedTip("ccDrawColor4B","cc.DrawPrimitives.drawColor4B")
    return cc.DrawPrimitives.drawColor4B(r,g,b,a)
end
_G.ccDrawColor4B = CCDrawPrimitivesDeprecated.ccDrawColor4B

function CCDrawPrimitivesDeprecated.ccDrawColor4F(r,g,b,a)
    deprecatedTip("ccDrawColor4F","cc.DrawPrimitives.drawColor4F")
    return cc.DrawPrimitives.drawColor4F(r,g,b,a)
end
_G.ccDrawColor4F = CCDrawPrimitivesDeprecated.ccDrawColor4F

function CCDrawPrimitivesDeprecated.ccPointSize(pointSize)
    deprecatedTip("ccPointSize","cc.DrawPrimitives.setPointSize")
    return cc.DrawPrimitives.setPointSize(pointSize)
end
_G.ccPointSize = CCDrawPrimitivesDeprecated.ccPointSize
--functions of CCDrawPrimitives will be deprecated end
--CCDrawPrimitives will be deprecated end

local CCProgressTimerDeprecated = {}
function CCProgressTimerDeprecated.setReverseProgress(self,...)
    deprecatedTip("CCProgressTimer","CCProgressTimer:setReverseDirection")
    return self:setReverseDirection(...)
end
CCProgressTimer.setReverseProgress = CCProgressTimerDeprecated.setReverseProgress

--functions of CCSpriteFrameCache will be deprecated begin
local CCSpriteFrameCacheDeprecated = { }
function CCSpriteFrameCacheDeprecated.spriteFrameByName(self,szName)
    deprecatedTip("CCSpriteFrameCache:spriteFrameByName","CCSpriteFrameCache:getSpriteFrameByName")
    return self:getSpriteFrameByName(szName)
end
CCSpriteFrameCache.spriteFrameByName = CCSpriteFrameCacheDeprecated.spriteFrameByName

function CCSpriteFrameCacheDeprecated.sharedSpriteFrameCache()
    deprecatedTip("CCSpriteFrameCache:sharedSpriteFrameCache","CCSpriteFrameCache:getInstance")
    return CCSpriteFrameCache:getInstance()
end
CCSpriteFrameCache.sharedSpriteFrameCache = CCSpriteFrameCacheDeprecated.sharedSpriteFrameCache

function CCSpriteFrameCacheDeprecated.purgeSharedSpriteFrameCache()
    deprecatedTip("CCSpriteFrameCache:purgeSharedSpriteFrameCache","CCSpriteFrameCache:destroyInstance")
    return CCSpriteFrameCache:destroyInstance()
end
CCSpriteFrameCache.purgeSharedSpriteFrameCache = CCSpriteFrameCacheDeprecated.purgeSharedSpriteFrameCache

function CCSpriteFrameCacheDeprecated.addSpriteFramesWithFile(self,...)
    deprecatedTip("CCSpriteFrameCache:addSpriteFramesWithFile","CCSpriteFrameCache:addSpriteFrames")
    return self:addSpriteFrames(...)
end
rawset(CCSpriteFrameCache,"addSpriteFramesWithFile",CCSpriteFrameCacheDeprecated.addSpriteFramesWithFile)

function CCSpriteFrameCacheDeprecated.getSpriteFrameByName(self,...)
    deprecatedTip("CCSpriteFrameCache:getSpriteFrameByName","CCSpriteFrameCache:getSpriteFrame")
    return self:getSpriteFrame(...)
end
CCSpriteFrameCache.getSpriteFrameByName = CCSpriteFrameCacheDeprecated.getSpriteFrameByName
--functions of CCSpriteFrameCache will be deprecated end

--functions of CCLabelAtlas will be deprecated begin
local CCLabelAtlasDeprecated = {}
function CCLabelAtlasDeprecated.create(self,...)
    deprecatedTip("CCLabelAtlas:create","CCLabelAtlas:_create")
    return self:_create(...)
end
CCLabelAtlas.create = CCLabelAtlasDeprecated.create
--functions of CCLabelAtlas will be deprecated end


---------------------------
--global functions wil be deprecated, begin
local function CCRectMake(x,y,width,height)
    deprecatedTip("CCRectMake(x,y,width,height)","cc.rect(x,y,width,height) in lua")
    return cc.rect(x,y,width,height)
end
_G.CCRectMake = CCRectMake

local function ccc3(r,g,b)
    deprecatedTip("ccc3(r,g,b)","cc.c3b(r,g,b)")
    return cc.c3b(r,g,b)
end
_G.ccc3 = ccc3

local function ccp(x,y)
    deprecatedTip("ccp(x,y)","cc.p(x,y)")
    return cc.p(x,y)
end
_G.ccp = ccp

local function CCSizeMake(width,height)
    deprecatedTip("CCSizeMake(width,height)","cc.size(width,height)")
    return cc.size(width,height)
end
_G.CCSizeMake = CCSizeMake

local function ccc4(r,g,b,a)
    deprecatedTip("ccc4(r,g,b,a)","cc.c4b(r,g,b,a)")
    return cc.c4b(r,g,b,a)
end
_G.ccc4 = ccc4

local function ccc4FFromccc3B(color3B)
    deprecatedTip("ccc4FFromccc3B(color3B)","cc.c4f(color3B.r / 255.0,color3B.g / 255.0,color3B.b / 255.0,1.0)")
    return cc.c4f(color3B.r/255.0, color3B.g/255.0, color3B.b/255.0, 1.0)
end
_G.ccc4FFromccc3B = ccc4FFromccc3B

local function ccc4f(r,g,b,a)
    deprecatedTip("ccc4f(r,g,b,a)","cc.c4f(r,g,b,a)")
    return cc.c4f(r,g,b,a)
end
_G.ccc4f = ccc4f

local function ccc4FFromccc4B(color4B)
    deprecatedTip("ccc4FFromccc4B(color4B)","cc.c4f(color4B.r/255.0, color4B.g/255.0, color4B.b/255.0, color4B.a/255.0)")
    return cc.c4f(color4B.r/255.0, color4B.g/255.0, color4B.b/255.0, color4B.a/255.0)
end
_G.ccc4FFromccc4B = ccc4FFromccc4B

local function ccc4FEqual(a,b)
    deprecatedTip("ccc4FEqual(a,b)","a:equals(b)")
    return a:equals(b)
end
_G.ccc4FEqual = ccc4FEqual
--global functions wil be deprecated, end


--functions of _G will be deprecated begin
local function ccpLineIntersect(a,b,c,d,s,t)
    deprecatedTip("ccpLineIntersect","cc.pIsLineIntersect")
    return cc.pIsLineIntersect(a,b,c,d,s,t)
end
_G.ccpLineIntersect = ccpLineIntersect


local function CCPointMake(x,y)
    deprecatedTip("CCPointMake(x,y)","cc.p(x,y)")
    return cc.p(x,y)
end
_G.CCPointMake = CCPointMake



local function ccpNeg(pt)
    deprecatedTip("ccpNeg","cc.pSub")
    return cc.pSub({x = 0,y = 0}, pt)
end
_G.ccpNeg = ccpNeg

local function ccpAdd(pt1,pt2)
    deprecatedTip("ccpAdd","cc.pAdd")
    return cc.pAdd(pt1,pt2)
end
_G.ccpAdd = ccpAdd

local function ccpSub(pt1,pt2)
    deprecatedTip("ccpSub","cc.pSub")
    return cc.pSub(pt1,pt2)
end
_G.ccpSub = ccpSub

local function ccpMult(pt,factor)
    deprecatedTip("ccpMult","cc.pMul")
    return cc.pMul(pt,factor)
end
_G.ccpMult = ccpMult

local function ccpMidpoint(pt1,pt2)
    deprecatedTip("ccpMidpoint","cc.pMidpoint")
    return cc.pMidpoint(pt1,pt2)
end
_G.ccpMidpoint = ccpMidpoint

local function ccpDot(pt1,pt2)
    deprecatedTip("ccpDot","cc.pDot")
    return cc.pDot(pt1,pt2)
end
_G.ccpDot = ccpDot

local function ccpCross(pt1,pt2)
    deprecatedTip("ccpCross","cc.pCross")
    return cc.pCross(pt1, pt2)
end
_G.ccpCross = ccpCross

local function ccpPerp(pt)
    deprecatedTip("ccpPerp","cc.pPerp")
    return cc.pPerp(pt)
end
_G.ccpPerp = ccpPerp

local function ccpRPerp(pt)
    deprecatedTip("ccpRPerp","cc.RPerp")
    return cc.RPerp(pt)
end
_G.ccpRPerp = ccpRPerp

local function ccpProject(pt1,pt2)
    deprecatedTip("ccpProject","cc.pProject")
    return cc.pProject(pt1,pt2)
end
_G.ccpProject = ccpProject

local function ccpRotate(pt1,pt2)
    deprecatedTip("ccpRotate","cc.pRotate")
    return cc.pRotate(pt1,pt2)
end
_G.ccpRotate = ccpRotate

local function ccpUnrotate(pt1,pt2)
    deprecatedTip("ccpUnrotate","cc.pUnrotate")
    return cc.pUnrotate(pt1,pt2)
end
_G.ccpUnrotate = ccpUnrotate

local function ccpLengthSQ(pt)
    deprecatedTip("ccpLengthSQ","cc.pLengthSQ")
    return cc.pLengthSQ(pt)
end
_G.ccpLengthSQ = ccpLengthSQ

local function ccpDistanceSQ(pt1,pt2)
    deprecatedTip("ccpDistanceSQ","cc.pDistanceSQ")
    return cc.pDistanceSQ(pt1,pt2)
end
_G.ccpDistanceSQ = ccpDistanceSQ

local function ccpLength(pt)
    deprecatedTip("ccpLength","cc.pGetLength")
    return cc.pGetLength(pt)
end
_G.ccpLength = ccpLength

local function ccpDistance(pt1,pt2)
    deprecatedTip("ccpDistance","cc.pGetDistance")
    return cc.pGetDistance(pt1, pt2)
end
_G.ccpDistance = ccpDistance

local function ccpNormalize(pt)
    deprecatedTip("ccpNormalize","cc.pNormalize")
    return cc.pNormalize(pt)
end
_G.ccpNormalize = ccpNormalize

local function ccpForAngle(angle)
    deprecatedTip("ccpForAngle","cc.pForAngle")
    return cc.pForAngle(angle)
end
_G.ccpForAngle = ccpForAngle

local function ccpToAngle(pt)
    deprecatedTip("ccpToAngle","cc.pToAngleSelf")
    return cc.pToAngleSelf(pt)
end
_G.ccpToAngle = ccpToAngle

local function ccpClamp(pt1,pt2,pt3)
    deprecatedTip("ccpClamp","cc.pGetClampPoint")
    return cc.pGetClampPoint(pt1,pt2,pt3)
end
_G.ccpClamp = ccpClamp


local function ccpFromSize(sz)
    deprecatedTip("ccpFromSize(sz)","cc.pFromSize")
    return cc.pFromSize(sz)
end
_G.ccpFromSize = ccpFromSize

local function ccpLerp(pt1,pt2,alpha)
    deprecatedTip("ccpLerp","cc.pLerp")
    return cc.pLerp(pt1,pt2,alpha)
end
_G.ccpLerp = ccpLerp

local function ccpFuzzyEqual(pt1,pt2,variance)
    deprecatedTip("ccpFuzzyEqual","cc.pFuzzyEqual")
    return cc.pFuzzyEqual(pt1,pt2,variance)
end
_G.ccpFuzzyEqual = ccpFuzzyEqual

local function ccpCompMult(pt1,pt2)
    deprecatedTip("ccpCompMult","cc.p")
    return cc.p(pt1.x * pt2.x , pt1.y * pt2.y)
end
_G.ccpCompMult = ccpCompMult

local function ccpAngleSigned(pt1,pt2)
    deprecatedTip("ccpAngleSigned","cc.pGetAngle")
    return cc.pGetAngle(pt1, pt2)
end
_G.ccpAngleSigned = ccpAngleSigned

local function ccpAngle(pt1,pt2)
    deprecatedTip("ccpAngle","cc.pGetAngle")
    return cc.pGetAngle(pt1,ptw)
end
_G.ccpAngle = ccpAngle

local function ccpRotateByAngle(pt1,pt2,angle)
    deprecatedTip("ccpRotateByAngle","cc.pRotateByAngle")
    return cc.pRotateByAngle(pt1, pt2, angle)
end
_G.ccpRotateByAngle = ccpRotateByAngle

local function ccpSegmentIntersect(pt1,pt2,pt3,pt4)
    deprecatedTip("ccpSegmentIntersect","cc.pIsSegmentIntersect")
    return cc.pIsSegmentIntersect(pt1,pt2,pt3,pt4)
end
_G.ccpSegmentIntersect = ccpSegmentIntersect

local function ccpIntersectPoint(pt1,pt2,pt3,pt4)
    deprecatedTip("ccpIntersectPoint","cc.pGetIntersectPoint")
    return cc.pGetIntersectPoint(pt1,pt2,pt3,pt4)
end
_G.ccpIntersectPoint = ccpIntersectPoint


local function vertex2(x,y)
    deprecatedTip("vertex2(x,y)","cc.vertex2F(x,y)")
    return cc.vertex2F(x,y)
end
_G.vertex2 = vertex2

local function vertex3(x,y,z)
    deprecatedTip("vertex3(x,y,z)","cc.Vertex3F(x,y,z)")
    return cc.Vertex3F(x,y,z)
end
_G.vertex3 = vertex3

local function tex2(u,v)
    deprecatedTip("tex2(u,v)","cc.tex2f(u,v)")
    return cc.tex2f(u,v)
end
_G.tex2 = tex2

local function ccc4BFromccc4F(color4F)
    deprecatedTip("ccc4BFromccc4F(color4F)","Color4B(color4F.r * 255.0, color4F.g * 255.0, color4F.b * 255.0, color4B.a * 255.0)")
    return Color4B(color4F.r * 255.0, color4F.g * 255.0, color4F.b * 255.0, color4B.a * 255.0)
end
_G.ccc4BFromccc4F = ccc4BFromccc4F

local function ccColor3BDeprecated()
    deprecatedTip("ccColor3B","cc.c3b(0,0,0)")
    return cc.c3b(0,0,0)
end
_G.ccColor3B = ccColor3BDeprecated

local function ccColor4BDeprecated()
    deprecatedTip("ccColor4B","cc.c4b(0,0,0,0)")
    return cc.c4b(0,0,0,0)
end
_G.ccColor4B = ccColor4BDeprecated

local function ccColor4FDeprecated()
    deprecatedTip("ccColor4F","cc.c4f(0.0,0.0,0.0,0.0)")
    return cc.c4f(0.0,0.0,0.0,0.0)
end
_G.ccColor4F = ccColor4FDeprecated

local function ccVertex2FDeprecated()
    deprecatedTip("ccVertex2F","cc.vertex2F(0.0,0.0)")
    return cc.vertex2F(0.0,0.0)
end
_G.ccVertex2F = ccVertex2FDeprecated

local function ccVertex3FDeprecated()
    deprecatedTip("ccVertex3F","cc.Vertex3F(0.0, 0.0, 0.0)")
    return cc.Vertex3F(0.0, 0.0, 0.0)
end
_G.ccVertex3F = ccVertex3FDeprecated

local function ccTex2FDeprecated()
    deprecatedTip("ccTex2F","cc.tex2F(0.0, 0.0)")
    return cc.tex2F(0.0, 0.0)
end
_G.ccTex2F = ccTex2FDeprecated

local function ccPointSpriteDeprecated()
    deprecatedTip("ccPointSprite","cc.PointSprite(cc.vertex2F(0.0, 0.0),cc.c4b(0.0, 0.0, 0.0),0)")
    return cc.PointSprite(cc.vertex2F(0.0, 0.0),cc.c4b(0.0, 0.0, 0.0),0)
end
_G.ccPointSprite = ccPointSpriteDeprecated

local function ccQuad2Deprecated()
    deprecatedTip("ccQuad2","cc.Quad2(cc.vertex2F(0.0, 0.0), cc.vertex2F(0.0, 0.0), cc.vertex2F(0.0, 0.0), cc.vertex2F(0.0, 0.0))")
    return cc.Quad2(cc.vertex2F(0.0, 0.0), cc.vertex2F(0.0, 0.0), cc.vertex2F(0.0, 0.0), cc.vertex2F(0.0, 0.0))
end
_G.ccQuad2 = ccQuad2Deprecated

local function ccQuad3Deprecated()
    deprecatedTip("ccQuad3","cc.Quad3(cc.Vertex3F(0.0, 0.0 ,0.0), cc.Vertex3F(0.0, 0.0 ,0.0), cc.Vertex3F(0.0, 0.0 ,0.0), cc.Vertex3F(0.0, 0.0 ,0.0))")
    return cc.Quad3(cc.Vertex3F(0.0, 0.0 ,0.0), cc.Vertex3F(0.0, 0.0 ,0.0), cc.Vertex3F(0.0, 0.0 ,0.0), cc.Vertex3F(0.0, 0.0 ,0.0))
end
_G.ccQuad3 = ccQuad3Deprecated

local function ccV2FC4BT2FDeprecated()
    deprecatedTip("ccV2F_C4B_T2F","cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0))")
    return cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0))
end
_G.ccV2F_C4B_T2F = ccV2FC4BT2FDeprecated


local function ccV2FC4FT2FDeprecated()
    deprecatedTip("ccV2F_C4F_T2F","cc.V2F_C4F_T2F(cc.vertex2F(0.0, 0.0), cc.c4f(0.0 , 0.0 , 0.0 , 0.0 ), cc.tex2F(0.0, 0.0))")
    return cc.V2F_C4F_T2F(cc.vertex2F(0.0, 0.0), cc.c4f(0.0 , 0.0 , 0.0 , 0.0), cc.tex2F(0.0, 0.0))
end
_G.ccV2F_C4F_T2F = ccV2FC4FT2FDeprecated

local function ccV3FC4BT2FDeprecated()
    deprecatedTip("ccV3F_C4B_T2F","cc.V3F_C4B_T2F(cc.vertex3F(0.0, 0.0, 0.0), cc.c4b(0 , 0 , 0, 0 ), cc.tex2F(0.0, 0.0))")
    return cc.V3F_C4B_T2F(cc.vertex3F(0.0, 0.0, 0.0), cc.c4b(0 , 0 , 0, 0 ), cc.tex2F(0.0, 0.0))
end
_G.ccV3F_C4B_T2F = ccV3FC4BT2FDeprecated

local function ccV2FC4BT2FQuadDeprecated()
    deprecatedTip("ccV2F_C4B_T2F_Quad","cc.V2F_C4B_T2F_Quad(cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)))")
    return cc.V2F_C4B_T2F_Quad(cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V2F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)))
end
_G.ccV2F_C4B_T2F_Quad = ccV2FC4BT2FQuadDeprecated

local function ccV3FC4BT2FQuadDeprecated()
    deprecatedTip("ccV3F_C4B_T2F_Quad","cc.V3F_C4B_T2F_Quad(_tl, _bl, _tr, _br)")
    return cc.V3F_C4B_T2F_Quad(cc.V3F_C4B_T2F(cc.vertex3F(0.0, 0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V3F_C4B_T2F(cc.vertex3F(0.0, 0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V3F_C4B_T2F(cc.vertex3F(0.0, 0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)), cc.V3F_C4B_T2F(cc.vertex3F(0.0, 0.0, 0.0), cc.c4b(0 , 0, 0, 0 ), cc.tex2F(0.0, 0.0)))
end
_G.ccV3F_C4B_T2F_Quad = ccV3FC4BT2FQuadDeprecated

local function ccV2FC4FT2FQuadDeprecated()
    deprecatedTip("ccV2F_C4F_T2F_Quad","cc.V2F_C4F_T2F_Quad(_bl, _br, _tl, _tr)")
    return cc.V2F_C4F_T2F_Quad(cc.V2F_C4F_T2F(cc.vertex2F(0.0, 0.0), cc.c4f(0.0 , 0.0, 0.0, 0.0 ), cc.tex2F(0.0, 0.0)), cc.V2F_C4F_T2F(cc.vertex2F(0.0, 0.0), cc.c4f(0.0 , 0.0, 0.0, 0.0 ), cc.tex2F(0.0, 0.0)), cc.V3F_C4B_T2F(cc.vertex2F(0.0, 0.0), cc.c4f(0.0 , 0.0, 0.0, 0.0 ), cc.tex2F(0.0, 0.0)), cc.V2F_C4F_T2F(cc.vertex2F(0.0, 0.0), cc.c4f(0.0 , 0.0, 0.0, 0.0 ), cc.tex2F(0.0, 0.0)))
end
_G.ccV2F_C4F_T2F_Quad = ccV2FC4FT2FQuadDeprecated

local function ccT2FQuadDeprecated()
    deprecatedTip("ccT2F_Quad","cc.T2F_Quad(_bl, _br, _tl, _tr)")
    return cc.T2F_Quad(cc.tex2F(0.0,0.0), cc.tex2F(0.0,0.0), cc.tex2F(0.0,0.0), cc.tex2F(0.0,0.0))
end
_G.ccT2F_Quad = ccT2FQuadDeprecated

local function ccAnimationFrameDataDeprecated()
    deprecatedTip("ccAnimationFrameData","cc.AnimationFrameData( _texCoords, _delay, _size)")
    return cc.AnimationFrameData(cc.T2F_Quad(cc.tex2F(0.0,0.0), cc.tex2F(0.0,0.0), cc.tex2F(0.0,0.0), cc.tex2F(0.0,0.0)), 0, cc.size(0,0))
end
_G.ccAnimationFrameData = ccAnimationFrameDataDeprecated



local function tex2(u,v)
    deprecatedTip("tex2(u,v)","cc.tex2f(u,v)")
    return cc.tex2f(u,v)
end
_G.tex2 = tex2


--functions of CCApplication will be deprecated end
local CCApplicationDeprecated = { }
function CCApplicationDeprecated.sharedApplication()
    deprecatedTip("CCApplication:sharedApplication","CCApplication:getInstance")
    return CCApplication:getInstance()
end
CCApplication.sharedApplication = CCApplicationDeprecated.sharedApplication
--functions of CCApplication will be deprecated end


--functions of CCDirector will be deprecated end
local CCDirectorDeprecated = { }
function CCDirectorDeprecated.sharedDirector()
    deprecatedTip("CCDirector:sharedDirector","CCDirector:getInstance")
    return CCDirector:getInstance()
end
CCDirector.sharedDirector = CCDirectorDeprecated.sharedDirector
--functions of CCDirector will be deprecated end


--functions of CCUserDefault will be deprecated end
local CCUserDefaultDeprecated = { }
function CCUserDefaultDeprecated.sharedUserDefault()
    deprecatedTip("CCUserDefault:sharedUserDefault","CCUserDefault:getInstance")
    return CCUserDefault:getInstance()
end
CCUserDefault.sharedUserDefault = CCUserDefaultDeprecated.sharedUserDefault

function CCUserDefaultDeprecated.purgeSharedUserDefault()
    deprecatedTip("CCUserDefault:purgeSharedUserDefault","CCUserDefault:destroyInstance")
    return CCUserDefault:destroyInstance()
end
CCUserDefault.purgeSharedUserDefault = CCUserDefaultDeprecated.purgeSharedUserDefault
--functions of CCUserDefault will be deprecated end

--functions of CCGrid3DAction will be deprecated begin
local CCGrid3DActionDeprecated = { }
function CCGrid3DActionDeprecated.vertex(self,pt)
    deprecatedTip("vertex","CCGrid3DAction:getVertex")
    return self:getVertex(pt)
end
CCGrid3DAction.vertex = CCGrid3DActionDeprecated.vertex

function CCGrid3DActionDeprecated.originalVertex(self,pt)
    deprecatedTip("originalVertex","CCGrid3DAction:getOriginalVertex")
    return self:getOriginalVertex(pt)
end
CCGrid3DAction.originalVertex = CCGrid3DActionDeprecated.originalVertex
--functions of CCGrid3DAction will be deprecated end


--functions of CCTiledGrid3DAction will be deprecated begin
local CCTiledGrid3DActionDeprecated = { }
function CCTiledGrid3DActionDeprecated.tile(self,pt)
    deprecatedTip("tile","CCTiledGrid3DAction:getTile")
    return self:getTile(pt)
end
CCTiledGrid3DAction.tile = CCTiledGrid3DActionDeprecated.tile

function CCTiledGrid3DActionDeprecated.originalTile(self,pt)
    deprecatedTip("originalTile","CCTiledGrid3DAction:getOriginalTile")
    return self:getOriginalTile(pt)
end
CCTiledGrid3DAction.originalTile = CCTiledGrid3DActionDeprecated.originalTile
--functions of CCTiledGrid3DAction will be deprecated end


--functions of CCTexture2D will be deprecated begin
local CCTexture2DDeprecated = { }
function CCTexture2DDeprecated.stringForFormat(self)
    deprecatedTip("Texture2D:stringForFormat","Texture2D:getStringForFormat")
    return self:getStringForFormat()
end
CCTexture2D.stringForFormat = CCTexture2DDeprecated.stringForFormat

function CCTexture2DDeprecated.bitsPerPixelForFormat(self)
    deprecatedTip("Texture2D:bitsPerPixelForFormat","Texture2D:getBitsPerPixelForFormat")
    return self:getBitsPerPixelForFormat()
end
CCTexture2D.bitsPerPixelForFormat = CCTexture2DDeprecated.bitsPerPixelForFormat

function CCTexture2DDeprecated.bitsPerPixelForFormat(self,pixelFormat)
    deprecatedTip("Texture2D:bitsPerPixelForFormat","Texture2D:getBitsPerPixelForFormat")
    return self:getBitsPerPixelForFormat(pixelFormat)
end
CCTexture2D.bitsPerPixelForFormat = CCTexture2DDeprecated.bitsPerPixelForFormat

function CCTexture2DDeprecated.defaultAlphaPixelFormat(self)
    deprecatedTip("Texture2D:defaultAlphaPixelFormat","Texture2D:getDefaultAlphaPixelFormat")
    return self:getDefaultAlphaPixelFormat()
end
CCTexture2D.defaultAlphaPixelFormat = CCTexture2DDeprecated.defaultAlphaPixelFormat
--functions of CCTexture2D will be deprecated end


--functions of CCTimer will be deprecated begin
local CCTimerDeprecated = { }
function CCTimerDeprecated.timerWithScriptHandler(handler,seconds)
    deprecatedTip("CCTimer:timerWithScriptHandler","CCTimer:createWithScriptHandler")
    return CCTimer:createWithScriptHandler(handler,seconds)
end
CCTimer.timerWithScriptHandler = CCTimerDeprecated.timerWithScriptHandler

function CCTimerDeprecated.numberOfRunningActionsInTarget(self,target)
    deprecatedTip("CCActionManager:numberOfRunningActionsInTarget","CCActionManager:getNumberOfRunningActionsInTarget")
    return self:getNumberOfRunningActionsInTarget(target)
end
CCTimer.numberOfRunningActionsInTarget = CCTimerDeprecated.numberOfRunningActionsInTarget
--functions of CCTimer will be deprecated end


--functions of CCMenuItemFont will be deprecated begin
local CCMenuItemFontDeprecated = { }
function CCMenuItemFontDeprecated.fontSize()
    deprecatedTip("CCMenuItemFont:fontSize","CCMenuItemFont:getFontSize")
    return CCMenuItemFont:getFontSize()
end
CCMenuItemFont.fontSize = CCMenuItemFontDeprecated.fontSize

function CCMenuItemFontDeprecated.fontName()
    deprecatedTip("CCMenuItemFont:fontName","CCMenuItemFont:getFontName")
    return CCMenuItemFont:getFontName()
end
CCMenuItemFont.fontName = CCMenuItemFontDeprecated.fontName

function CCMenuItemFontDeprecated.fontSizeObj(self)
    deprecatedTip("CCMenuItemFont:fontSizeObj","CCMenuItemFont:getFontSizeObj")
    return self:getFontSizeObj()
end
CCMenuItemFont.fontSizeObj = CCMenuItemFontDeprecated.fontSizeObj

function CCMenuItemFontDeprecated.fontNameObj(self)
    deprecatedTip("CCMenuItemFont:fontNameObj","CCMenuItemFont:getFontNameObj")
    return self:getFontNameObj()
end
CCMenuItemFont.fontNameObj = CCMenuItemFontDeprecated.fontNameObj
--functions of CCMenuItemFont will be deprecated end


--functions of CCMenuItemToggle will be deprecated begin
local CCMenuItemToggleDeprecated = { }
function CCMenuItemToggleDeprecated.selectedItem(self)
    deprecatedTip("CCMenuItemToggle:selectedItem","CCMenuItemToggle:getSelectedItem")
    return self:getSelectedItem()
end
CCMenuItemToggle.selectedItem = CCMenuItemToggleDeprecated.selectedItem
--functions of CCMenuItemToggle will be deprecated end


--functions of CCTileMapAtlas will be deprecated begin
local CCTileMapAtlasDeprecated = { }
function CCTileMapAtlasDeprecated.tileAt(self,pos)
    deprecatedTip("CCTileMapAtlas:tileAt","CCTileMapAtlas:getTileAt")
    return self:getTileAt(pos)
end
CCTileMapAtlas.tileAt = CCTileMapAtlasDeprecated.tileAt
--functions of CCTileMapAtlas will be deprecated end


--functions of CCTMXLayer will be deprecated begin
local CCTMXLayerDeprecated = { }
function CCTMXLayerDeprecated.tileAt(self,tileCoordinate)
    deprecatedTip("CCTMXLayer:tileAt","CCTMXLayer:getTileAt")
    return self:getTileAt(tileCoordinate)
end
CCTMXLayer.tileAt = CCTMXLayerDeprecated.tileAt

function CCTMXLayerDeprecated.tileGIDAt(self,tileCoordinate)
    deprecatedTip("CCTMXLayer:tileGIDAt","CCTMXLayer:getTileGIDAt")
    return self:getTileGIDAt(tileCoordinate)
end
CCTMXLayer.tileGIDAt = CCTMXLayerDeprecated.tileGIDAt

function CCTMXLayerDeprecated.positionAt(self,tileCoordinate)
    deprecatedTip("CCTMXLayer:positionAt","CCTMXLayer:getPositionAt")
    return self:getPositionAt(tileCoordinate)
end
CCTMXLayer.positionAt = CCTMXLayerDeprecated.positionAt

function CCTMXLayerDeprecated.propertyNamed(self,propertyName)
    deprecatedTip("CCTMXLayer:propertyNamed","CCTMXLayer:getProperty")
    return self:getProperty(propertyName)
end
CCTMXLayer.propertyNamed = CCTMXLayerDeprecated.propertyNamed
--functions of CCTMXLayer will be deprecated end

--functions of CCTMXTiledMap will be deprecated begin
local CCTMXTiledMapDeprecated = { }
function CCTMXTiledMapDeprecated.layerNamed(self,layerName)
    deprecatedTip("CCTMXTiledMap:layerNamed","CCTMXTiledMap:getLayer")
    return self:getLayer(layerName)
end
CCTMXTiledMap.layerNamed = CCTMXTiledMapDeprecated.layerNamed

function CCTMXTiledMapDeprecated.propertyNamed(self,propertyName)
    deprecatedTip("CCTMXTiledMap:propertyNamed","CCTMXTiledMap:getProperty")
    return self:getProperty(propertyName)
end
CCTMXTiledMap.propertyNamed = CCTMXTiledMapDeprecated.propertyNamed

function CCTMXTiledMapDeprecated.propertiesForGID(self,GID)
    deprecatedTip("CCTMXTiledMap:propertiesForGID","CCTMXTiledMap:getPropertiesForGID")
    return self:getPropertiesForGID(GID)
end
CCTMXTiledMap.propertiesForGID = CCTMXTiledMapDeprecated.propertiesForGID

function CCTMXTiledMapDeprecated.objectGroupNamed(self,groupName)
    deprecatedTip("CCTMXTiledMap:objectGroupNamed","CCTMXTiledMap:getObjectGroup")
    return self:getObjectGroup(groupName)
end
CCTMXTiledMap.objectGroupNamed = CCTMXTiledMapDeprecated.objectGroupNamed
--functions of CCTMXTiledMap will be deprecated end


--functions of CCTMXMapInfo will be deprecated begin
local CCTMXMapInfoDeprecated = { }
function CCTMXMapInfoDeprecated.getStoringCharacters(self)
    deprecatedTip("CCTMXMapInfo:getStoringCharacters","CCTMXMapInfo:isStoringCharacters")
    return self:isStoringCharacters()
end
CCTMXMapInfo.getStoringCharacters = CCTMXMapInfoDeprecated.getStoringCharacters

function CCTMXMapInfoDeprecated.formatWithTMXFile(infoTable,tmxFile)
    deprecatedTip("CCTMXMapInfo:formatWithTMXFile","CCTMXMapInfo:create")
    return CCTMXMapInfo:create(tmxFile)
end
CCTMXMapInfo.formatWithTMXFile = CCTMXMapInfoDeprecated.formatWithTMXFile

function CCTMXMapInfoDeprecated.formatWithXML(infoTable,tmxString,resourcePath)
    deprecatedTip("CCTMXMapInfo:formatWithXML","TMXMapInfo:createWithXML")
    return CCTMXMapInfo:createWithXML(tmxString,resourcePath)
end
CCTMXMapInfo.formatWithXML = CCTMXMapInfoDeprecated.formatWithXML
--functions of CCTMXMapInfo will be deprecated end


--functions of CCTMXObject will be deprecated begin
local CCTMXObjectGroupDeprecated = { }
function CCTMXObjectGroupDeprecated.propertyNamed(self,propertyName)
    deprecatedTip("CCTMXObjectGroup:propertyNamed","CCTMXObjectGroup:getProperty")
    return self:getProperty(propertyName)
end
CCTMXObjectGroup.propertyNamed = CCTMXObjectGroupDeprecated.propertyNamed

function CCTMXObjectGroupDeprecated.objectNamed(self, objectName)
    deprecatedTip("CCTMXObjectGroup:objectNamed","CCTMXObjectGroup:getObject")
    return self:getObject(objectName)
end
CCTMXObjectGroup.objectNamed = CCTMXObjectGroupDeprecated.objectNamed
--functions of CCTMXObject will be deprecated end

--functions of CCRenderTexture will be deprecated begin
local CCRenderTextureDeprecated = { }
function CCRenderTextureDeprecated.newCCImage(self)
    deprecatedTip("CCRenderTexture:newCCImage","CCRenderTexture:newImage")
    return self:newImage()
end
CCRenderTexture.newCCImage = CCRenderTextureDeprecated.newCCImage
--functions of CCRenderTexture will be deprecated end

--functions of Sprite will be deprecated begin
local CCSpriteDeprecated = { }
function CCSpriteDeprecated.setFlipX(self,flag)
    deprecatedTip("CCSpriteDeprecated:setFlipX","CCSpriteDeprecated:setFlippedX")
    return self:setFlippedX(flag)
end
cc.Sprite.setFlipX = CCSpriteDeprecated.setFlipX

function CCSpriteDeprecated.setFlipY(self,flag)
    deprecatedTip("CCSpriteDeprecated:setFlipY","CCSpriteDeprecated:setFlippedY")
    return self:setFlippedY(flag)
end
cc.Sprite.setFlipY = CCSpriteDeprecated.setFlipY
--functions of Sprite will be deprecated end


--functions of Layer will be deprecated begin
local CCLayerDeprecated = {}
function CCLayerDeprecated.setKeypadEnabled( self, enabled)
    return self:setKeyboardEnabled(enabled)
end
cc.Layer.setKeypadEnabled = CCLayerDeprecated.setKeypadEnabled

function CCLayerDeprecated.isKeypadEnabled(self)
    return self:isKeyboardEnabled()
end
cc.Layer.isKeypadEnabled = CCLayerDeprecated.isKeypadEnabled
--functions of Layer will be deprecated end

--functions of cc.Node will be deprecated begin
local NodeDeprecated = { }
function NodeDeprecated.setZOrder(self,zOrder)
    deprecatedTip("cc.Node:setZOrder","cc.Node:setLocalZOrder")
    return self:setLocalZOrder(zOrder)
end
cc.Node.setZOrder = NodeDeprecated.setZOrder

function NodeDeprecated.getZOrder(self)
    deprecatedTip("cc.Node:getZOrder","cc.Node:getLocalZOrder")
    return self:getLocalZOrder()
end
cc.Node.getZOrder = NodeDeprecated.getZOrder

function NodeDeprecated.setVertexZ(self,vertexZ)
    deprecatedTip("cc.Node:setVertexZ", "cc.Node:setPositionZ")
    return self:setPositionZ(vertexZ)
end
cc.Node.setVertexZ = NodeDeprecated.setVertexZ

function NodeDeprecated.getVertexZ(self)
    deprecatedTip("cc.Node:getVertexZ", "cc.Node:getPositionZ")
    return self:getPositionZ()
end
cc.Node.getVertexZ = NodeDeprecated.getVertexZ

function NodeDeprecated.ignoreAnchorPointForPosition(self,ignore)
    deprecatedTip("cc.Node:ignoreAnchorPointForPosition", "cc.Node:setIgnoreAnchorPointForPosition")
    return self:setIgnoreAnchorPointForPosition(ignore)
end

cc.Node.ignoreAnchorPointForPosition = NodeDeprecated.ignoreAnchorPointForPosition
--functions of cc.Node will be deprecated end

--functions of cc.GLProgram will be deprecated begin
local GLProgram = { }
function GLProgram.initWithVertexShaderByteArray(self,vShaderByteArray, fShaderByteArray)
    deprecatedTip("cc.GLProgram:initWithVertexShaderByteArray","cc.GLProgram:initWithByteArrays")
    return self:initWithByteArrays(vShaderByteArray, fShaderByteArray)
end
cc.GLProgram.initWithVertexShaderByteArray = GLProgram.initWithVertexShaderByteArray

function GLProgram.initWithVertexShaderFilename(self,vShaderByteArray, fShaderByteArray)
    deprecatedTip("cc.GLProgram:initWithVertexShaderFilename","cc.GLProgram:initWithFilenames")
    return self:initWithFilenames(vShaderByteArray, fShaderByteArray)
end
cc.GLProgram.initWithVertexShaderFilename = GLProgram.initWithVertexShaderFilename

function GLProgram.addAttribute(self, attributeName, index)
    deprecatedTip("cc.GLProgram:addAttribute","cc.GLProgram:bindAttribLocation")
    return self:bindAttribLocation(attributeName, index)
end
cc.GLProgram.addAttribute = GLProgram.addAttribute
--functions of cc.GLProgram will be deprecated end
