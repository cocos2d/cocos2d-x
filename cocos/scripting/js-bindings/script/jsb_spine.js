/*
 * Copyright (c) 2013-2016 Chukong Technologies Inc.
 * Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
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

sp.ANIMATION_EVENT_TYPE = {
	START: 0,
    INTERRUPT: 1,
	END: 2,
	COMPLETE: 3,
    DISPOSE: 4,
	EVENT: 5
};

// Temporary solution before upgrade the Spine API
sp.SkeletonAnimation.prototype.setAnimationListener = function (target, callback) {
    this._target = target;
    this._callback = callback;

    this.setStartListener(function (trackIndex) {
    	if (this._target && this._callback) {
            this._callback.call(this._target, this, trackIndex, sp.ANIMATION_EVENT_TYPE.START, null, 0);
        }
    });

    this.setEndListener(function (trackIndex) {
    	if (this._target && this._callback) {
            this._callback.call(this._target, this, trackIndex, sp.ANIMATION_EVENT_TYPE.END, null, 0);
        }
    });

    this.setCompleteListener(function (trackIndex, loopCount) {
    	if (this._target && this._callback) {
            this._callback.call(this._target, this, trackIndex, sp.ANIMATION_EVENT_TYPE.COMPLETE, null, loopCount);
        }
    });

    this.setEventListener(function (trackIndex, event) {
    	if (this._target && this._callback) {
            this._callback.call(this._target, this, trackIndex, sp.ANIMATION_EVENT_TYPE.EVENT, event, 0);
        }
    });
}