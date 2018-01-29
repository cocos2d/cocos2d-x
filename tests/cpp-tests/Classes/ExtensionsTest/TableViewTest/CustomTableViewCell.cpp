/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "CustomTableViewCell.h"

USING_NS_CC;

void CustomTableViewCell::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
	TableViewCell::draw(renderer, transform, flags);
	// draw bounding box
// 	auto pos = getPosition();
// 	auto size = Size(178, 200);
// 	Vec2 vertices[4]={
// 		Vec2(pos.x+1, pos.y+1),
// 		Vec2(pos.x+size.width-1, pos.y+1),
// 		Vec2(pos.x+size.width-1, pos.y+size.height-1),
// 		Vec2(pos.x+1, pos.y+size.height-1),
// 	};
// 	DrawPrimitives::drawColor4B(0, 0, 255, 255);
// 	DrawPrimitives::drawPoly(vertices, 4, true);
}
