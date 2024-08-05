@echo off
REM create obj and bin folders if non exiting, since
REM the development tools will not create them themselves
if not exist obj mkdir obj
if not exist bin mkdir bin

echo.
echo Compile the C code
echo --------------------------
compile src\Retrotime.c -o obj\Retrotime.asm || goto :failed
echo.
echo Assemble the ASM code
echo --------------------------
assemble obj\Retrotime.asm -o obj\Retrotime.vbin || goto :failed

echo.
echo Convert the PNG textures
echo --------------------------
png2vircon assets\graphics\fasterdave\fasterdave.png -o obj\fasterdave.vtex || goto :failed
png2vircon assets\graphics\blockstacker\blockstacker.png -o obj\blockstacker.vtex || goto :failed
png2vircon assets\graphics\breakout\breakout.png -o obj\breakout.vtex || goto :failed
png2vircon assets\graphics\frog\frog.png -o obj\frog.vtex || goto :failed
png2vircon assets\graphics\invaders\invaders.png -o obj\invaders.vtex || goto :failed
png2vircon assets\graphics\pang\pang.png -o obj\pang.vtex || goto :failed
png2vircon assets\graphics\main\main.png -o obj\main.vtex || goto :failed
png2vircon assets\graphics\gamepreview\gamepreview.png -o obj\gamepreview.vtex || goto :failed
png2vircon assets\graphics\ramit\ramit.png -o obj\ramit.vtex || goto :failed
png2vircon assets\graphics\snakey\snakey.png -o obj\snakey.vtex || goto :failed

REM fonts
png2vircon src\fonts\Roboto_Regular_14.png -o obj\Roboto_Reguluar_14.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_17.png -o obj\Roboto_Reguluar_17.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_19.png -o obj\Roboto_Reguluar_19.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_20.png -o obj\Roboto_Reguluar_20.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_22.png -o obj\Roboto_Reguluar_22.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_25.png -o obj\Roboto_Reguluar_25.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_30.png -o obj\Roboto_Reguluar_30.vtex || goto :failed
png2vircon src\fonts\Roboto_Regular_40.png -o obj\Roboto_Reguluar_40.vtex || goto :failed


echo.
echo Convert the WAV sounds
echo --------------------------
rem wav2vircon assets\music\title.wav -o obj\title.vsnd || goto :failed

echo.
echo Pack the ROM
echo --------------------------
packrom Retrotime.xml -o "bin\Retrotime.v32" || goto :failed
goto :succeeded

:failed
echo.
echo BUILD FAILED
exit /b %errorlevel%

:succeeded
echo.
echo BUILD SUCCESSFUL
exit /b

@echo on