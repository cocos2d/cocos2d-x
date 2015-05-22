/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
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
 * The audio component for Cocostudio.
 * @class
 * @extends ccs.Component
 */
ccs.ComAudio = ccs.Component.extend(/** @lends ccs.ComAudio# */{
    _filePath: "",
    _loop: false,

    /**
     * Construction of ccs.ComAudio
     */
    ctor: function () {
        cc.Component.prototype.ctor.call(this);
        this._name = "Audio";
        ccs.ComAudio.prototype.init.call(this);
    },

    /**
     * Initializes a ccs.ComAudio.
     * @returns {boolean}
     */
    init: function () {
        return true;
    },

    /**
     * The callback calls when a audio component enter stage.
     * @override
     */
    onExit: function () {
        this.stopBackgroundMusic(true);
        this.stopAllEffects();
    },

    /**
     * Stops all audios.
     */
    end: function () {
        cc.audioEngine.end();
    },

    /**
     * Preload background music resource
     * @param {String} pszFilePath
     */
    preloadBackgroundMusic: function (pszFilePath) {
        cc.loader.load(pszFilePath);
    },

    /**
     * Play background music
     * @param {String} [pszFilePath]
     * @param {Boolean} [loop]
     */
    playBackgroundMusic: function (pszFilePath, loop) {
        if(pszFilePath){
            cc.audioEngine.playMusic(pszFilePath, loop);
        }else{
            cc.audioEngine.playMusic(this._filePath, this._loop);
        }
    },

    /**
     * Stop background music
     * @param {String} releaseData
     */
    stopBackgroundMusic: function (releaseData) {
        cc.audioEngine.stopMusic(releaseData);
    },

    /**
     * Pause background music
     */
    pauseBackgroundMusic: function () {
        cc.audioEngine.pauseMusic();
    },

    /**
     * Resume background music
     */
    resumeBackgroundMusic: function () {
        cc.audioEngine.resumeMusic();
    },

    /**
     * Rewind background music
     */
    rewindBackgroundMusic: function () {
        cc.audioEngine.rewindMusic();
    },

    /**
     * Indicates whether any background music can be played or not.
     * @returns {boolean}
     */
    willPlayBackgroundMusic: function () {
        return cc.audioEngine.willPlayMusic();
    },

    /**
     * Whether the music is playing.
     * @returns {Boolean}
     */
    isBackgroundMusicPlaying: function () {
        return cc.audioEngine.isMusicPlaying();
    },

    /**
     * The volume of the music max value is 1.0,the min value is 0.0 .
     * @returns {Number}
     */
    getBackgroundMusicVolume: function () {
        return cc.audioEngine.getMusicVolume();
    },

    /**
     * Set the volume of music.
     * @param {Number} volume   must be in 0.0~1.0 .
     */
    setBackgroundMusicVolume: function (volume) {
        cc.audioEngine.setMusicVolume(volume);
    },

    /**
     * The volume of the effects max value is 1.0,the min value is 0.0 .
     * @returns {Number}
     */
    getEffectsVolume: function () {
        return cc.audioEngine.getEffectsVolume();
    },

    /**
     * Set the volume of sound effects.
     * @param {Number} volume
     */
    setEffectsVolume: function (volume) {
        cc.audioEngine.setEffectsVolume(volume);
    },

    /**
     * Play sound effect.
     * @param {String} [pszFilePath]
     * @param {Boolean} [loop]
     * @returns {Boolean}
     */
    playEffect: function (pszFilePath, loop) {
        if (pszFilePath)
            return cc.audioEngine.playEffect(pszFilePath, loop);
         else
            return cc.audioEngine.playEffect(this._filePath, this._loop);
    },

    /**
     * Pause playing sound effect.
     * @param {Number} soundId
     */
    pauseEffect: function (soundId) {
        cc.audioEngine.pauseEffect(soundId);
    },

    /**
     * Pause all effects
     */
    pauseAllEffects: function () {
        cc.audioEngine.pauseAllEffects();
    },

    /**
     * Resume effect
     * @param {Number} soundId
     */
    resumeEffect: function (soundId) {
        cc.audioEngine.resumeEffect(soundId);
    },

    /**
     * Resume all effects
     */
    resumeAllEffects: function () {
        cc.audioEngine.resumeAllEffects();
    },

    /**
     * Stop effect
     * @param {Number} soundId
     */
    stopEffect: function (soundId) {
        cc.audioEngine.stopEffect(soundId);
    },

    /**
     * stop all effects
     */
    stopAllEffects: function () {
        cc.audioEngine.stopAllEffects();
    },

    /**
     * Preload effect
     * @param {String} pszFilePath
     */
    preloadEffect: function (pszFilePath) {
        cc.loader.getRes(pszFilePath);
        this.setFile(pszFilePath);
        this.setLoop(false);
    },

    /**
     * Unload effect
     * @param {String} pszFilePath
     */
    unloadEffect: function (pszFilePath) {
        cc.audioEngine.unloadEffect(pszFilePath);
    },

    /**
     * File path setter
     * @param {String} pszFilePath
     */
    setFile: function (pszFilePath) {
        this._filePath = pszFilePath;
    },

    /**
     * Sets audio component whether plays loop
     * @param {Boolean} loop
     */
    setLoop: function (loop) {
        this._loop = loop;
    },

    /**
     * Returns the file path of audio component.
     * @returns {string}
     */
    getFile: function () {
        return this._filePath;
    },

    /**
     * Returns audio component whether plays loop
     * @returns {boolean}
     */
    isLoop: function () {
        return this._loop;
    }
});

/**
 * allocates and initializes a ComAudio.
 * @deprecated since v3.0, please use new construction instead.
 * @return {ccs.ComAudio}
 * @example
 * // example
 * var com = ccs.ComAudio.create();
 */
ccs.ComAudio.create = function () {
    return new ccs.ComAudio();
};