#include "FacialAnimation.h"
#include "FacialAnimManager.h"

#include "StringTool.h"

namespace cocos3d
{

FacialAnimManager::FacialAnimManager()
{
	_anims = new map<string,list<SheetAnimation*>*>();
}


FacialAnimManager::~FacialAnimManager()
{
	map_iter mapIter;
	list_iter listIter;
	list<SheetAnimation*>* partAnims;
	SheetAnimation* anim;
	for(mapIter=_anims->begin();mapIter!=_anims->end();mapIter++)
	{
		partAnims = mapIter->second;
		for(listIter=partAnims->begin();listIter!=partAnims->end();listIter++)
		{
			anim = *listIter;
			if(anim != NULL)
			{
				delete anim;
				anim = NULL;
			}			
		}
		partAnims->clear();

		delete partAnims;partAnims = NULL;
	}
	_anims->clear();
	delete _anims;_anims = NULL;

}

void FacialAnimManager::update(long elapsedTime)
{
	if(_anims->size()==0)
		return;

	map_iter mapIter;
	list_iter listIter;
	list<SheetAnimation*>* partAnims;
	SheetAnimation* anim;
	for(mapIter=_anims->begin();mapIter!=_anims->end();mapIter++)
	{
		partAnims = mapIter->second;
		for(listIter=partAnims->begin();listIter!=partAnims->end();listIter++)
		{
			anim = *listIter;
			if(anim->enable==true)
			{
				anim->update(elapsedTime);
				break;
			}
		}
	}			
		
}

void FacialAnimManager::addTextureAnim(string partName,string typeName,int frameNum,string frameSerial)
{
	map_iter mapIter;
	if(_anims->find(partName)==_anims->end())
	{
		_anims->insert(map_pair(partName,new list<SheetAnimation*>()));
	}
		
	mapIter = _anims->find(partName);
	if(mapIter==_anims->end())
		return;

	list<SheetAnimation*>* partAnims = mapIter->second;

	std::list<SheetAnimation*>::iterator iter;
	for(iter=partAnims->begin();iter!=partAnims->end();iter)
	{
		SheetAnimation* anim = *iter;
		if(anim->typeName==typeName)
		{
			iter = partAnims->erase(iter);
		}
		else
			iter++;
	}
				
	TextureAnimation* sheetAnim = new TextureAnimation();
	sheetAnim->enable = false;
	sheetAnim->partName = partName;
	sheetAnim->typeName = typeName;
	sheetAnim->mat = NULL;	
	sheetAnim->frameNum = frameNum;
	sheetAnim->generateFrameSerial(frameSerial);

	(*_anims)[partName]->push_back(sheetAnim);		
		
}

void FacialAnimManager::addUVAnim(string partName,string typeName,int tileX,int tileY,int frameNum,string frameSerial)
{
	map_iter mapIter;
	if(_anims->find(partName)==_anims->end())
	{
		_anims->insert(map_pair(partName,new list<SheetAnimation*>()));
	}
		
	mapIter = _anims->find(partName);
	if(mapIter==_anims->end())
		return;

	list<SheetAnimation*>* partAnims = mapIter->second;

	std::list<SheetAnimation*>::iterator iter;
	for(iter=partAnims->begin();iter!=partAnims->end();iter)
	{
		SheetAnimation* anim = *iter;
		if(anim->typeName==typeName)
		{
			iter = partAnims->erase(iter);
		}
		else
			iter++;
	}
				
	UVAnimation* sheetAnim = new UVAnimation();
	sheetAnim->enable = false;
	sheetAnim->partName = partName;
	sheetAnim->typeName = typeName;
	sheetAnim->mat = NULL;	
	sheetAnim->tileX = tileX;
	sheetAnim->tileY = tileY;
	sheetAnim->frameNum = frameNum;
	sheetAnim->generateFrameSerial(frameSerial);

	(*_anims)[partName]->push_back(sheetAnim);		
		
}

bool FacialAnimManager::setAnim(string partName, string typeName,C3DMaterial* mat)
{
	bool found = false;

	map_iter mapIter = _anims->find(partName);
	if(mapIter==_anims->end())
		return false;

	list<SheetAnimation*>* partAnims = mapIter->second;

	list_iter iter;
	for(iter=partAnims->begin();iter!=partAnims->end();iter++)
	{
		SheetAnimation* anim = *iter;
		if(anim->typeName==typeName)
		{
			anim->mat = mat;
			anim->enable = true;
			found = true;
		}
		else
		{
			anim->enable = false;
		}
	}

	return found;
}

}
