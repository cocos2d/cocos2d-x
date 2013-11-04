#ifndef SHEETANIMMANAGER_H_
#define SHEETANIMMANAGER_H_

#include <map>
#include <list>

using namespace std;
namespace cocos3d
{

/**
 * Defines structure to describe runtime expression.
 */
struct Expression
{
	string name;
	int frameNum;
	string frameSerials;
};

/**
 * Defines structure to describe facial.
 */
class  FacialComponent
{
private:
	string name;
	std::map<std::string,Expression*>* _expressions;
	
};


class SheetAnimation;

/**
 * Defines structure to Manage facial animation.
 */
class FacialAnimManager
{
public:
	FacialAnimManager();
	~FacialAnimManager();

	void update(long elapsedTime);

	/**
	* Add TextureAnimation to Manager.
	*/
	void addTextureAnim(string partName,string typeName,int frameNum,string frameSerial);

	/**
	* Add UVAnimation to Manager.
	*/
	void addUVAnim(string partName,string typeName,int tileX,int tileY,int frameNum,string frameSerial);

	/**
	* Sets target animation material.
	*/
	bool setAnim(string partName,string typeName,C3DMaterial *mat);

private:
	typedef pair <string, list<SheetAnimation*>*> map_pair;
	typedef map<string,list<SheetAnimation*>*>::iterator map_iter;
	typedef list<SheetAnimation*>::iterator list_iter;
	map<string,list<SheetAnimation*>*>* _anims;

};


}

#endif
