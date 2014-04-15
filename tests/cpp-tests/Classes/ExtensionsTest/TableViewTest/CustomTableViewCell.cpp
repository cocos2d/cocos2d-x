#include "CustomTableViewCell.h"

USING_NS_CC;

void CustomTableViewCell::draw(Renderer *renderer, const Matrix &transform, bool transformUpdated)
{
	TableViewCell::draw(renderer, transform, transformUpdated);
	// draw bounding box
// 	auto pos = getPosition();
// 	auto size = Size(178, 200);
// 	Vector2 vertices[4]={
// 		Vector2(pos.x+1, pos.y+1),
// 		Vector2(pos.x+size.width-1, pos.y+1),
// 		Vector2(pos.x+size.width-1, pos.y+size.height-1),
// 		Vector2(pos.x+1, pos.y+size.height-1),
// 	};
// 	DrawPrimitives::drawColor4B(0, 0, 255, 255);
// 	DrawPrimitives::drawPoly(vertices, 4, true);
}
