var exec = require("child_process").exec;
var fs = require("fs");
var path = require("path");
var core4cc = require("./core4cc");
console.log("Publishing...");

var projectDir = path.join(__dirname, "../");

var projectJson = require(path.join(projectDir, "project.json"));
var engineDir = path.join(projectJson.engineDir || "frameworks/cocos2d-html5", "/");
var realEngineDir = path.join(projectDir, engineDir, "/");

var realPublishDir = path.join(projectDir, "publish/html5");

var buildOpt = {
    outputFileName : "game.min.js",
//    compilationLevel : "simple",
    compilationLevel : "advanced",
    sourceMapOpened : true
};

if(!fs.existsSync(realPublishDir)) core4cc.mkdirSyncRecursive(realPublishDir);

var externalList = require("./genBuildXml")(projectDir, projectJson, buildOpt);

var outputJsPath = path.join(realPublishDir, buildOpt.outputFileName);
if(fs.existsSync(outputJsPath)) fs.unlinkSync(outputJsPath);

exec("cd " + realPublishDir + " && ant", function(err, data, info){
    console.log(info);
    console.log(data);
    if(err) {
        console.error(err);
        console.log(err[0]);
        return console.log("Failed!")
    }
    var sourceMapPath = path.join(realPublishDir, "sourcemap");
    if(fs.existsSync(sourceMapPath)){
        var smContent = fs.readFileSync(sourceMapPath).toString();
        smContent = smContent.replace(new RegExp(path.join(projectDir, "/").replace(/\\/g, "\\\\\\\\") , "gi"), path.join(path.relative(realPublishDir, projectDir), "/"));
        smContent = smContent.replace(new RegExp(path.join(realEngineDir, "/").replace(/\\/g, "\\\\\\\\"), "gi"), path.join(path.relative(realPublishDir, realEngineDir), "/"));
        fs.writeFileSync(sourceMapPath, smContent);
    }

    delete projectJson.engineDir;
    delete projectJson.modules;
    delete projectJson.jsList;
    fs.writeFileSync(path.join(realPublishDir, "project.json"), JSON.stringify(projectJson, null, 4));

    var publishResDir = path.join(realPublishDir, "res");
    core4cc.rmdirSyncRecursive(publishResDir);
    core4cc.copyFiles(path.join(projectDir, "res"), publishResDir);

    var indexContent = fs.readFileSync(path.join(projectDir, "index.html")).toString();
    var externalScript = "";
    externalList.forEach(function(external){
        externalScript += "<script src=\"" + path.join("../../", engineDir, external) + "\"></script>\n";
    });
    indexContent = indexContent.replace(/<script\s+src\s*=\s*("|')[^"']*CCBoot\.js("|')\s*><\/script>/g, externalScript);
    indexContent = indexContent.replace(/"main\.js"\s*/, '"' + buildOpt.outputFileName + '"');

    externalScript = "";
    [
        "external/pluginx/platform/facebook_sdk.js",
        "external/pluginx/platform/facebook.js"
    ].forEach(function(external){
        externalScript += "\n<script src=\"" + path.join("../../", engineDir, external) + "\"></script>";
    });
    indexContent += externalScript;
    fs.writeFileSync(path.join(realPublishDir, "index.html"), indexContent);
    console.log("Finished!")
});