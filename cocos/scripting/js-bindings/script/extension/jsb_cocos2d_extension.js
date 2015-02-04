/*
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * @type {Object}
 * @name jsb.AssetsManager
 * jsb.AssetsManager is the native AssetsManager for your game resources or scripts.
 * please refer to this document to know how to use it: http://www.cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/en
 * Only available in JSB
 */
jsb.AssetsManager = cc.AssetsManager;
delete cc.AssetsManager;
/**
 * @type {Object}
 * @name jsb.EventListenerAssetsManager
 * jsb.EventListenerAssetsManager is the native event listener for AssetsManager.
 * please refer to this document to know how to use it: http://www.cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/en
 * Only available in JSB
 */
jsb.EventListenerAssetsManager = cc.EventListenerAssetsManager;
delete cc.EventListenerAssetsManager;
/**
 * @type {Object}
 * @name jsb.EventAssetsManager
 * jsb.EventAssetsManager is the native event for AssetsManager.
 * please refer to this document to know how to use it: http://www.cocos2d-x.org/docs/manual/framework/html5/v3/assets-manager/en
 * Only available in JSB
 */
jsb.EventAssetsManager = cc.EventAssetsManager;
delete cc.EventAssetsManager;

// move from jsb_cocos2d
//start------------------------------
cc.ControlButton.extend = cc.Class.extend;
cc.ControlColourPicker.extend = cc.Class.extend;
cc.ControlPotentiometer.extend = cc.Class.extend;
cc.ControlSlider.extend = cc.Class.extend;
cc.ControlStepper.extend = cc.Class.extend;
cc.ControlSwitch.extend = cc.Class.extend;
//end------------------------------

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

cc.CONTROL_ZOOM_ACTION_TAG = 0xCCCB0001;       //CCControlButton.js

cc.CONTROL_STEPPER_PARTMINUS = 0;               //CCControlStepper.js
cc.CONTROL_STEPPER_PARTPLUS = 1;
cc.CONTROL_STEPPER_PARTNONE = 2;
cc.CONTROL_STEPPER_LABELCOLOR_ENABLED = cc.color(55, 55, 55);
cc.CONTROL_STEPPER_LABELCOLOR_DISABLED = cc.color(147, 147, 147);
cc.CONTROL_STEPPER_LABELFONT = "CourierNewPSMT";
cc.AUTOREPEAT_DELTATIME = 0.15;
cc.AUTOREPEAT_INCREASETIME_INCREMENT = 12;


jsb.EventAssetsManager.ERROR_NO_LOCAL_MANIFEST = 0;
jsb.EventAssetsManager.ERROR_DOWNLOAD_MANIFEST = 1;
jsb.EventAssetsManager.ERROR_PARSE_MANIFEST = 2;
jsb.EventAssetsManager.NEW_VERSION_FOUND = 3;
jsb.EventAssetsManager.ALREADY_UP_TO_DATE = 4;
jsb.EventAssetsManager.UPDATE_PROGRESSION = 5;
jsb.EventAssetsManager.ASSET_UPDATED = 6;
jsb.EventAssetsManager.ERROR_UPDATING = 7;
jsb.EventAssetsManager.UPDATE_FINISHED = 8;
jsb.EventAssetsManager.UPDATE_FAILED = 9;
jsb.EventAssetsManager.ERROR_DECOMPRESS = 10;

cc.ScrollView.extend = cc.Class.extend;
cc.TableView.extend = cc.Class.extend;
cc.TableViewCell.extend = cc.Class.extend;

