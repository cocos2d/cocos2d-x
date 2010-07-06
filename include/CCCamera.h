#ifndef __CCCAMERA_H__
#define __CCCAMERA_H__

#include "NSObject.h"
#include "ccMacros.h"
#include <string>

class CCCamera : public NSObject
{
protected:
	float m_fEyeX;
	float m_fEyeY;
	float m_fEyeZ;

	float m_fCenterX;
	float m_fCenterY;
	float m_fCenterZ;

	float m_fUpX;
	float m_fUpY;
	float m_fUpZ;

	BOOL m_bDirty;
public:
	CCCamera(void);
	~CCCamera(void);

	std::string description(void);

	// sets the camera in the defaul position
	void restore(void);
	// Sets the camera using gluLookAt using its eye, center and up_vector
	void locate(void);
    // sets the eye values
	void setEyeXYZ(float fEyeX, float fEyeY, float fEyeZ);
	// sets the center values
	void setCenterXYZ(float fCenterX, float fCenterY, float fCenterZ);
	// sets the up values
	void setUpXYZ(float fUpX, float fUpY, float fUpZ);

	// get the eye vector values
	void getEyeXYZ(float *pEyeX, float *pEyeY, float *pEyeZ);
	// get the center vector values
	void getCenterXYZ(float *pCenterX, float *pCenterY, float *pCenterZ);
	// get the up vector values
	void getUpXYZ(float *pUpX, float *pUpY, float *pUpZ);
public:
	// returns the Z eye
	static float getZEye();

private:
	DISALLOW_COPY_AND_ASSIGN(CCCamera);
};

#endif // __CCCAMERA_H__
