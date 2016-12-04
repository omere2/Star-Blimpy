# Microsoft Developer Studio Project File - Name="StarBlimpy" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=StarBlimpy - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "StarBlimpy.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "StarBlimpy.mak" CFG="StarBlimpy - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "StarBlimpy - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "StarBlimpy - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "StarBlimpy - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "C:\projects\allegro\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "NDEBUG"
# ADD RSC /l 0x40d /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 png\libpng.lib png\zlib.lib alleg.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "StarBlimpy - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /I "C:\projects\allegro\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40d /d "_DEBUG"
# ADD RSC /l 0x40d /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 png\libpng.lib png\zlib.lib alleg.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "StarBlimpy - Win32 Release"
# Name "StarBlimpy - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "png"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\png\loadpng.c
# End Source File
# End Group
# Begin Group "Animation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation.cpp
# End Source File
# Begin Source File

SOURCE=.\AnimationFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\basicanimation.cpp
# End Source File
# Begin Source File

SOURCE=.\compositeanimation.cpp
# End Source File
# End Group
# Begin Group "widgets"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation_bar.cpp
# End Source File
# Begin Source File

SOURCE=.\health_infobar.cpp
# End Source File
# Begin Source File

SOURCE=.\infobar.cpp
# End Source File
# Begin Source File

SOURCE=.\weapon_bar.cpp
# End Source File
# End Group
# Begin Group "AI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AI.CPP
# End Source File
# Begin Source File

SOURCE=.\CircleAI.cpp
# End Source File
# Begin Source File

SOURCE=.\KeyboardAI.cpp
# End Source File
# Begin Source File

SOURCE=.\ShipKeyboardAI.cpp
# End Source File
# End Group
# Begin Group "Entities"

# PROP Default_Filter ""
# Begin Group "Interfaces"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ShotInterface.cpp
# End Source File
# End Group
# Begin Group "Shots"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CruiseMissile.cpp
# End Source File
# Begin Source File

SOURCE=.\Missile.cpp
# End Source File
# Begin Source File

SOURCE=.\Shot.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ActiveShield.cpp
# End Source File
# Begin Source File

SOURCE=.\AdvDynamicEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\DynamicEntity.cpp
# End Source File
# Begin Source File

SOURCE=.\Entity.cpp
# End Source File
# Begin Source File

SOURCE=.\Explosion.cpp
# End Source File
# Begin Source File

SOURCE=.\Ship.cpp
# End Source File
# Begin Source File

SOURCE=.\star.cpp
# End Source File
# Begin Source File

SOURCE=.\WeaponCarrier.cpp
# End Source File
# End Group
# Begin Group "Weapons"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gun.cpp
# End Source File
# Begin Source File

SOURCE=.\MissileLauncher.cpp
# End Source File
# Begin Source File

SOURCE=.\NullWeapon.cpp
# End Source File
# Begin Source File

SOURCE=.\Weapon.cpp
# End Source File
# End Group
# Begin Group "CoreComponents"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Engine.cpp
# End Source File
# Begin Source File

SOURCE=.\Observable.cpp
# End Source File
# Begin Source File

SOURCE=.\Observer.cpp
# End Source File
# End Group
# Begin Group "views"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WorldView.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoomingView.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\baseexception.cpp
# End Source File
# Begin Source File

SOURCE=.\callback.cpp
# End Source File
# Begin Source File

SOURCE=.\Collision.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\DeathException.cpp
# End Source File
# Begin Source File

SOURCE=.\EntityFactory.cpp
# End Source File
# Begin Source File

SOURCE=.\EntityPool.cpp
# End Source File
# Begin Source File

SOURCE=.\GameEngine.cpp
# End Source File
# Begin Source File

SOURCE=.\GameException.cpp
# End Source File
# Begin Source File

SOURCE=.\refbitmap.cpp
# End Source File
# Begin Source File

SOURCE=.\testgame.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "Animation h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation.h
# End Source File
# Begin Source File

SOURCE=.\AnimationFactory.h
# End Source File
# Begin Source File

SOURCE=.\basicanimation.h
# End Source File
# Begin Source File

SOURCE=.\compositeanimation.h
# End Source File
# Begin Source File

SOURCE=.\Drawable.h
# End Source File
# End Group
# Begin Group "png h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\png\loadpng.h
# End Source File
# End Group
# Begin Group "widgets h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\animation_bar.h
# End Source File
# Begin Source File

SOURCE=.\health_infobar.h
# End Source File
# Begin Source File

SOURCE=.\infobar.h
# End Source File
# Begin Source File

SOURCE=.\weapon_bar.h
# End Source File
# End Group
# Begin Group "AI h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\AI.H
# End Source File
# Begin Source File

SOURCE=.\CircleAI.h
# End Source File
# Begin Source File

SOURCE=.\KeyboardAI.h
# End Source File
# Begin Source File

SOURCE=.\ShipKeyboardAI.h
# End Source File
# End Group
# Begin Group "Entities h"

# PROP Default_Filter ""
# Begin Group "Interfaces.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ShotInterface.h
# End Source File
# End Group
# Begin Group "Shots h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CruiseMissile.h
# End Source File
# Begin Source File

SOURCE=.\missile.h
# End Source File
# Begin Source File

SOURCE=.\Shot.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ActiveShield.h
# End Source File
# Begin Source File

SOURCE=.\AdvDynamicEntity.h
# End Source File
# Begin Source File

SOURCE=.\dynamicEntity.h
# End Source File
# Begin Source File

SOURCE=.\Entity.h
# End Source File
# Begin Source File

SOURCE=.\Explosion.h
# End Source File
# Begin Source File

SOURCE=.\Ship.h
# End Source File
# Begin Source File

SOURCE=.\star.h
# End Source File
# Begin Source File

SOURCE=.\WeaponCarrier.h
# End Source File
# End Group
# Begin Group "Weapons h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Gun.h
# End Source File
# Begin Source File

SOURCE=.\MissileLauncher.h
# End Source File
# Begin Source File

SOURCE=.\NullWeapon.h
# End Source File
# Begin Source File

SOURCE=.\Weapon.h
# End Source File
# End Group
# Begin Group "CoreComponents.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Engine.h
# End Source File
# Begin Source File

SOURCE=.\Observable.h
# End Source File
# Begin Source File

SOURCE=.\Observer.h
# End Source File
# End Group
# Begin Group "views.h"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WorldView.h
# End Source File
# Begin Source File

SOURCE=.\ZoomingView.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\baseexception.h
# End Source File
# Begin Source File

SOURCE=.\callback.h
# End Source File
# Begin Source File

SOURCE=.\Collision.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\common.h
# End Source File
# Begin Source File

SOURCE=.\DeathException.h
# End Source File
# Begin Source File

SOURCE=.\EntityFactory.h
# End Source File
# Begin Source File

SOURCE=.\EntityPool.h
# End Source File
# Begin Source File

SOURCE=.\GameEngine.h
# End Source File
# Begin Source File

SOURCE=.\GameException.h
# End Source File
# Begin Source File

SOURCE=.\keys.h
# End Source File
# Begin Source File

SOURCE=.\refbitmap.h
# End Source File
# Begin Source File

SOURCE=.\Utility.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
