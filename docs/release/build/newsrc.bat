set from=c:\HBMAME
set to=c:\HBMAME\docs\release

rd %to%\src /q /s

md %to%\src\emu
copy /Y %from%\src\version.cpp %to%\src\version.cpp
copy /Y %from%\src\emu\validity.cpp %to%\src\emu
copy /Y %from%\src\emu\digfx.h %to%\src\emu
copy /Y %from%\src\emu\emuopts.* %to%\src\emu
copy /Y %from%\src\emu\gamedrv.h %to%\src\emu
copy /Y %from%\src\emu\video.* %to%\src\emu
copy /Y %from%\src\version.cpp %to%\src

md %to%\src\frontend\mame
copy /Y %from%\src\frontend\mame\audit.* %to%\src\frontend\mame
copy /Y %from%\src\frontend\mame\info.cpp %to%\src\frontend\mame
copy /Y %from%\src\frontend\mame\mameopts.* %to%\src\frontend\mame

md %to%\src\devices\cpu\m68000
copy /Y %from%\src\devices\cpu\m68000\m68kcpu.cpp %to%\src\devices\cpu\m68000

md %to%\src\mame\drivers
copy /Y %from%\src\mame\drivers\jrpacman.cpp %to%\src\mame\drivers

md %to%\src\hbmame
xcopy /E /Y %from%\src\hbmame %to%\src\hbmame

md %to%\src\osd\winui
xcopy /E /Y %from%\src\osd\winui %to%\src\osd\winui

md %to%\src\osd\modules\render
copy /Y %from%\src\osd\modules\render\drawd3d.cpp %to%\src\osd\modules\render

rem now save all our stuff to github
copy %from%\*.bat %to%\build
xcopy /E /Y %from%\scripts %to%\scripts

rem convert all the unix documents to windows format for notepad
type %from%\docs\BSD3Clause.txt    | MORE /P > %to%\docs\BSD3Clause.txt
type %from%\docs\LICENSE           | MORE /P > %to%\docs\license.txt
type %from%\docs\winui_license.txt | MORE /P > %to%\docs\winui_license.txt

pause
echo off
cls
echo.
echo RAR up everything.
echo.

pause
