#include "CustomTableViewCell.h"

USING_NS_CC;

void CustomTableViewCell::draw()
{
	TableViewCell::draw();
	// draw bounding box
// 	auto pos = getPosition();
// 	auto size = Size(178, 200);
// 	Point vertices[4]={
// 		Point(pos.x+1, pos.y+1),
// 		Point(pos.x+size.width-1, pos.y+1),
// 		Point(pos.x+size.width-1, pos.y+size.height-1),
// 		Point(pos.x+1, pos.y+size.height-1),
// 	};
// 	DrawPrimitives::drawColor4B(0, 0, 255, 255);
// 	DrawPrimitives::drawPoly(vertices, 4, true);
}
