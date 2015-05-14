/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

/**
 * Facebook SDK for Web Platform <br/>
 * FacebookAgent...
 *
 * @property {String} name - plugin name
 * @property {String} version - API version
 */
plugin.extend('facebook', {
    name: "",
    version: "",
    _userInfo: null,
    _isLoggedIn: false,

    /**
     * HTTP methods constants
     * @constant
     * @type {Object}
     */
    HttpMethod: {
        'GET': 'get',
        'POST': 'post',
        'DELETE': 'delete'
    },

    /**
     * Succeed code returned in callbacks
     * @constant
     * @type {Number}
     */
    CODE_SUCCEED: 0,

    /**
     * App event names constants
     * @constant
     * @type {Object}
     */
    AppEvent: {
        'ACTIVATED_APP': FB.AppEvents.EventNames.ACTIVATED_APP,
        'COMPLETED_REGISTRATION': FB.AppEvents.EventNames.COMPLETED_REGISTRATION,
        'VIEWED_CONTENT': FB.AppEvents.EventNames.VIEWED_CONTENT,
        'SEARCHED': FB.AppEvents.EventNames.SEARCHED,
        'RATED': FB.AppEvents.EventNames.RATED,
        'COMPLETED_TUTORIAL': FB.AppEvents.EventNames.COMPLETED_TUTORIAL,
        'ADDED_TO_CART': FB.AppEvents.EventNames.ADDED_TO_CART,
        'ADDED_TO_WISHLIST': FB.AppEvents.EventNames.ADDED_TO_WISHLIST,
        'INITIATED_CHECKOUT': FB.AppEvents.EventNames.INITIATED_CHECKOUT,
        'ADDED_PAYMENT_INFO': FB.AppEvents.EventNames.ADDED_PAYMENT_INFO,
        'PURCHASED': FB.AppEvents.EventNames.PURCHASED,
        'ACHIEVED_LEVEL': FB.AppEvents.EventNames.ACHIEVED_LEVEL,
        'UNLOCKED_ACHIEVEMENT': FB.AppEvents.EventNames.UNLOCKED_ACHIEVEMENT,
        'SPENT_CREDITS': FB.AppEvents.EventNames.SPENT_CREDITS
    },

    /**
     * App event parameter names constants
     * @constant
     * @type {Object}
     */
    AppEventParam: {
        'CURRENCY': FB.AppEvents.ParameterNames.CURRENCY,
        'REGISTRATION_METHOD': FB.AppEvents.ParameterNames.REGISTRATION_METHOD,
        'CONTENT_TYPE': FB.AppEvents.ParameterNames.CONTENT_TYPE,
        'CONTENT_ID': FB.AppEvents.ParameterNames.CONTENT_ID,
        'SEARCH_STRING': FB.AppEvents.ParameterNames.SEARCH_STRING,
        'SUCCESS': FB.AppEvents.ParameterNames.SUCCESS,
        'MAX_RATING_VALUE': FB.AppEvents.ParameterNames.MAX_RATING_VALUE,
        'PAYMENT_INFO_AVAILABLE': FB.AppEvents.ParameterNames.PAYMENT_INFO_AVAILABLE,
        'NUM_ITEMS': FB.AppEvents.ParameterNames.NUM_ITEMS,
        'LEVEL': FB.AppEvents.ParameterNames.LEVEL,
        'DESCRIPTION': FB.AppEvents.ParameterNames.DESCRIPTION
    },

    /**
     * App event parameter values constants
     * @constant
     * @type {Object}
     */
    AppEventParamValue: {
        'VALUE_YES': "1",
        'VALUE_NO': "0"
    },

    _checkLoginStatus: function() {
        var self = this;
        FB.getLoginStatus(function (response) {
            if (response && response.status === 'connected') {
                //login
                self._isLoggedIn = true;
                //save user info
                self._userInfo = response['authResponse'];
            } else {
                // Reset cached status
                self._isLoggedIn = false;
                self._userInfo = {};
            }
        });
    },

    ctor: function (config) {
        this.name = "facebook";
        this.version = "1.0";
        this._userInfo = {};
        this._isLoggedIn = false;

        if (!FB) {
            return;
        }

        //This configuration will be read from the project.json.
        FB.init(config);
        this._checkLoginStatus();

        plugin.FacebookAgent = this;
    },
    /**
     * Gets the current object
     * @returns {FacebookAgent}
     */
    getInstance: function () {
        return this;
    },
    /**
     * Login to facebook
     * @param {Function} callback
     * @param {Array} permissions
     * @example
     * //example
     * plugin.FacebookAgent.login();
     */
    login: function (permissions, callback) {
        var self = this;
        if (typeof permissions == 'function') {
            callback = permissions;
            permissions = [];
        }
        if (permissions.every(function (item) {
            if (item != 'public_profile')
                return true;
        })) {
            permissions.push("public_profile");
        }
        var permissionsStr = permissions.join(',');
        FB.login(function (response) {
            if (response['authResponse']) {
                //save user info
                self._isLoggedIn = true;
                self._userInfo = response['authResponse'];
                var permissList = response['authResponse']['grantedScopes'].split(",");
                typeof callback === 'function' && callback(0, {
                    accessToken: response['authResponse']['accessToken'],
                    permissions: permissList
                });
            } else {
                self._isLoggedIn = false;
                self._userInfo = {};
                typeof callback === 'function' && callback(response['error_code'] || 1, {
                    error_message: response['error_message'] || "Unknown error"
                });
            }
        }, {
            scope: permissionsStr,
            return_scopes: true
        });
    },
    /**
     * Checking login status
     * @return {Bool} Whether user is logged in
     * @example
     * //example
     * plugin.FacebookAgent.isLoggedIn(type, msg);
     */
    isLoggedIn: function () {
        //this._checkLoginStatus();
        return this._isLoggedIn;
    },

    /**
     * Logout of facebook
     * @param {Function} callback
     * @example
     * //example
     * plugin.FacebookAgent.logout(callback);
     */
    logout: function (callback) {
        var self = this;
        FB.logout(function (response) {
            if (response['authResponse']) {
                // user is now logged out
                self._isLoggedIn = false;
                self._userInfo = {};
                typeof callback === 'function' && callback(0, {"isLoggedIn": false});
            } else {
                typeof callback === 'function' && callback(response['error_code'] || 1, {
                    error_message: response['error_message'] || "Unknown error"
                });
            }
        });
    },

    /**
     * Acquiring new permissions
     * @deprecated since v3.0
     * @param permissions
     * @param callback
     * @example
     * //example
     * plugin.FacebookAgent.requestPermissions(["manage_pages"], callback);
     */
    _requestPermissions: function (permissions, callback) {
        var permissionsStr = permissions.join(',');
        var self = this;
        FB.login(function (response) {
            if (response['authResponse']) {
                var permissList = response['authResponse']['grantedScopes'].split(",");
                //save user info
                self._isLoggedIn = true;
                self._userInfo = response['authResponse'];
                typeof callback === 'function' && callback(0, {
                    permissions: permissList
                });
            } else {
                self._isLoggedIn = false;
                self._userInfo = {};
                typeof callback === 'function' && callback(response['error_code'] || 1, {
                    error_message: response['error_message'] || "Unknown error"
                });
            }
        }, {
            scope: permissionsStr,
            return_scopes: true
        });
    },

    /**
     * Acquiring AccessToken
     * @return {String}
     * @example
     * //example
     * var accessToken = plugin.FacebookAgent.getAccessToken();
     */
    getAccessToken: function () {
        return this._userInfo ? this._userInfo['accessToken'] : null;
    },

    /**
     * Acquiring User ID
     * @return {String}
     * @example
     * //example
     * var userID = plugin.FacebookAgent.getUserID();
     */
    getUserID: function () {
        return this._userInfo ? this._userInfo['userID'] : null;
    },

    _share: function (info, callback) {
        FB.ui({
                method: 'share',
                name: info['title'],
                caption: info['caption'],
                description: info['text'],
                href: info['link'],
                picture: info['imageUrl']
            },
            function (response) {
                if (response) {
                    if (response['post_id'])
                        typeof callback === 'function' && callback(0, {
                            didComplete: true,
                            post_id: response['post_id']
                        });
                    else
                        typeof callback === 'function' && callback(response['error_code'] || 1, {
                            error_message: response['error_message'] || "Unknown error"
                        });
                } else {
                    typeof callback === 'function' && callback(1, {
                        error_message: "Unknown error"
                    });
                }
            });
    },

    /**
     * Request a web dialog for Facebook sharing
     * @param info
     * @param callback
     */
    dialog: function (info, callback) {
        if (!info) {
            typeof callback === 'function' && callback(1, {
                error_message: "No info parameter provided"
            });
            return;
        }
        if (!this.canPresentDialog(info)) {
            typeof callback === 'function' && callback(1, {
                error_message: "The requested dialog: " + info['dialog'] + " can not be presented on Web"
            });
            return;
        }

        // Preprocess properties
        info['name'] = info['name'] || info['site'];
        delete info['site'];

        info['href'] = info['href'] || info['link'] || info['siteUrl'];
        delete info['siteUrl'];
        delete info['link'];

        info['picture'] = info['picture'] || info['image'] || info['photo'] || info['imageUrl'] || info['imagePath'];
        delete info['imageUrl'];
        delete info['imagePath'];
        delete info['photo'];
        delete info['image'];

        info['caption'] = info['title'] || info['caption'];
        delete info['title'];

        info['description'] = info['text'] || info['description'];
        delete info['text'];

        var method = info['dialog'];
        delete info['dialog'];

        if (method === 'shareLink' || method == 'feedDialog') {
            info['method'] = 'share';
        } else if (method == 'messageLink') {
            info['method'] = 'send';
            info['link'] = info['href'];
        } else if (method == 'shareOpenGraph') {
            info['method'] = 'share_open_graph';

            if (info['url']) {
                var obj = {};
                if (info["preview_property_name"])
                    obj[info["preview_property_name"]] = info["url"];
                else
                    obj["object"] = info["url"];

                for (var p in info) {
                    if (p != "method" && p != "action_type" && p != "action_properties") {
                        info[p] && (obj[p] = info[p]);
                        delete info[p];
                    }
                }

                info['action_properties'] = JSON.stringify(obj);
            }
        }

        FB.ui(info,
            function (response) {
                if (response && typeof callback === 'function') {
                    if (response['post_id'] || response['success']) {
                        callback(0, {
                            didComplete: true,
                            post_id: response['post_id'] || ""
                        });
                    }
                    else {
                        if (response['error_code']) {
                             callback(response['error_code'], {
                                 error_message : response['error_message'] || 'Unknown error'
                             });
                        }
                        else callback(0, response);
                    }
                } else if (response == undefined && typeof callback === 'function') {
                    callback(1, {
                        error_message: "Unknown error"
                    });
                }
            });
    },

    /**
     * Check whether the share request can be achieved
     * @param info
     */
    canPresentDialog: function (info) {
        if (info && info['dialog'] && (
            info['dialog'] === 'shareLink' ||
                info['dialog'] === 'feedDialog' ||
                info['dialog'] === 'shareOpenGraph' ||
                info['dialog'] === 'messageLink'))
            return true;
        else
            return false;
    },
    /**
     * FB.api
     * @param {String} path
     * @param {Number} httpmethod
     * @param {Object} params
     * @param {Function} callback
     */
    api: function (path, httpmethod, params, callback) {
        if (typeof params === 'function') {
            callback = params;
            params = {};
        }
        FB.api(path, httpmethod, params, function (response) {
            if (response.error) {
                typeof callback === 'function' && callback(response['error']['code'], {
                    error_message: response['error']['message'] || 'Unknown error'
                })
            } else {
                typeof callback === 'function' && callback(0, response);
            }
        });
    },

    _getPermissionList: function (callback) {
        FB.api("/me/permissions", function (response) {
            if (response['data']) {
                var permissionList = [];
                for (var i = 0; i < response['data'].length; i++) {
                    if (response['data'][i]["status"] == "granted") {
                        permissionList.push(response['data'][i]['permission']);
                    }
                }
                typeof callback == 'function' && callback(0, {
                    permissions: permissionList
                });
            } else {
                if (!response['error'])
                    response['error'] = {};
                typeof callback == 'function' && callback(response['error']['code'] || 1, {
                    error_message: response['error']['message'] || 'Unknown error'
                });
            }
        })
    },

    destroyInstance: function () {
    },
    canvas:{
        /**
         * Payment request
         * @param {Object} info
         * @param {Function} callback
         */
        pay: function (info, callback) {
            /*
             * Reference document
             * https://developers.facebook.com/docs/payments/reference/paydialog
             */
            info['method'] = 'pay';
            info['action'] = 'purchaseitem';

            FB.ui(info, function (response) {
                if (response['error_code']) {
                    callback(response['error_code'] || 1, {
                        error_message: response['error_message'] || response['error_msg'] || 'Unknown error'
                    });
                } else {
                    callback(0, response);
                }
            })
        }
    },

    /**
     * Send an app requests to friends
     * @param {Object} info
     * @param {Function} callback
     */
    appRequest: function (info, callback) {
        if (!info) {
            typeof callback === 'function' && callback(1, {
                error_message: "No info parameter provided"
            });
            return;
        }

        info['method'] = "apprequests";

        FB.ui(info,
            function (response) {
                if (response) {
                    if (response['error_code']) {
                        typeof callback === 'function' && callback(response['error_code'], {
                            error_message : response['error_message'] || 'Unknown error'
                        });
                    }
                    else {
                        typeof callback === 'function' && callback(0, response);
                    }
                } else {
                    typeof callback === 'function' && callback(1, {
                        error_message: "Unknown error"
                    });
                }
            });
    },

    /**
     * Log an event
     * @param {String} eventName
     * @param {Number} valueToSum
     * @param {Object} parameters
     */
    logEvent: function (eventName, valueToSum, parameters) {
        if (eventName == undefined) return;
        if (valueToSum === undefined && parameters === undefined) {
            FB.AppEvents.logEvent(eventName, null, null);
        } else if (typeof valueToSum === "number" && parameters === undefined) {
            FB.AppEvents.logEvent(eventName, valueToSum);
        } else if (typeof valueToSum === "object" && parameters === undefined) {
            FB.AppEvents.logEvent(eventName, null, valueToSum);
        } else {
            FB.AppEvents.logEvent(eventName, valueToSum, parameters);
        }
    },

    /**
     * Activate App
     */
    activateApp: function () {
        FB.AppEvents.activateApp();
    },

    /**
     * Log a purchase
     * @param {Number} amount Amount of the purchase
     * @param {String} currency The currency
     * @param {Object} param Supplemental parameters
     */
    logPurchase:function(amount, currency, param){
        FB.AppEvents.logPurchase(amount, currency, param);
    }
});
