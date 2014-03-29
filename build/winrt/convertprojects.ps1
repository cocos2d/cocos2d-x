. ".\scripts\createsln.ps1"
. ".\scripts\converterutils.ps1"
. ".\scripts\winrtconverter.ps1"


$workingDir = $PSScriptRoot


$cocosDir = join-path $workingDir "..\..\cocos" -Resolve
$libGUI = join-path $cocosDir "\gui\proj.wp8\libGUI.vcxproj"
$in = join-path $cocosDir "\gui\proj.win32\libGUI.vcxproj"
#WinrtConverter $in $libGUI "wp8" >> $null

$c2dLib = join-path $cocosDir "\2d\cocos2d_wp8.vcxproj"
$in = join-path $cocosDir "\2d\cocos2d.vcxproj"
#WinrtConverter $in $c2dLib "wp8" >> $null

$c2dLib = join-path $cocosDir "\2d\cocos2d_winrt.vcxproj"
$in = join-path $cocosDir "\2d\cocos2d.vcxproj"
#WinrtConverter $in $c2dLib "winrt" >> $null

$libNetwork = join-path $cocosDir "\network\proj.wp8\libNetwork.vcxproj"
$in = join-path $cocosDir "\network\proj.win32\libNetwork.vcxproj"
#WinrtConverter $in $libNetwork "wp8" >> $null

$libLocalStorage = join-path $cocosDir "\storage\local-storage\proj.wp8\libLocalStorage.vcxproj"
$in = join-path $cocosDir "\storage\local-storage\proj.win32\libLocalStorage.vcxproj"
#WinrtConverter $in $libLocalStorage "wp8" >> $null

$libAudio = join-path $cocosDir "\audio\proj.wp8\CocosDenshion.vcxproj"
$in = join-path $cocosDir "\audio\proj.win32\CocosDenshion.vcxproj"
#WinrtConverter $in $libAudio "wp8" >> $null

$libSpine = join-path $cocosDir "\editor-support\spine\proj.wp8\libSpine.vcxproj"
$in = join-path $cocosDir "\editor-support\spine\proj.win32\libSpine.vcxproj"
#WinrtConverter $in $libSpine "wp8" >> $null

$libCocosStudio = join-path $cocosDir "\editor-support\cocostudio\proj.wp8\libCocosStudio.vcxproj"
$in = join-path $cocosDir "\editor-support\cocostudio\proj.win32\libCocosStudio.vcxproj"
#WinrtConverter $in $libCocosStudio "wp8" >> $null

$libCocosBuilder = join-path $cocosDir "\editor-support\cocosbuilder\proj.wp8\libCocosBuilder.vcxproj"
$in = join-path $cocosDir "\editor-support\cocosbuilder\proj.win32\libCocosBuilder.vcxproj"
#WinrtConverter $in $libCocosBuilder "wp8" >> $null

$extensionsDir = join-path $workingDir "..\..\extensions" -Resolve
$libExtensions = join-path $extensionsDir "\proj.wp8\libExtensions.vcxproj"
#$in = join-path $extensionsDir "\proj.win32\libExtensions.vcxproj"
#WinrtConverter $in $libExtensions "wp8" >> $null

$externalDir = join-path $workingDir "..\..\external" -Resolve
$box2dDir = join-path $workingDir "..\..\external\Box2D" -Resolve
$libBox2d = join-path $box2dDir "\proj.wp8\Box2D.vcxproj"
$in = join-path $box2dDir "\proj.win32\Box2D.vcxproj"
#WinrtConverter $in $libBox2d "wp8" >> $null

$freetypeDir = join-path $workingDir "..\..\external\freetype2\include\wp8" -Resolve
$libFreetype = join-path $freetypeDir "\freetype-2.5.3\builds\windows\vc2010\freetype_wp8.vcxproj"
$in = join-path $freetypeDir "\freetype-2.5.3\builds\windows\vc2010\freetype.vcxproj"
#WinrtConverter $in $libFreetype "wp8" >> $null


$chipmunkDir = join-path $workingDir "..\..\external\chipmunk" -Resolve
$libChipmunk = join-path $chipmunkDir "\proj.wp8\chipmunk.vcxproj"
$in = join-path $chipmunkDir "\proj.win32\chipmunk.vcxproj"
#WinrtConverter $in $libChipmunk "wp8" >> $null

$chipmunkDir = join-path $workingDir "..\..\external\chipmunk" -Resolve
$libChipmunk = join-path $chipmunkDir "\proj.winrt\chipmunk.vcxproj"
$in = join-path $chipmunkDir "\proj.win32\chipmunk.vcxproj"
#WinrtConverter $in $libChipmunk "winrt" >> $null


$testDir = join-path $workingDir "..\..\tests" -Resolve
$testApp = join-path $testDir "\proj.wp8\TestCpp.vcxproj"
$in = join-path $testDir "\proj.win32\TestCpp.vcxproj"
#WinrtConverter $in $testApp "wp8" >> $null

#create opencv sln 
$solutionDir = join-path $workingDir "..\" -Resolve
$solution = join-path $solutionDir "cocos2d-wp8.vc2012.sln"
#CreateSolutionFile $solution "wp8" ($c2dLib, $libGUI, $libSpine, $libCocosStudio, $libCocosBuilder, $libExtensions, $libBox2d, $libChipmunk, $libLocalStorage, $libAudio, $testApp)

