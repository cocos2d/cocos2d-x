fbxconverter version 0.2

Convert .fbx to .c3t used by cocos2d-x. Thanks to libgdx fbx-conv. We use their code and do some change.

It is the first version and has many bugs for sure. Feel free to contact us. Source code is here,
https://github.com/Trace0429/fbx-conv 

USAGE:

Command line
MAC:
cd -a|-b|t [path of fbx-conv]
./fbx-conv FBXFile

Windows:
cd [path of fbx-conv]
fbx-conv -a|-b|t FBXFile

-a export both c3t and c3b
-b export c3b
-t export c3t


Note: the bones in the FBX file should not be more than 60. 
