
local function deprecatedTip(funcName)
    local tip = string.format("%s is deprecated function",funcName)
    print(tip)
end
local function addHandleOfControlEvent(self,func,controlEvent)
    deprecatedTip("addHandleOfControlEvent")
    self:registerControlEventHandler(func,controlEvent)
end
rawset(CCControl,"addHandleOfControlEvent",addHandleOfControlEvent)

local function ccpLineIntersect(a,b,c,d,s,t)
    deprecatedTip("ccpLineIntersect")
    return CCPoint:isLineIntersect(a,b,c,d,s,t)
end
rawset(_G,"ccpLineIntersect",ccpLineIntersect)


local function CCPointMake(x,y)
    deprecatedTip("CCPointMake")
    return CCPoint:new_local(x,y)
end 
rawset(_G,"CCPointMake",CCPointMake)

local function ccp(x,y)
    deprecatedTip("ccp")
    return CCPoint:new_local(x,y)
end 
rawset(_G,"ccp",ccp)

local function CCSizeMake(width,height)
    deprecatedTip("CCSizeMake")
    return CCSize:new_local(width,height)
end
rawset(_G,"CCSizeMake",CCSizeMake)

local function CCRectMake(x,y,width,height)
    deprecatedTip("CCRectMake")
    return CCRect:new_local(x,y,width,height)
end
rawset(_G,"CCRectMake",CCRectMake)

local function ccpNeg(pt)
    deprecatedTip("ccpNeg")
    return CCPoint.__sub(CCPoint:new_local(0,0),pt)
end
rawset(_G,"ccpNeg",ccpNeg)

local function ccpAdd(pt1,pt2)
    deprecatedTip("ccpAdd")
    return CCPoint.__add(pt1,pt2)
end
rawset(_G,"ccpAdd",ccpAdd)

local function ccpSub(pt1,pt2)
    deprecatedTip("ccpSub")
    return CCPoint.__sub(pt1,pt2)
end
rawset(_G,"ccpSub",ccpSub)

local function ccpMult(pt,factor)
    deprecatedTip("ccpMult")
    return CCPoint.__mul(pt,factor)
end
rawset(_G,"ccpMult",ccpMult)

local function ccpMidpoint(pt1,pt2)
    deprecatedTip("ccpMidpoint")
    return pt1:getMidpoint(pt2)
end
rawset(_G,"ccpMidpoint",ccpMidpoint)

local function ccpDot(pt1,pt2)
    deprecatedTip("ccpDot")
    return pt1:dot(pt2)
end
rawset(_G,"ccpDot",ccpDot)

local function ccpCross(pt1,pt2)
    deprecatedTip("ccpCross")
    return pt1:cross(pt2)
end
rawset(_G,"ccpCross",ccpCross)

local function ccpPerp(pt)
    deprecatedTip("ccpPerp")
    return pt:getPerp()
end
rawset(_G,"ccpPerp",ccpPerp)

local function ccpRPerp(pt)
    deprecatedTip("ccpRPerp")
    return pt:getRPerp()
end
rawset(_G,"ccpRPerp",ccpRPerp)

--no test
local function ccpProject(pt1,pt2)
    deprecatedTip("ccpProject")
    return pt1:project(pt2)
end
rawset(_G,"ccpProject",ccpProject)

local function ccpRotate(pt1,pt2)
    deprecatedTip("ccpRotate")
    return pt1:rotate(pt2)
end
rawset(_G,"ccpRotate",ccpRotate)

local function ccpUnrotate(pt1,pt2)
    deprecatedTip("ccpUnrotate")
    return pt1:unrotate(pt2)
end
rawset(_G,"ccpUnrotate",ccpUnrotate)

local function ccpLengthSQ(pt)
    deprecatedTip("ccpLengthSQ")
    return pt:getLengthSq(pt)
end
rawset(_G,"ccpLengthSQ",ccpLengthSQ)

local function ccpDistanceSQ(pt1,pt2)
    deprecatedTip("ccpDistanceSQ")
    return (CCPoint.__sub(pt1,pt2)):getLengthSq()
end
rawset(_G,"ccpDistanceSQ",ccpDistanceSQ)

local function ccpLength(pt)
    deprecatedTip("ccpLength")
    return pt:getLength()
end
rawset(_G,"ccpLength",ccpLength)

local function ccpDistance(pt1,pt2)
    deprecatedTip("ccpDistance")
    return pt1:getDistance(pt2)
end
rawset(_G,"ccpDistance",ccpDistance)

local function ccpNormalize(pt)
    deprecatedTip("ccpNormalize")
    return pt:getDistance()
end
rawset(_G,"ccpNormalize",ccpNormalize)

local function ccpForAngle(angle)
    deprecatedTip("ccpForAngle")
    return CCPoint:forAngle(angle)
end
rawset(_G,"ccpForAngle",ccpForAngle)

local function ccpToAngle(pt)
    deprecatedTip("ccpToAngle")
    return pt:getAngle()
end
rawset(_G,"ccpToAngle",ccpToAngle)

local function ccpClamp(pt1,pt2,pt3)
    deprecatedTip("ccpClamp")
    return pt1:getClampPoint(pt2, pt3)
end
rawset(_G,"ccpClamp",ccpClamp)


local function ccpFromSize(sz)
    deprecatedTip("ccpFromSize")
    return CCPoint:new_local(sz)
end
rawset(_G,"ccpFromSize",ccpFromSize)

local function ccpLerp(pt1,pt2,alpha)
    deprecatedTip("ccpLerp")
    return pt1:lerp(pt2,alpha)
end
rawset(_G,"ccpLerp",ccpLerp)

local function ccpFuzzyEqual(pt1,pt2,variance)
    deprecatedTip("ccpFuzzyEqual")
    return pt1:fuzzyEquals(pt2,variance)
