#ifndef _CCB_CCNODELOADERLISTENER_H_
#define _CCB_CCNODELOADERLISTENER_H_


namespace cocosbuilder {

class CC_DLL NodeLoaderListener {
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
