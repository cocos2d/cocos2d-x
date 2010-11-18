
function OnFinish(selProj, selObj) {
    try {
        // 		var WizardVersion = wizard.FindSymbol('WIZARD_VERSION');

        // Create symbols based on the project name
        var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
        var strProjectName = wizard.FindSymbol('PROJECT_NAME');

        wizard.AddSymbol('PROJECT_NAME_LOWER', strProjectName.toLowerCase(), false);
        wizard.AddSymbol('PROJECT_NAME_UPPER', strProjectName.toUpperCase(), false);

//         if (strProjectName.length >= 6) {
//             wizard.AddSymbol('PRO_NAME_PREFIX', strProjectName.substr(0, 6).toUpperCase(), false);
//         }
//         else {
//             var strRes = '_RES';
//             var strNewFormId = strProjectName + strRes.substr(0, (6 - strProjectName.length));
// 
//             wizard.AddSymbol('PRO_NAME_PREFIX', strNewFormId.toUpperCase(), false);
//         }

        // Set current year symbol
        var d = new Date();
        var nYear = 0;
        nYear = d.getFullYear();
        wizard.AddSymbol("CCX_CURRENT_YEAR", nYear);
        wizard.AddSymbol("CCX_CURRENT_DATE", d.toString());

        var FileSys = new ActiveXObject("Scripting.FileSystemObject");
        var strUserTarget = strProjectName + ".uphone.vcproj.user";
        var strUserPath = FileSys.BuildPath(strProjectPath, strUserTarget);

        if (!FileSys.FolderExists(strProjectPath))
            FileSys.CreateFolder(strProjectPath);

        var file = FileSys.OpenTextFile(strUserPath, 2, true);
        if (file == null) {
            return;
        }
        var strUserValue = "<?xml version=\"1.0\" encoding=\"utf-8\"?><VisualStudioUserFile ProjectType=\"Visual C++\" Version=\"9.00\" ShowAllFiles=\"true\"><Configurations><Configuration Name=\"Debug|Win32\"><DebugSettings Command=\"TG3_RunDLL.exe\" CommandArguments=\"$(TargetPath)\"/></Configuration></VisualStudioUserFile>";
        file.WriteLine(strUserValue);
        file.Close();

        selProj = CreateCustomProject(strProjectName, strProjectPath);
        AddConfig(selProj, strProjectName);
        AddFilters(selProj);

        var InfFile = CreateCustomInfFile();
        AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
        PchSettings(selProj);
        InfFile.Delete();

        selProj.Object.Save();
    }
    catch (e) {
        if (e.description.length != 0)
            SetErrorInfo(e);
        return e.number
    }
}

function CreateCustomProject(strProjectName, strProjectPath) {
    try {
        var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
        var strProjTemplate = '';
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

        var strProjectNameWithExt = '';
        strProjectNameWithExt = strProjectName + '.uphone.vcproj';

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
        var strSrcFilter = wizard.FindSymbol('SOURCE_FILTER');
        var group = proj.Object.AddFilter('source');
        group.Filter = strSrcFilter;

        strSrcFilter = wizard.FindSymbol('INCLUDE_FILTER');
        group = proj.Object.AddFilter('include');
        group.Filter = strSrcFilter;

        if (wizard.FindSymbol('CCX_USE_UI_RESOURCE')) {
            strSrcFilter = wizard.FindSymbol('RESOURCE_FILTER');
            group = proj.Object.AddFilter('resource');
            group.Filter = strSrcFilter;
        }

        strSrcFilter = wizard.FindSymbol('MAKEFILE_FILTER');
        group = proj.Object.AddFilter('makefile');
        group.Filter = strSrcFilter;

    }
    catch (e) {
        throw e;
    }
}

