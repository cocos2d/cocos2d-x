// Setup program for the Cocos2d-win32 App Wizard for VC++ 9.0 (Orcas)

main();

function main()
{
	// Decode command line arguments
	var bDebug = false;
	var bElevated = false;
	var Args = WScript.Arguments;
	for(var i = 0; i < Args.length; i++)
	{
		if(Args(i) == "/debug")
			bDebug = true;
		else if(Args(i) == "/elevated")
			bElevated = true;
	}

	// See if UAC is enabled
	var Shell = WScript.CreateObject("Shell.Application");
	if(!bElevated && Shell.IsRestricted("System", "EnableLUA"))
	{
		// Check that the script is being run interactively.
		if(!WScript.Interactive)
		{
			WScript.Echo("ERROR: Elevation required.");
			return;
		}
		
		// Now relaunch the script, using the "RunAs" verb to elevate
		var strParams = "\"" + WScript.ScriptFullName + "\"";
		if (bDebug)
			strParams += " /debug";
		strParams += " /elevated";
		Shell.ShellExecute(WScript.FullName, strParams, null, "RunAs");
		return;
	}
	
	// Create shell object
	var WSShell = WScript.CreateObject("WScript.Shell");
	// Create file system object
	var FileSys = WScript.CreateObject("Scripting.FileSystemObject");

	// Get the folder containing the script file
	var strValue = FileSys.GetParentFolderName(WScript.ScriptFullName);
	if(strValue == null || strValue == "")
		strValue = ".";

	var strSourceFolder = FileSys.BuildPath(strValue, "CCXAppWiz");
	if(bDebug)
		WScript.Echo("Source: " + strSourceFolder);

	if(!FileSys.FolderExists(strSourceFolder))
	{
		WScript.Echo("ERROR: Cannot find Wizard folder (should be: " + strSourceFolder + ")");
		return;
	}

	try
	{
		var strVC9Key = "HKLM\\Software\\Microsoft\\VisualStudio\\9.0\\Setup\\VC\\ProductDir";
		strValue = WSShell.RegRead(strVC9Key);
	}
	catch(e)
	{
		try
		{
			var strVC9Key_x64 = "HKLM\\Software\\Wow6432Node\\Microsoft\\VisualStudio\\9.0\\Setup\\VC\\ProductDir";
			strValue = WSShell.RegRead(strVC9Key_x64);
		}
		catch(e)
		{
			WScript.Echo("ERROR: Cannot find where Visual Studio 9.0 is installed.");
			return;
		}
	}

	var strDestFolder = FileSys.BuildPath(strValue, "vcprojects");
	if(bDebug)
		WScript.Echo("Destination: " + strDestFolder);
	if(!FileSys.FolderExists(strDestFolder))
	{
		WScript.Echo("ERROR: Cannot find destination folder (should be: " + strDestFolder + ")");
		return;
	}

	// Copy files
	try
	{
		var strSrc = FileSys.BuildPath(strSourceFolder, "CCXAppWiz.ico");
		var strDest = FileSys.BuildPath(strDestFolder, "CCXAppWiz.ico");
		FileSys.CopyFile(strSrc, strDest);

		strSrc = FileSys.BuildPath(strSourceFolder, "CCXAppWiz.vsdir");
		strDest = FileSys.BuildPath(strDestFolder, "CCXAppWiz.vsdir");
		FileSys.CopyFile(strSrc, strDest);
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot copy file (" + strError + ")");
		return;
	}

	// Read and write CCXAppWiz.vsz, add engine version and replace path when found
	try
	{
		var strSrc = FileSys.BuildPath(strSourceFolder, "CCXAppWiz.vsz");
		var strDest = FileSys.BuildPath(strDestFolder, "CCXAppWiz.vsz");

		var ForReading = 1;
		var fileSrc = FileSys.OpenTextFile(strSrc, ForReading);
		if(fileSrc == null)
		{
			WScript.Echo("ERROR: Cannot open source file " + strSrc);
			return;
		}

		var ForWriting = 2;
		var fileDest = FileSys.OpenTextFile(strDest, ForWriting, true);
		if(fileDest == null)
		{
			WScript.Echo("ERROR: Cannot open destination file" + strDest);
			return;
		}

		while(!fileSrc.AtEndOfStream)
		{
			var strLine = fileSrc.ReadLine();
			if(strLine.indexOf("Wizard=VsWizard.VsWizardEngine") != -1)
				strLine += ".9.0";
			else if(strLine.indexOf("WIZARD_VERSION") != -1)
				strLine = "Param=\"WIZARD_VERSION = 9.0\"";
			else if(strLine.indexOf("ABSOLUTE_PATH") != -1)
				strLine = "Param=\"ABSOLUTE_PATH = " + strSourceFolder + "\"";
			fileDest.WriteLine(strLine);
		}

		fileSrc.Close();
		fileDest.Close();
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot read and write CCXAppWiz.vsz (" + strError + ")");
		return;
	}

	// Create Cocos2d-x folder
	var strDestCCXFolder = "";
	try
	{
		strDestCCXFolder = FileSys.BuildPath(strDestFolder, "Cocos2d-x");
		if(!FileSys.FolderExists(strDestCCXFolder))
			FileSys.CreateFolder(strDestCCXFolder);
		if(bDebug)
			WScript.Echo("CCX Folder: " + strDestCCXFolder);
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot create CCX folder (" + strError + ")");
		return;
	}

	// Read and write additional CCXAppWiz.vsdir, add path to the wizard location
	try
	{
		var strSrc = FileSys.BuildPath(strSourceFolder, "CCXAppWiz.vsdir");
		var strDest = FileSys.BuildPath(strDestCCXFolder, "CCXAppWiz.vsdir");

		var ForReading = 1;
		var fileSrc = FileSys.OpenTextFile(strSrc, ForReading);
		if(fileSrc == null)
		{
			WScript.Echo("ERROR: Cannot open source file " + strSrc);
			return;
		}

		var ForWriting = 2;
		var fileDest = FileSys.OpenTextFile(strDest, ForWriting, true);
		if(fileDest == null)
		{
			WScript.Echo("ERROR: Cannot open destination file" + strDest);
			return;
		}

		while(!fileSrc.AtEndOfStream)
		{
			var strLine = fileSrc.ReadLine();
			if(strLine.indexOf("CCXAppWiz.vsz|") != -1)
				strLine = "..\\" + strLine;
			fileDest.WriteLine(strLine);
		}

		fileSrc.Close();
		fileDest.Close();
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot read and write CCX\\CCXAppWiz.vsdir (" + strError + ")");
		return;
	}

	WScript.Echo("App Wizard successfully installed!");
}
