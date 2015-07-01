/**
 * @module cocos2dx_3d
 */
var jsb = jsb || {};

/**
 * @class Animation3D
 */
jsb.Animation3D = {

/**
 * @method initWithFile
 * @param {String} arg0
 * @param {String} arg1
 * @return {bool}
 */
initWithFile : function (
str, 
str 
)
{
    return false;
},

/**
 * @method init
 * @param {cc.Animation3DData} arg0
 * @return {bool}
 */
init : function (
animation3ddata 
)
{
    return false;
},

/**
 * @method getBoneCurveByName
 * @param {String} arg0
 * @return {cc.Animation3D::Curve}
 */
getBoneCurveByName : function (
str 
)
{
    return cc.Animation3D::Curve;
},

/**
 * @method getDuration
 * @return {float}
 */
getDuration : function (
)
{
    return 0;
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @return {cc.Animation3D}
 */
create : function (
str, 
str 
)
{
    return cc.Animation3D;
},

/**
 * @method Animation3D
 * @constructor
 */
Animation3D : function (
)
{
},

};

/**
 * @class Animate3D
 */
jsb.Animate3D = {

/**
 * @method getSpeed
 * @return {float}
 */
getSpeed : function (
)
{
    return 0;
},

/**
 * @method setQuality
 * @param {cc.Animate3DQuality} arg0
 */
setQuality : function (
animate3dquality 
)
{
},

/**
 * @method setWeight
 * @param {float} arg0
 */
setWeight : function (
float 
)
{
},

/**
 * @method removeFromMap
 */
removeFromMap : function (
)
{
},

/**
 * @method initWithFrames
 * @param {cc.Animation3D} arg0
 * @param {int} arg1
 * @param {int} arg2
 * @param {float} arg3
 * @return {bool}
 */
initWithFrames : function (
animation3d, 
int, 
int, 
float 
)
{
    return false;
},

/**
 * @method getOriginInterval
 * @return {float}
 */
getOriginInterval : function (
)
{
    return 0;
},

/**
 * @method setSpeed
 * @param {float} arg0
 */
setSpeed : function (
float 
)
{
},

/**
 * @method init
* @param {cc.Animation3D|cc.Animation3D} animation3d
* @param {float} float
* @param {float} float
* @return {bool|bool}
*/
init : function(
animation3d,
float,
float 
)
{
    return false;
},

/**
 * @method setOriginInterval
 * @param {float} arg0
 */
setOriginInterval : function (
float 
)
{
},

/**
 * @method getWeight
 * @return {float}
 */
getWeight : function (
)
{
    return 0;
},

/**
 * @method getQuality
 * @return {cc.Animate3DQuality}
 */
getQuality : function (
)
{
    return 0;
},

/**
 * @method create
* @param {cc.Animation3D|cc.Animation3D} animation3d
* @param {float} float
* @param {float} float
* @return {cc.Animate3D|cc.Animate3D}
*/
create : function(
animation3d,
float,
float 
)
{
    return cc.Animate3D;
},

/**
 * @method getTransitionTime
 * @return {float}
 */
getTransitionTime : function (
)
{
    return 0;
},

/**
 * @method createWithFrames
 * @param {cc.Animation3D} arg0
 * @param {int} arg1
 * @param {int} arg2
 * @param {float} arg3
 * @return {cc.Animate3D}
 */
createWithFrames : function (
animation3d, 
int, 
int, 
float 
)
{
    return cc.Animate3D;
},

/**
 * @method setTransitionTime
 * @param {float} arg0
 */
setTransitionTime : function (
float 
)
{
},

/**
 * @method Animate3D
 * @constructor
 */
Animate3D : function (
)
{
},

};

/**
 * @class AttachNode
 */
jsb.AttachNode = {

/**
 * @method create
 * @param {cc.Bone3D} arg0
 * @return {cc.AttachNode}
 */
create : function (
bone3d 
)
{
    return cc.AttachNode;
},

/**
 * @method AttachNode
 * @constructor
 */
AttachNode : function (
)
{
},

};

/**
 * @class BillBoard
 */
jsb.BillBoard = {

/**
 * @method getMode
 * @return {cc.BillBoard::Mode}
 */
getMode : function (
)
{
    return 0;
},

/**
 * @method setMode
 * @param {cc.BillBoard::Mode} arg0
 */
setMode : function (
mode 
)
{
},

/**
 * @method create
* @param {String|cc.BillBoard::Mode|String} str
* @param {cc.BillBoard::Mode|rect_object} mode
* @param {cc.BillBoard::Mode} mode
* @return {cc.BillBoard|cc.BillBoard|cc.BillBoard}
*/
create : function(
str,
rect,
mode 
)
{
    return cc.BillBoard;
},

/**
 * @method createWithTexture
 * @param {cc.Texture2D} arg0
 * @param {cc.BillBoard::Mode} arg1
 * @return {cc.BillBoard}
 */
createWithTexture : function (
texture2d, 
mode 
)
{
    return cc.BillBoard;
},

/**
 * @method BillBoard
 * @constructor
 */
BillBoard : function (
)
{
},

};

/**
 * @class Mesh
 */
jsb.Mesh = {

/**
 * @method setTexture
* @param {cc.Texture2D|String} texture2d
*/
setTexture : function(
str 
)
{
},

/**
 * @method getTexture
 * @return {cc.Texture2D}
 */
getTexture : function (
)
{
    return cc.Texture2D;
},

/**
 * @method getSkin
 * @return {cc.MeshSkin}
 */
getSkin : function (
)
{
    return cc.MeshSkin;
},

/**
 * @method getMaterial
 * @return {cc.Material}
 */
getMaterial : function (
)
{
    return cc.Material;
},

/**
 * @method getVertexSizeInBytes
 * @return {int}
 */
getVertexSizeInBytes : function (
)
{
    return 0;
},

/**
 * @method setMaterial
 * @param {cc.Material} arg0
 */
setMaterial : function (
material 
)
{
},

/**
 * @method getName
 * @return {String}
 */
getName : function (
)
{
    return ;
},

/**
 * @method getIndexFormat
 * @return {unsigned int}
 */
getIndexFormat : function (
)
{
    return 0;
},

/**
 * @method getGLProgramState
 * @return {cc.GLProgramState}
 */
getGLProgramState : function (
)
{
    return cc.GLProgramState;
},

/**
 * @method getVertexBuffer
 * @return {unsigned int}
 */
getVertexBuffer : function (
)
{
    return 0;
},

/**
 * @method calculateAABB
 */
calculateAABB : function (
)
{
},

/**
 * @method hasVertexAttrib
 * @param {int} arg0
 * @return {bool}
 */
hasVertexAttrib : function (
int 
)
{
    return false;
},

/**
 * @method getBlendFunc
 * @return {cc.BlendFunc}
 */
getBlendFunc : function (
)
{
    return cc.BlendFunc;
},

/**
 * @method getMeshIndexData
 * @return {cc.MeshIndexData}
 */
getMeshIndexData : function (
)
{
    return cc.MeshIndexData;
},

/**
 * @method setName
 * @param {String} arg0
 */
setName : function (
str 
)
{
},

/**
 * @method getIndexCount
 * @return {long}
 */
getIndexCount : function (
)
{
    return 0;
},

/**
 * @method setMeshIndexData
 * @param {cc.MeshIndexData} arg0
 */
setMeshIndexData : function (
meshindexdata 
)
{
},

/**
 * @method getMeshVertexAttribCount
 * @return {long}
 */
getMeshVertexAttribCount : function (
)
{
    return 0;
},

/**
 * @method setBlendFunc
 * @param {cc.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method setForce2DQueue
 * @param {bool} arg0
 */
setForce2DQueue : function (
bool 
)
{
},

/**
 * @method getPrimitiveType
 * @return {unsigned int}
 */
getPrimitiveType : function (
)
{
    return 0;
},

/**
 * @method setSkin
 * @param {cc.MeshSkin} arg0
 */
setSkin : function (
meshskin 
)
{
},

/**
 * @method isVisible
 * @return {bool}
 */
isVisible : function (
)
{
    return false;
},

/**
 * @method getIndexBuffer
 * @return {unsigned int}
 */
getIndexBuffer : function (
)
{
    return 0;
},

/**
 * @method setGLProgramState
 * @param {cc.GLProgramState} arg0
 */
setGLProgramState : function (
glprogramstate 
)
{
},

/**
 * @method setVisible
 * @param {bool} arg0
 */
setVisible : function (
bool 
)
{
},

/**
 * @method Mesh
 * @constructor
 */
Mesh : function (
)
{
},

};

/**
 * @class Skeleton3D
 */
jsb.Skeleton3D = {

/**
 * @method removeAllBones
 */
removeAllBones : function (
)
{
},

/**
 * @method addBone
 * @param {cc.Bone3D} arg0
 */
addBone : function (
bone3d 
)
{
},

/**
 * @method getBoneByName
 * @param {String} arg0
 * @return {cc.Bone3D}
 */
getBoneByName : function (
str 
)
{
    return cc.Bone3D;
},

/**
 * @method getRootBone
 * @param {int} arg0
 * @return {cc.Bone3D}
 */
getRootBone : function (
int 
)
{
    return cc.Bone3D;
},

/**
 * @method updateBoneMatrix
 */
updateBoneMatrix : function (
)
{
},

/**
 * @method getBoneByIndex
 * @param {unsigned int} arg0
 * @return {cc.Bone3D}
 */
getBoneByIndex : function (
int 
)
{
    return cc.Bone3D;
},

/**
 * @method getRootCount
 * @return {long}
 */
getRootCount : function (
)
{
    return 0;
},

/**
 * @method getBoneIndex
 * @param {cc.Bone3D} arg0
 * @return {int}
 */
getBoneIndex : function (
bone3d 
)
{
    return 0;
},

/**
 * @method getBoneCount
 * @return {long}
 */
getBoneCount : function (
)
{
    return 0;
},

/**
 * @method Skeleton3D
 * @constructor
 */
Skeleton3D : function (
)
{
},

};

/**
 * @class Skybox
 */
jsb.Skybox = {

/**
 * @method reload
 */
reload : function (
)
{
},

/**
 * @method init
* @param {String} str
* @param {String} str
* @param {String} str
* @param {String} str
* @param {String} str
* @param {String} str
* @return {bool|bool}
*/
init : function(
str,
str,
str,
str,
str,
str 
)
{
    return false;
},

/**
 * @method setTexture
 * @param {cc.TextureCube} arg0
 */
setTexture : function (
texturecube 
)
{
},

/**
 * @method create
* @param {String} str
* @param {String} str
* @param {String} str
* @param {String} str
* @param {String} str
* @param {String} str
* @return {cc.Skybox|cc.Skybox}
*/
create : function(
str,
str,
str,
str,
str,
str 
)
{
    return cc.Skybox;
},

/**
 * @method Skybox
 * @constructor
 */
Skybox : function (
)
{
},

};

/**
 * @class Sprite3D
 */
jsb.Sprite3D = {

/**
 * @method setCullFaceEnabled
 * @param {bool} arg0
 */
setCullFaceEnabled : function (
bool 
)
{
},

/**
 * @method setTexture
* @param {cc.Texture2D|String} texture2d
*/
setTexture : function(
str 
)
{
},

/**
 * @method getLightMask
 * @return {unsigned int}
 */
getLightMask : function (
)
{
    return 0;
},

/**
 * @method createAttachSprite3DNode
 * @param {cc.NodeData} arg0
 * @param {cc.MaterialDatas} arg1
 */
createAttachSprite3DNode : function (
nodedata, 
materialdatas 
)
{
},

/**
 * @method loadFromFile
 * @param {String} arg0
 * @param {cc.NodeDatas} arg1
 * @param {cc.MeshDatas} arg2
 * @param {cc.MaterialDatas} arg3
 * @return {bool}
 */
loadFromFile : function (
str, 
nodedatas, 
meshdatas, 
materialdatas 
)
{
    return false;
},

/**
 * @method getMaterial
 * @param {int} arg0
 * @return {cc.Material}
 */
getMaterial : function (
int 
)
{
    return cc.Material;
},

/**
 * @method setCullFace
 * @param {unsigned int} arg0
 */
setCullFace : function (
int 
)
{
},

/**
 * @method addMesh
 * @param {cc.Mesh} arg0
 */
addMesh : function (
mesh 
)
{
},

/**
 * @method removeAllAttachNode
 */
removeAllAttachNode : function (
)
{
},

/**
 * @method setMaterial
* @param {cc.Material|cc.Material} material
* @param {int} int
*/
setMaterial : function(
material,
int 
)
{
},

/**
 * @method genGLProgramState
 */
genGLProgramState : function (
)
{
},

/**
 * @method getMesh
 * @return {cc.Mesh}
 */
getMesh : function (
)
{
    return cc.Mesh;
},

/**
 * @method createSprite3DNode
 * @param {cc.NodeData} arg0
 * @param {cc.ModelData} arg1
 * @param {cc.MaterialDatas} arg2
 * @return {cc.Sprite3D}
 */
createSprite3DNode : function (
nodedata, 
modeldata, 
materialdatas 
)
{
    return cc.Sprite3D;
},

/**
 * @method getMeshCount
 * @return {long}
 */
getMeshCount : function (
)
{
    return 0;
},

/**
 * @method onAABBDirty
 */
onAABBDirty : function (
)
{
},

/**
 * @method getMeshByIndex
 * @param {int} arg0
 * @return {cc.Mesh}
 */
getMeshByIndex : function (
int 
)
{
    return cc.Mesh;
},

/**
 * @method createNode
 * @param {cc.NodeData} arg0
 * @param {cc.Node} arg1
 * @param {cc.MaterialDatas} arg2
 * @param {bool} arg3
 */
createNode : function (
nodedata, 
node, 
materialdatas, 
bool 
)
{
},

/**
 * @method isForceDepthWrite
 * @return {bool}
 */
isForceDepthWrite : function (
)
{
    return false;
},

/**
 * @method getBlendFunc
 * @return {cc.BlendFunc}
 */
getBlendFunc : function (
)
{
    return cc.BlendFunc;
},

/**
 * @method getMeshIndexData
 * @param {String} arg0
 * @return {cc.MeshIndexData}
 */
getMeshIndexData : function (
str 
)
{
    return cc.MeshIndexData;
},

/**
 * @method setLightMask
 * @param {unsigned int} arg0
 */
setLightMask : function (
int 
)
{
},

/**
 * @method afterAsyncLoad
 * @param {void} arg0
 */
afterAsyncLoad : function (
void 
)
{
},

/**
 * @method loadFromCache
 * @param {String} arg0
 * @return {bool}
 */
loadFromCache : function (
str 
)
{
    return false;
},

/**
 * @method initFrom
 * @param {cc.NodeDatas} arg0
 * @param {cc.MeshDatas} arg1
 * @param {cc.MaterialDatas} arg2
 * @return {bool}
 */
initFrom : function (
nodedatas, 
meshdatas, 
materialdatas 
)
{
    return false;
},

/**
 * @method getAttachNode
 * @param {String} arg0
 * @return {cc.AttachNode}
 */
getAttachNode : function (
str 
)
{
    return cc.AttachNode;
},

/**
 * @method initWithFile
 * @param {String} arg0
 * @return {bool}
 */
initWithFile : function (
str 
)
{
    return false;
},

/**
 * @method setBlendFunc
 * @param {cc.BlendFunc} arg0
 */
setBlendFunc : function (
blendfunc 
)
{
},

/**
 * @method setForce2DQueue
 * @param {bool} arg0
 */
setForce2DQueue : function (
bool 
)
{
},

/**
 * @method removeAttachNode
 * @param {String} arg0
 */
removeAttachNode : function (
str 
)
{
},

/**
 * @method getSkeleton
 * @return {cc.Skeleton3D}
 */
getSkeleton : function (
)
{
    return cc.Skeleton3D;
},

/**
 * @method setForceDepthWrite
 * @param {bool} arg0
 */
setForceDepthWrite : function (
bool 
)
{
},

/**
 * @method getMeshByName
 * @param {String} arg0
 * @return {cc.Mesh}
 */
getMeshByName : function (
str 
)
{
    return cc.Mesh;
},

/**
 * @method create
* @param {String|String} str
* @param {String} str
* @return {cc.Sprite3D|cc.Sprite3D|cc.Sprite3D}
*/
create : function(
str,
str 
)
{
    return cc.Sprite3D;
},

/**
 * @method Sprite3D
 * @constructor
 */
Sprite3D : function (
)
{
},

};

/**
 * @class Sprite3DCache
 */
jsb.Sprite3DCache = {

/**
 * @method removeSprite3DData
 * @param {String} arg0
 */
removeSprite3DData : function (
str 
)
{
},

/**
 * @method removeAllSprite3DData
 */
removeAllSprite3DData : function (
)
{
},

/**
 * @method destroyInstance
 */
destroyInstance : function (
)
{
},

/**
 * @method getInstance
 * @return {cc.Sprite3DCache}
 */
getInstance : function (
)
{
    return cc.Sprite3DCache;
},

};

/**
 * @class Terrain
 */
jsb.Terrain = {

/**
 * @method initHeightMap
 * @param {char} arg0
 * @return {bool}
 */
initHeightMap : function (
char 
)
{
    return false;
},

/**
 * @method setMaxDetailMapAmount
 * @param {int} arg0
 */
setMaxDetailMapAmount : function (
int 
)
{
},

/**
 * @method setDrawWire
 * @param {bool} arg0
 */
setDrawWire : function (
bool 
)
{
},

/**
 * @method setIsEnableFrustumCull
 * @param {bool} arg0
 */
setIsEnableFrustumCull : function (
bool 
)
{
},

/**
 * @method setDetailMap
 * @param {unsigned int} arg0
 * @param {cc.Terrain::DetailMap} arg1
 */
setDetailMap : function (
int, 
map 
)
{
},

/**
 * @method resetHeightMap
 * @param {char} arg0
 */
resetHeightMap : function (
char 
)
{
},

/**
 * @method setAlphaMap
 * @param {cc.Texture2D} arg0
 */
setAlphaMap : function (
texture2d 
)
{
},

/**
 * @method setSkirtHeightRatio
 * @param {float} arg0
 */
setSkirtHeightRatio : function (
float 
)
{
},

/**
 * @method convertToTerrainSpace
 * @param {vec2_object} arg0
 * @return {vec2_object}
 */
convertToTerrainSpace : function (
vec2 
)
{
    return cc.Vec2;
},

/**
 * @method initTextures
 * @return {bool}
 */
initTextures : function (
)
{
    return false;
},

/**
 * @method initProperties
 * @return {bool}
 */
initProperties : function (
)
{
    return false;
},

/**
 * @method getHeight
* @param {vec2_object|float} vec2
* @param {vec3_object|float} vec3
* @param {vec3_object} vec3
* @return {float|float}
*/
getHeight : function(
float,
float,
vec3 
)
{
    return 0;
},

/**
 * @method setLODDistance
 * @param {float} arg0
 * @param {float} arg1
 * @param {float} arg2
 */
setLODDistance : function (
float, 
float, 
float 
)
{
},

/**
 * @method getTerrainSize
 * @return {size_object}
 */
getTerrainSize : function (
)
{
    return cc.Size;
},

/**
 * @method getIntersectionPoint
* @param {cc.Ray|cc.Ray} ray
* @param {vec3_object} vec3
* @return {bool|vec3_object}
*/
getIntersectionPoint : function(
ray,
vec3 
)
{
    return false;
},

/**
 * @method getNormal
 * @param {int} arg0
 * @param {int} arg1
 * @return {vec3_object}
 */
getNormal : function (
int, 
int 
)
{
    return cc.Vec3;
},

/**
 * @method reload
 */
reload : function (
)
{
},

/**
 * @method getImageHeight
 * @param {int} arg0
 * @param {int} arg1
 * @return {float}
 */
getImageHeight : function (
int, 
int 
)
{
    return 0;
},

/**
 * @method getMaxHeight
 * @return {float}
 */
getMaxHeight : function (
)
{
    return 0;
},

/**
 * @method getMinHeight
 * @return {float}
 */
getMinHeight : function (
)
{
    return 0;
},

};

/**
 * @class TextureCube
 */
jsb.TextureCube = {

/**
 * @method reloadTexture
 * @return {bool}
 */
reloadTexture : function (
)
{
    return false;
},

/**
 * @method create
 * @param {String} arg0
 * @param {String} arg1
 * @param {String} arg2
 * @param {String} arg3
 * @param {String} arg4
 * @param {String} arg5
 * @return {cc.TextureCube}
 */
create : function (
str, 
str, 
str, 
str, 
str, 
str 
)
{
    return cc.TextureCube;
},

/**
 * @method TextureCube
 * @constructor
 */
TextureCube : function (
)
{
},

};

/**
 * @class Bundle3D
 */
jsb.Bundle3D = {

/**
 * @method load
 * @param {String} arg0
 * @return {bool}
 */
load : function (
str 
)
{
    return false;
},

/**
 * @method loadSkinData
 * @param {String} arg0
 * @param {cc.SkinData} arg1
 * @return {bool}
 */
loadSkinData : function (
str, 
skindata 
)
{
    return false;
},

/**
 * @method clear
 */
clear : function (
)
{
},

/**
 * @method loadMaterials
 * @param {cc.MaterialDatas} arg0
 * @return {bool}
 */
loadMaterials : function (
materialdatas 
)
{
    return false;
},

/**
 * @method loadMeshDatas
 * @param {cc.MeshDatas} arg0
 * @return {bool}
 */
loadMeshDatas : function (
meshdatas 
)
{
    return false;
},

/**
 * @method loadNodes
 * @param {cc.NodeDatas} arg0
 * @return {bool}
 */
loadNodes : function (
nodedatas 
)
{
    return false;
},

/**
 * @method loadAnimationData
 * @param {String} arg0
 * @param {cc.Animation3DData} arg1
 * @return {bool}
 */
loadAnimationData : function (
str, 
animation3ddata 
)
{
    return false;
},

/**
 * @method createBundle
 * @return {cc.Bundle3D}
 */
createBundle : function (
)
{
    return cc.Bundle3D;
},

/**
 * @method destroyBundle
 * @param {cc.Bundle3D} arg0
 */
destroyBundle : function (
bundle3d 
)
{
},

/**
 * @method loadObj
 * @param {cc.MeshDatas} arg0
 * @param {cc.MaterialDatas} arg1
 * @param {cc.NodeDatas} arg2
 * @param {String} arg3
 * @param {char} arg4
 * @return {bool}
 */
loadObj : function (
meshdatas, 
materialdatas, 
nodedatas, 
str, 
char 
)
{
    return false;
},

/**
 * @method Bundle3D
 * @constructor
 */
Bundle3D : function (
)
{
},

};
