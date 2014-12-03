
local CryptoTestScene = game.createSceneClass("CryptoTestScene")

function CryptoTestScene:ctor()
    cc.FileUtils:getInstance():addSearchPath("src/")

    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "AES256",
        "XXTEA",
        "Base64",
        "MD5File",
        "MD5",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function CryptoTestScene:AES256Test()
    local p = "Test123"
    local k = "KEYKEY"
    local c = crypto.encryptAES256(p, k)
    if not c then
        return
    end
    printf("source: %s", p)
    printf("encrypt AES256: %s", bin2hex(c))
    printf("decrypt AES256: %s", crypto.decryptAES256(c, k))

    local p = string.rep("HELLO", 15)
    local c = crypto.encryptAES256(p, k)
    printf("source: %s", p)
    printf("encrypt AES256: %s", bin2hex(c))
    printf("decrypt AES256: %s", crypto.decryptAES256(c, k))
end

function CryptoTestScene:XXTEATest()
    local p = "Test123"
    local k = "KEYKEY"
    local c = crypto.encryptXXTEA(p, k)
    printf("source: %s", p)
    printf("encrypt XXTEA: %s", bin2hex(c))
    printf("decrypt XXTEA: %s", crypto.decryptXXTEA(c, k))

    local p = string.rep("HELLO", 15)
    local k = "keykey"
    local c = crypto.encryptXXTEA(p, k)
    printf("source: %s", p)
    printf("encrypt XXTEA: %s", bin2hex(c))
    printf("decrypt XXTEA: %s", crypto.decryptXXTEA(c, k))
end

function CryptoTestScene:Base64Test()
    local p = "Test123"
    local c = crypto.encodeBase64(p)
    printf("source: %s", p)
    printf("encode Base64: %s", c)
    printf("decode Base64: %s", crypto.decodeBase64(c))

    local p = string.rep("HELLO", 15)
    local c = crypto.encodeBase64(p)
    printf("source: %s", p)
    printf("encode Base64: %s", c)
    printf("decode Base64: %s", crypto.decodeBase64(c))
end

function CryptoTestScene:MD5FileTest()
    local file = cc.FileUtils:getInstance():fullPathForFilename("config.lua")
    printf("md5 file test: %s -> %s", file, crypto.md5file(file))
end

function CryptoTestScene:MD5Test()
    local p = string.rep("HELLO", 5)
    printf("md5Test: %s -> %s", p, crypto.md5(p))
end

return CryptoTestScene
