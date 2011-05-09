function LogInfo(strInfo) {
    var FileSys = new ActiveXObject("Scripting.FileSystemObject");
    var strLogPath = "\\CCApplicationWizardLog.txt"
    var file = FileSys.OpenTextFile(strLogPath, 8, true);
    file.WriteLine(strInfo);   
    file.Close();        
}

function OnFinish(selProj, selObj) {
    try {
        // Create symbols based on the project name
        var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
        var strProjectName = wizard.FindSymbol('PROJECT_NAME');

        wizard.AddSymbol('PROJECT_NAME_LOWER', strProjectName.toLowerCase(), false);
        wizard.AddSymbol('PROJECT_NAME_UPPER', strProjectName.toUpperCase(), false);

        if (strProjectName.length >= 6) {
            wizard.AddSymbol('PRO_NAME_PREFIX', strProjectName.substr(0, 6).toUpperCase(), false);
        }
        else {
            var strRes = '_RES';
            var strNewFormId = strProjectName + strRes.substr(0, (6 - strProjectName.length));

            wizard.AddSymbol('PRO_NAME_PREFIX', strNewFormId.toUpperCase(), false);
        }

        // Set current year symbol
        var d = new Date();
        var nYear = 0;
        nYear = d.getFullYear();
        wizard.AddSymbol("CC_CURRENT_YEAR", nYear);
        wizard.AddSymbol("CC_CURRENT_DATE", d.toString());

        // Create project and configurations
        selProj = CreateCustomProject(strProjectName, strProjectPath);
        AddConfigurations(selProj, strProjectName);
        AddFilters(selProj);

        var InfFile = CreateCustomInfFile();
        AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
        AddPchSettings(selProj);
        InfFile.Delete();

        selProj.Object.Save();
    }
    catch (e) {
        if (e.description.length != 0)
            SetErrorInfo(e);
        return e.number;
    }
}

function CreateCustomProject(strProjectName, strProjectPath) {
    try {
        var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
        var strProjTemplate = '';
        var WizardVersion = wizard.FindSymbol('WIZARD_VERSION'); 
        if(WizardVersion >= 10.0)
            strProjTemplate = strProjTemplatePath + '\\default.vcxproj';
        else
            strProjTemplate = strProjTemplatePath + '\\default.vcproj';

        var Solution = dte.Solution;
        var strSolutionName = "";
        if (wizard.FindSymbol("CLOSE_SOLUTION")) {
            Solution.Close();
            strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
            if (strSolutionName.length) {
                var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
                Solution.Create(strSolutionPath, strSolutionName);
            }
        }

        // Create vcproj.user file
        var FileSys = new ActiveXObject("Scripting.FileSystemObject");
        var strUserTarget = "";
        if(WizardVersion >= 10.0)
            strUserTarget = strProjectName + ".wophone.vcxproj.user";
        else
            strUserTarget = strProjectName + ".wophone.vcproj.user";

        var strUserPath = FileSys.BuildPath(strProjectPath, strUserTarget);

        var astrParentPath = new Array();
        astrParentPath[0] = strProjectPath;
        while (astrParentPath.length) {
            var strPath = astrParentPath.pop();
            var strParentPath = FileSys.GetParentFolderName(strPath);

            if (!FileSys.FolderExists(strParentPath)) {
                astrParentPath.push(strPath);
                astrParentPath.push(strParentPath);
                continue;
            }
            else {
                FileSys.CreateFolder(strPath);
            }
        }

        var file = FileSys.OpenTextFile(strUserPath, 2, true);
        var strUserValue = "";
        if(WizardVersion >= 10.0)
            strUserValue = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n<Project ToolsVersion=\"4.0\" xmlns=\"http://schemas.microsoft.com/developer/msbuild/2003\">\r\n  <PropertyGroup>\r\n    <ShowAllFiles>true</ShowAllFiles>\r\n  </PropertyGroup>\r\n</Project>";
        else
            strUserValue = "<?xml version=\"1.0\" encoding=\"utf-8\"?><VisualStudioUserFile ProjectType=\"Visual C++\" Version=\"9.00\" ShowAllFiles=\"true\"><Configurations><Configuration Name=\"Debug|Win32\"><DebugSettings Command=\"TG3_RunDLL.exe\" CommandArguments=\"$(TargetPath)\"/></Configuration></VisualStudioUserFile>";
        file.WriteLine(strUserValue);
        file.Close(); 

        // Create project file
        var strProjectNameWithExt = '';
        if(WizardVersion >= 10.0)
            strProjectNameWithExt = strProjectName + '.wophone.vcxproj';
        else
            strProjectNameWithExt = strProjectName + '.wophone.vcproj';

        var oTarget = wizard.FindSymbol("TARGET");
        var prj;
        if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
        {
            var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
            prj = prjItem.SubProject;
        }
        else {
            prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
        }
        var fxtarget = wizard.FindSymbol("TARGET_FRAMEWORK_VERSION");
        if (fxtarget != null && fxtarget != "") {
            fxtarget = fxtarget.split('.', 2);
            if (fxtarget.length == 2)
                prj.Object.TargetFrameworkVersion = parseInt(fxtarget[0]) * 0x10000 + parseInt(fxtarget[1])
        }
        return prj;
    }
    catch (e) {
        throw e;
    }
}

