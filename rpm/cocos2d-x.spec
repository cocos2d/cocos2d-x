Name: cocos2d-x
Version: 1.0.0
Release: 2
Summary: Cocos2D-X Cross-Platform 2D Games Framework

Group: System/GUI/Other
License: MIT
URL: http://cocos2d-x.org
Source: %{name}-%{version}.tar.bz2
BuildRequires: pkgconfig(egl)
BuildRequires: pkgconfig(glesv2)
BuildRequires: pkgconfig(Qt5Core)
BuildRequires: pkgconfig(Qt5Gui)
BuildRequires: pkgconfig(Qt5Multimedia)
BuildRequires: pkgconfig(Qt5Sensors)
BuildRequires: pkgconfig(zlib)
BuildRequires: pkgconfig(fontconfig)
BuildRequires: pkgconfig(freetype2)
BuildRequires: pkgconfig(libpng)
BuildRequires: pkgconfig(libtiff-4)
BuildRequires: libjpeg-turbo-devel
BuildRequires: pkgconfig(libcurl)

%description
cocos2d-x is a multi-platform 2D game framework in C++,
branched on cocos2d-iphone and licensed under MIT.

%package tests
Summary: Cocos2D-X Test Applications
Group: Development/Libraries
Requires: %{name} = %{version}

%description tests
cocos2d-x is a multi-platform 2D game framework in C++,
branched on cocos2d-iphone and licensed under MIT.

This package contains test applications for Cocos2D-X.

%package devel
Summary: Cocos2D-X Development Libraries
Group: Development/Libraries
Requires: %{name} = %{version}

%description devel
cocos2d-x is a multi-platform 2D game framework in C++,
branched on cocos2d-iphone and licensed under MIT.

This package contains development libraries for Cocos2D-X.

%prep
%setup -q

%build
%qmake5
make

%install
make INSTALL_ROOT=%{buildroot} install

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%defattr(-,root,root,-)
%doc README.mdown licenses
%{_libdir}/lib*.so.*

%files tests
%defattr(-,root,root,-)
%doc README.mdown
/opt/cocos2dx_TestCpp/*
/usr/share/applications/*.desktop

%files devel
%defattr(-,root,root,-)
%doc README.mdown AUTHORS CHANGELOG
%{_libdir}/lib*.so
#%{_includedir}/*/*.h
