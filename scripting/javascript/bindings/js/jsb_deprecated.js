// Deprecated functions

var cc = cc || {};

(function() {

    var logW = function(old_name, new_name) {
        cc.log("\n********** \n"+old_name +" was deprecated, please use "+ new_name +" instead.\n**********");
    };

    cc.AnimationCache.purgeSharedAnimationCache = function() {
        logW("cc.AnimationCache.purgeSharedAnimationCache", "cc.AnimationCache.destroyInstance");
        cc.AnimationCache.destroyInstance();
    };

    // Example of deprecating a member function
    // cc.TiledGrid3DAction.prototype.originalTile = function() {
    //     logW("cc.TiledGrid3DAction.prototype.originalTile", "cc.TiledGrid3DAction.prototype.getOriginalTile");
    //     return cc.TiledGrid3DAction.prototype.getOriginalTile.apply(this, arguments);
    // };


})();