function AddFilters(proj) {
    try {
        // Add the folders to your project
        var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
        var group = proj.Object.AddFilter('source');
        group.Filter = strSrcFilter;

        strSrcFilter = wizard.FindSymbol('INCLUDE_FILTER');
        group = proj.Object.AddFilter('include');
        group.Filter = strSrcFilter;

        strSrcFilter = wizard.FindSymbol('MAKEFILE_FILTER');
        group = proj.Object.AddFilter('makefile');
        group.Filter = strSrcFilter;
    }
    catch (e) {
        throw e;
    }
}

// Configurations data
var nNumConfigs = 2;

var astrConfigName = new Array();
astrConfigName[0] = "Debug";
astrConfigName[1] = "Release";

function AddConfigurations(proj, strProjectName) {
    try {
        proj.Object.Keyword = "uPhoneProj";
        var strPrjTG3Dir = '../../PRJ_TG3';
        wizard.AddSymbol('PROJECT_PRJ_TG3_DIR', strPrjTG3Dir, false);
        
        // header files and libraries directories
        var strOutputDir = '../../PRJ_TG3/LIB/Win32Lib';
        var strCurIncludeDir = '..\\..\\PRJ_TG3\\Include;..\\..\\PRJ_TG3\\Include\\MTAPI;..\\..\\PRJ_TG3\\Include\\ThirdParty;..\\..\\PRJ_TG3\\Include\\TCOM;..\\..\\PRJ_TG3\\Include\\OpenGL';
        strCurIncludeDir += ';.;.\\Classes;.\\wophone;.\\wophone\\Res;..\\cocos2dx;..\\cocos2dx\\include;..\\cocos2dx\\platform';

        var strDefinitions = 'WIN32;_CONSOLE;_TRANZDA_VM_;SS_MAKEDLL';
        var strDependLibs = 'WS2_32.Lib EosConfig.lib SoftSupport.lib TG3_DLL.lib libcocos2d.lib';
        var strCurLibsDir = '../../PRJ_TG3/Common/ICU/lib;../../PRJ_TG3/Mtapi/Win32/lib;../../PRJ_TG3/LIB/Win32Lib;../../PRJ_TG3/Common/SoftSupport';
        var strImportLib = '$(OutDir)/' + wizard.FindSymbol("PROJECT_NAME") + '.lib';
        var strOutputFile = '$(OutDir)/' + wizard.FindSymbol("PROJECT_NAME") + '.dll';
        
        if (wizard.FindSymbol('CC_USE_BOX2D')) {
            strCurIncludeDir += ';..\\';
            strDependLibs += ' libBox2d.lib';
        }
        if (wizard.FindSymbol('CC_USE_CHIPMUNK')) {
            strCurIncludeDir += ';..\\chipmunk\\include\\chipmunk';
            strDependLibs += ' chipmunk.lib';
        }
        if (wizard.FindSymbol('CC_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE')) {
            strCurIncludeDir += ';..\\CocosDenshion\\Include';
            strDependLibs += ' libCocosDenshion.lib';
        }

        if (wizard.FindSymbol("CC_USE_TCOM_SUPPORT")) {
            strDefinitions = strDefinitions + ';__TCOM_SUPPORT__';
        }

        // create configure
        var nCntr;
        for (nCntr = 0; nCntr < nNumConfigs; nCntr++) {

            // Check if it's Debug configuration
            var bDebug = false;
            if (astrConfigName[nCntr].search("Debug") != -1)
                bDebug = true;

            var config = proj.Object.Configurations(astrConfigName[nCntr]);

            if (bDebug) {
                strDefinitions = '_DEBUG;COCOS2D_DEBUG=1;' + strDefinitions;
            } 
            else {
                strDefinitions = 'NDEBUG;' + strDefinitions;
            }

            config.InheritedPropertySheets = '$(VCInstallDir)VCProjectDefaults\UpgradeFromVC71.vsprops';
            config.OutputDirectory = strOutputDir;
            config.IntermediateDirectory = '$(ConfigurationName).wophone';
            config.ConfigurationType = '2';

            var CLTool = config.Tools('VCCLCompilerTool');
            if (bDebug) {
                CLTool.RuntimeLibrary = rtMultiThreadedDebug;
                CLTool.MinimalRebuild = true;
                CLTool.DebugInformationFormat = debugEditAndContinue;
                CLTool.BasicRuntimeChecks = runtimeBasicCheckAll;
                CLTool.Optimization = optimizeDisabled;
            }
            else {
                CLTool.RuntimeLibrary = rtMultiThreaded;
                CLTool.ExceptionHandling = false;
                CLTool.DebugInformationFormat = debugDisabled;
            }
            CLTool.AdditionalIncludeDirectories = strCurIncludeDir;
            CLTool.PreprocessorDefinitions = strDefinitions;
            CLTool.RuntimeLibrary = '3';
            CLTool.StructMemberAlignment = '3';
            CLTool.TreatWChar_tAsBuiltInType = 'false';
            CLTool.UsePrecompiledHeader = '0';
            CLTool.WarningLevel = '3';
            CLTool.ForcedIncludeFiles = '';

            var LinkTool = config.Tools('VCLinkerTool');
            if (bDebug) {
                LinkTool.LinkIncremental = linkIncrementalYes;
                LinkTool.GenerateDebugInformation = true;
                LinkTool.GenerateMapFile = 'true';
                LinkTool.MapExports = 'true';
            }
            else {
                LinkTool.LinkIncremental = linkIncrementalNo;
            }
            LinkTool.AdditionalDependencies = strDependLibs;
            LinkTool.OutputFile = strOutputFile;
            LinkTool.AdditionalLibraryDirectories = strCurLibsDir;
            LinkTool.SubSystem = '1';
            LinkTool.RandomizedBaseAddress = '1';
            LinkTool.DataExecutionPrevention = '0';
            LinkTool.ImportLibrary = strImportLib;
            LinkTool.TargetMachine = '1';

            var PostBuildTool = config.Tools("VCPostBuildEventTool");
            PostBuildTool.Description = "Performing registration...";
            var strResDir = "..\\..\\NEWPLUS\\TG3\\ConstData\\";
            var strPostCmd = "mkdir " + strResDir;
            strPostCmd += "\r\nxcopy /E /Y .\\Resource\\*.* " + strResDir;
            PostBuildTool.CommandLine = strPostCmd;
        }
    }
    catch (e) {
        throw e;
    }
}

