set IN_DIR=.\..\..\..\..\..\..\angle\src\WP8\redist\vs2012\ARM\Release
set OUT_DIR=.\..\..\wp8\libraries\arm\

xcopy "%IN_DIR%\libGLESv2_phone\libGLESv2_phone.dll" "%OUT_DIR%" /iycq
xcopy "%IN_DIR%\libGLESv2_phone\libGLESv2_phone.lib" "%OUT_DIR%" /iycq
xcopy "%IN_DIR%\libEGL_phone\libEGL_phone.dll" "%OUT_DIR%" /iycq
xcopy "%IN_DIR%\libEGL_phone\libEGL_phone.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\esUtil_phone\esUtil_phone.lib" "%OUT_DIR%"  /iycq

set IN_DIR=.\..\..\..\..\..\..\angle\src\WP8\redist\vs2012\Win32\Release
set OUT_DIR=.\..\..\wp8\libraries\x86\

xcopy "%IN_DIR%\libGLESv2_phone\libGLESv2_phone.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libGLESv2_phone\libGLESv2_phone.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_phone\libEGL_phone.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_phone\libEGL_phone.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\esUtil_phone\esUtil_phone.lib" "%OUT_DIR%"  /iycq

set IN_DIR=.\..\..\..\..\..\..\angle\src\WinRT\redist\vs2012\ARM\Release
set OUT_DIR=.\..\..\winrt\libraries\vs2012\arm\

xcopy "%IN_DIR%\libGLESv2_winrt\libGLESv2.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libGLESv2_winrt\libGLESv2.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_winrt\libEGL.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_winrt\libEGL.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\esUtil_winrt\esUtil.lib" "%OUT_DIR%"  /iycq

set IN_DIR=.\..\..\..\..\..\..\angle\src\WinRT\redist\vs2012\Win32\Release
set OUT_DIR=.\..\..\winrt\libraries\vs2012\Win32\
xcopy "%IN_DIR%\libGLESv2_winrt\libGLESv2.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libGLESv2_winrt\libGLESv2.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_winrt\libEGL.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_winrt\libEGL.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\esUtil_winrt\esUtil.lib" "%OUT_DIR%"  /iycq

set IN_DIR=.\..\..\..\..\..\..\angle\src\WinRT\redist\vs2013\ARM\Release
set OUT_DIR=.\..\..\winrt\libraries\vs2013\arm\

xcopy "%IN_DIR%\libGLESv2_winrt_2013\libGLESv2.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libGLESv2_winrt_2013\libGLESv2.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_winrt_2013\libEGL.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_winrt_2013\libEGL.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\esUtil_winrt_2013\esUtil.lib" "%OUT_DIR%"  /iycq

set IN_DIR=.\..\..\..\..\..\..\angle\src\WinRT\redist\vs2013\Win32\Release
set OUT_DIR=.\..\..\winrt\libraries\vs2013\Win32\

xcopy "%IN_DIR%\libGLESv2_winrt_2013\libGLESv2.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libGLESv2_winrt_2013\libGLESv2.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_winrt_2013\libEGL.dll" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\libEGL_winrt_2013\libEGL.lib" "%OUT_DIR%"  /iycq
xcopy "%IN_DIR%\esUtil_winrt_2013\esUtil.lib" "%OUT_DIR%"  /iycq

set IN_DIR=.\..\..\..\..\..\..\angle

xcopy "%IN_DIR%\include" "include" /eiycq

xcopy "%IN_DIR%\src\common\winrtangle.h" "include" /iycq
xcopy "%IN_DIR%\src\common\winrtangleutils.h" "include" /iycq
xcopy "%IN_DIR%\src\common\winrtplatform.h" "include" /iycq
xcopy "%IN_DIR%\src\common\angleutils.h" "include" /iycq
xcopy "%IN_DIR%\samples\gles2_book\Common\esUtil.h" "include" /iycq

