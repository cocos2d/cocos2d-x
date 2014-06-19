set IN_DIR=.\..\..\..\angle\src\WP8\redist\vs2012\ARM\Release

set OUT_DIR=.\..\..\external\wp8-specific\angle\prebuilt\ARM\
xcopy "%IN_DIR%\libGLESv2_phone\libGLESv2_phone.dll" "%OUT_DIR%" /iycq

xcopy "%IN_DIR%\libGLESv2_phone\libGLESv2_phone.lib" "%OUT_DIR%" /iycq

xcopy "%IN_DIR%\libEGL_phone\libEGL_phone.dll" "%OUT_DIR%" /iycq

xcopy "%IN_DIR%\libEGL_phone\libEGL_phone.lib" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\esUtil_phone\esUtil_phone.lib" "%OUT_DIR%"  /iycq



set IN_DIR=.\..\..\..\angle\src\WP8\redist\vs2012\Win32\Release

set OUT_DIR=.\..\..\external\wp8-specific\angle\prebuilt\Win32\


xcopy "%IN_DIR%\libGLESv2_phone\libGLESv2_phone.dll" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libGLESv2_phone\libGLESv2_phone.lib" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libEGL_phone\libEGL_phone.dll" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libEGL_phone\libEGL_phone.lib" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\esUtil_phone\esUtil_phone.lib" "%OUT_DIR%"  /iycq



set IN_DIR=.\..\..\..\angle\src\WinRT\redist\vs2013\ARM\Release\
set OUT_DIR=.\..\..\external\winrt-specific\angle\prebuilt\ARM\
xcopy "%IN_DIR%\libGLESv2_winrt_2013\libGLESv2.dll" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libGLESv2_winrt_2013\libGLESv2.lib" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libEGL_winrt_2013\libEGL.dll" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libEGL_winrt_2013\libEGL.lib" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\esUtil_winrt_2013\esUtil.lib" "%OUT_DIR%"  /iycq


set IN_DIR=.\..\..\..\angle\src\WinRT\redist\vs2013\Win32\Release\
set OUT_DIR=.\..\..\external\winrt-specific\angle\prebuilt\Win32\
xcopy "%IN_DIR%\libGLESv2_winrt_2013\libGLESv2.dll" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libGLESv2_winrt_2013\libGLESv2.lib" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libEGL_winrt_2013\libEGL.dll" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\libEGL_winrt_2013\libEGL.lib" "%OUT_DIR%"  /iycq

xcopy "%IN_DIR%\esUtil_winrt_2013\esUtil.lib" "%OUT_DIR%"  /iycq


set OUT_DIR=.\..\..\external\winrt-specific\angle\include
xcopy ".\..\..\..\angle\include" "%OUT_DIR%" /eiycq
xcopy ".\..\..\..\angle\src\common\winrtangle.h" "%OUT_DIR%" /iycq
xcopy ".\..\..\..\angle\samples\gles2_book\Common\esUtil.h" "%OUT_DIR%" /iycq

