var fs = require("fs");
var path = require("path");
var exec = require('child_process').exec;
var spawn = require('child_process').spawn;
var url = require('url');

var core4cc = {};
module.exports = core4cc;

/**
 * Desc:merge js code from client to server.
 * @param src               src path
 * @param targetDir         target path
 * @param requireArr        dependencies
 * @param name
 */
core4cc.trans2Module = function(src, targetDir, requireArr, name){
    if(!fs.existsSync(targetDir)) fs.mkdirSync(targetDir);
    var srcBaseName = path.basename(src);
    name = name || path.basename(src, ".js");
    var content = fs.readFileSync(src).toString();
    var requireStr = "";
    for(var i = 0, li = requireArr.length; i < li; ++i){
        var strs = requireArr[i].split("->");
        requireStr = requireStr + "var " + strs[0] + " = require('" + strs[1] + "');\r\n";
    }
    fs.writeFileSync(targetDir + srcBaseName, requireStr + content + "\r\nmodule.exports = " + name + ";");
};

/**
 * Desc:merge js arr to one
 * @param srcs
 * @param target
 * @param requireArr
 * @param name
 */
core4cc.merge2Module = function(srcs, target, requireArr, name){
    var targetDir = path.dirname(target);
    if(!fs.existsSync(targetDir)) fs.mkdirSync(targetDir);
    var content = "";
    for(var i = 0, li = srcs.length; i < li; ++i){
        content += fs.readFileSync(srcs[i]).toString() + "\r\n";
    }
    var requireStr = "";
    for(var i = 0, li = requireArr.length; i < li; ++i){
        var strs = requireArr[i].split("->");
        requireStr = requireStr + "var " + strs[0] + " = require('" + strs[1] + "');\r\n";
    }
    fs.writeFileSync(target, requireStr + content + "\r\nmodule.exports = " + name + ";");
};

/**
 * dESC: Get key name by the file name.
 * @param name
 * @returns {String}
 */
core4cc.getKeyName = function(name){
    var key = name.replace(/[.]/g, "_");
    key = key.replace(/[\-\(\)]/g, "_");
    var r = key.match(/^[0-9]/);
    if(r != null) key = "_" + key;
    return key.replace(/\s/g, "");
};
/**
 * Desc: Returns array for dependencies.
 * @param temp
 * @returns {Array}
 * @private
 */
core4cc.getDependencies = function(temp){
    var dependencies = [];
    for(var key in temp){
        dependencies.push(key);
    };
    return dependencies;
};

/**
 * Desc: unzip
 * @param srcZip
 * @param targetDir
 * @param cb
 */
core4cc.unzip = function(srcZip, targetDir, cb){
    var execCode = "unzip " + srcZip + " -d " + targetDir;
    exec(execCode, function(err, data, info){
        if(err) return cb(err);
        else cb(null);
    });
};



/**
 * Desc: Download resources.
 * @param downLoadDir
 * @param fileUrl
 * @param cb
 */
core4cc.download = function(downLoadDir, fileUrl, cb) {
    // extract the file name
    var fileName = url.parse(fileUrl).pathname.split('/').pop();
    // create an instance of writable stream
    var file = fs.createWriteStream(path.join(downLoadDir, fileName));
    // execute curl using child_process' spawn function
    var curl = spawn('curl', [fileUrl]);
    // add a 'data' event listener for the spawn instance
    curl.stdout.on('data', function(data) { file.write(data); });
    // add an 'end' event listener to close the writeable stream
    curl.stdout.on('end', function(data) {
        file.end();
        console.log(fileName + ' downloaded to ' + downLoadDir);
        cb(null);
    });
    // when the spawn child process exits, check if there were any errors and close the writeable stream
    curl.on('exit', function(code) {
        if (code != 0) {
            console.error('Failed: ' + code);
            cb("error")
        }
    });
};

/**
 * Desc: Remove dir recursively.
 * @param filePath
 * @param ignores
 */
