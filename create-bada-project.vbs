set fso = Wscript.CreateObject("Scripting.FileSystemObject")

dim szPrompt, msgRet
szPrompt = "Prompt"

function ReplaceFileContent(fileName, oldStr, newStr)
    set f = fso.opentextfile(fileName)
    s = replace(f.readall, oldStr, newStr)
    f.close
    set r = fso.opentextfile(fileName, 2, true)
    r.write s
end function

function CopyFolder(srcFolder, desFolder)
    if (fso.FolderExists(desFolder)) then
        'msgbox("none:"+srcFolder+":"+desFolder)
        'If the desFolder exist, do nothing.
    else
        CopyFolder = fso.CopyFolder(srcFolder, desFolder)
    end if
end function

function ConfigureProject()
    dim szProjectName
    szProjectName = Inputbox("Please Input Project Name:", szPrompt)

    if szProjectName = "" then
        Wscript.quit
    end if

    if (0 = strcomp(szProjectName, "HelloWorld", 1) or 0 = strcomp(szProjectName, "tests", 1)) then
        msgRet = msgbox("Can not create a project named with "+szProjectName+", Please input again!", 1, szPrompt)
        if (msgRet = 1) then
            call ConfigureProject
        end if
        Wscript.quit
    end if

    if (fso.FolderExists(szProjectName)) then
    else
        fso.CreateFolder(szProjectName)
    end if

    dim badaFolder
    badaFolder = szProjectName + "\bada"
    if (fso.FolderExists(badaFolder)) then
        msgRet = msgbox("The '"+szProjectName+"' project exists, can't override! Please input again!", 1, szPrompt)
        if (msgRet = 1) then
            call ConfigureProject
        end if
        Wcript.quit
    end if

    dim szSrcClass, szSrcBada, szSrcResource
    dim szDesClass, szDesBada, szDesResource
    
    szSrcClass = "HelloWorld\Classes"
    szSrcBada = "HelloWorld\bada"
    szSrcResource = "HelloWorld\Resource"
    
    szDesClass = szProjectName+"\Classes"
    szDesBada = szProjectName+"\bada"
    szDesResource = szProjectName+"\Resource"
    
    call CopyFolder(szSrcClass, szDesClass)
    call CopyFolder(szSrcBada, szDesBada)
    call CopyFolder(szSrcResource, szDesResource)
    
    dim i
    for i=1 to 2
        call ReplaceFileContent(szProjectName+"\bada\sdk"+cstr(i)+".0\application.xml", "HelloWorld", szProjectName)
        call ReplaceFileContent(szProjectName+"\bada\sdk"+cstr(i)+".0\.project", "HelloWorld", szProjectName)
        call ReplaceFileContent(szProjectName+"\bada\sdk"+cstr(i)+".0\.cproject", "HelloWorld", szProjectName)
    next
    
    call msgbox("Congratulations, the '"+szProjectName+"' project have been created successfully, please use Bada IDE to import the project!", 0, szPrompt)

end function

call ConfigureProject
Wscript.quit 