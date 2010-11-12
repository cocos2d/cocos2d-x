#include "TG3.h"
#include "../AppDelegate.h"

Int32 TG3AppMain(const TUChar * pAppID, UInt32 nCmd, void * pCmdParam)
{
	switch(nCmd)
	{
	case 0: // main entry
		{
			// run app
			AppDelegate app;
            app.Run();
		}
	}
	return 1;
}


