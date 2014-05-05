local function CurrentLanguageTest()
    local ret = CCLayer:create()
    local  label = CCLabelTTF:create("Current language Test", "Arial", 28)
    ret:addChild(label, 0)
    label:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y-50) )

    local labelLanguage = CCLabelTTF:create("", "Arial", 20)
    labelLanguage:setPosition(VisibleRect:center())

    local currentLanguageType = CCApplication:sharedApplication():getCurrentLanguage()

    if currentLanguageType == kLanguageEnglish then
        labelLanguage:setString("current language is English")
    elseif currentLanguageType == kLanguageChinese then
        labelLanguage:setString("current language is Chinese")
    elseif currentLanguageType == kLanguageFrench then
        labelLanguage:setString("current language is French")
    elseif currentLanguageType == kLanguageGerman then
        labelLanguage:setString("current language is German")
    elseif currentLanguageType == kLanguageItalian then
        labelLanguage:setString("current language is Italian")
    elseif currentLanguageType == kLanguageRussian then
        labelLanguage:setString("current language is Russian")
    elseif currentLanguageType == kLanguageSpanish then
        labelLanguage:setString("current language is Spanish")
    elseif currentLanguageType == kLanguageKorean then
        labelLanguage:setString("current language is Korean")
    elseif currentLanguageType == kLanguageJapanese then
        labelLanguage:setString("current language is Japanese")
    elseif currentLanguageType == kLanguageHungarian then
        labelLanguage:setString("current language is Hungarian")
    elseif currentLanguageType == kLanguagePortuguese then
        labelLanguage:setString("current language is Portuguese")
    elseif currentLanguageType == kLanguageArabic then
        labelLanguage:setString("current language is Arabic")
    end
    ret:addChild(labelLanguage)
    return ret
end

function CurrentLanguageTestMain()
    local scene = CCScene:create()
    local pLayer = CurrentLanguageTest()
    scene:addChild(pLayer)
    scene:addChild(CreateBackMenuItem())
    return scene
end
