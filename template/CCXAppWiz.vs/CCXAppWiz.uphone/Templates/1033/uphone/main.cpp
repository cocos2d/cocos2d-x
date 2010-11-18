#include  "AppDelegate.h"

#include  "[!output PROJECT_NAME]_res_c.h"

const  ResourceRegisterEntry		ResRegList_[!output PROJECT_NAME][]  =
{
	TG_RESOURCE_DEFINE
};

extern const  AppResourceEntry		[!output PROJECT_NAME]ResourceEntry  =
{
	(ResourceRegisterEntry*)ResRegList_[!output PROJECT_NAME],                    //  res  list  in  this  app
		sizeof(ResRegList_[!output PROJECT_NAME]) /  sizeof(ResourceRegisterEntry),    //number  of  item  in  res
};



Int32 TG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
	AppDelegate app;
	app.WM_SetResourceEntry(&[!output PROJECT_NAME]ResourceEntry);
	app.Run();

	return 1;
}


