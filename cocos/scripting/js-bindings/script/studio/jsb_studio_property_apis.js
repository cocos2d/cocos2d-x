/*
 * Copyright (c) 2014 Chukong Technologies Inc.
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

var _proto = ccs.Bone.prototype;
cc.defineGetterSetter(_proto, "color", _proto.getColor, _proto.setColor);
cc.defineGetterSetter(_proto, "opacity", _proto.getOpacity, _proto.setOpacity);
cc.defineGetterSetter(_proto, "zIndex", _proto.getLocalZOrder, _proto.setLocalZOrder);
cc.defineGetterSetter(_proto, "boneData", _proto.getBoneData, _proto.setBoneData);
cc.defineGetterSetter(_proto, "armature", _proto.getArmature, _proto.setArmature);
cc.defineGetterSetter(_proto, "parentBone", _proto.getParentBone, _proto.setParentBone);
cc.defineGetterSetter(_proto, "childArmature", _proto.getChildArmature, _proto.setChildArmature);
cc.defineGetterSetter(_proto, "childrenBone", _proto.getChildrenBone);
cc.defineGetterSetter(_proto, "tween", _proto.getTween);
cc.defineGetterSetter(_proto, "tweenData", _proto.getTweenData);
cc.defineGetterSetter(_proto, "transformDirty", _proto.getTransformDirty, _proto.setTransformDirty);
cc.defineGetterSetter(_proto, "colliderFilter", _proto.getColliderFilter, _proto.setColliderFilter);
cc.defineGetterSetter(_proto, "displayManager", _proto.getDisplayManager, _proto.setDisplayManager);
cc.defineGetterSetter(_proto, "ignoreMovementBoneData", _proto.getIgnoreMovementBoneData, _proto.setIgnoreMovementBoneData);
cc.defineGetterSetter(_proto, "name", _proto.getName, _proto.setName);
cc.defineGetterSetter(_proto, "blendDirty", _proto.getBlendDirty, _proto.setBlendDirty);

_proto = ccs.Armature.prototype;
cc.defineGetterSetter(_proto, "parentBone", _proto.getParentBone, _proto.setParentBone);
cc.defineGetterSetter(_proto, "animation", _proto.getAnimation, _proto.setAnimation);
cc.defineGetterSetter(_proto, "armatureData", _proto.getArmatureData, _proto.setArmatureData);
cc.defineGetterSetter(_proto, "name", _proto.getName, _proto.setName);
cc.defineGetterSetter(_proto, "batchNode", _proto.getBatchNode, _proto.setBatchNode);
cc.defineGetterSetter(_proto, "version", _proto.getVersion, _proto.setVersion);
cc.defineGetterSetter(_proto, "body", _proto.getBody, _proto.setBody);
cc.defineGetterSetter(_proto, "colliderFilter", _proto.setColliderFilter);

_proto = ccs.Skin.prototype;
cc.defineGetterSetter(_proto, "skinData", _proto.getSkinData, _proto.setSkinData);
cc.defineGetterSetter(_proto, "bone", _proto.getBone, _proto.setBone);
cc.defineGetterSetter(_proto, "displayName", _proto.getDisplayName);

_proto = ccs.ColliderDetector.prototype;
cc.defineGetterSetter(_proto, "colliderFilter", _proto.getColliderFilter, _proto.setColliderFilter);
cc.defineGetterSetter(_proto, "active", _proto.getActive, _proto.setActive);
cc.defineGetterSetter(_proto, "body", _proto.getBody, _proto.setBody);