end
rawset(_G,"ccpFuzzyEqual",ccpFuzzyEqual)

local function ccpCompMult(pt1,pt2)
    deprecatedTip("ccpCompMult")
    return CCPoint:new_local(pt1.x * pt2.x , pt1.y * pt2.y)
end
rawset(_G,"ccpCompMult",ccpCompMult)

local function ccpAngleSigned(pt1,pt2)
    deprecatedTip("ccpAngleSigned")
    return pt1:getAngle(pt2)
end
rawset(_G,"ccpAngleSigned",ccpAngleSigned)

local function ccpAngle(pt1,pt2)
    deprecatedTip("ccpAngle")
    return pt1:getAngle(pt2)
end
rawset(_G,"ccpAngle",ccpAngle)

local function ccpRotateByAngle(pt1,pt2,angle)
    deprecatedTip("ccpRotateByAngle")
    return pt1:rotateByAngle(pt2, angle)
end
rawset(_G,"ccpRotateByAngle",ccpRotateByAngle)

local function ccpSegmentIntersect(pt1,pt2,pt3,pt4)
    deprecatedTip("ccpSegmentIntersect")
    return CCPoint:isSegmentIntersect(pt1,pt2,pt3,pt4)
end
rawset(_G,"ccpSegmentIntersect",ccpSegmentIntersect)

local function ccpIntersectPoint(pt1,pt2,pt3,pt4)
    deprecatedTip("ccpIntersectPoint")
    return CCPoint:getIntersectPoint(pt1,pt2,pt3,pt4)
end
rawset(_G,"ccpIntersectPoint",ccpIntersectPoint)


local function sharedOpenGLView()
    deprecatedTip("sharedOpenGLView")
    return CCEGLView:getInstance()
end
rawset(CCEGLView,"sharedOpenGLView",sharedOpenGLView)

local function sharedFileUtils()
    deprecatedTip("sharedFileUtils")
    return CCFileUtils:getInstance()
end
rawset(CCFileUtils,"sharedFileUtils",sharedFileUtils)

local function purgeFileUtils()
    deprecatedTip("purgeFileUtils")
    return CCFileUtils:destroyInstance()
end
rawset(CCFileUtils,"purgeFileUtils",purgeFileUtils)

local function sharedApplication()
    deprecatedTip("sharedApplication")
    return CCApplication:getInstance()
end
rawset(CCApplication,"sharedApplication",sharedApplication)

local function sharedDirector()
    deprecatedTip("sharedDirector")
    return CCDirector:getInstance()
end
rawset(CCDirector,"sharedDirector",sharedDirector)

local function sharedUserDefault()
    deprecatedTip("sharedUserDefault")
    return CCUserDefault:getInstance()
end
rawset(CCUserDefault,"sharedUserDefault",sharedUserDefault)

local function purgeSharedUserDefault()
    deprecatedTip("purgeSharedUserDefault")
    return CCUserDefault:destroyInstance()
end
rawset(CCUserDefault,"purgeSharedUserDefault",purgeSharedUserDefault)


local function sharedNotificationCenter()
    deprecatedTip("sharedNotificationCenter")
    return CCNotificationCenter:getInstance()
end
rawset(CCNotificationCenter,"sharedNotificationCenter",sharedNotificationCenter)

local function purgeNotificationCenter()
    deprecatedTip("purgeNotificationCenter")
    return CCNotificationCenter:destroyInstance()
end
rawset(CCNotificationCenter,"purgeNotificationCenter",purgeNotificationCenter)

local function sharedTextureCache()
    deprecatedTip("sharedTextureCache")
    return CCTextureCache:getInstance()
end
rawset(CCTextureCache,"sharedTextureCache",sharedTextureCache)

local function purgeSharedTextureCache()
    deprecatedTip("purgeSharedTextureCache")
    return CCTextureCache:destroyInstance()
end
rawset(CCTextureCache,"purgeSharedTextureCache",purgeSharedTextureCache)

local function sharedSpriteFrameCache()
    deprecatedTip("sharedSpriteFrameCache")
    return CCSpriteFrameCache:getInstance()
end
rawset(CCSpriteFrameCache,"sharedSpriteFrameCache",sharedSpriteFrameCache)

local function purgeSharedSpriteFrameCache()
    deprecatedTip("purgeSharedSpriteFrameCache")
    return CCSpriteFrameCache:destroyInstance()
end
rawset(CCSpriteFrameCache,"purgeSharedSpriteFrameCache",purgeSharedSpriteFrameCache)

local function vertex(self,pt)
    deprecatedTip("vertex")
    return self:getVertex(pt)
end
rawset(CCGrid3DAction,"vertex",vertex)

local function originalVertex(self,pt)
    deprecatedTip("originalVertex")
    return self:getOriginalVertex(pt)
end
rawset(CCGrid3DAction,"originalVertex",originalVertex)

local function tile(self,pt)
    deprecatedTip("tile")
    return self:getTile(pt)
end
rawset(CCTiledGrid3DAction,"tile",tile)

local function originalTile(self,pt)
    deprecatedTip("originalTile")
    return self:getOriginalTile(pt)
end
rawset(CCTiledGrid3DAction,"originalTile",originalTile)

local function sharedAnimationCache()
    deprecatedTip("sharedAnimationCache")
    return CCAnimationCache:getInstance()
end
rawset(CCAnimationCache,"sharedAnimationCache",sharedAnimationCache)

local function purgeSharedAnimationCache()
    deprecatedTip("purgeSharedAnimationCache")
    return CCAnimationCache:destroyInstance()
end
rawset(CCAnimationCache,"purgeSharedAnimationCache",purgeSharedAnimationCache)









