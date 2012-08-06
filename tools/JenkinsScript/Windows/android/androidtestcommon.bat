echo off
rem =========Basic parameters============
rem jdk path
set JAVA_HOME=C:\Program Files\Java\jdk1.6.0_31
rem jdk version
set JDK_Version=1.6
rem sdk path
set AndroidHome=D:\Windows7\android-sdk-windows
rem android version path
set AndroidVersion=\platforms\android-8
rem android project path
set AndroidProject=D:\cocos2d-x\tests\proj.android
rem unsigned apk name
set unsign_apk=Tests.apk
rem signed apk name
set sign_apk=Tests-sign.apk
rem sign keystore
set apk_key=cdykeystore
set apk_keypass=123456
set apk_keystore=D:\cdykeystore

for %%x in ("%AndroidProject%") do set AndroidProject=%%~sx
for %%x in ("%JAVA_HOME%") do set JAVA_HOME=%%~sx
for %%x in ("%AndroidHome%") do set AndroidHome=%%~sx

rem jdk kit
set EXE_JAVA=%JAVA_HOME%\bin\java
set JAVAC=%JAVA_HOME%\bin\javac
set JAR=%JAVA_HOME%\bin\jar
set KeyTool=%JAVA_HOME%\bin\keytool
set Jarsigner=%JAVA_HOME%\bin\jarsigner

rem sdk kit
set AndroidAAPT=%AndroidHome%\platform-tools\aapt.exe
set AndroidDx=%AndroidHome%\platform-tools\dx.bat
set AndroidApkBuilder=%AndroidHome%\tools\apkbuilder.bat
set AndroidJar=%AndroidHome%%AndroidVersion%\android.jar

rem android project directory
set AndroidProjectDrive=D:
set AndroidProjectRes=%AndroidProject%\res
set AndroidProjectGen=%AndroidProject%\gen
set AndroidProjectBin=%AndroidProject%\bin
set AndroidProjectAsset=%AndroidProject%\assets
set AndroidProjectLibs=%AndroidProject%\libs
set AndroidProjectAndroidMainfest=%AndroidProject%\AndroidManifest.xml
set AndroidProjectSrc=%AndroidProject%\src\org\cocos2dx\tests\*.java
set AndroidProjectSrc=%AndroidProjectSrc% %AndroidProject%\src\org\cocos2dx\lib\*.java
set AndroidProjectSrc=%AndroidProjectSrc% %AndroidProject%\gen\org\cocos2dx\tests\*.java

rem output file
set AndroidProjectClassDex=%AndroidProject%\bin\classes.dex
set AndroidProjectResources=%AndroidProject%\bin\resources.ap_
set AndroidProjectApk="%AndroidProject%\bin\%unsign_apk%"
set AndroidProjectSignApk="%AndroidProject%\bin\%sign_apk%"

mkdir %AndroidProject%\gen
mkdir %AndroidProject%\src\org\cocos2dx\lib
mkdir %AndroidProject%\bin
::mkdir %AndroidProject%\bin\classes
xcopy D:\cocos2d-x\cocos2dx\platform\android\java\src_common\org\cocos2dx\lib %AndroidProject%\src\org\cocos2dx\lib /s

echo generate R.java file
%AndroidAAPT% package -f -m -J %AndroidProjectGen% -S %AndroidProjectRes% -I %AndroidJar% -M %AndroidProjectAndroidMainfest%

echo generate class file
%JAVAC% -encoding UTF-8 -target %JDK_Version% -bootclasspath %AndroidJar% -d %AndroidProjectBin% %AndroidProjectSrc% %AndroidProjectGen%\org\cocos2dx\tests\R.java

echo generate dex file
echo on
%AndroidProjectDrive%
cd %AndroidProjectBin%
rem packaging the *.class file into *.jar file
%JAR% cvf %AndroidProjectBin%\classes.jar *.*
cd %AndroidProject%
rem generate *.dex file
call %AndroidDx% --dex --output=%AndroidProjectClassDex% %AndroidProjectBin%\classes.jar

echo package resources files
%AndroidAAPT% package -f -M %AndroidProjectAndroidMainfest% -S %AndroidProjectRes% -A %AndroidProjectAsset% -I %AndroidJar% -F %AndroidProjectResources%

echo generate unsigned apk file
call %AndroidApkBuilder% %AndroidProjectApk% -v -u -z %AndroidProjectResources% -f %AndroidProjectClassDex% -rf %AndroidProject%\src -nf %AndroidProjectLibs% -rj %AndroidProjectLibs%

echo generate signed apk file
%Jarsigner% -verbose -keystore %apk_keystore% -keypass %apk_keypass% -storepass %apk_keypass% -signedjar %AndroidProjectSignApk% %AndroidProjectApk% cdykeystore

echo sign success!
pause