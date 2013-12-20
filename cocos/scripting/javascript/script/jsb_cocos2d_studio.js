//
// cocos2d studio constants
//
// This helper file should be required after jsb_cocos2d.js
//

var ccs = ccs || {};

//movement event type
ccs.MovementEventType = {
    start: 0,
    complete: 1,
    loopComplete: 2
};

// Armature
if(ccs.Armature){
	ccs.Armature.prototype.setBody = function( body ) {
    var b = body;
    if( body.handle !== undefined )
        b = body.handle;
    return this._setCPBody( b );
  };
  
  ccs.ComController.extend = cc.Class.extend;
  ccs.Armature.extend = cc.Class.extend;
}
