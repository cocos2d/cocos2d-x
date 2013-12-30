#include "C3DViewport.h"

namespace cocos2d
{
C3DViewport::C3DViewport(int left, int top, int width1, int height1)
	: x(left)
	, y(top)
	, width(width1)
	, height(height1)
{
}

C3DViewport::C3DViewport(const C3DViewport& viewport)
	: x(viewport.x)
	, y(viewport.y)
	, width(viewport.width)
	, height(viewport.height)
{
}

C3DViewport::~C3DViewport()
{
}

C3DViewport& C3DViewport::operator==(const C3DViewport& viewport)
{
	this->x = viewport.x;
	this->y = viewport.y;
	this->width = viewport.width;
	this->height = viewport.height;

	return *this;
}

void C3DViewport::apply()
{
	glViewport((GLuint)x, (GLuint)y, (GLuint)width, (GLuint)height);
}
}
