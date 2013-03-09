// Setup program for the Cocos2d-win32 App Wizard for VC++ 11.0 (VC2012)

main();

function EchoInfo(bQuiet, strMsg) {
    if (! bQuiet) {
        WScript.Echo(strMsg);
    }
    else {
        var FileSys = new ActiveXObject("Scripting.FileSystemObject");
        var strLogPath = "InstallWizardLog.txt"
        var file = FileSys.OpenTextFile(strLogPath, 8, true);
        file.WriteLine(strMsg);
        file.Close(); 
    }
}

function EchoError(bQuiet, strMsg) {
    strMsg = "Error: " + strMsg;
    if (! bQuiet) {
        WScript.Echo(strMsg);
    }
    else {
        var FileSys = new ActiveXObject("Scripting.FileSystemObject");
        var strLogPath = "InstallWizardLog.txt"
        var file = FileSys.OpenTextFile(strLogPath, 8, true);
        file.WriteLine(strMsg);
        file.Close(); 
    }
}

function main() {
    // Decode command line arguments
    var bDebug = false;
    var bQuiet = false;
    var bElevated = false;
    var Args = WScript.Arguments;
    for (var i = 0; i < Args.length; i++) {
        if (Args(i) == "/debug")
            bDebug = true;
        else if (Args(i) == "/elevated")
            bElevated = true;
        else if (Args(i) == "/quiet")
            bQuiet = true;
    }

    // See if UAC is enabled
    var Shell = WScript.CreateObject("Shell.Application");
    if (!bElevated && Shell.IsRestricted("System", "EnableLUA")) {
        // Check that the script is being run interactively.
        if (!WScript.Interactive) {
            EchoError(bQuiet, "(Windows LUA) Elevation required.");
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
    var strScriptPath = FileSys.GetParentFolderName(WScript.ScriptFullName);
    if (strScriptPath == null || strScriptPath == "")
        strScriptPath = ".";

    // Get the folder script files copy to
    var strValue = "";
    try {
        var strVCKey = "HKLM\\Software\\Microsoft\\VisualStudio\\11.0\\Setup\\VC\\ProductDir";
        strValue = WSShell.RegRead(strVCKey);
    }
    catch (e) {
        try {
            var strVCKey_x64 = "HKLM\\Software\\Wow6432Node\\Microsoft\\VisualStudio\\11.0\\Setup\\VC\\ProductDir";
            strValue = WSShell.RegRead(strVCKey_x64);
        }
        catch (e) {
            EchoError(bQuiet, "Cannot find where Visual Studio 2012 is installed.");
            return;
        }
    }

    var strDestFolder = FileSys.BuildPath(strValue, "vcprojects");
    if (bDebug)
        WScript.Echo("Destination: " + strDestFolder);
        
    if (!FileSys.FolderExists(strDestFolder)) {
        EchoError(bQuiet, "Cannot find destination folder (should be: " + strDestFolder + ")");
        return;
    }

    // Wizard Info
    var nNumWizards = 1;

    var astrWizardName = new Array();
    astrWizardName[0] = "CCAppWiz.win32";

    var nCntr;
    for (nCntr = 0; nCntr < nNumWizards; nCntr++) {
        var strSourceFolder = FileSys.BuildPath(strScriptPath, astrWizardName[nCntr]);

        if (bDebug)
            WScript.Echo("Source: " + strSourceFolder);

        if (!FileSys.FolderExists(strSourceFolder)) {
            EchoError(bQuiet, "Cannot find Wizard folder (should be: " + strSourceFolder + ")");
            return;
        }

        // Copy files
        try {
            var strSrc = FileSys.BuildPath(strSourceFolder, astrWizardName[nCntr] + ".ico");
            var strDest = FileSys.BuildPath(strDestFolder, astrWizardName[nCntr] + ".ico");
            FileSys.CopyFile(strSrc, strDest);

            strSrc = FileSys.BuildPath(strSourceFolder, astrWizardName[nCntr] + ".vsdir");
            strDest = FileSys.BuildPath(strDestFolder, astrWizardName[nCntr] + ".vsdir");
            FileSys.CopyFile(strSrc, strDest);
        }
        catch (e) {
            var strError = "no info";
            if (e.description.length != 0)
                strError = e.description;
            EchoError(bQuiet, "Cannot copy file (" + strError + ")");
            return;
        }

        // Read and write CCAppWiz.vsz, add engine version and replace path when found
        try {
            var strSrc = FileSys.BuildPath(strSourceFolder, astrWizardName[nCntr] + ".vsz");
            var strDest = FileSys.BuildPath(strDestFolder, astrWizardName[nCntr] + ".vsz");

            var ForReading = 1;
            var fileSrc = FileSys.OpenTextFile(strSrc, ForReading);
            if (fileSrc == null) {
                EchoError(bQuiet, "Cannot open source file: " + strSrc);
                return;
            }

            var ForWriting = 2;
            var fileDest = FileSys.OpenTextFile(strDest, ForWriting, true);
            if (fileDest == null) {
                EchoError(bQuiet, " Cannot open destination file: " + strDest);
                return;
            }

            while (!fileSrc.AtEndOfStream) {
                var strLine = fileSrc.ReadLine();
                if (strLine.indexOf("Wizard=VsWizard.VsWizardEngine") != -1)
                    strLine += ".11.0";
                else if (strLine.indexOf("WIZARD_VERSION") != -1)
                    strLine = "Param=\"WIZARD_VERSION = 11.0\"";
                else if (strLine.indexOf("ABSOLUTE_PATH") != -1)
                    strLine = "Param=\"ABSOLUTE_PATH = " + strSourceFolder + "\"";
                fileDest.WriteLine(strLine);
            }

            fileSrc.Close();
            fileDest.Close();
        }
        catch (e) {
            var strError = "no info";
            if (e.description.length != 0)
                strError = e.description;
            EchoError(bQuiet, "Cannot read and write CCAppWiz.vsz (" + strError + ")");
            return;
        }
    }

    // Create Cocos2d-x folder
    var strDestCCFolder = "";
    try {
        strDestCCFolder = FileSys.BuildPath(strDestFolder, "Cocos2d-x");
        if (!FileSys.FolderExists(strDestCCFolder))
            FileSys.CreateFolder(strDestCCFolder);
        if (bDebug)
            WScript.Echo("Cocos2d-x Folder: " + strDestCCFolder);
    }
    catch (e) {
        var strError = "no info";
        if (e.description.length != 0)
            strError = e.description;
        EchoError(bQuiet, "Cannot create Cocos2d-x folder (" + strError + ")");
        return;
    }

    // Read and write additional CCAppWiz.vsdir, add path to the wizard location
    try {
        var strDest = FileSys.BuildPath(strDestCCFolder, "Cocos2d-x.vsdir");

        var ForWriting = 2;

        var fileDest = FileSys.OpenTextFile(strDest, ForWriting, true);
        if (fileDest == null) {
            EchoError(bQuiet, "Cannot open destination file: " + strDest);
            return;
        }

        var nCntr;
        for (nCntr = 0; nCntr < nNumWizards; nCntr++) {
            var strSourceFolder = FileSys.BuildPath(strScriptPath, astrWizardName[nCntr]);
            var strSrc = FileSys.BuildPath(strSourceFolder, astrWizardName[nCntr] + ".vsdir");
            var ForReading = 1;
            var fileSrc = FileSys.OpenTextFile(strSrc, ForReading);
            if (fileSrc == null) {
                EchoError(bQuiet, "Cannot open source file: " + strSrc);
                return;
            }

            while (!fileSrc.AtEndOfStream) {
                var strLine = fileSrc.ReadLine();
                if (strLine.indexOf(astrWizardName[nCntr] + ".vsz|") != -1)
                    strLine = "..\\" + strLine;
                fileDest.WriteLine(strLine);
            }

            fileSrc.Close();
        }
        fileDest.Close();
    }
    catch (e) {
        var strError = "no info";
        if (e.description.length != 0)
            strError = e.description;
        EchoError(bQuiet, "Cannot read and write Cocos2d-x\\CCAppWiz.vsdir (" + strError + ")");
        return;
    }

    EchoInfo(bQuiet, "App Wizard successfully installed for VS2012!");
}
