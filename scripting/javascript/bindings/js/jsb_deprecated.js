// Deprecated functions

var cc = cc || {};

(function() {

    var logW = function(old_name, new_name) {
        cc.log("\n********** \n"+old_name +" was deprecated, please use "+ new_name +" instead.\n**********");
    };

    // Deprecated static functions
    cc.AnimationCache.purgeSharedAnimationCache = function() {
        logW("cc.AnimationCache.purgeSharedAnimationCache", "cc.AnimationCache.destroyInstance");
        cc.AnimationCache.destroyInstance();
    };

    // Deprecated member functions
    cc.Action.prototype.copy = function() {
        logW("cc.Action.copy", "cc.Action.clone");
        return cc.Action.prototype.clone.apply(this, arguments);
    };

    cc.Animation.prototype.copy = function() {
        logW("cc.Animation.copy", "cc.Animation.clone");
        return cc.Animation.prototype.clone.apply(this, arguments);
    };

})();
