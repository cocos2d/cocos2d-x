#ifndef ANIMATED_LIGHT_H_
#define ANIMATED_LIGHT_H_

#include "C3DLight.h"
#include "C3DVector2.h"

namespace cocos3d
{

class C3DTexture;
class C3DSampler;

/**
 * Defines a class for Animate Light
 */
class C3DAnimatedLight : public C3DLightComponent
{
public:
	/**
	 * Creats AnimatedLight.
	 */
	static C3DAnimatedLight* create(const C3DVector3& color, C3DTexture* texture);
	static C3DAnimatedLight* create(const C3DVector3& color, const char* texturePath);

	/**
     * Destructor.
     */
	virtual ~C3DAnimatedLight();

	/**
     * Intensity.
     */
	void setIntensity(float orginalColor, float texture1, float texture2, float textureProduct);
	const C3DVector4& getIntensity() const { return _intensity; }

	/**
     * set texture u, v animation
     */
	void setOffsetUV(float u1, float v1, float u2, float v2);
	void setSpeedUV(float speedU1, float speedV1, float speedU2, float speedV2);
	void setScaleUV(float scaleU1, float scaleV1, float scaleU2, float scaleV2);
	void setRotateUV(float rotate1, float rotate2);
	void setRotateSpeedUV(float rotate1, float rotate2);
	
	/**
     * get uv offset {x, y} : uv1 offset, {z, w} uv2 offset 
     */
	const C3DVector4& getUVOffset() const { return _offsetUV; }

	/**
     * get uv1 rotation and scale, u'=dot([x, y], [u, v]), v'=dot([z,w], [u,v])
     */
	const C3DVector4& getUV1RotScale() const { return _uv1RotScale; }

	/**
     * get uv2 rotation and scale, u'=dot([x, y], [u, v]), v'=dot([z,w], [u,v])
     */
	const C3DVector4& getUV2RotScale() const { return _uv2RotScale; }

	/**
     * override C3DLightComponent::update
     */
	virtual void update(unsigned int deltatime);

	/**
     * set animate light texture
     */
	void setTexture(C3DTexture* texture);

	/**
     * get animate light sampler
     */
	C3DSampler* getSampler() const { return _sampler; };


protected:
	/**
     * Constructor.
     */
	C3DAnimatedLight();

	C3DSampler* _sampler;

	C3DVector4 _intensity;

	C3DVector4 _speedUV;
	C3DVector4 _scaleUV;
	C3DVector2 _rotateUV;
	C3DVector2 _rotateSpeedUV;

	C3DVector4 _offsetUV;
	C3DVector4 _uv1RotScale;
	C3DVector4 _uv2RotScale;

	void updateRotScale();

};

}
#endif