core4cc.rmdirSyncRecursive = function(filePath, ignores) {
    var files = [];
    if( fs.existsSync(filePath) ) {
        if(ignores && ignores.length > 0 && ignores.indexOf(filePath) >= 0) return;
        if(!fs.statSync(filePath).isDirectory()) return fs.unlinkSync(filePath);
        files = fs.readdirSync(filePath);
        for(var i = 0, li = files.length; i < li; i++){
            var curPath = path.join(filePath, files[i]);
            core4cc.rmdirSyncRecursive(curPath, ignores); // recurse
        }
        files = fs.readdirSync(filePath);//read again
        if(files.length == 0) fs.rmdirSync(filePath);
    }
};

/**
 * Desc: Create dir recursively.
 * @param arr
 * @param index
 * @param cb
 * @returns {*}
 */
core4cc.mkdirRecursive = function(arr, index, cb){
    if(index >= arr.length) cb();
    var dir = path.join(process.cwd(), arr.slice(0, index +1).join(path.sep));
    if(fs.existsSync(dir)) return core4cc.mkdirRecursive(arr, index+1, cb);
    fs.mkdir(dir, function(){
        core4cc.mkdirRecursive(arr, index+1, cb);
    });
}
/**
 * Desc: create dir sync recursively.
 * @param targetPath
 */
core4cc.mkdirSyncRecursive = function(targetPath){
    if(targetPath == null || targetPath == "") return;
    targetPath = core4cc.isAbsolute(targetPath) ? path.normalize(targetPath) : path.join(process.cwd(), targetPath);
    if(fs.existsSync(targetPath)) return;

    var arr = targetPath.split(path.sep);
    var index = arr.length - 1;
    var tempStr = arr[index];
    while(tempStr == "" && arr.length > 0){
        index--;
        tempStr = arr[index];
    }
    if(tempStr == "") return;
    var newPath = targetPath.substring(0, targetPath.length - tempStr.length - 1);
    if(!fs.existsSync(newPath)) core4cc.mkdirSyncRecursive(newPath);
    fs.mkdirSync(targetPath);
}
/**
 * Desc: Returns true if the filePath is absolute.
 * @param filePath
 * @returns {boolean}
 */
core4cc.isAbsolute = function(filePath){
    filePath = path.normalize(filePath);
    if(filePath.substring(0, 1) == "/") return true;
    if(filePath.search(/[\w]+:/) == 0) return true;
    return false;
};

/**
 * Desc: Copy files in srcPath to targetPath, then replace info by config.
 * @param srcPath
 * @param targetPath
 * @param handler
 * @private
 */
core4cc.copyFiles = function(srcPath, targetPath, handler){
    if(!fs.statSync(srcPath).isDirectory()) return fs.writeFileSync(targetPath, fs.readFileSync(srcPath));//copy if it`s a file

    if(!fs.existsSync(targetPath)) fs.mkdirSync(targetPath);
    var files = fs.readdirSync(srcPath);
    for(var i = 0, li = files.length; i < li; i++){
        var file = files[i];
        if(fs.statSync(path.join(srcPath, file)).isDirectory()){//make dir if it`s a dir
            var dir = path.join(targetPath, file, "./");
            if(!fs.existsSync(dir)) fs.mkdirSync(dir);
            core4cc.copyFiles(path.join(srcPath, file + "/"), dir, handler);//goes on
        }else{
            var filePath = path.join(targetPath, file);
            fs.writeFileSync(filePath, fs.readFileSync(path.join(srcPath, file)));//copy if it`s a file
            if(handler) {
                handler.fmt(filePath);
            }
        }
    }
}

/**
 * Desc: Get string for command.
 * e.g. aaaa ---> aaaa
 *      "a a" ---> a a
 * @param str
 * @returns {*}
 */
core4cc.getStr4Cmd = function(str){
    if(!str) return null;
    if(str.length < 2) return str;
    return str.substring(0, 1) == '"' && str.substring(str.length - 1) == '"' ? str.substring(1, str.length - 1) : str;
}
/**
 * Desc: Merge data by default value
 * @param data
 * @param defData default value
 * @returns {{}|*}
 */
core4cc.mergeData = function(data, defData){
    data = data || {};
    if(defData == null) return data;;
    for (var key in defData) {
        if(data[key] == null && defData[key] != null) data[key] = defData[key];
    }
    return data;
}
