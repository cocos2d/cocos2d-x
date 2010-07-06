#ifndef __COCOA_NSOBJECT_H__
#define __COCOA_NSOBJECT_H__

#include "Cocos2dTypes.h"
class NSZone;
class NSObject;
class NSString;

class NSCopying
{
public:
	virtual NSObject* copyWithZone(NSZone* zone);
};

class NSObject : public NSCopying
{
protected:
	// object id
    UINT32		m_nID;
	// count of refrence
	UINT32		m_nRefrence;
	// is the object autoreleased
	BOOL		m_bManaged;		
public:
	NSObject(void);
	~NSObject(void);
    
	virtual void release(void);
	virtual void retain(void);
	NSObject* autorelease(void);
	NSObject* copy(void);
	BOOL isSingleRefrence(void);
	UINT32 retainCount(void);
	BOOL isEqual(const NSObject* pObject);
};

#endif // __COCOA_NSOBJECT_H__
