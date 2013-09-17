import sys, string, os
from xml.etree import ElementTree as ET
from xml.dom import minidom

classPathFile = sys.argv[1]
pluginStr = sys.argv[2]
pluginsDir = sys.argv[3]

def getLibElement(pathAttr):
    ret = ET.Element('classpathentry')
    ret.set('exported', 'true')
    ret.set('kind', 'lib')
    ret.set('path', pathAttr)
    return ret

def fomatTree(elem):
    root_str = ET.tostring(elem, 'UTF-8')
    reparse = minidom.parseString(root_str)
    return reparse

tree = ET.parse(classPathFile)
root = tree.getroot()
entryNodes = root.findall('classpathentry')
linkedLibs = []
for node in entryNodes:
    entryKind = node.get('kind')
    entryPath = node.get('path')
    entryKind = entryKind.strip(' \n\r\t')
    entryPath = entryPath.strip(' \n\r\t')
    if entryKind == 'lib' and entryPath.endswith('.jar'):
        linkedLibs.append(entryPath)

plugins = pluginStr.split(':')
modified = False
for pluginName in plugins:
    pluginAndroidDir = pluginsDir + '/' + pluginName + '/android'
    
    for fileName in os.listdir(pluginAndroidDir):
        if os.path.splitext(fileName)[1] == '.jar':
            needAdd = True
            for linkedJar in linkedLibs:
                jarName = os.path.basename(linkedJar)
                if fileName == jarName:
                    needAdd = False
                    break
            
            if needAdd:
                modified = True
                pathAttr = 'plugin-x/' + pluginName + '/android/' + fileName
                root.append(getLibElement(pathAttr))
                linkedLibs.append(pathAttr)

if modified:
    f = open(classPathFile, 'w')
    fomatDom = fomatTree(root)
    fomatDom.writexml(f, '', '\t', '\n', 'UTF-8')
    f.close()
