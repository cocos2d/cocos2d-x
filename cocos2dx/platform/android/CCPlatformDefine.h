#ifndef __CCPLATFORMDEFINE_H__
#define __CCPLATFORMDEFINE_H__

#define CC_DLL 

#define CC_ASSERT(cond) \
if (! (cond)) \
{ \
    char content[256]; \
    sprintf(content, "%s function:%s line:%d", __FILE__, __FUNCTION__, __LINE__);  \
    CCMessageBox(content, "Assert error"); \
}


#define CC_UNUSED_PARAM(unusedparam) (void)unusedparam

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif



#endif /* __CCPLATFORMDEFINE_H__*/