function AddConfig(proj, strProjectName) {
    try {
        var config = proj.Object.Configurations('Debug');
        var strSolutionName = "";

        var strPrjTG3Dir = '../../PRJ_TG3';

        var strOutputDir = '../../PRJ_TG3/LIB/Win32Lib';
        var strCurIncludeDir = '..\\..\\PRJ_TG3\\Include;..\\..\\PRJ_TG3\\Include\\MTAPI;..\\..\\PRJ_TG3\\Include\\ThirdParty;..\\..\\PRJ_TG3\\Include\\TCOM;..\\..\\PRJ_TG3\\Include\\OpenGL';
        strCurIncludeDir += ';.;.\\Classes;.\\uphone;.\\uphone\\Res;..\\cocos2dx;..\\cocos2dx\\include';

        var strDefinitions = 'WIN32;_DEBUG;_CONSOLE;_TRANZDA_VM_;SS_MAKEDLL';
        var strDependLibs = 'WS2_32.Lib EosConfig.lib SoftSupport.lib TG3_DLL.lib libcocos2d.lib';
        var strCurLibsDir = '../../PRJ_TG3/Common/ICU/lib;../../PRJ_TG3/Mtapi/Win32/lib;../../PRJ_TG3/LIB/Win32Lib;../../PRJ_TG3/Common/SoftSupport';
        var strImportLib = '$(OutDir)/' + wizard.FindSymbol("PROJECT_NAME") + '.lib';
        var strOutputFile = '$(OutDir)/' + wizard.FindSymbol("PROJECT_NAME") + '.dll';

        if (wizard.FindSymbol('CCX_USE_BOX2D')) {
            strCurIncludeDir += ';..\\;..\\Box2D';
            strDependLibs += ' libBox2d.lib';
        }
        if (wizard.FindSymbol('CCX_USE_CHIPMUNK')) {
            strCurIncludeDir += ';..\\chipmunk\\include\\chipmunk';
            strDependLibs += ' libchipmunk.lib';
        }
        if (wizard.FindSymbol('CCX_USE_COCOS_DENSHION_SIMPLE_AUDIO_ENGINE')) {
            strCurIncludeDir += ';..\\CocosDenshion\\Include';
            strDependLibs += ' libCocosDenshion.lib';
        }

        if (wizard.FindSymbol("CCX_USE_TCOM_SUPPORT")) {
            strDefinitions = strDefinitions + ';__TCOM_SUPPORT__';
        }

        wizard.AddSymbol('PROJECT_PRJ_TG3_DIR', strPrjTG3Dir, false);

        config.IntermediateDirectory = 'Debug';
        config.OutputDirectory = strOutputDir;
        config.ConfigurationType = '2';
        config.InheritedPropertySheets = '$(VCInstallDir)VCProjectDefaults\UpgradeFromVC71.vsprops';
        //         config.DebugSettings.Command = 'TG3_RunDll.exe';
        //         config.DebugSettings.CommandArguments = '$(TargetPath)';

        proj.Object.Keyword = "uPhoneProj";


        var CLTool = config.Tools('VCCLCompilerTool');
        CLTool.Optimization = "0";
        CLTool.AdditionalIncludeDirectories = strCurIncludeDir;
        CLTool.PreprocessorDefinitions = strDefinitions;
        CLTool.MinimalRebuild = 'true';
        CLTool.BasicRuntimeChecks = '3';
        CLTool.RuntimeLibrary = '3';
        CLTool.StructMemberAlignment = '3';
        CLTool.TreatWChar_tAsBuiltInType = 'false';
        CLTool.UsePrecompiledHeader = '0';
        CLTool.WarningLevel = '3';
        CLTool.DebugInformationFormat = '4';
        CLTool.ForcedIncludeFiles = '';

        var LinkTool = config.Tools('VCLinkerTool');
        LinkTool.AdditionalDependencies = strDependLibs;
        LinkTool.OutputFile = strOutputFile;
        LinkTool.LinkIncremental = '2';
        LinkTool.AdditionalLibraryDirectories = strCurLibsDir;
        LinkTool.GenerateDebugInformation = 'true';
        LinkTool.GenerateMapFile = 'true';
        LinkTool.MapExports = 'true';
        LinkTool.SubSystem = '1';
        LinkTool.RandomizedBaseAddress = '1';
        LinkTool.DataExecutionPrevention = '0';
        LinkTool.ImportLibrary = strImportLib;
        LinkTool.TargetMachine = '1';

        config = proj.Object.Configurations('Release');
        config.IntermediateDirectory = '$(ConfigurationName)';
        config.OutputDirectory = '$(ConfigurationName)';

        var CLTool = config.Tools('VCCLCompilerTool');
        CLTool.Optimization = "0";
        CLTool.AdditionalIncludeDirectories = strCurIncludeDir;
        CLTool.PreprocessorDefinitions = strDefinitions;
        CLTool.MinimalRebuild = 'true';
        CLTool.BasicRuntimeChecks = '3';
        CLTool.RuntimeLibrary = '3';
        CLTool.StructMemberAlignment = '3';
        CLTool.TreatWChar_tAsBuiltInType = 'false';
        CLTool.UsePrecompiledHeader = '0';
        CLTool.WarningLevel = '3';
        CLTool.DebugInformationFormat = '4';
        CLTool.ForcedIncludeFiles = '';

        var LinkTool = config.Tools('VCLinkerTool');
        LinkTool.AdditionalDependencies = strDependLibs;
        LinkTool.OutputFile = strOutputFile;
        LinkTool.LinkIncremental = '2';
        LinkTool.AdditionalLibraryDirectories = strCurLibsDir;
        LinkTool.GenerateDebugInformation = 'true';
        LinkTool.GenerateMapFile = 'true';
        LinkTool.MapExports = 'true';
        LinkTool.SubSystem = '1';
        LinkTool.RandomizedBaseAddress = '1';
        LinkTool.DataExecutionPrevention = '0';
        LinkTool.ImportLibrary = strImportLib;
        LinkTool.TargetMachine = '1';
    }
    catch (e) {
        throw e;
    }
}

function PchSettings(proj) {
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
            strTarget = strName.substring(0, nIndex) + strProjectName + strName.substring(nIndex + 4, strName.length);
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
		    
  			var strTarget = GetTargetName(strName, strProjectName);
  			var strTemplate = strTemplatePath + '\\' + strName;
 			var strFile = strProjectPath + '\\' + strTarget;

			var bCopyOnly = false;  
			var strExt = strName.substr(strName.lastIndexOf("."));
			if (strExt == ".jpg" || strExt == ".png" || strExt == ".bmp" || strExt == ".ico" || strExt == ".gif" || strExt == ".rtf" || strExt == ".css") {
			    bCopyOnly = true;
			}
			wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);

            if (strExt == ".h") {
                if (strName.indexOf("UnicodeScript") >= 0) {
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
