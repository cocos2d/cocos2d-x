
#include "RichtextStringVisitor.h"

#include <stdlib.h>
#include <algorithm>

NS_CCR_BEGIN

const std::string RichtextStringVisitor::COLOR_FLAG = "color=";
const std::string RichtextStringVisitor::SIZE_FLAG = "size=";
const std::string RichtextStringVisitor::IMG_FLAG = "img";
const std::string RichtextStringVisitor::BR_FLAG = "br";

const std::map<std::string, std::string> RichtextStringVisitor::COLOR_MAP = {
    {"white", "#ffffff"},
    {"silver", "#c0c0c0"},
    {"gray", "#808080"},
    {"black", "#000000"},
    {"red", "#ff0000"},
    {"maroon", "#800000"},
    {"yellow", "#ffff00"},
    {"olive", "#808000"},
    {"lime", "#00ff00"},
    {"green", "#00ff00"},
    {"aqua", "#00ffff"},
    {"teal", "#008080"},
    {"blue", "#0000ff"},
    {"navy", "#000080"},
    {"fuchsia", "#ff00ff"},
    {"purple", "#800080"},
};

RichtextStringVisitor::RichtextStringVisitor()
: _maxFontSize(0)
, _rawString("")
, _outputXML("")
{}

void RichtextStringVisitor::startElement(void *ctx, const char *name, const char **atts)
{
    std::string nameStr(name);
    if (nameStr.find(COLOR_FLAG) != std::string::npos)
    {
        // <color=xxx>yyy</color> -> <font color=xxx>yyy</font>
        // if xxx is color name, then need to conver to hex string
        
        _outputXML.append("<font color=\"");
        auto colorValue = nameStr.substr(COLOR_FLAG.length());
        colorValue.erase(std::remove_if(colorValue.begin(), colorValue.end(), ::isspace ), colorValue.end());
        colorValue = RichtextStringVisitor::convertColorString2Hex(colorValue);
        _outputXML.append(colorValue);
        _outputXML.append("\">");
        _addFontEndFlags.push(true);
    }
    else if (nameStr.find(SIZE_FLAG) != std::string::npos)
    {
        // <size=xxx>yyy</size> -> <font size=xxx>yyy</font>
        
        _outputXML.append("<font size=\"");
        _outputXML.append(nameStr.substr(SIZE_FLAG.length()));
        _outputXML.append("\">");
        _addFontEndFlags.push(true);
        
        int fontSize = atoi(name + 5);
        _maxFontSize = std::max(fontSize, _maxFontSize);
    }
    else
    {
        _outputXML.append("<");
        _outputXML.append(name);
        
        while(*atts)
        {
            _outputXML.append(" ");
            std::string attributeName = convertAttributeName(name, *atts++);
            _outputXML.append(attributeName);
            _outputXML.append("=");
            
            _outputXML.append("\"");
            std::string attributeValue = convertAttributeValue(name, attributeName, *atts++);
            _outputXML.append(attributeValue);
            _outputXML.append("\"");
        }
        // the resource type is a sprite frame name
        // creator only supports sprite frame for img tag
        if (name == RichtextStringVisitor::IMG_FLAG)
            _outputXML.append(" type='1' ");
        
        _outputXML.append(">");
        
        _addFontEndFlags.push(false);
    }
}

void RichtextStringVisitor::endElement(void *ctx, const char *name)
{
    bool needAddFont = _addFontEndFlags.top();
    _addFontEndFlags.pop();
    if (needAddFont)
    {
        _outputXML.append("</font>");
    }
    else
    {
        _outputXML.append("</");
        _outputXML.append(name);
        _outputXML.append(">");
    }
    
    if (BR_FLAG == name)
    {
        _rawString.append("\n");
    }
}

void RichtextStringVisitor::textHandler(void *ctx, const char *s, size_t len)
{
    std::string content(s, len);
    _outputXML.append(content);
    
    _rawString.append(content);
}

const std::string& RichtextStringVisitor::getOutput() const
{
    return _outputXML;
}

const std::string& RichtextStringVisitor::getRawString() const
{
    return _rawString;
}

int RichtextStringVisitor::getMaxFontSize() const
{
    return _maxFontSize;
}

std::string RichtextStringVisitor::convertColorString2Hex(const std::string& colorString) const
{
    if (colorString[0] == '#')
        return colorString;
    
    if (COLOR_MAP.find(colorString) != COLOR_MAP.end())
        return COLOR_MAP.at(colorString);
    else
    {
        CCLOG("do't understand color string: %s, return white color", colorString.c_str());
        return COLOR_MAP.at("white");
    }
}

std::string RichtextStringVisitor::convertAttributeName(const std::string& tagName, const std::string& attributeName) const
{
    // <outline width...> -> <outline size...>
    if (tagName == "outline" && attributeName == "width")
        return "size";
    else
        return attributeName;
}

std::string RichtextStringVisitor::convertAttributeValue(const std::string& tagName, const std::string& attributeName, const std::string& attributeValue) const
{
    if (attributeName == "color")
        return convertColorString2Hex(attributeValue);
    
    if (tagName == RichtextStringVisitor::IMG_FLAG && attributeName == "src")
        return attributeValue + ".png";
    
    return attributeValue;
}

NS_CCR_END
