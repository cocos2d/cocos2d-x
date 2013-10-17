#ifndef _CCB_CCNODELOADERLISTENER_H_
#define _CCB_CCNODELOADERLISTENER_H_

#include "cocos2d.h"

namespace cocosbuilder {

class NodeLoaderListener {
    public:
        /**
         * @js NA
         * @lua NA
         */
        virtual ~NodeLoaderListener() {};
        /**
         * @js NA
         * @lua NA
         */
        virtual void onNodeLoaded(cocos2d::Node * pNode, NodeLoader * pNodeLoader) = 0;
};

}

#endif
