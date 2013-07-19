
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end
local function addHandleOfControlEvent(self,func,controlEvent)
    deprecatedTip("addHandleOfControlEvent","registerControlEventHandler")
    self:registerControlEventHandler(func,controlEvent)
end
rawset(CCControl,"addHandleOfControlEvent",addHandleOfControlEvent)

local function ccpLineIntersect(a,b,c,d,s,t)
    deprecatedTip("ccpLineIntersect","CCPoint:isLineIntersect")
    return CCPoint:isLineIntersect(a,b,c,d,s,t)
end
rawset(_G,"ccpLineIntersect",ccpLineIntersect)


local function CCPointMake(x,y)
    deprecatedTip("CCPointMake","CCPoint:__call")
    return CCPoint:__call(x,y)
end 
rawset(_G,"CCPointMake",CCPointMake)

local function ccp(x,y)
    deprecatedTip("ccp","CCPoint:__call")
    return CCPoint:__call(x,y)
end 
rawset(_G,"ccp",ccp)

local function CCSizeMake(width,height)
    deprecatedTip("CCSizeMake","CCSize:__call")
    return CCSize:__call(width,height)
end
rawset(_G,"CCSizeMake",CCSizeMake)

local function CCRectMake(x,y,width,height)
    deprecatedTip("CCRectMake","CCRect:__call")
    return CCRect:__call(x,y,width,height)
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

--no test
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
    deprecatedTip("ccpNormalize","CCPoint:getDistance")
    return pt:getDistance()
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
    deprecatedTip("ccpFromSize","CCPoint:__call")
    return CCPoint:__call(sz)
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
    deprecatedTip("ccpCompMult","CCPoint:__call")
    return CCPoint:__call(pt1.x * pt2.x , pt1.y * pt2.y)
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


local function sharedOpenGLView()
    deprecatedTip("CCEGLView:sharedOpenGLView","CCEGLView:getInstance")
    return CCEGLView:getInstance()
end
rawset(CCEGLView,"sharedOpenGLView",sharedOpenGLView)

local function sharedFileUtils()
    deprecatedTip("CCFileUtils:sharedFileUtils","CCFileUtils:getInstance")
    return CCFileUtils:getInstance()
end
rawset(CCFileUtils,"sharedFileUtils",sharedFileUtils)

local function purgeFileUtils()
    deprecatedTip("CCFileUtils:purgeFileUtils","CCFileUtils:destroyInstance")
    return CCFileUtils:destroyInstance()
end
rawset(CCFileUtils,"purgeFileUtils",purgeFileUtils)

local function sharedApplication()
    deprecatedTip("CCApplication:sharedApplication","CCApplication:getInstance")
    return CCApplication:getInstance()
end
rawset(CCApplication,"sharedApplication",sharedApplication)

local function sharedDirector()
    deprecatedTip("CCDirector:sharedDirector","CCDirector:getInstance")
    return CCDirector:getInstance()
end
rawset(CCDirector,"sharedDirector",sharedDirector)

local function sharedUserDefault()
    deprecatedTip("CCUserDefault:sharedUserDefault","CCUserDefault:getInstance")
    return CCUserDefault:getInstance()
end
rawset(CCUserDefault,"sharedUserDefault",sharedUserDefault)

local function purgeSharedUserDefault()
    deprecatedTip("CCUserDefault:purgeSharedUserDefault","CCUserDefault:destroyInstance")
    return CCUserDefault:destroyInstance()
end
rawset(CCUserDefault,"purgeSharedUserDefault",purgeSharedUserDefault)


local function sharedNotificationCenter()
    deprecatedTip("CCNotificationCenter:sharedNotificationCenter","CCNotificationCenter:getInstance")
    return CCNotificationCenter:getInstance()
end
rawset(CCNotificationCenter,"sharedNotificationCenter",sharedNotificationCenter)

local function purgeNotificationCenter()
    deprecatedTip("CCNotificationCenter:purgeNotificationCenter","CCNotificationCenter:destroyInstance")
    return CCNotificationCenter:destroyInstance()
end
rawset(CCNotificationCenter,"purgeNotificationCenter",purgeNotificationCenter)

local function sharedTextureCache()
    deprecatedTip("CCTextureCache:sharedTextureCache","CCTextureCache:getInstance")
    return CCTextureCache:getInstance()
end
rawset(CCTextureCache,"sharedTextureCache",sharedTextureCache)

local function purgeSharedTextureCache()
    deprecatedTip("CCTextureCache:purgeSharedTextureCache","CCTextureCache:destroyInstance")
    return CCTextureCache:destroyInstance()
end
rawset(CCTextureCache,"purgeSharedTextureCache",purgeSharedTextureCache)

local function sharedSpriteFrameCache()
    deprecatedTip("CCSpriteFrameCache:sharedSpriteFrameCache","CCSpriteFrameCache:getInstance")
    return CCSpriteFrameCache:getInstance()
end
rawset(CCSpriteFrameCache,"sharedSpriteFrameCache",sharedSpriteFrameCache)

local function purgeSharedSpriteFrameCache()
    deprecatedTip("CCSpriteFrameCache:purgeSharedSpriteFrameCache","CCSpriteFrameCache:destroyInstance")
    return CCSpriteFrameCache:destroyInstance()
end
rawset(CCSpriteFrameCache,"purgeSharedSpriteFrameCache",purgeSharedSpriteFrameCache)

local function vertex(self,pt)
    deprecatedTip("vertex","CCGrid3DAction:getVertex")
    return self:getVertex(pt)
end
rawset(CCGrid3DAction,"vertex",vertex)

local function originalVertex(self,pt)
    deprecatedTip("originalVertex","CCGrid3DAction:getOriginalVertex")
    return self:getOriginalVertex(pt)
end
rawset(CCGrid3DAction,"originalVertex",originalVertex)

local function tile(self,pt)
    deprecatedTip("tile","CCTiledGrid3DAction:getTile")
    return self:getTile(pt)
end
rawset(CCTiledGrid3DAction,"tile",tile)

local function originalTile(self,pt)
    deprecatedTip("originalTile","CCTiledGrid3DAction:getOriginalTile")
    return self:getOriginalTile(pt)
end
rawset(CCTiledGrid3DAction,"originalTile",originalTile)

local function sharedAnimationCache()
    deprecatedTip("CCAnimationCache:sharedAnimationCache","CCAnimationCache:getInstance")
    return CCAnimationCache:getInstance()
end
rawset(CCAnimationCache,"sharedAnimationCache",sharedAnimationCache)

local function purgeSharedAnimationCache()
    deprecatedTip("CCAnimationCache:purgeSharedAnimationCache","CCAnimationCache:destroyInstance")
    return CCAnimationCache:destroyInstance()
end
rawset(CCAnimationCache,"purgeSharedAnimationCache",purgeSharedAnimationCache)

local function boundingBox(self)
    deprecatedTip("CCNode:boundingBox","CCNode:getBoundingBox")
    return self:getBoundingBox()
end
rawset(CCNode,"boundingBox",boundingBox)










