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

    dim qnxFolder
    qnxFolder = szProjectName + "\qnx"
    if (fso.FolderExists(qnxFolder)) then
        msgRet = msgbox("The '"+szProjectName+"' project exists, can't override! Please input again!", 1, szPrompt)
        if (msgRet = 1) then
            call ConfigureProject
        end if
        Wcript.quit
    end if

    dim szSrcClass, szSrcQnx, szSrcResource
    dim szDesClass, szDesQnx, szDesResource
    
    szSrcClass = "HelloWorld\Classes"
    szSrcQnx = "HelloWorld\qnx"
    szSrcResource = "HelloWorld\Resources"
    
    szDesClass = szProjectName+"\Classes"
    szDesQnx = szProjectName+"\qnx"
    szDesResource = szProjectName+"\Resources"
    
    call CopyFolder(szSrcClass, szDesClass)
    call CopyFolder(szSrcQnx, szDesQnx)
    call CopyFolder(szSrcResource, szDesResource)
    
    call ReplaceFileContent(szProjectName+"\qnx\bar-descriptor.xml", "HelloWorld", szProjectName)
    call ReplaceFileContent(szProjectName+"\qnx\.project", "HelloWorld", szProjectName)
    call ReplaceFileContent(szProjectName+"\qnx\.cproject", "HelloWorld", szProjectName)

    call msgbox("Congratulations, the '"+szProjectName+"' project have been created successfully, please use QNX IDE to import the project!", 0, szPrompt)

end function

call ConfigureProject
Wscript.quit 