function AddPchSettings(proj) {
}

function DelFile(fso, strWizTempFile) {
    try {
        if (fso.FileExists(strWizTempFile)) {
            var tmpFile = fso.GetFile(strWizTempFile);
            tmpFile.Delete();
        }
    }
    catch (e) {
        throw e;
    }
}

function CreateCustomInfFile() {
    try {
        var fso, TemplatesFolder, TemplateFiles, strTemplate;
        fso = new ActiveXObject('Scripting.FileSystemObject');

        var TemporaryFolder = 2;
        var tfolder = fso.GetSpecialFolder(TemporaryFolder);
        var strTempFolder = tfolder.Drive + '\\' + tfolder.Name;

        var strWizTempFile = strTempFolder + "\\" + fso.GetTempName();

        var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
        var strInfFile = strTemplatePath + '\\Templates.inf';
        wizard.RenderTemplate(strInfFile, strWizTempFile);

        var WizTempFile = fso.GetFile(strWizTempFile);
        return WizTempFile;
    }
    catch (e) {
        throw e;
    }
}

function GetTargetName(strName, strProjectName) {
    try {
        var strTarget = strName;

        var nIndex = strName.indexOf("root");

        if (nIndex >= 0) {
            var strMid = strProjectName;
            if (strName.indexOf("_res_") >= 0) {
                strMid = wizard.FindSymbol('PROJECT_NAME_LOWER');
            }
            strTarget = strName.substring(0, nIndex) + strMid + strName.substring(nIndex + 4, strName.length);
        }

        return strTarget;

    }
    catch (e) {
        throw e;
    }
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile) {
    try {
        var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

        var strName = '';

        var strTextStream = InfFile.OpenAsTextStream(1, -2);
        while (!strTextStream.AtEndOfStream)
        {
            strName = strTextStream.ReadLine();

            if (!strName.length || strName == '') {
                continue;
            }
//             log.WriteLine(strName);
            var strTarget = GetTargetName(strName, strProjectName);
            var strTemplate = strTemplatePath + '\\' + strName;
            var strFile = strProjectPath + '\\' + strTarget;

            var bCopyOnly = false;  
            var strExt = strName.substr(strName.lastIndexOf("."));
            if (strExt == ".ARM"
            || strExt == ".jpg"
            || strExt == ".png"
            || strExt == ".bmp"
            || strExt == ".ico"
            || strExt == ".gif"
            || strExt == ".rtf" 
            || strExt == ".css") {
                bCopyOnly = true;
            }
            wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);

            if (strExt == ".h") {
                if (strName.indexOf("UnicodeScript.h") >= 0) {
                    unFile = proj.Object.AddFile(strFile);
                    var strPrjTG3DirWin = '..\\..\\PRJ_TG3\\';
                    var unFileCfg = unFile.FileConfigurations('Debug');
                    var strCommandLine = strPrjTG3DirWin + 'Common\\StrConv\\TzdStrConv_V1.exe $(InputPath) $(InputDir)$(InputName)_str.h';
                    var strAddDepend = strPrjTG3DirWin + 'Common\\StrConv\\TzdStrConv_V1.exe';
                    unFileCfg.Tool.CommandLine = strCommandLine;
                    unFileCfg.Tool.AdditionalDependencies = strAddDepend;
                    unFileCfg.Tool.Outputs = '$(InputDir)$(InputName)_str.h';
                    continue;
                }
                
            }
            proj.Object.AddFile(strFile);
        }
        strTextStream.Close();
    }
    catch (e) {
        throw e;
    }
}
