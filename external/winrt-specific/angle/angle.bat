xcopy ".\..\angleproject\src\WP8\redist\vs2012\ARM\Release\libGLESv2_phone\libGLESv2_phone.dll" ".\..\..\wp8-specific\angle\prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\ARM\Release\libGLESv2_phone\libGLESv2_phone.lib" ".\..\..\wp8-specific\angle\prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\ARM\Release\libGLESv2_phone\libGLESv2_phone.exp" ".\..\..\wp8-specific\angle\prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\ARM\Release\libEGL_phone\libEGL_phone.dll" ".\..\..\wp8-specific\angle\prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\ARM\Release\libEGL_phone\libEGL_phone.lib" ".\..\..\wp8-specific\angle\prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\ARM\Release\libEGL_phone\libEGL_phone.exp" ".\..\..\wp8-specific\angle\prebuilt\ARM\" /iycq

xcopy ".\..\angleproject\src\WP8\redist\vs2012\Win32\Release\libGLESv2_phone\libGLESv2_phone.dll" ".\..\..\wp8-specific\angle\prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\Win32\Release\libGLESv2_phone\libGLESv2_phone.lib" ".\..\..\wp8-specific\angle\prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\Win32\Release\libGLESv2_phone\libGLESv2_phone.exp" ".\..\..\wp8-specific\angle\prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\Win32\Release\libEGL_phone\libEGL_phone.dll" ".\..\..\wp8-specific\angle\prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\Win32\Release\libEGL_phone\libEGL_phone.lib" ".\..\..\wp8-specific\angle\prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WP8\redist\vs2012\Win32\Release\libEGL_phone\libEGL_phone.exp" ".\..\..\wp8-specific\angle\prebuilt\Win32\" /iycq

xcopy ".\..\angleproject\src\WinRT\redist\vs2013\ARM\Release\libGLESv2_winrt_2013\libGLESv2.dll" ".\..\..\winrt-specific\angle\prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\ARM\Release\libGLESv2_winrt_2013\libGLESv2.lib" "prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\ARM\Release\libGLESv2_winrt_2013\libGLESv2.exp" "prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\ARM\Release\libEGL_winrt_2013\libEGL.dll" "prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\ARM\Release\libEGL_winrt_2013\libEGL.lib" "prebuilt\ARM\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\ARM\Release\libEGL_winrt_2013\libEGL.exp" "prebuilt\ARM\" /iycq

xcopy ".\..\angleproject\src\WinRT\redist\vs2013\Win32\Release\libGLESv2_winrt_2013\libGLESv2.dll" "prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\Win32\Release\libGLESv2_winrt_2013\libGLESv2.lib" "prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\Win32\Release\libGLESv2_winrt_2013\libGLESv2.exp" "prebuilt\Win32" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\Win32\Release\libEGL_winrt_2013\libEGL.dll" "prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\Win32\Release\libEGL_winrt_2013\libEGL.lib" "prebuilt\Win32\" /iycq
xcopy ".\..\angleproject\src\WinRT\redist\vs2013\Win32\Release\libEGL_winrt_2013\libEGL.exp" "prebuilt\Win32\" /iycq



xcopy ".\..\angleproject\include" "include" /eiycq

xcopy ".\..\angleproject\src\common\winrtangle.h" "include" /iycq
xcopy ".\..\angleproject\src\common\winrtangleutils.h" "include" /iycq
xcopy ".\..\angleproject\src\common\winrtplatform.h" "include" /iycq
xcopy ".\..\angleproject\src\common\angleutils.h" "include" /iycq
xcopy ".\..\angleproject\samples\gles2_book\Common\esUtil.h" "include" /iycq

