#ifndef LIGHTFILTER_H_
#define LIGHTFILTER_H_

#include "C3DModel.h"
#include "C3DLight.h"


namespace cocos3d
{

/**
 * Defines a class for Light Filter
 */
class C3DLightFilter
    {
    public:
		/**
        * Constructor.
        */
        C3DLightFilter()
        {
            
        }

		/**
		 * Destructor.
		 */
        virtual ~C3DLightFilter()
        {
            
        }
        
        /**
         * Is light validate for this model
         */
        virtual bool isLightValidate(C3DModel* model, C3DLight* light)
        {
            return true;
        }
    };

}


#endif
