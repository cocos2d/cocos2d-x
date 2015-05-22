const fs = require("fs");
const path = require("path");
const modules = JSON.parse(fs.readFileSync("../moduleConfig.json"));

var contains = [
    "../cocos2d",
    "../extensions",
    "../external",
    "../Base64Images.js",
    "../CCBoot.js",
    "../CCDebugger.js"
];
(function(){
    var i = 0;
    function read(name){
        if(fs.existsSync(name)){
            var stat = fs.statSync(name);
            if(stat.isDirectory()){
                contains.splice(i--, 1);
                var fileList = fs.readdirSync(name);
                for(var n=0; n<fileList.length; n++){
                    if(/^\./.test(fileList[n])){
                        fileList.splice(n--, 1);
                    }
                }
                fileList = fileList.map(function(file){
                    return path.join(name, file);
                });
                contains = contains.concat(fileList);
            }
        }
    }
    for(; i<contains.length; i++){
        read(contains[i]);
    }

})();

console.log("  The number of files in the engine : %d", contains.length);

var moduleFile = [];
(function(){
    var module = modules.module;
    for(var p in module){
        moduleFile = moduleFile.concat(
            module[p].filter(function(file){
                if(file && /\./.test(file))
                    return file;
            })
        );
    }

    moduleFile = moduleFile.map(function(file){
        return "../" + file;
    });
})();

console.log("  Number of module within the definition file : %s", moduleFile.length);


var xmlFile = [];
var xmlFile2 = [];
(function(){
    var fileStr = fs.readFileSync("./build.xml").toString();
    var index = 0, arr = [xmlFile, xmlFile2];
    fileStr.replace(/\<sources dir\=\"\.\/\.\.\/\"\>((.|\r\n|\r|\n)*?)\<\/sources/g, function(a, b){
        a.replace(/file name\=\"(.*)\"\/\>/g, function(c, d){
            arr[index] && arr[index].push("../" + d);
        });
        index++;
    });
})();
console.log("  The number of files in the XML file : %s", xmlFile.length);

contains = contains.map(function(a){
    return path.normalize(a);
});
moduleFile = moduleFile.map(function(a){
    return path.normalize(a);
});
xmlFile = xmlFile.map(function(a){
    return path.normalize(a);
});
xmlFile2 = xmlFile2.map(function(a){
    return path.normalize(a);
});

console.log("\x1B[0m\x1B[33m");
console.log("  warn : moduleConfig missing...");
contains.forEach(function(a){
    if(!moduleFile.some(function(b){return b==a}))
        console.log("     " + a);
});


console.log("\x1B[0m\x1B[92m");
console.log("  warn : engine dir missing...");
moduleFile.forEach(function(a){
    if(!contains.some(function(b){return b==a}))
        console.log("     " + a);
});


console.log("\x1B[0m\x1B[96m");
console.log("  warn : xml(all) file missing...");
contains.forEach(function(a){
    if(!xmlFile.some(function(b){return b==a}))
        console.log("     " + a);
});


console.log("\x1B[0m\x1B[91m");
console.log("  warn : xml(all) redundant files...");
xmlFile.forEach(function(a){
    if(!contains.some(function(b){return b==a}))
        console.log("     " + a);
});


console.log("\x1B[0m\x1B[94m");
console.log("  warn : xml(core) maybe missing files...");
xmlFile2.forEach(function(a){
    var basename = path.basename(a);
    basename = basename.substr(0, basename.indexOf("."));
    contains.forEach(function(b){
        if(b.indexOf(basename) > -1 && a != b){
            if(
                b.indexOf("extensions") == -1 &&
                !xmlFile2.some(function(c){return b == c;})
                )
                console.log("     " + b);
        }
    });
});


console.log("\x1B[0m\x1B[35m");
console.log("  warn : xml(core) redundant files...");
xmlFile2.forEach(function(a){
    if(!contains.some(function(b){return b==a}))
        console.log("     " + a);
});
console.log("\x1B[0m");