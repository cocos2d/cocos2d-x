set fso = Wscript.CreateObject("Scripting.FileSystemObject")

function ReplaceFileContent(fileName, oldStr, newStr)
    set f = fso.opentextfile(fileName)
    s = replace(f.readall, oldStr, newStr)
    f.close
    set r = fso.opentextfile(fileName, 2, true)
    r.write s
end function

dim szProjectName
szProjectName = Inputbox("Please Input Project Name:", "Prompt")

if (fso.FolderExists(szProjectName)) then
else
    fso.CreateFolder(szProjectName)
end if

dim qnxFolder
qnxFolder = szProjectName + "\qnx"
if (fso.FolderExists(qnxFolder)) then
    msgbox("the project exists, can't override!")
    Wscript.quit
else
    fso.CreateFolder(qnxFolder)
end if

ret = fso.CopyFolder("HelloWorld\Classes", szProjectName+"\Classes")
ret = fso.CopyFolder("HelloWorld\qnx", szProjectName+"\qnx")
ret = fso.CopyFolder("HelloWorld\Resource", szProjectName+"\Resource")


call ReplaceFileContent(szProjectName+"\qnx\bar-descriptor.xml", "HelloWorld", szProjectName)
call ReplaceFileContent(szProjectName+"\qnx\.project", "HelloWorld", szProjectName)
call ReplaceFileContent(szProjectName+"\qnx\.cproject", "HelloWorld", szProjectName)



Wscript.quit 