
local CryptoTestScene = game.createSceneClass("CryptoTestScene")

function CryptoTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "XXTEA",
        "Base64",
        "MD5",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
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

function CryptoTestScene:MD5Test()
    local p = string.rep("HELLO", 5)
    printf("md5Test: %s -> %s", p, crypto.md5(p))
end

return CryptoTestScene
