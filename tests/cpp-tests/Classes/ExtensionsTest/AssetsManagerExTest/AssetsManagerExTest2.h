#ifndef __AssetsManagerEx_Test2_H__
#define __AssetsManagerEx_Test2_H__

#include "cocos-ext.h"
USING_NS_CC_EXT;

class AssetsManagerExTest2:public cocos2d::Node
{
public:
		static const char * EVENT_PROGRESS;
		
		static const char * EVENT_FINISHED;
		
		static AssetsManagerExTest2	*	getInstance();
		
		static void					destoryInstance();
		
		void doAssetsUpdate(std::string manifestPath);
    
private:
		cocos2d::extension::AssetsManagerEx					* _am;
		
		cocos2d::extension::EventListenerAssetsManagerEx	* _amListener;
		
		static AssetsManagerExTest2								* _single_instance;

		AssetsManagerExTest2();
		
		~AssetsManagerExTest2();

};

#endif /* defined(__AssetsManagerEx_Test2_H__) */
