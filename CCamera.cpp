#include "CCCamera.h"
//#include "CCDirector.h"
#include "ccMacros.h"

#include "glu.h"

#include "CCDrawingPrimitives.h"

using namespace std;

CCCamera::CCCamera(void)
{
}

CCCamera::~CCCamera(void)
{
}

string CCCamera::description(void)
{
	char des[100];
	sprintf_s(des, 100, "<CCCamera | center = (%.2f,%.2f,%.2f)>", m_fCenterX, m_fCenterY, m_fCenterZ);
	string ret(des);

	return ret;
}

void CCCamera::restore(void)
{
	m_fEyeX = m_fEyeY = 0.0f;
	m_fEyeZ = getZEye();

	m_fCenterX = m_fCenterY = m_fCenterZ = 0.0f;

	m_fUpX = 0.0f;
	m_fUpY = 1.0f;
	m_fUpZ = 0.0f;

	m_bDirty = FALSE;
}

void CCCamera::locate(void)
{
	if (m_bDirty)
	{
		gluLookAt(m_fEyeX, m_fEyeY, m_fEyeZ,
			m_fCenterX, m_fCenterY, m_fCenterZ,
			m_fUpX, m_fUpY, m_fUpZ);
	}
}

float CCCamera::getZEye(void)
{
	return FLT_EPSILON;
}

void CCCamera::setEyeXYZ(float fEyeX, float fEyeY, float fEyeZ)
{
	m_fEyeX = fEyeX;
	m_fEyeY = fEyeY;
	m_fEyeZ = fEyeZ;
}

void CCCamera::setCenterXYZ(float fCenterX, float fCenterY, float fCenterZ)
{
	m_fCenterX = fCenterX;
	m_fCenterY = fCenterY;
	m_fCenterZ = fCenterZ;
}

void CCCamera::setUpXYZ(float fUpX, float fUpY, float fUpZ)
{
	m_fUpX = fUpX;
	m_fUpY = fUpY;
	m_fUpZ = fUpZ;
}

void CCCamera::getEyeXYZ(float *pEyeX, float *pEyeY, float *pEyeZ)
{
	*pEyeX = m_fEyeX;
	*pEyeY = m_fEyeY;
	*pEyeZ = m_fEyeZ;
}

void CCCamera::getCenterXYZ(float *pCenterX, float *pCenterY, float *pCenterZ)
{
	*pCenterX = m_fCenterX;
	*pCenterY = m_fCenterY;
	*pCenterZ = m_fCenterZ;
}

void CCCamera::getUpXYZ(float *pUpX, float *pUpY, float *pUpZ)
{
	*pUpX = m_fUpX;
	*pUpY = m_fUpY;
	*pUpZ = m_fUpZ;
}
