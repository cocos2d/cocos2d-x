#include "CustomTableViewCell.h"

USING_NS_CC;

void CustomTableViewCell::draw()
{
	CCTableViewCell::draw();
	// draw bounding box
// 	CCPoint pos = getPosition();
// 	CCSize size = CCSizeMake(178, 200);
// 	CCPoint vertices[4]={
// 		ccp(pos.x+1, pos.y+1),
// 		ccp(pos.x+size.width-1, pos.y+1),
// 		ccp(pos.x+size.width-1, pos.y+size.height-1),
// 		ccp(pos.x+1, pos.y+size.height-1),
// 	};
// 	ccDrawColor4B(0, 0, 255, 255);
// 	ccDrawPoly(vertices, 4, true);
}
