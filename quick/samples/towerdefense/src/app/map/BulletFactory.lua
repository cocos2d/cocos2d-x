
local BulletType   = require("app.map.BulletType")
local ArrowBullet  = require("app.map.bullets.ArrowBullet")
local CannonBullet = require("app.map.bullets.CannonBullet")

local BulletFactory = {}

function BulletFactory.newBullets(bulletType, source, target, delay)
    if bulletType == BulletType.ARROW then
        return {ArrowBullet.new(source, target, delay)}
    elseif bulletType == BulletType.CANNON then
        return {CannonBullet.new(source, target, delay)}
    end

    echoError("BulletFactory.newBullets() - invalid bullet type %s", tostring(bulletType))
end

return BulletFactory
