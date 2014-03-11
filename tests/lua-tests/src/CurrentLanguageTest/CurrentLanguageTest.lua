local function CurrentLanguageTest()
    local ret = cc.Layer:create()
    local  label = cc.LabelTTF:create("Current language Test", "Arial", 28)
    ret:addChild(label, 0)
    label:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y-50) )

    local labelLanguage = cc.LabelTTF:create("", "Arial", 20)
    labelLanguage:setPosition(VisibleRect:center())

    local currentLanguageType = cc.Application:getInstance():getCurrentLanguage()

    if currentLanguageType == cc.LANGUAGE_ENGLISH then
        labelLanguage:setString("current language is English")
    elseif currentLanguageType == cc.LANGUAGE_CHINESE then
        labelLanguage:setString("current language is Chinese")
    elseif currentLanguageType == cc.LANGUAGE_FRENCH then
        labelLanguage:setString("current language is French")
    elseif currentLanguageType == cc.LANGUAGE_GERMAN then
        labelLanguage:setString("current language is German")
    elseif currentLanguageType == cc.LANGUAGE_ITALIAN then
        labelLanguage:setString("current language is Italian")
    elseif currentLanguageType == cc.LANGUAGE_RUSSIAN then
        labelLanguage:setString("current language is Russian")
    elseif currentLanguageType == cc.LANGUAGE_SPANISH then
        labelLanguage:setString("current language is Spanish")
    elseif currentLanguageType == cc.LANGUAGE_KOREAN then
        labelLanguage:setString("current language is Korean")
    elseif currentLanguageType == cc.LANGUAGE_JAPANESE then
        labelLanguage:setString("current language is Japanese")
    elseif currentLanguageType == cc.LANGUAGE_HUNGARIAN then
        labelLanguage:setString("current language is Hungarian")
    elseif currentLanguageType == cc.LANGUAGE_PORTUGUESE then
        labelLanguage:setString("current language is Portuguese")
    elseif currentLanguageType == cc.LANGUAGE_ARABIC then
        labelLanguage:setString("current language is Arabic")
    end
    ret:addChild(labelLanguage)
    return ret
end

function CurrentLanguageTestMain()
    local scene = cc.Scene:create()
    local pLayer = CurrentLanguageTest()
    scene:addChild(pLayer)
    scene:addChild(CreateBackMenuItem())
    return scene
end
