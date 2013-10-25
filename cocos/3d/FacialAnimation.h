#ifndef SHEETANIMATION_H_
#define SHEETANIMATION_H_
#include <string>

using namespace std;
namespace cocos3d
{

/**
 * Sheet animation wrap type
 */
enum SheetAnimWrapType
{
    SheetAnimWrapType_Loop   = 0 ,
	SheetAnimWrapType_Once ,
    
};

class C3DMaterial;
class C3DTexture;

/**
 * Defines a base class to describe sheet animation.
 */
class SheetAnimation
{
	friend class FacialAnimManager;
	friend class TextureAnimation;
	friend class UVAnimation;
public:
	/**
     * Constructor.
     */
	SheetAnimation();

	/**
     * Destructor.
     */
    virtual ~SheetAnimation();

	/**
	 * Create SheetAnimation by frame serial string.
	 */
	virtual void generateFrameSerial(string &frameSerial);

	/**
	 * Update per frame.
	 */
	virtual void update(long elapsedTime);	

private:

	int frameNum;

	string partName;
	string typeName;	

	SheetAnimWrapType wrapType;
	float fps;
	bool enable;

	int  *frameSerials;	
	int frameSerialNum;	

	C3DMaterial *mat;
	int _curFrameIndex;

};

/**
 * Defines a class for texture animation
 */
class TextureAnimation : public SheetAnimation
{
public:
	/**
     * Constructor.
     */
	TextureAnimation();

	/**
     * Destructor.
     */
	virtual ~TextureAnimation();

	/**
	 * Create SheetAnimation by frame serial string.
	 */
	virtual void generateFrameSerial(string &frameSerial);

	/**
	 * Update per frame.
	 */
	virtual void update(long elapsedTime);

private:
	C3DTexture** _textures;
};

/**
 * Defines a class for UV animation
 */
class UVAnimation : public SheetAnimation
{
	friend class FacialAnimManager;
public:
	/**
     * Constructor.
     */
	UVAnimation();

	/**
     * Destructor.
     */
	virtual ~UVAnimation();

	/**
	 * Update per frame.
	 */
	virtual void update(long elapsedTime);

private:
	int tileX;
	int tileY;
};




}

#endif
