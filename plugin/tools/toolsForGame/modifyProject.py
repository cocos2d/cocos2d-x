import sys, string, os
from xml.etree import ElementTree as ET
from xml.dom import minidom

projFile = sys.argv[1]
targetPath = sys.argv[2]

def getLinkElement():
    global targetPath
    ret = ET.Element('link')
    nameEle = ET.Element('name')
    nameEle.text = 'plugin-x'
    typeEle = ET.Element('type')
    typeEle.text = '2'
    locEle = ET.Element('locationURI')
    locEle.text = targetPath
    ret.append(nameEle)
    ret.append(typeEle)
    ret.append(locEle)
    
    return ret

tree = ET.parse(projFile)
root = tree.getroot()
nodeLinkRes = root.find('linkedResources')
if nodeLinkRes != None:
    linkNodes = nodeLinkRes.findall('link')
    haveTarget = False
    if linkNodes != None and len(linkNodes) > 0:
        for node in linkNodes:
            locNode = node.find('locationURI')
            if locNode == None:
                continue
            tempText = locNode.text
            tempText = tempText.strip(' \n\r\t')
            if tempText == targetPath:
                haveTarget = True
                break
    if not haveTarget:
        nodeLinkRes.append(getLinkElement())
        tree.write(projFile, 'UTF-8')
else:
    linkResEle = ET.Element('linkedResources')
    linkResEle.append(getLinkElement())
    root.append(linkResEle)
    tree.write(projFile, 'UTF-8')
