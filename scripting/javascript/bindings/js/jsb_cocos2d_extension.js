//
// cocos2d constants
//
// This helper file should be required after jsb_cocos2d.js
//

var cc = cc || {};

cc.SCROLLVIEW_DIRECTION_NONE = -1;
cc.SCROLLVIEW_DIRECTION_HORIZONTAL = 0;
cc.SCROLLVIEW_DIRECTION_VERTICAL = 1;
cc.SCROLLVIEW_DIRECTION_BOTH = 2;
cc.TABLEVIEW_FILL_TOPDOWN = 0;
cc.TABLEVIEW_FILL_BOTTOMUP = 1;


/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_DEFAULT = 0;

/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_DONE = 1;

/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_SEND = 2;

/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_SEARCH = 3;

/**
 * @constant
 * @type Number
 */
cc.KEYBOARD_RETURNTYPE_GO = 4;

/**
 * The EditBox::InputMode defines the type of text that the user is allowed * to enter.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_ANY = 0;

/**
 * The user is allowed to enter an e-mail address.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_EMAILADDR = 1;

/**
 * The user is allowed to enter an integer value.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_NUMERIC = 2;

/**
 * The user is allowed to enter a phone number.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_PHONENUMBER = 3;

/**
 * The user is allowed to enter a URL.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_URL = 4;

/**
 * The user is allowed to enter a real number value.
 * This extends kEditBoxInputModeNumeric by allowing a decimal point.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_DECIMAL = 5;

/**
 * The user is allowed to enter any text, except for line breaks.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_MODE_SINGLELINE = 6;

/**
 * Indicates that the text entered is confidential data that should be
 * obscured whenever possible. This implies EDIT_BOX_INPUT_FLAG_SENSITIVE.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_PASSWORD = 0;

/**
 * Indicates that the text entered is sensitive data that the
 * implementation must never store into a dictionary or table for use
 * in predictive, auto-completing, or other accelerated input schemes.
 * A credit card number is an example of sensitive data.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_SENSITIVE = 1;

/**
 * This flag is a hint to the implementation that during text editing,
 * the initial letter of each word should be capitalized.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_INITIAL_CAPS_WORD = 2;

/**
 * This flag is a hint to the implementation that during text editing,
 * the initial letter of each sentence should be capitalized.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_INITIAL_CAPS_SENTENCE = 3;

/**
 * Capitalize all characters automatically.
 * @constant
 * @type Number
 */
cc.EDITBOX_INPUT_FLAG_INITIAL_CAPS_ALL_CHARACTERS = 4;

cc.CONTROL_EVENT_TOTAL_NUMBER = 9;

cc.CONTROL_EVENT_TOUCH_DOWN = 1 << 0;    // A touch-down event in the control.
cc.CONTROL_EVENT_TOUCH_DRAG_INSIDE = 1 << 1;    // An event where a finger is dragged inside the bounds of the control.
cc.CONTROL_EVENT_TOUCH_DRAG_OUTSIDE = 1 << 2;    // An event where a finger is dragged just outside the bounds of the control.
cc.CONTROL_EVENT_TOUCH_DRAG_ENTER = 1 << 3;    // An event where a finger is dragged into the bounds of the control.
cc.CONTROL_EVENT_TOUCH_DRAG_EXIT = 1 << 4;    // An event where a finger is dragged from within a control to outside its bounds.
cc.CONTROL_EVENT_TOUCH_UP_INSIDE = 1 << 5;    // A touch-up event in the control where the finger is inside the bounds of the control.
cc.CONTROL_EVENT_TOUCH_UP_OUTSIDE = 1 << 6;    // A touch-up event in the control where the finger is outside the bounds of the control.
cc.CONTROL_EVENT_TOUCH_CANCEL = 1 << 7;    // A system event canceling the current touches for the control.
cc.CONTROL_EVENT_VALUECHANGED = 1 << 8;    // A touch dragging or otherwise manipulating a control; causing it to emit a series of different values.

cc.CONTROL_STATE_NORMAL = 1 << 0; // The normal; or default state of a control梩hat is; enabled but neither selected nor highlighted.
cc.CONTROL_STATE_HIGHLIGHTED = 1 << 1; // Highlighted state of a control. A control enters this state when a touch down; drag inside or drag enter is performed. You can retrieve and set this value through the highlighted property.
cc.CONTROL_STATE_DISABLED = 1 << 2; // Disabled state of a control. This state indicates that the control is currently disabled. You can retrieve and set this value through the enabled property.
cc.CONTROL_STATE_SELECTED = 1 << 3;  // Selected state of a control. This state indicates that the control is currently selected. You can retrieve and set this value through the selected property.
cc.CONTROL_STATE_INITIAL = 1 << 3;

// PhysicsDebugNode
cc.PhysicsDebugNode.create = function( space ) {
    var s = space;
    if( space.handle !== undefined )
        s = space.handle;
    return cc.PhysicsDebugNode._create( s );
};
cc.PhysicsDebugNode.prototype.setSpace = function( space ) {
    var s = space;
    if( space.handle !== undefined )
        s = space.handle;
    return this._setSpace( s );
};

// PhysicsSprite
cc.PhysicsSprite.prototype.setBody = function( body ) {
    var b = body;
    if( body.handle !== undefined )
        b = body.handle;
    return this._setCPBody( b );
};

cc.PhysicsSprite.prototype.getBody = function() {
    return this.getCPBody();
};

cc.ScrollView.extend = cc.Class.extend;
cc.TableView.extend = cc.Class.extend;
cc.TableViewCell.extend = cc.Class.extend;
cc.GLNode.extend = cc.Class.extend;
