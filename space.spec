# $Id$
%define today	%(echo 'LC_ALL="C" date +"%a %b %d %Y"')

Summary:		SPACE
Name:			space
Version:		0.0.1
Release:		1
Copyright:		GPL
Group:			Applications/Text
Source:			%{name}-%{version}.tar.gz
Vendor:			Aki Hasegawa <aki@gsc.riken.jp>
Packager:		Aki Hasegawa <aki@gsc.riken.jp>
BuildRoot:		%{_tmppath}/%{name}-%{version}-root

%description
SPACE: The Sequence Pattern Capture Engine.

%prep
%setup

%build
%configure
make

%install
rm -rf ${RPM_BUILD_ROOT}
%makeinstall

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root)
%doc AUTHORS BUGS COPYING ChangeLog INSTALL* NEWS README THANKS TODO
%attr(755,root,root) %{_bindir}/*
%{_mandir}/man1/*
%{_infodir}/*
%{_datadir}/*
%{_sysconfdir}/space.db.sample

%changelog
* Mon Nov 07 2005 Aki Hasegawa <aki@gsc.riken.jp>
- first build
