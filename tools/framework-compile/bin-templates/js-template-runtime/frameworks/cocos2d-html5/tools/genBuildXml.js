/**
 * Put the `tools` in the root of your project, then run this script with nodejs.
 * @type {exports|*}
 */

var fs = require("fs");
var path = require("path");


module.exports = function(projectDir, projectJson, buildOpt){
    var engineDir = projectJson.engineDir || "frameworks/cocos2d-html5";
    var realEngineDir = path.join(projectDir, engineDir);
    var realPublishDir = path.join(projectDir, "publish/html5");
    var realToolsDir = path.dirname(__filename);
    var moduleConfig = require(path.join(realEngineDir, "moduleConfig.json"));
    var ccModuleMap = moduleConfig.module;
    var modules = projectJson.modules || ["core"];
    var renderMode = projectJson.renderMode || 0;
    var mainJs = projectJson.main || "main.js";


    var ccJsList = [moduleConfig.bootFile];
    var userJsList = projectJson.jsList || [];

    if(renderMode != 1 && modules.indexOf("base4webgl") < 0){
        modules.splice(0, 0, "base4webgl");
    }


    //cache for js and module that has added into jsList to be loaded.
    var _jsAddedCache = {};
    function _getJsListOfModule(moduleMap, moduleName){
        var jsAddedCache = _jsAddedCache;
        if(jsAddedCache[moduleName]) return null;
        jsAddedCache[moduleName] = true;
        var jsList = [];
        var tempList = moduleMap[moduleName];
        if(!tempList) throw "can not find module [" + moduleName + "]";
        for(var i = 0, li = tempList.length; i < li; i++){
            var item = tempList[i];
            if(jsAddedCache[item]) continue;
            var extname = path.extname(item);
            if(!extname) {
                var arr = _getJsListOfModule(moduleMap, item);
                if(arr) jsList = jsList.concat(arr);
            }else if(extname.toLowerCase() == ".js") jsList.push(item);
            jsAddedCache[item] = true;
        }
        return jsList;
    };



    for(var i = 0, li = modules.length; i < li; i++){
        var item = modules[i];
        var arr = _getJsListOfModule(ccModuleMap, item, "");
        if(arr) ccJsList = ccJsList.concat(arr);
    }

    var externalList = [];
    function getFileArrStr(jsList){
        var str = "";
        for(var i = 0, li = jsList.length; i < li; i++){
            if(/^external/.test(jsList[i]) && !/Plugin/.test(jsList[i])){
                externalList.push(jsList[i]);
            }else{
                str += '                <file name="' + jsList[i] + '"/>';
                if(i < li - 1) str += '\r\n';
            }
        }
        return str;
    }

    userJsList.push(mainJs);

    var buildContent = fs.readFileSync(path.join(realToolsDir, "template/build.xml")).toString();
    buildContent = buildContent.replace(/%projectDir%/gi, projectDir);
    buildContent = buildContent.replace(/%engineDir%/gi, realEngineDir);
    buildContent = buildContent.replace(/%publishDir%/gi, realPublishDir);
    buildContent = buildContent.replace(/%outputFileName%/gi, buildOpt.outputFileName);
    buildContent = buildContent.replace(/%toolsDir%/gi, realToolsDir);
    buildContent = buildContent.replace(/%compilationLevel%/gi, buildOpt.compilationLevel);
    buildContent = buildContent.replace(/%sourceMapCfg%/gi, buildOpt.sourceMapOpened ? 'sourceMapOutputFile="' + path.join(realPublishDir, "sourcemap") + '" sourceMapFormat="V3"' : "");
    buildContent = buildContent.replace(/%ccJsList%/gi, getFileArrStr(ccJsList));
    buildContent = buildContent.replace(/%userJsList%/gi, getFileArrStr(userJsList));
    fs.writeFileSync(path.join(realPublishDir, "build.xml"), buildContent);

    return externalList;
};
