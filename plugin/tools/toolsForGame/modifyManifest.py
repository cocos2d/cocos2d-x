import sys, string, os
from xml.etree import ElementTree as ET

manifestFile = sys.argv[1]
pluginStr = sys.argv[2]
pluginsDir = sys.argv[3]

androidNS = 'http://schemas.android.com/apk/res/android'
sourceCfgFile = '/android/ForManifest.xml'

def doModify(sourceFile, root):
    bRet = False
    sourceTree = ET.parse(sourceFile)
    sourceRoot = sourceTree.getroot()
    
    # get target content
    f = open(manifestFile)
    targetContent = f.read()
    f.close()
    
    # check config for application
    appCfgNode = sourceRoot.find('applicationCfg')
    if appCfgNode is not None and len(appCfgNode) > 0:
        appKeyWord = appCfgNode.get('keyword')
        
        if appKeyWord != None and len(appKeyWord) > 0:
            keyIndex = targetContent.find(appKeyWord)
            if -1 == keyIndex:
                bRet = True
                for node in list(appCfgNode):
                    root.find('application').append(node)
    
    # check permission config
    perCfgNode = sourceRoot.find('permissionCfg')
    if perCfgNode is not None and len(perCfgNode) > 0:
        for oneNode in list(perCfgNode):
            key = '{' + androidNS + '}name'
            perAttr = oneNode.get(key)
            if perAttr != None and len(perAttr) > 0:
                attrIndex = targetContent.find(perAttr)
                if -1 == attrIndex:
                    bRet = True
                    root.append(oneNode)
    
    return bRet

# parse file AndroidManifest.xml of game project
ET.register_namespace("android", androidNS)
targetTree = ET.parse(manifestFile)
targetRoot = targetTree.getroot()

# traverse all plugins
plugins = pluginStr.split(':')
for pluginName in plugins:
    # find the file 'ForManifest.xml'
    sourceXml = pluginsDir + '/' + pluginName + sourceCfgFile
    if not os.path.exists(sourceXml):
        continue
    
    # check & modify target xml
    haveChanged = doModify(sourceXml, targetRoot)
    if haveChanged:
        print 'Modify AndroidManifest.xml for plugin ' + pluginName
        targetTree.write(manifestFile, 'UTF-8')
